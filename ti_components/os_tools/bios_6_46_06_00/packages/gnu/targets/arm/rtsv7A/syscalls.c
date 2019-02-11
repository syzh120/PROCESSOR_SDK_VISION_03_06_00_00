/* 
 *  Copyright (c) 2013 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
/*
 *  ======== syscalls.c ========
 *  Minimal implementation of newlib syscall stub functions.
 *
 */

/*
 *  ======== _exit ========
 */
void _exit(int code) 
{
    asm(" .global C$$EXIT");
    asm("C$$EXIT:");
    while(1){};
}
/*
 *  @(#) gnu.targets.arm.rtsv7A; 1, 0, 0,0; 10-21-2016 18:36:41; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

