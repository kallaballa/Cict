ifdef JAVASCRIPT
CXX     := em++
endif
ifdef JAVASCRIPT
TARGET  := cict.js
else
TARGET  := cict 
endif
SRCS    := src/Cict.cpp src/NamedColorTable.cpp
OBJS    := ${SRCS:.cpp=.o} 
DEPS    := ${SRCS:.cpp=.dep} 

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CXXFLAGS = -std=c++0x -pedantic -Wall -I /usr/X11/include/
	LDFLAGS = -L/usr/X11/lib/
else
	CXXFLAGS = -std=c++0x -pedantic -Wall
	LDFLAGS = -L/usr/lib64/
endif

LIBS    = -lX11 -lpthread

.PHONY: all clean distclean 

all: release

debug: CXXFLAGS += -g3 -O0 -rdynamic
debug: LDFLAGS += -Wl,--export-dynamic
debug: LIBS+= -lbfd
debug: ${TARGET}

release: ${TARGET}

${TARGET}: ${OBJS} 
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.cpp %.dep 
	${CXX} ${CXXFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.cpp Makefile 
	${CXX} ${CXXFLAGS} -MM $< > $@ 

clean:
	rm -f src/*~ src/*.o src/*.dep ${TARGET} 

distclean: clean

