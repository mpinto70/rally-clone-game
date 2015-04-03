
default: exetarget

EXE=visualizer.exe

GRAPHLIBS =	\
			-lalleg-4.2.3 \
			-lalleg_unsharable \

LIBS =	\
		-ltoolsutil \
		-lgameliballegro \
		-lgamelib \
		-lmap \
		-lutil \
		$(GRAPHLIBS) \

SUBDIRS =

OBJS =	\
		visualizer.o \

EXE_PARAMS=$(RALLY_ROOT)/Stuff/car_player_32.bmp 32

include $(RALLY_ROOT)/tools/tools.mk

