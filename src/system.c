/* system.c -- The code needed in order to start child processes.  */

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
#include <wchar.h>
#include <stdlib.h>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPE_H */
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Not all systems declare ERRNO in errno.h... and some systems #define it! */
#if !defined (errno)
extern int errno;
#endif /* !errno */

#include "xmalloc.h"
#include "xstring.h"
#include "xio.h"
#include "tty.h"
#include "signals.h"
#include "inputline.h"
#include "system.h"
#include "misc.h"


extern char **environ;
extern char *screen;

extern wchar_t il_read_char PROTO ((wchar_t *, wchar_t *, int));

char *stdout_log_template = NULL;
char *stderr_log_template = NULL;
char *stdout_log_name = NULL;
char *stderr_log_name = NULL;

/*
 * A modified (and incompatible) version of system().
 */

static int
my_system(command, hide)
    const char *command;
    int hide;
{
    pid_t pid;
    int status;
    FILE *stdout_log=NULL;
    FILE *stderr_log=NULL;
    int stdout_log_fd, stderr_log_fd;
    int old_stdout=-1, old_stderr=-1;

    /* Preserve the system() semantics.  UNIX always has a command
       processor.  */
    if (command == NULL)
	return 1;

    remove_log();

    if(hide)
    {
	/* We have to call mkstemp here, so the parent knows
	   the values of std{out,err}_log_name, then clean up
	   in the parent code below */

	old_stdout = dup(1);
	old_stderr = dup(2);

	close(1);
	close(2);

	strcpy(stdout_log_name,stdout_log_template);
	stdout_log_fd = mkstemp(stdout_log_name);
	if(stdout_log_fd != -1)
	    stdout_log = fdopen(stdout_log_fd, "w");

	strcpy(stderr_log_name,stderr_log_template);
	stderr_log_fd = mkstemp(stderr_log_name);
	if(stderr_log_fd != -1)
	    stderr_log = fdopen(stderr_log_fd, "w");

	if(!stdout_log || !stderr_log)
	{
	    if(stdout_log)
		fclose(stdout_log);
	    if(stderr_log)
		fclose(stderr_log);

	    remove_log();

	    dup(old_stdout);
	    dup(old_stderr);

	    close(old_stdout);
	    close(old_stderr);
	    return -1;
	}
    }

    /* POSIX.2 says that we should ignore SIGINT & SIGQUIT.  It
       actually makes sense :-), but we won't bother to do it, as we
       ignore them anyway.  */

    pid = fork();

    if (pid < 0)
	status = -1;
    else if (pid == 0)
    {
	/* This is the child code.  */
	char buf[32];

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	/* Update the LINES & COLUMNS environment variables to reflect the
	   change in the window size.  This is important in order to avoid
	   passing children incorrect environment values.
	   Thanks to xax@roedu.net for the suggestion.
	   Moved here from tty_resize as LINES and COLUMNS override curses
	*/
	sprintf(buf, "%d", tty_lines);
	xsetenv("LINES", buf);
	sprintf(buf, "%d", tty_columns);
	xsetenv("COLUMNS", buf);

	if (hide)
	{
	    /* The reason we want stdin closed is that some programs
	       (like gunzip) try to ask the user what to do in certain
	       situations.  If stdin is closed, they default to a
	       reasonable action.  */

	    /* OLD-FIX-ME: rpm has an obscure bug that prevents it from
	       working if standard input is closed.  Until that is
	       fixed, we need this kludge here (i.e. don't close 0
	       for `rpm').  */
	    if (strncmp(command, "rpm ", 4) != 0)
		close(0);
	}

	execle("/bin/sh", "sh", "-c", command, (char *)NULL, environ);

	/* Make sure we exit if exec() fails.  Call _exit() instead of
	   exit() to avoid flushing file descriptors twice (in the
	   parent and in the child).  */
	_exit(127);
    }
    else
    {
	/* This is the parent code.  */
	if(hide)
	{
	    if(stdout_log)
		fclose(stdout_log);
	    if(stderr_log)
		fclose(stderr_log);
	    dup(old_stdout);
	    dup(old_stderr);

	    close(old_stdout);
	    close(old_stderr);
	}
	while (wait(&status) != pid);
    }

    /* Don't extract exit code, return full status so caller can see
       if child died */

    return status;
}


extern void resize PROTO ((int));


int
start(command, hide)
    char *command;
    int hide;
{
    int child_exit_code;

    if (hide)
    {
	signals(ON);
	child_exit_code = my_system(command, hide);
	signals(OFF);
    }
    else
    {
	tty_defaults();
	tty_put_screen(screen);

	signal_handlers(OFF);
	tty_end_cursorapp();
	child_exit_code = my_system(command, hide);
	signal_handlers(ON);

	xwrite(1, "\n\n", 2);
    }

    return child_exit_code;
}


void
remove_log()
{
    if (stdout_log_name && *stdout_log_name)
	unlink(stdout_log_name);

    if (stderr_log_name && *stderr_log_name)
	unlink(stderr_log_name);
}

void
display_errors(command)
    char *command;
{
    FILE *stderr_log = fopen(stderr_log_name, "r");

    if (stderr_log == NULL)
    {
	size_t buf_len = strlen(command) + 32 + strlen(stderr_log_name);
	wchar_t *buf = xmalloc(buf_len * sizeof(wchar_t));

	swprintf(buf, buf_len, L"%s: cannot open log file %s", command, stderr_log_name);

	il_read_char(buf, NULL, IL_MOVE | IL_BEEP | IL_SAVE | IL_ERROR);
	xfree(buf);
    }
    else
    {
	char *buf = xmalloc(2048 + 1);
	wchar_t *wbuf;

	while (fgets(buf, 2048 + 1, stderr_log))
	{
	    int len = strlen(buf);

	    if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	    wbuf=mbsduptowcs(buf);
	    if (il_read_char(wbuf, NULL, IL_MOVE | IL_ERROR) == 0)
	    {
		xfree(wbuf);
		break;
	    }
	    xfree(wbuf);
	}

	xfree(buf);
	fclose(stderr_log);
    }
}
