
default: exetarget

EXE=visualizer.exe

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
		visualizer.o \

EXE_PARAMS=$(RALLY_ROOT)/Stuff/car_player.bmp 16

include $(RALLY_ROOT)/tools/tools.mk

