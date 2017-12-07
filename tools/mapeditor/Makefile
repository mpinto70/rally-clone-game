
default: exetarget

EXE=map_editor.exe

GRAPHLIBS =	\
			-lalleg \

LIBS =	\
		-ltoolsutil \
		-lgameliballegro \
		-lgameliballegrobmp \
		-lgamelib \
		-lmap \
		-lutil \
		-lboost_filesystem \
		-lboost_system \
		$(GRAPHLIBS) \

SUBDIRS =

OBJS =	\
		map_editor.o \

EXE_PARAMS=stages/stage_type0 1 2 4

include $(RALLY_ROOT)/tools/tools.mk

