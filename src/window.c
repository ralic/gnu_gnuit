/* window.c -- A *very* simple window management.  */

/* Copyright (C) 1993-1999, 2006-2009 Free Software Foundation, Inc.

 This file is part of gnuit.

 gnuit is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 gnuit is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public
 License along with this program. If not, see
 http://www.gnu.org/licenses/. */

/* Written by Tudor Hulubei and Andrei Pitis.  */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPE_H */
#include <stddef.h>
#ifdef HAVE_ASSERT_H
#include <assert.h>
#endif /* HAVE_ASSERT_H */
#include "window.h"
#include "xmalloc.h"
#include "tty.h"

window_t *
window_init(lines, cols, y, x)
    int lines, cols, y, x;
{
    window_t *window = (window_t *)xmalloc(sizeof(window_t));
    window_resize(window, lines, cols, x, y);
    return window;
}


void
window_end(window)
    window_t *window;
{
    if (window)
	xfree(window);
}


void
window_resize(window, x, y, lines, columns)
    window_t *window;
    int x, y, lines, columns;
{
    window->x       = x;
    window->y       = y;
    window->wlines   = lines;
    window->wcolumns = columns;
}


int
window_puts(window, str, length)
    window_t *window;
    wchar_t *str;
    int length;
{
    int x = window->cursor_x;

    window->cursor_x += length;

    if (x >= window->wcolumns)
	return 0;

    if (window->cursor_y >= window->wlines)
	return 0;

    if (x + length <= window->wcolumns)
	return tty_puts(str, length);

    /* Write the visible part of the string.  */
    return tty_puts(str, window->wcolumns - x);
}


int
window_putc(window, c)
    window_t *window;
    wchar_t c;
{
    if (++window->cursor_x > window->wcolumns)
	return 0;

    if (window->cursor_y >= window->wlines)
	return 0;

    return tty_putc(c);
}


void
window_goto(window, y, x)
    window_t *window;
    int y, x;
{
    window->cursor_x = x;
    window->cursor_y = y;
    tty_goto(y + window->y, x + window->x);
}


int
window_x(window)
    window_t *window;
{
    return window->x;
}


int
window_y(window)
    window_t *window;
{
    return window->y;
}


int
window_lines(window)
    window_t *window;
{
    return window->wlines;
}


int
window_columns(window)
    window_t *window;
{
    return window->wcolumns;
}
