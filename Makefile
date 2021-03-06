
CC=			g++

CXXFLAGS	+=	-W -Wall -Wextra -std=c++14
CXXFLAGS	+= -O3
CXXFLAGS	+= -g3
CXXFLAGS	+=	-I./headers/
 
ifeq ($(shell uname -s), Darwin)
CXXFLAGS += -I/usr/local/Cellar/glew/1.12.0/include/ -I/usr/local/include/
LDFLAGS   = -framework GLUT -framework OpenGL -L/usr/local/Cellar/glew/1.12.0/lib -lGLEW
else
LDFLAGS = -lGL -lGLU -lglut -lGLEW
endif


NAME=	MeshEditor

SRCS = src/main.cpp				\
	   src/Mesh.cpp 			\
	   src/OFFLoader.cpp 		\
	   src/SDFace.cpp			\
	   src/SDVertex.cpp			\
	   src/SDDataStructure.cpp

OBJ=		$(SRCS:.cpp=.o)

all: 	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) 
clean:	
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
