
.PHONY: bot player action

default: exetarget

EXE=visualizer.exe

GRAPHLIBS =	\
			-lalleg \

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

PLAYER_PARAMS=$(RALLY_ROOT)/Stuff/car_player_32.bmp car
BOT_PARAMS=$(RALLY_ROOT)/Stuff/car_bot_32.bmp car
ACTION_PARAMS=$(RALLY_ROOT)/Stuff/actions.bmp action
TILE_PARAMS=$(RALLY_ROOT)/Stuff/tileset.bmp tile

EXE_PARAMS=$(PLAYER_PARAMS)

bot: EXE_PARAMS=$(BOT_PARAMS)
	
player: EXE_PARAMS=$(PLAYER_PARAMS)

action: EXE_PARAMS=$(ACTION_PARAMS)

tile: EXE_PARAMS=$(TILE_PARAMS)

bot player action tile : $(EXE) run 

include $(RALLY_ROOT)/tools/tools.mk
