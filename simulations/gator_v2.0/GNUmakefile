# --------------------------------------------------------------
# GNUmakefile for physics list user.  
# JPW. Fri Jul 25 10:39:58 CEST 2003
# --------------------------------------------------------------

name := gator_1.2
G4TARGET := $(name)
G4EXLIB := true

G4DEBUG := 0

ROOTCFLAGS      = $(shell root-config --cflags)
ROOTLIBS        = $(shell root-config --libs)
ROOTGLIBS       = $(shell root-config --glibs)

#INCDIR		=-I$(shell root-config --incdir)

EXTRALIBS +=$(ROOTLIBS)
EXTRALIBS +=$(ROOTGLIBS)
#EXTRALIBS +=-L/Applications/CLHEP


CPPFLAGS += $(ROOTCFLAGS)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk


