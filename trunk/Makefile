
default: subdirs

SUBDIRS = src tst mck tools

subdirs: $(SUBDIRS)

$(MAKECMDGOALS): $(SUBDIRS)

tst: src mck
tools: src

# define an environment variable RALLY_ROOT that points to this directory
include $(RALLY_ROOT)/project.mk

