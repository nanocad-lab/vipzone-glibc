/* Copyright (C) 1994, 1995, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */


#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

#define vip_mmap_NR 312
/*

#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>*/


/* Map addresses starting near ADDR and extending for LEN bytes.  From
   OFFSET into the file FD describes according to PROT and FLAGS.  If ADDR
   is nonzero, it is the desired mapping address.  If the MAP_FIXED bit is
   set in FLAGS, the mapping will be at ADDR exactly (which must be
   page-aligned); otherwise the system chooses a convenient nearby address.
   The return value is the actual mapping address chosen or MAP_FAILED
   for errors (in which case `errno' is set).  A successful `mmap' call
   deallocates any previous mapping for the affected region.  */

//vipzone
__ptr_t
__vip_mmap (__ptr_t addr, size_t len, int prot, int flags,
	    int fd, off_t offset)
{
  return (unsigned long *)(syscall(vip_mmap_NR, addr, len, prot, flags, fd, offset)); //vip_flags are embedded in flags
}

//vipzone
stub_warning (vip_mmap)
#include <stub-tag.h>
weak_alias (__vip_mmap, vip_mmap) //vipzone

#if 0
#include <sysdep.h>

#include <kernel-features.h>

#define EINVAL	22

	.text

/* vipzone */
ENTRY (__vip_mmap)

	/* Save registers.  */
	pushl %ebp
	cfi_adjust_cfa_offset (4)
	pushl %ebx
	cfi_adjust_cfa_offset (4)
	pushl %esi
	cfi_adjust_cfa_offset (4)
	pushl %edi
	cfi_adjust_cfa_offset (4)

	movl 20(%esp), %ebx
	cfi_rel_offset (ebx, 8)
	movl 24(%esp), %ecx
	movl 28(%esp), %edx
	movl 32(%esp), %esi
	cfi_rel_offset (esi, 4)
	movl 36(%esp), %edi
	cfi_rel_offset (edi, 0)
	movl 40(%esp), %ebp
	cfi_rel_offset (ebp, 12)
	testl $0xfff, %ebp
	movl $-EINVAL, %eax
	jne L(skip)
	shrl $12, %ebp			/* vip_mmap takes the offset in pages.  */

	movl $SYS_ify(vip_mmap), %eax	/* System call number in %eax.  */

	/* Do the system call trap.  */
	ENTER_KERNEL

L(skip):
	/* Restore registers.  */
	popl %edi
	cfi_adjust_cfa_offset (-4)
	cfi_restore (edi)
	popl %esi
	cfi_adjust_cfa_offset (-4)
	cfi_restore (esi)
	popl %ebx
	cfi_adjust_cfa_offset (-4)
	cfi_restore (ebx)
	popl %ebp
	cfi_adjust_cfa_offset (-4)
	cfi_restore (ebp)


	/* If 0 > %eax > -4096 there was an error.  */
	cmpl $-4096, %eax
	ja SYSCALL_ERROR_LABEL

	/* Successful; return the syscall's value.  */
L(pseudo_end):
	ret

/* vipzone */
PSEUDO_END (__vip_mmap)

/* vipzone */
weak_alias (__vip_mmap, vip_mmap)

#endif
