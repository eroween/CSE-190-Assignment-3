#Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS = main.cpp Mesh.cpp HalfEdge.cpp

# Executable name
EXENAME = MeshEditor

# Macros
CC = g++
CCOPTS = -c -g -O3 -Wall -Wno-deprecated
LINK = g++
LINKOPTS = -o
INCLUDES =-I../headers/ -I../utility/glm/glm/
all : $(EXENAME)

# Testing for OS X v Linux
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -framework GLUT -framework OpenGL
else
	LIBS = -lGL -lGLU -lglut
endif

# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS) $(INCLUDES)

# Object files
main.o : main.cpp 
	$(CC) $(CCOPTS) main.cpp
mesh.o : Mesh.cpp Mesh.hpp
	$(CC) $(CCOPTS) Mesh.cpp
HalfEdge.o: HalfEdge.cpp HalfEdge.hpp
	$(CC) $(CCOPTS) HalfEDge.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null
