###################################################################
#
# Run 'make' to compile the program and 'make clean' to remove
# all compiled parts and 'clean' the directory.
#
# You might need to adjust the CFLAGS and LIBS based on
# the BAT installation on your system. Consult the gmake manual
# for details.
#
###################################################################

# Root variables
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := -lMinuit $(shell root-config --libs)

# This program needs RooFit and RooStats, otherwise it won't compile
ROOTLIBS     += -lRooFitCore -lRooFit -lRooStats -lFoam -lMathMore

# Programs
CXX          = g++
CXXFLAGS     = -g -O2 -Wall -fPIC -Wno-deprecated 
LD           = /usr/x86_64-suse-linux/bin/ld -m elf_x86_64
LDFLAGS      = -g -O2 

RM           = rm -f
MV           = mv
ECHO         = echo

# Assign or Add variables
CXXFLAGS    += $(ROOTCFLAGS) 

# ----------------------------------------------------------------------
# The following definitions depend on the setup of the system where
# the project is being compiled. If BAT is installed in the standard
# system search path or the installation directory is defined in the
# BATINSTALLDIR environmental variable then the lines below are correct
# and the compilation will work
CXXFLAGS    += -I. -I./include -I$(BATINSTALLDIR)/include
LIBS        += -L$(BATINSTALLDIR)/lib -lBATmodels -lBAT $(ROOTLIBS)

#LIBS        +=  -lcuba

#CXXFLAGS    += -I. -I./include -I$(BATINSTALLDIR)/BAT -I$(ROOTSYS)/roofit/roofitcore/inc -I$(ROOTSYS)/roofit/roofit/inc

#LIBS        += $(ROOTLIBS)  -L$(BATINSTALLDIR)/lib -lRooFit -lRooFitCore -lFoam -lRooStats -lBAT -lBATmodels

CXSRCS      = 
CXXSRCS      = $(patsubst %.cxx,%.cxx,$(CXSRCS))
CXXOBJS      = $(patsubst %.cxx,%.o,$(CXSRCS))
EXEOBJS      =
GARBAGE      = $(CXXOBJS) $(EXEOBJS) *.o *~ link.d runRooInterface

all : # runRooInterface

link.d : $(patsubst %.cxx,%.h,$(CXSRCS))
	$(CXX) -MM $(CXXFLAGS) $(CXXSRCS) > link.d;

-include link.d

%.o : %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	$(RM) $(GARBAGE)

runRooInterface : runRooInterface.cxx $(CXXOBJS)
	$(CXX) $(CXXFLAGS) -c $<
	$(CXX) $(LDFLAGS) $@.o $(CXXOBJS) $(LIBS) -o $@

print :
	echo compiler  : $(CXX)
	echo compiler  : $(CXSRCS)
	echo c++ srcs  : $(CXXSRCS)
	echo c++ objs  : $(CXXOBJS)
	echo c++ flags : $(CXXFLAGS)
	echo libs      : $(LIBS)

	echo rootlibs  : $(ROOTLIBS)
