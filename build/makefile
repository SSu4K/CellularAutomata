CC = g++
CPPFLAGS = -Wall

PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/source
BUILDDIR := $(PROJDIR)/build
VPATH = $(SOURCEDIR)

INCLUDE = 

%.o : %.cpp;
	$(CC) -c $< -o $@

%.o : %.hpp;
	$(CC) -c $< -o $@

%.a : %.o;
	ar rvs $@ $?

grid_test: grid_test.o grid.o moore_nhood_generator.o nhood_generator_template.o
	$(CC) $(CPPFLAGS) -o $@ $?

gol_test: game_of_life_test.o game_of_life.o automaton.a square_grid_util.o
	$(CC) $(CPPFLAGS) -o $@ $?

nhood_test: grid.o square_grid_util.o nhood_test.o
	$(CC) $(CPPFLAGS) -o $@ $?

automaton.a: automaton.o

square_grid_util.o: square_grid_util.cpp

automaton.o: automaton.hpp 

game_of_life.o: game_of_life.cpp

game_of_life_test.o: game_of_life_test.cpp

clean:
	find . -not -name "*.*" -exec ls -l {} \;
	rm *.o
