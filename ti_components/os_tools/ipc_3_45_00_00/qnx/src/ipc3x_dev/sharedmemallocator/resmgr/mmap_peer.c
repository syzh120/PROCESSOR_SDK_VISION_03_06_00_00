/*
 * $QNXLicenseC$
*/
/*
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
* mmap_peer/munmap_peer implementation PR47400
*/

#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/mman.h>
#include <sys/memmsg.h>


int memmgr_peer_sendnc( pid_t pid, int coid, void *smsg, size_t sbytes, void *rmsg, size_t rbytes )
{
	mem_peer_t	peer;
	iov_t		siov[2];

	peer.i.type = _MEM_PEER;
	peer.i.peer_msg_len = sizeof(peer);
	peer.i.pid = pid;

	SETIOV(siov + 0, &peer, sizeof peer);
	SETIOV(siov + 1, smsg, sbytes);
	return MsgSendvsnc( coid, siov, 2, rmsg, rbytes );
}

void *
_mmap2_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off,
		unsigned align, unsigned pre_load, void **base, size_t *size) {
	mem_map_t						msg;

	msg.i.type = _MEM_MAP;
	msg.i.zero = 0;
	msg.i.addr = (uintptr_t)addr;
	msg.i.len = len;
	msg.i.prot = prot;
	msg.i.flags = flags;
	msg.i.fd = fd;
	msg.i.offset = off;
	msg.i.align = align;
	msg.i.preload = pre_load;
	msg.i.reserved1 = 0;
	if(memmgr_peer_sendnc(pid, MEMMGR_COID, &msg.i, sizeof msg.i, &msg.o, sizeof msg.o) == -1) {
		return MAP_FAILED;
	}
	if(base) {
		*base = (void *)(uintptr_t)msg.o.real_addr;
	}
	if(size) {
		*size = msg.o.real_size;
	}
	return (void *)(uintptr_t)msg.o.addr;
}


void *
mmap64_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off) {
	return _mmap2_peer(pid, addr, len, prot, flags, fd, off, 0, 0, 0, 0);
}


// Make an unsigned version of the 'off_t' type so that we get a zero
// extension down below.
#if __OFF_BITS__ == 32
	typedef _Uint32t uoff_t;
#elif __OFF_BITS__ == 64
	typedef _Uint64t uoff_t;
#else
	#error Do not know what size to make uoff_t
#endif

void *
mmap_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off_t off) {
	return _mmap2_peer(pid, addr, len, prot, flags, fd, (uoff_t)off, 0, 0, 0, 0);
}

int
munmap_flags_peer(pid_t pid, void *addr, size_t len, unsigned flags) {
	mem_ctrl_t						msg;

	msg.i.type = _MEM_CTRL;
	msg.i.subtype = _MEM_CTRL_UNMAP;
	msg.i.addr = (uintptr_t)addr;
	msg.i.len = len;
	msg.i.flags = flags;
	return memmgr_peer_sendnc(pid, MEMMGR_COID, &msg.i, sizeof msg.i, 0, 0);
}

int
munmap_peer(pid_t pid, void *addr, size_t len) {
	return munmap_flags_peer(pid, addr, len, 0);
}

int
mem_offset64_peer(pid_t pid, const uintptr_t addr, size_t len,
				off64_t *offset, size_t *contig_len) {
	struct _peer_mem_off {
		struct _mem_peer peer;
		struct _mem_offset msg;
	};
	typedef union {
		struct _peer_mem_off i;
		struct _mem_offset_reply o;
	} memoffset_peer_t;
	memoffset_peer_t msg;

	msg.i.peer.type = _MEM_PEER;
	msg.i.peer.peer_msg_len = sizeof(msg.i.peer);
	msg.i.peer.pid = pid;
	msg.i.peer.reserved1 = 0;

	msg.i.msg.type = _MEM_OFFSET;
	msg.i.msg.subtype = _MEM_OFFSET_PHYS;
	msg.i.msg.addr = addr;
	msg.i.msg.reserved = -1;
	msg.i.msg.len = len;
	if(MsgSendnc(MEMMGR_COID, &msg.i, sizeof msg.i, &msg.o, sizeof msg.o) == -1) {
		return -1;
	}
	*offset = msg.o.offset;
	*contig_len = msg.o.size;
	return(0);
}


#if defined(__X86__)
#define CPU_VADDR_SERVER_HINT 0x30000000u
#elif defined(__ARM__)
#define CPU_VADDR_SERVER_HINT 0x20000000u
#else
#error NO CPU SOUP FOR YOU!
#endif

/*
 * map the object into both client and server at the same virtual address
 */
void *
mmap64_join(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off) {
	void *svaddr, *cvaddr = MAP_FAILED;
	uintptr_t hint = (uintptr_t)addr;
	uintptr_t start_hint = hint;

	if ( hint == 0 ) hint = (uintptr_t)CPU_VADDR_SERVER_HINT;

	do {
		svaddr = mmap64( (void *)hint, len, prot, flags, fd, off );
		if ( svaddr == MAP_FAILED ) {
			break;
		}
		if ( svaddr == cvaddr ) {
			return svaddr;
		}

		cvaddr = mmap64_peer( pid, svaddr, len, prot, flags, fd, off );
		if ( cvaddr == MAP_FAILED ) {
			break;
		}
		if ( svaddr == cvaddr ) {
			return svaddr;
		}

		if ( munmap( svaddr, len ) == -1 ) {
			svaddr = MAP_FAILED;
			break;
		}

		svaddr = mmap64( cvaddr, len, prot, flags, fd, off );
		if ( svaddr == MAP_FAILED ) {
			break;
		}
		if ( svaddr == cvaddr ) {
			return svaddr;
		}

		if ( munmap( svaddr, len ) == -1 ) {
			svaddr = MAP_FAILED;
			break;
		}
		if ( munmap_peer( pid, cvaddr, len ) == -1 ) {
			cvaddr = MAP_FAILED;
			break;
		}

		hint += __PAGESIZE;

	} while(hint != start_hint); /* do we really want to wrap all the way */

	if ( svaddr != MAP_FAILED ) {
		munmap( svaddr, len );
	}
	if ( cvaddr != MAP_FAILED ) {
		munmap_peer( pid, cvaddr, len );
	}
	return MAP_FAILED;
}
