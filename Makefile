#Makefile for OpenGL flight simulator
# ------------------------------------

# Object files list
OBJS = src/main.cpp		\
	   src/Mesh.cpp 	\
	   src/HalfEdge.cpp	\
	   src/SDFace.cpp	\
	   src/SDEdge.cpp	\
	   src/SDVertex.cpp

# Executable name
EXENAME = MeshEditor

# Macros
CC = g++
CXXFLAGS = -g -O3 -Wall -Wno-deprecated -std=c++14
LINK = g++
LINKOPTS = -o
INCLUDES = -I./headers/ -I/usr/local/include/ -I/usr/local/Cellar/glew/1.12.0/include/
all : $(EXENAME)

# Testing for OS X v Linux
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -framework GLUT -framework OpenGL -L/usr/local/Cellar/glew/1.12.0/lib -lGLEW
else
	LIBS = -lGL -lGLU -lglut -lGLEW
endif

#LIBS = -lGL -lGLU -lglut -lGLEW

# The compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(CXXFLAGS) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS) $(INCLUDES)

# Object files
main.o : main.cpp 
	$(CC) $(CCOPTS) main.cpp
mesh.o : Mesh.cpp Mesh.hpp
	$(CC) $(CCOPTS) Mesh.cpp
HalfEdge.o: HalfEdge.cpp HalfEdge.hpp
	$(CC) $(CCOPTS) HalfEDge.cpp

clean :
	rm -f *.o $(EXENAME) 2>/dev/null
