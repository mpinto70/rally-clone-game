
VPATH = .:$(TSTBIN)

CXXTEST_INC=$(CXXTEST_ROOT)
CXXTEST_BIN=$(CXXTEST_ROOT)/bin

HEADERS = $(subst .o,.h,$(OBJS))
MAIN = unit_test_main
MAIN_CPP = $(MAIN).cpp
MAIN_O = $(MAIN).o

ifneq ($(HEADERS),)
EXE = $(MAIN)
endif

OTHER_DISTCLEAN=$(MAIN_O) $(MAIN_CPP) $(EXE)
OTHER_OBJS=$(MAIN_O)
OTHERLIBDIR=$(MCKBIN)
OTHERINCLIBDIR=-L$(MCKBIN)

ifneq ($(EXE),)
ifdef  PROF
OTHER_EXE_PARMS=-pg
else
OTHER_EXE_PARMS=
endif
endif

include $(RALLY_ROOT)/project.mk

CFLAGS +=	-I$(CXXTEST_INC) \
			-DCXXTEST_HAVE_STD \
			-DCXXTEST_HAVE_EH \

$(MAIN_CPP): $(HEADERS) Makefile
	$(ECHO) "[SHELL ] $@ "
	$(SILENT)$(CXXTEST_BIN)/cxxtestgen --error-printer -o $@ $(HEADERS)

run: directory_message run_local $(SUBDIRS)

run_local:
ifneq ($(EXE),)
	$(SILENT)LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(LIBDIR):$(MCKBIN) ./$(EXE)
endif

valgrind: directory_message valgrind_local $(SUBDIRS)

valgrind_local:
ifneq ($(EXE),)
	$(SILENT)valgrind --leak-check=full --leak-resolution=high --suppressions=$(RALLY_ROOT)/tst/valgrind_suppressions --show-reachable=yes ./$(EXE)
endif

OTHER_DISTCLEAN=$(MAIN_CPP)

