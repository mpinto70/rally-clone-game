
VPATH = .:$(LIBDIR):$(APPDIR)

MOVE_TO_BINDIR=1

DESTLIBDIR=$(LIBDIR)

LIB_BASE_NAME = lib$(subst /,,$(subst $(RALLY_ROOT)/src,,$(shell pwd)))
LIBA=$(LIB_BASE_NAME).a
LIBSO=$(LIB_BASE_NAME).so

include $(RALLY_ROOT)/project.mk

libsotarget: directory_message $(LIBSO) $(SUBDIRS)

libatarget: directory_message $(LIBA) $(SUBDIRS)

libbothtarget: directory_message $(LIBA) $(LIBSO) $(SUBDIRS)

exetarget: directory_message $(EXE) $(SUBDIRS)

exectarget: directory_message $(EXEC) $(SUBDIRS)

local: $(LIBA) $(LIBSO) $(EXE)

ifneq ($(LIBA),)
OTHER_DISTCLEAN+= $(LIBDIR)/$(LIBA)
endif
ifneq ($(LIBSO),)
OTHER_DISTCLEAN+= $(LIBDIR)/$(LIBSO)
endif
ifneq ($(EXE),)
OTHER_DISTCLEAN+= $(APPDIR)/$(EXE)
endif

run_local: run

run:
	$(ECHO) -n ""

