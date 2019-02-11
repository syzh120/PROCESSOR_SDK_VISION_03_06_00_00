/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== listlib.h ========
 *
 * 	Contains structures and exported function that are used by the linked
 * 	list library.
 *
 */

#ifndef __LISTLIB_H__
#define __LISTLIB_H__

/**************************************************************************
 * STRUCTURE -  LIST_NODE
 **************************************************************************
 *	The structure defines a LIST NODE structure that contains links to the 
 *	previous and next element in the list.
 **************************************************************************/
typedef struct LIST_NODE
{
	void*	p_next;		/* Pointer to the next element in the list. 	*/	
    void*   p_prev;     /* Pointer to the prev element in the list. */
}LIST_NODE;

/************************ EXTERN Functions *********************************/

_extern void list_add (LIST_NODE **ptr_list, LIST_NODE *ptr_node);
_extern LIST_NODE* list_remove (LIST_NODE **ptr_list);
_extern LIST_NODE* list_get_head (LIST_NODE **ptr_list);
_extern LIST_NODE* list_get_next (LIST_NODE *ptr_list);
_extern int list_remove_node (LIST_NODE **ptr_list, LIST_NODE *ptr_remove);
_extern void list_cat (LIST_NODE **ptr_dst, LIST_NODE **ptr_src);
_extern LIST_NODE* list_replicate (LIST_NODE* ptr_srcList, int size, void* alloc(UINT32 size), void free (void *ptr));
_extern void list_clean (LIST_NODE* ptr_list, void free (void *ptr));

#endif	/* __LISTLIB_H__ */



