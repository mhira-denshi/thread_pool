AC_INIT([thread_pool], [1.0], [youremail@example.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT
# Check for C compiler
AC_PROG_CC

# Check for pthread library
AC_CHECK_LIB([pthread], [pthread_create])

# Define source files
AC_CONFIG_SRCDIR([test-thread-pool.c])

# Generate the Makefile
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
