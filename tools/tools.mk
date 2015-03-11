
VPATH = .:$(TLSLIB):$(TLSAPP)

MOVE_TO_BINDIR=1

DESTLIBDIR=$(TLSLIB)
DESTAPPDIR=$(TLSAPP)
OTHERINCLIBDIR = -L$(TLSLIB) \

LIB_BASE_NAME = lib$(subst /,,$(subst $(RALLY_ROOT),,$(shell pwd)))
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
OTHER_DISTCLEAN+= $(DESTLIBDIR)/$(LIBA)
endif
ifneq ($(LIBSO),)
OTHER_DISTCLEAN+= $(DESTLIBDIR)/$(LIBSO)
endif
ifneq ($(EXE),)
OTHER_DISTCLEAN+= $(DESTAPPDIR)/$(EXE)
endif

run_local: run

ifneq ($(EXE),)
run: run_app
else
run: run_noapp
endif

run_app:
	@$(TLSAPP)/$(EXE) $(EXE_PARAMS)

run_noapp:
	$(ECHO) -n ""
