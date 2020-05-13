EXE = sampleanalysis_v2.1

#OPTIONS = -fPIC -DLINUX

OPTIONS = -g -O2 -O -ansi -W -Wall -fPIC -D_GNU_SOURCE -DLINUX 

CFLAGS = $(shell root-config --cflags)
LDFLAGS = $(shell root-config --ldflags)

#LIBDIR = -L $(shell root-config --libdir)
LIBS = $(shell root-config --libs --glibs)

INCDIR = -I./include

VPATH = ./:src

SOURCES = $(shell cd src; ls *.cpp)

OBJS = $(SOURCES:%.cpp=%.o)


############################################################

all: $(EXE)


$(EXE): $(EXE).o $(OBJS)
	/bin/rm -f $(EXE)
	g++ $(OPTIONS) -o $(EXE) $(EXE).o $(OBJS) $(LIBS)
	#/bin/rm -f *.o

$(EXE).o: $(EXE).cpp
	g++ $(OPTIONS) $(CFLAGS) $(INCDIR) $(LDFLAGS) -c -o $@ $<

%.o: %.cpp
	g++ $(OPTIONS) $(CFLAGS) $(INCDIR) $(LDFLAGS) -c -o $@ $<
