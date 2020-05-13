EXE = energy_resol

OPTIONS = -fPIC -DLINUX

CFLAGS = -g -Wall $(shell root-config --cflags)
LDFLAGS = $(shell root-config --ldflags)

#LIBDIR = -L $(shell root-config --libdir)
LIBS = -lm $(shell root-config --libs --glibs)

#INCDIR = -I $(shell root-config --incdir)$
VPATH = ./:src

SOURCES = $(shell cd src; ls *.cpp)

OBJS = $(SOURCES:%.cpp=%.o)


############################################################

all: $(EXE)


$(EXE): $(EXE).o $(OBJS)
	/bin/rm -f $(EXE)
	g++ -Wall -o $(EXE) $(EXE).o $(OBJS) $(LIBS)

$(EXE).o: $(EXE).cpp
	g++ $(OPTIONS) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

%.o: %.cpp
	g++ $(OPTIONS) $(CFLAGS) $(LDFLAGS) -c -o $@ $<


