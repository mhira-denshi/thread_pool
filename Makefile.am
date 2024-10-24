ACLOCAL_AMFLAGS = -I m4

######### libthreadpool.so #########

lib_LTLIBRARIES        = libthreadpool.la

libthreadpool_la_SOURCES     = thread_pool.c
libthreadpool_la_SOURCES    += thread_queue.c

libthreadpool_la_CPPFLAGS   = -I$(top_srcdir)/inc
libthreadpool_la_CPPFLAGS  += -std=c++11 -Wall -Wno-unused-parameter
libthreadpool_la_CPPFLAGS  += $(AM_CPPFLAGS) -Wno-deprecated-

libthreadpool_la_LDFLAGS    = -lpthread

# Export header
libthreadpool_includedir       = $(includedir)
libthreadpool_include_HEADERS  = $(top_srcdir)/thread_pool.h

######### test-thread-pool #########

root_sbindir        = "/usr/sbin"
root_sbin_PROGRAMS  = test-thread-pool

test_thread_pool_SOURCES    = test-thread-pool.c

test_thread_pool_CPPFLAGS   = -I$(top_srcdir)/inc
test_thread_pool_CPPFLAGS  += -std=c++11 -Wall -Wno-unused-parameter

test_thread_pool_LDADD      = libthreadpool.la