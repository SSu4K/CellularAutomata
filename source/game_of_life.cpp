#include "game_of_life.h"
#include "square_grid_util.h"
#include <cstdlib>
#include <iostream>

#define UNDERPOPULATION_TRESH 2
#define OVERPOPULATION_TRESH 3
#define BIRTH_TRESH 2

using namespace std;

const string symbols[4] = {"\u25A0", "\uFF65", "\033[33m\u25A0\033[0m",
                           "\033[33m\uFF65\033[0m"};

bool cell_step(const CellTemplate<bool> &cell) {
  int sum = 0;
  for (auto neighbour : cell.nhood) {
    sum += neighbour->value;
  }
  if (sum < UNDERPOPULATION_TRESH || sum > OVERPOPULATION_TRESH) {
    return false;
  }
  if (sum > BIRTH_TRESH) {
    return true;
  }
  return cell.value;
}

size_vector get_nhood(const size_t &index, const size_vector &size) {
  return get_square_grid_nhood(index, size);
}

GameOfLife::GameOfLife(size_t width, size_t height)
    : automaton({width, height}, get_nhood, cell_step) {}

void GameOfLife::print() {
  cout << "\"Game Of Life\" time: " << automaton.get_generation() << endl;
  size_t width = automaton.get_size()[0];
  for (size_t i = 0; i < automaton.get_cell_count(); i++) {
    bool value = automaton.get_cell_value(i);
    cout << (value ? symbols[0] : symbols[1])
         << (((i + 1) % width) ? " " : "\n");
  }
}

void GameOfLife::debug_print() {
  size_t count = automaton.get_cell_count();
  size_t width = automaton.get_size()[0];
  cout << "gof debug" << endl;
  cout << "Loaded: " << automaton.get_loaded_cell_count() << "/" << count
       << endl;
  cout << "Generations: " << automaton.get_generation() << endl;

  for (size_t i = 0; i < count; i++) {
    bool value = automaton.get_cell_value(i);
    if (automaton.is_loaded(i)) {
      cout << (value ? symbols[0] : symbols[1])
           << (((i + 1) % width) ? " " : "\n");
    } else {
      cout << (value ? symbols[2] : symbols[3])
           << (((i + 1) % width) ? " " : "\n");
    }
  }
}

void GameOfLife::random_fill(const double &p) {
  for (size_t i = 0; i < automaton.get_cell_count(); i++) {
    automaton.set_cell_value(i, double(rand()) / RAND_MAX < p);
  }
}
