AM_CPPFLAGS = -I../.. -I$(srcdir)/../.. 
AM_CXXFLAGS += -Wno-overloaded-virtual -Wno-unused-command-line-argument
LDADD = ../../tsk/libtsk.la
LDFLAGS += -static
EXTRA_DIST = .indent.pro

bin_PROGRAMS = tsk_recover tsk_loaddb tsk_comparedir tsk_gettimes delete
tsk_recover_SOURCES = tsk_recover.cpp 
tsk_loaddb_SOURCES = tsk_loaddb.cpp 
tsk_gettimes_SOURCES = tsk_gettimes.cpp 
tsk_comparedir_SOURCES = tsk_comparedir.cpp tsk_comparedir.h
delete_SOURCES = delete.c

indent:
	indent *.cpp

clean-local:
	-rm -f *.cpp~
