#include "game_of_life.h"
#include <chrono>
#include <thread>

#define WIDTH 60
#define HEIGHT 40
#define GENETARIONS 1000

using namespace std;

void gol_simulate(GameOfLife &gol, const size_t generations,
                  const size_t framerate) {
  std::chrono::milliseconds timespan(1000 / framerate);
  do {
    system("clear");
    gol.debug_print();
    gol.automaton.step();
    this_thread::sleep_for(timespan);
  } while (gol.automaton.get_generation() < GENETARIONS);
}

int main() {

  srand(time(NULL));
  GameOfLife gol(WIDTH, HEIGHT);
  gol.random_fill(0.4);
  // gol.automaton.set_cell_value(gol.automaton.get_cell_count() / 3, true);
  gol_simulate(gol, GENETARIONS, 12);

  gol.debug_print();
  return 0;
}
