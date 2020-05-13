EXE = filechoice

OPTIONS = -fPIC -DLINUX

CFLAGS = -g -Wall $(shell root-config --cflags)
LDFLAGS = $(shell root-config --ldflags)

#LIBDIR = -L $(shell root-config --libdir)
LIBS = -lm $(shell root-config --libs --glibs)

#INCDIR = -I $(shell root-config --incdir)$


OBJS = $(EXE).o


############################################################

all: $(EXE)

$(EXE): $(OBJS)
	/bin/rm -f $(EXE)
	g++ -Wall -o $(EXE) $(OBJS) $(LIBS) 

$(OBJS): $(EXE).cpp
	g++ $(OPTIONS) $(CFLAGS) $(LDFLAGS) -c -o $@ $<
