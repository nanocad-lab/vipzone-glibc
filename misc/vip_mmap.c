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
#include <stdio.h>
*/

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
  //__ptr_t c;
  size_t i;

  printf("vip_mmap @ %lu, for %lu ammount, with flags %lu\n", 
	 (unsigned long)addr, (unsigned long)len, (unsigned long)flags);
  
  unsigned long *ptr = (unsigned long * )(syscall(vip_mmap_NR, addr, len, prot, flags, fd, offset)); //hangs here
 
  if (ptr == NULL) {
	  __set_errno(ENOMEM);
	  return MAP_FAILED;
  }

  for(i = 0; i < len/4; i++)
  {
     *(ptr+i) = i;
      if(i % 16==0)
			printf("c(%lu)= %lu\n", i, *(ptr+i));
  }
  
  return (void *) ptr;
#endif

/*__set_errno (ENOSYS);
  return MAP_FAILED;
  */

/*
  printf("vip_mmap @ %lu, for %lu ammount, with flags %lu\n", 
	 (unsigned long)addr, (unsigned long)len, (unsigned long)v_flags);
  unsigned long c = syscall(vip_mmap_NR, addr, len, prot, flags, fd, offset, v_flags);
  printf("System call returned %lu == %lu?\n", c, 
	   (unsigned long)(addr+len));
  //_set_errno (ENOSYS);
  return MAP_FAILED;
*/
}

//vipzone
stub_warning (vip_mmap)
#include <stub-tag.h>
weak_alias (__vip_mmap, vip_mmap) //vipzone
