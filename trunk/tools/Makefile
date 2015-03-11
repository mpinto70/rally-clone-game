
default: subdirs

SUBDIRS_T =	\
			mapeditor \
			visualizer \

SUBDIRS =	\
			$(SUBDIRS_T) \
			util \

subdirs: $(SUBDIRS) \

$(SUBDIRS_T): util

include tools.mk

