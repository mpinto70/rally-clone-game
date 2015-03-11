
default: exetarget

EXE=map_editor.exe

GRAPHLIBS =	\
			-lalleg-4.2.3 \
			-lalleg_unsharable \

LIBS =	\
		-lutil \
		-lgamelib \
		-lgameliballegro \
		-ltoolsutil \
		$(GRAPHLIBS) \

SUBDIRS =

OBJS =	\
		map_editor.o \

EXE_PARAMS=stages/stage_type0 1 2 4

include $(RALLY_ROOT)/tools/tools.mk

