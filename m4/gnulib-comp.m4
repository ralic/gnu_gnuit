# Copyright (C) 2004-2006 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects using CVS, this file can be treated like other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([gl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  AC_REQUIRE([AC_PROG_RANLIB])
  AC_REQUIRE([AC_GNU_SOURCE])
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([gl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [false])
  gl_cond_libtool=false
  gl_libdeps=
  gl_ltlibdeps=
  gl_source_base='lib'
  gl_FUNC_ALLOCA
  gl_DIRNAME
  gl_ERROR
  gl_EXITFAIL
  # No macro. You should also use one of fnmatch-posix or fnmatch-gnu.
  gl_FUNC_FNMATCH_GNU
  gl_FSUSAGE
  gl_GETOPT
  gl_IDCACHE
  gl_MBCHAR
  gl_MBITER
  gl_FUNC_MEMCHR
  gl_FUNC_MEMMOVE
  gl_FUNC_PUTENV
  gl_FUNC_READLINK
  gl_FUNC_RENAME
  gl_SAFE_READ
  gl_SAFE_WRITE
  gt_TYPE_SSIZE_T
  AM_STDBOOL_H
  gl_STDINT_H
  gl_STRCASE
  gl_FUNC_STRNDUP
  gl_FUNC_STRNLEN
  gl_FUNC_STRSTR
  gl_HEADER_UNISTD
  gl_FUNC_WCWIDTH
  gl_XALLOC
  gl_XSTRNDUP
  LIBGNU_LIBDEPS="$gl_libdeps"
  AC_SUBST([LIBGNU_LIBDEPS])
  LIBGNU_LTLIBDEPS="$gl_ltlibdeps"
  AC_SUBST([LIBGNU_LTLIBDEPS])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([gl_FILE_LIST], [
  lib/alloca.c
  lib/alloca_.h
  lib/basename.c
  lib/dirname.c
  lib/dirname.h
  lib/error.c
  lib/error.h
  lib/exit.h
  lib/exitfail.c
  lib/exitfail.h
  lib/fnmatch.c
  lib/fnmatch_.h
  lib/fnmatch_loop.c
  lib/fsusage.c
  lib/fsusage.h
  lib/full-read.c
  lib/full-read.h
  lib/full-write.c
  lib/full-write.h
  lib/getopt.c
  lib/getopt1.c
  lib/getopt_.h
  lib/getopt_int.h
  lib/gettext.h
  lib/idcache.c
  lib/mbchar.c
  lib/mbchar.h
  lib/mbuiter.h
  lib/memchr.c
  lib/memmove.c
  lib/putenv.c
  lib/readlink.c
  lib/rename.c
  lib/safe-read.c
  lib/safe-read.h
  lib/safe-write.c
  lib/safe-write.h
  lib/stdbool_.h
  lib/stdint_.h
  lib/strcase.h
  lib/strcasecmp.c
  lib/stripslash.c
  lib/strncasecmp.c
  lib/strndup.c
  lib/strndup.h
  lib/strnlen.c
  lib/strnlen.h
  lib/strnlen1.c
  lib/strnlen1.h
  lib/strstr.c
  lib/strstr.h
  lib/wcwidth.h
  lib/xalloc-die.c
  lib/xalloc.h
  lib/xmalloc.c
  lib/xstrndup.c
  lib/xstrndup.h
  m4/absolute-header.m4
  m4/alloca.m4
  m4/dirname.m4
  m4/dos.m4
  m4/double-slash-root.m4
  m4/error.m4
  m4/exitfail.m4
  m4/fnmatch.m4
  m4/fsusage.m4
  m4/getopt.m4
  m4/idcache.m4
  m4/longlong.m4
  m4/mbchar.m4
  m4/mbiter.m4
  m4/mbrtowc.m4
  m4/mbstate_t.m4
  m4/memchr.m4
  m4/memmove.m4
  m4/onceonly_2_57.m4
  m4/putenv.m4
  m4/readlink.m4
  m4/rename.m4
  m4/safe-read.m4
  m4/safe-write.m4
  m4/ssize_t.m4
  m4/stdbool.m4
  m4/stdint.m4
  m4/strcase.m4
  m4/strndup.m4
  m4/strnlen.m4
  m4/strstr.m4
  m4/unistd_h.m4
  m4/wchar_t.m4
  m4/wcwidth.m4
  m4/xalloc.m4
  m4/xstrndup.m4
])
