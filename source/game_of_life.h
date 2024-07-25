#ifndef __GAME_OF_LIFE__
#define __GAME_OF_LIFE__
#include "automaton.hpp"

class GameOfLife {
public:
  Automaton<bool> automaton;
  GameOfLife(size_t width, size_t height);
  void print();
  void debug_print();
  void random_fill(const double &);
};
#endif
