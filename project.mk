
.SUFFIXES:
.SUFFIXES: .cpp .c .o

.PHONY: $(SUBDIRS) dirtarget

ifeq ($(DEBUG_MAKE),)
SILENT=@
else
SILENT=
endif

# diretórios de destino de programas e bibliotecas
BINDIR = $(RALLY_ROOT)/bin
LIBDIR = $(RALLY_ROOT)/bin/lib
APPDIR = $(RALLY_ROOT)/bin/app
SRCDIR = $(RALLY_ROOT)/src
TSTDIR = $(RALLY_ROOT)/tst
TSTBIN = $(TSTDIR)/bin
MCKDIR = $(RALLY_ROOT)/mck
MCKBIN = $(MCKDIR)/bin
TLSDIR = $(RALLY_ROOT)/tools
TLSLIB = $(TLSDIR)/bin/lib
TLSAPP = $(TLSDIR)/bin/app

INCDIR =	\
			-I ./ \
			-I $(SRCDIR) \
			-I $(BOOST_ROOT) \

INCLIBDIR = -L$(LIBDIR) \

# miscellaneous OS-dependent stuff
SHELL = /bin/sh
# make
MAKE = make
# nome do seu compilador C
CC = gcc
# nome do compilador c++
CXX = g++
# nome link editor
LD = ld
# comando de criação de arquivo de biblioteca (.a)
AR = ar rc
# segundo passo na criação de uma biblioteca .a (use "touch" se não for necessário)
AR2 = ranlib
# strip de biblioteca
STRIP = strip
# deleção de arquivo
RM = rm -f
# move de arquivo
MV = mv
# echo
ECHO = @echo

CFLAGS += 	-DRELEASE \
			-DNDEBUG \
			-DRALLY_ROOT="\"$(RALLY_ROOT)\"" \
			-Wall \
			-Werror \
			-Wparentheses \
			-fpic \
			-Os \
			$(INCDIR) \
			
CPPFLAGS = 	$(CFLAGS) \
			-fno-enforce-eh-specs \
			-pedantic-errors \
			-Wno-long-long \
			-std=c++1y \

.cpp.o:
	$(ECHO) "[C++   ] $< "
	$(SILENT)$(CXX) -c $(CPPFLAGS) $(LCPPFLAGS) $< -o $@

.c.o:
	$(ECHO) "[C     ] $< "
	$(SILENT)$(CC) -c $(CFLAGS) $(LCFLAGS) $< -o $@

ifneq ($(LIBA),)
$(LIBA): $(OBJS)
	$(ECHO) "[AR    ] $@ "
	$(SILENT)$(RM) $@
	$(SILENT)$(AR) $@ $(OBJS)
	$(SILENT)$(AR2) $@
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(DESTLIBDIR)/$@
	$(SILENT)$(MV) $@ $(DESTLIBDIR)
endif
endif

ifneq ($(LIBSO),)
$(LIBSO): $(OBJS)
	$(ECHO) "[SO    ] $@ "
	$(SILENT)$(RM) $@
ifdef  PROF
	$(SILENT)$(CXX) -pg -shared -o $@ $(OBJS) $(ARFILES) $(LIBFLAGS)
else
	$(SILENT)$(CXX) -shared -o $@ $(OBJS) $(ARFILES) $(LIBFLAGS)
endif
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(DESTLIBDIR)/$@
	$(SILENT)$(MV) $@ $(DESTLIBDIR)
endif
endif

exetarget: directory_message $(EXE) $(SUBDIRS)

ifneq ($(EXE),)
$(EXE): $(OBJS) $(OTHER_OBJS) $(LIBDIR) $(MAIN_CPP) $(OTHERLIBDIR)
	$(ECHO) "[EXE   ] $@ "
	$(SILENT)$(RM) $@
	$(SILENT)$(CXX) $(EXEFLAGS) -o $@ $(OBJS) $(OTHER_OBJS) $(INCLIBDIR) $(OTHERINCLIBDIR) $(OTHER_EXE_PARMS) $(LIBS)
ifneq ($(MOVE_TO_BINDIR),)
	$(SILENT)$(RM) $(DESTAPPDIR)/$(EXE)
	$(SILENT)$(MV) $@ $(DESTAPPDIR)
endif
endif

# if there are .o files to be created, create depend.mk
depend: warning_env depend_local $(SUBDIRS)

depend_local:
ifneq ($(strip $(OBJS)),)
	$(ECHO) "[DEPEND] $(subst $(RALLY_ROOT),,$(shell pwd)) "
	$(SILENT)$(CXX) -MM $(CPPFLAGS) $(LCFLAGS) $(subst .o,.c*,$(OBJS)) > depend.mk

-include depend.mk
endif

format: directory_message format_local $(SUBDIRS)

format_local:
ifneq ($(strip $(shell ls *.h 2>/dev/null)),)
	$(SILENT)astyle *.h
endif
ifneq ($(strip $(shell ls *.cpp 2>/dev/null)),)
	$(SILENT)astyle *.cpp
endif
ifneq ($(strip $(shell ls *.c 2>/dev/null)),)
	$(SILENT)astyle *.c
endif

$(SUBDIRS):
	$(SILENT)$(MAKE) $(MAKECMDGOALS) --no-print-directory -C $@

warning_env:
	@if test "$(RALLY_ROOT)+set" = "+set" ;\
	then echo "==========================================================="     ;\
	echo "Error: the environment variable RALLY_ROOT is undefined"              ;\
	echo "       define it and then run the command make"                       ;\
	echo "       ex: export RALLY_ROOT=~/projects/rally-clone-game"             ;\
	echo "==========================================================="          ;\
	exit 1 ; fi ;
	@if test "$(BOOST_ROOT)+set" = "+set" ;\
	then echo "==========================================================="     ;\
	echo "Error: the environment variable BOOST_ROOT is undefined"              ;\
	echo "       define it and then run the command make"                       ;\
	echo "       ex: export BOOST_ROOT=/usr/local/boost"                        ;\
	echo "==========================================================="          ;\
	exit 1 ; fi ;
	@if test "$(CXXTEST_ROOT)+set" = "+set" ;\
	then echo "==========================================================="     ;\
	echo "Error: the environment variable CXXTEST_ROOT is undefined"            ;\
	echo "       define it and then run the command make"                       ;\
	echo "       ex: export CXXTEST_ROOT=~/projects/cxxtest"                    ;\
	echo "==========================================================="          ;\
	exit 1 ; fi ;

directory_message: warning_env
	$(ECHO) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ $(subst $(RALLY_ROOT),,$(shell pwd))"

clean: warning_env clean_local $(SUBDIRS)

clean_local:
	$(ECHO) "[CLEAN ] $(subst $(RALLY_ROOT),,$(shell pwd)) "
	$(SILENT)$(RM)  \
					*.o \
					core \
					$(EXE) \
					$(LIBA) \
					$(LIBSO) \
					$(OBJS) \
					$(OTHER_CLEAN) \

distclean: clean
	$(SILENT)$(RM)  \
					$(OTHER_DISTCLEAN) \

reset: distclean
	$(SILENT)$(RM)  \
					depend.mk \

