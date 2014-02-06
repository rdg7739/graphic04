#!smake
#
#

MACHINE= $(shell uname -s)

ifeq ($(MACHINE),Darwin)
	OPENGL_INC= -FOpenGL
	OPENGL_LIB= -framework OpenGL -framework GLUT -framework Cocoa -lm
else
	OPENGL_INC= -I/usr/include
	OPENGL_LIB= -L/usr/lib64 
	LLDLIBS = $(GLUT) -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm
endif

CXX=g++
COMPILER_FLAGS= -g

INCLUDE= $(OPENGL_INC)
LIBS= $(OPENGL_LIB) $(LLDLIBS)

TARGETS =  pj5 

SRCS = pj5.cpp 

default : $(TARGETS)

OBJS = $(SRCS:.cpp=.o)

%.o: %.c
	$(CXX) -c $(COMPILER_FLAGS) -o $@ $< $(INCLUDE)

pj5: pj5.o  
	$(CXX) $(COMPILER_FLAGS) $(LIBS) pj5.o -o  pj5

clean:
	rm -f  *.o $(TARGETS) *~ .*.swp ._*
