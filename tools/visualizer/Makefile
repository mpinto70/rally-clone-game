
.PHONY: bot player action

default: exetarget

EXE=visualizer.exe

GRAPHLIBS =	\
			-lalleg-4.2.3 \
			-lalleg_unsharable \

LIBS =	\
		-ltoolsutil \
		-lgameliballegrobmp \
		-lgameliballegro \
		-lgamelib \
		-lmap \
		-lutil \
		$(GRAPHLIBS) \

SUBDIRS =

OBJS =	\
		visualizer.o \

PLAYER_PARAMS=$(RALLY_ROOT)/Stuff/car_player_32.bmp 32 car
BOT_PARAMS=$(RALLY_ROOT)/Stuff/car_bot_32.bmp 32 car
ACTION_PARAMS=$(RALLY_ROOT)/Stuff/actions.bmp 32 action

EXE_PARAMS=$(PLAYER_PARAMS)

bot: EXE_PARAMS=$(BOT_PARAMS)
	
player: EXE_PARAMS=$(PLAYER_PARAMS)

action: EXE_PARAMS=$(ACTION_PARAMS)

bot player action : $(EXE) run 

include $(RALLY_ROOT)/tools/tools.mk
