#  Makefile 
#  Auteur : Fares BELHADJ
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 23/02/2006

SHELL = /bin/sh
#definition des commandes utilisees
CC = gcc
MACHINE= $(shell uname -s)
#declaration des options du compilateur
#PG_FLAGS = -DOPENGL_1_5

#ifeq ($(MACHINE), Darwin)
#GL_LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
#else
#GL_LDFLAGS = -lGL -lglut -lGLU
#endif

CFLAGS = -Wall
LDFLAGS = -lm #$(GL_LDFLAGS)
DDEBUG = 
#definition des fichiers et dossiers
PROGNAME = quadtree
HEADERS = ppm.h utils.h quadtree.h
SOURCES = main.c quadtree.c ppm.c utils.c
#SOURCES = main.c ppm.c modif.c rgb_hls.c
OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(DDEBUG) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*
