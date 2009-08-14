/* window.c -- A *very* simple window management.  */

/* Copyright (C) 1993-1999, 2006-2007 Free Software Foundation, Inc.

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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#else /* !HAVE_STDLIB_H */
#include "ansi_stdlib.h"
#endif /* !HAVE_STDLIB_H */

#include <sys/types.h>

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#include <assert.h>
#include "window.h"
#include "xmalloc.h"
#include "tty.h"

extern WINDOW *top_window;

window_t *
window_init(lines, cols, y, x)
    int lines, cols, y, x;
{
    window_t *window = (window_t *)xmalloc(sizeof(window_t));
    window->window=subwin(top_window, lines, cols, y, x);
    return window;
}


void
window_end(window)
    window_t *window;
{
    if (window)
    {
	delwin(window->window);
	xfree(window);
    }
}


void
window_resize(window, x, y, lines, columns)
    window_t *window;
    int x, y, lines, columns;
{
/*    wresize(window->window, lines, columns);*/
    window->x       = x;
    window->y       = y;
    window->lines   = lines;
    window->columns = columns;
}


int
window_puts(window, str, length)
    window_t *window;
    wchar_t *str;
    int length;
{
    int x = window->cursor_x;

    window->cursor_x += length;

    if (x >= window->columns)
	return 0;

    if (window->cursor_y >= window->lines)
	return 0;

    if (x + length <= window->columns)
	return tty_puts(window->window, str, length);

    /* Write the visible part of the string.  */
    return tty_puts(window->window, str, window->columns - x);
}


int
window_putc(window, c)
    window_t *window;
    wchar_t c;
{
    if (++window->cursor_x > window->columns)
	return 0;

    if (window->cursor_y >= window->lines)
	return 0;

    return tty_putc(window->window, c);
}


void
window_goto(window, y, x)
    window_t *window;
    int y, x;
{
    window->cursor_x = x;
    window->cursor_y = y;
    tty_goto(window->window, y + window->y, x + window->x);
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
    return window->lines;
}


int
window_columns(window)
    window_t *window;
{
    return window->columns;
}
