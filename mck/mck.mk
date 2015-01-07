
VPATH = .:$(LIBDIR):$(APPDIR):$(MCKBIN)

CXXTEST_INC=$(CXXTEST_ROOT)

MOVE_TO_BINDIR=1

DESTLIBDIR=$(MCKBIN)

LIB_BASE_NAME = lib$(subst /,,$(subst $(RALLY_ROOT),,$(shell pwd)))
LIBA=$(LIB_BASE_NAME).a
LIBSO=$(LIB_BASE_NAME).so

include $(RALLY_ROOT)/project.mk

CFLAGS +=	-I$(CXXTEST_INC) \
			-DRALLY_ROOT="\"$(RALLY_ROOT)\"" \
			-DCXXTEST_HAVE_STD \
			-DCXXTEST_HAVE_EH \

libsotarget: directory_message $(LIBSO) $(SUBDIRS)

libatarget: directory_message $(LIBA) $(SUBDIRS)

libbothtarget: directory_message $(LIBA) $(LIBSO) $(SUBDIRS)

local: $(LIBA) $(LIBSO)

ifneq ($(LIBA),)
OTHER_DISTCLEAN+= $(MCKBIN)/$(LIBA)
endif
ifneq ($(LIBSO),)
OTHER_DISTCLEAN+= $(MCKBIN)/$(LIBSO)
endif

run_local: run

run:
	$(ECHO) -n ""

