
default: subdirs

SUBDIRS = src tst mck tools

subdirs: environment $(SUBDIRS)

$(MAKECMDGOALS): $(SUBDIRS)

tst: src mck
tools: src

# define an environment variable RALLY_ROOT that points to this directory
include project.mk

