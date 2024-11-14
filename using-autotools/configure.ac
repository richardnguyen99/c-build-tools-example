#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Initialize autoconf
AC_INIT([using-autotools], [0.0.1])
AC_PREREQ([2.69])

# Configure the build process
# AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CC
AC_PROG_INSTALL

# Check for automake
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall])
AM_PROG_AR
AM_PROG_CC_C_O

LT_INIT

# Check if `--enable-debug` flag is passed to configure script
AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug], [Enable debugging]),
    [debug=$enableval],
    [debug=no]
)

CFLAGS="-Wall -Werror"
if test "x$debug" = "xyes"; then
    CFLAGS="$CFLAGS -DDEBUG -g -O0"
else 
    CFLAGS="$CFLAGS -Wextra -O3"
fi

# Check for libraries or dependencies (if needed)
# Example: AC_CHECK_LIB([library_name], [function_name], [action-if-found], [action-if-not-found])

# Check for header files (if needed)
# Example: AC_CHECK_HEADERS([header_file], [action-if-found], [action-if-not-found])
AC_CHECK_HEADERS([fcntl.h],         [], [AC_MSG_ERROR([fcntl.h not found])])
AC_CHECK_HEADERS([unistd.h],        [], [AC_MSG_ERROR([unistd.h not found])])
AC_CHECK_HEADERS([sys/socket.h],    [], [AC_MSG_ERROR([sys/socket.h not found])])
AC_CHECK_HEADERS([netinet/in.h],    [], [AC_MSG_ERROR([netinet/in.h not found])])
AC_CHECK_HEADERS([arpa/inet.h],     [], [AC_MSG_ERROR([arpa/inet.h not found])])
AC_CHECK_HEADERS([sys/types.h],     [], [AC_MSG_ERROR([sys/types.h not found])])
AC_CHECK_HEADERS([sys/stat.h],      [], [AC_MSG_ERROR([sys/stat.h not found])])
AC_CHECK_HEADERS([stdlib.h],        [], [AC_MSG_ERROR([stdlib.h not found])])
AC_CHECK_HEADERS([stdio.h],         [], [AC_MSG_ERROR([stdio.h not found])])
AC_CHECK_HEADERS([string.h],        [], [AC_MSG_ERROR([string.h not found])])
AC_CHECK_HEADERS([errno.h],         [], [AC_MSG_ERROR([errno.h not found])])
AC_CHECK_HEADERS([signal.h],        [], [AC_MSG_ERROR([signal.h not found])])
AC_CHECK_HEADERS([sys/time.h],      [], [AC_MSG_ERROR([sys/time.h not found])])
AC_CHECK_HEADERS([time.h],          [], [AC_MSG_ERROR([time.h not found])])

# Check for functions (if needed)
# Example: AC_CHECK_FUNCS([function_name], [action-if-found], [action-if-not-found])
AC_CHECK_FUNCS([fcntl],             [], [AC_MSG_ERROR([fcntl not found])])
AC_CHECK_FUNCS([socket],            [], [AC_MSG_ERROR([socket not found])])
AC_CHECK_FUNCS([bind],              [], [AC_MSG_ERROR([bind not found])])
AC_CHECK_FUNCS([listen],            [], [AC_MSG_ERROR([listen not found])])
AC_CHECK_FUNCS([accept],            [], [AC_MSG_ERROR([accept not found])])
AC_CHECK_FUNCS([close],             [], [AC_MSG_ERROR([close not found])])
AC_CHECK_FUNCS([read],              [], [AC_MSG_ERROR([read not found])])
AC_CHECK_FUNCS([write],             [], [AC_MSG_ERROR([write not found])])
AC_CHECK_FUNCS([recv],              [], [AC_MSG_ERROR([recv not found])])

# Check for declarations (if needed)
# Example: AC_CHECK_DECLS([type_name], [action-if-found], [action-if-not-found])

# Tolerant macro declarations
AC_CHECK_DECLS([NULL],      [RX_HAVE_NULLPTR=1],    [])

# Check for type definitions
# Example: AC_CHECK_TYPES([type_name], [action-if-found], [action-if-not-found])
AC_CHECK_TYPES([pthread_t], [RX_HAVE_PTHREAD_T=1],  [AC_MSG_ERROR([pthread_t type not found])])
AC_CHECK_TYPES([int8_t],    [RX_HAVE_INT8_T=1],     [])
AC_CHECK_TYPES([ssize_t],   [RX_HAVE_SSIZE_T=1],    [])
AC_CHECK_TYPES([size_t],    [RX_HAVE_SIZE_T=1],     [])
AC_CHECK_TYPES([u_char],    [RX_HAVE_U_CHAR=1],     [])

# Generate a configuration header file that contains the above checks
AC_CONFIG_HEADERS([include/config.h])

# Generate Makefiles for subdirectories
AC_CONFIG_FILES([
    Makefile 
    src/Makefile
])

AC_OUTPUT
