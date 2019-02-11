/*
 * Userspace interface to hardware spinlocks
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UAPI_HWSPINLOCK_USER_H
#define _UAPI_HWSPINLOCK_USER_H

#include <linux/ioctl.h>

/**
 * struct hwspinlock_user_lock - Sent to lock a specific hwspinlock
 * @id:		hardware spinlock id
 * @timeout:	timeout value in msecs
 */
struct hwspinlock_user_lock {
	int id;
	unsigned int timeout;
};

/**
 * struct hwspinlock_user_unlock - Sent to unlock a specific hwspinlock
 * @id:		hardware spinlock id
 */
struct hwspinlock_user_unlock {
	int id;
};

#define HWSPINLOCK_IOC_MAGIC		'h'

#define HWSPINLOCK_USER_LOCK		_IOW(HWSPINLOCK_IOC_MAGIC, 0,	\
					     struct hwspinlock_user_lock)
#define HWSPINLOCK_USER_UNLOCK		_IOW(HWSPINLOCK_IOC_MAGIC, 1,	\
					     struct hwspinlock_user_unlock)

#endif  /* _UAPI_HWSPINLOCK_USER_H */
