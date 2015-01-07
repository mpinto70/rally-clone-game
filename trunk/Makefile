
default: subdirs

SUBDIRS = src tst mck

subdirs: $(SUBDIRS)

$(MAKECMDGOALS): $(SUBDIRS)

tst: src mck

# define an environment variable RALLY_ROOT that points to this directory
include $(RALLY_ROOT)/project.mk

