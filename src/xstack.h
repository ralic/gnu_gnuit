/* xstack.h -- Prototypes and #defines for the stuff in xstack.c.  */

/* Copyright (C) 1993-1999 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* Written by Tudor Hulubei and Andrei Pitis.  */
/* $Id: xstack.h,v 1.1.1.1 2004-11-10 17:44:38 ianb Exp $ */

#ifndef _GIT_XSTACK_H
#define _GIT_XSTACK_H


#include "stdc.h"


typedef struct
{
    void *data;         /* the stack data.  */
    int esize;          /* # of bytes in a stack element.  */
    int point;          /* # of elements in the stack.  */
} xstack_t;


extern xstack_t *xstack_init PROTO ((int));
extern void xstack_end PROTO ((xstack_t *));

extern void  xstack_push PROTO ((xstack_t *, void *));
extern void *xstack_pop PROTO ((xstack_t *, void *));
extern void *xstack_preview PROTO ((xstack_t *, void *, int));
extern void  xstack_truncate PROTO ((xstack_t *, int));
extern int xstack_point PROTO ((xstack_t *));


#endif  /* _GIT_XSTACK_H */