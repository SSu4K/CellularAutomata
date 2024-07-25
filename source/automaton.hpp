#include <functional>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

#define UNLOAD_AGE 2

using namespace std;

typedef std::vector<std::size_t> size_vector;

typedef function<size_vector(const size_t &, const size_vector &)>
    get_nhood_func;

template <class T> class CellTemplate {
public:
  T value;
  std::vector<CellTemplate<T> *> nhood;
  size_t generation;
};

template <class T> class Automaton {
  typedef CellTemplate<T> Cell;
  typedef function<T(const Cell &)> generation_func;

protected:
  size_vector size;
  size_t cell_count;
  Cell *cells;
  set<Cell *> loaded_cells;
  size_t generation;
  get_nhood_func get_nhood;
  generation_func cell_generation;

  void load_cell(Cell *);
  void set_cell_value(Cell *, const T);
  bool cell_unload_condition(const Cell *) const;

  T get_cell_value(const Cell *) const;
  bool is_loaded(Cell *) const;

public:
  Automaton(const size_vector, get_nhood_func, generation_func);
  ~Automaton();

  size_vector get_size() const;
  size_t get_cell_count() const;
  size_t get_loaded_cell_count() const;
  size_t get_generation() const;

  T get_cell_value(const size_t) const;
  void set_cell_value(const size_t, const T);
  bool is_loaded(const size_t) const;

  void step();
};

template <class T>
Automaton<T>::Automaton(const size_vector size, get_nhood_func get_nhood,
                        generation_func cell_generation)
    : size(size),
      cell_count(accumulate(size.begin(), size.end(), 1, multiplies<size_t>())),
      cells(cells = new Cell[cell_count]()), loaded_cells({}), generation(0),
      get_nhood(get_nhood), cell_generation(cell_generation) {
  for (size_t i = 0; i < cell_count; i++) {
    vector<size_t> offsets = this->get_nhood(i, size);
    for (size_t j = 0; j < offsets.size(); j++) {

      cells[i].nhood.push_back(&cells[offsets[j]]);
    }
  }
}
template <class T> Automaton<T>::~Automaton() { delete[] cells; }

template <class T> bool Automaton<T>::is_loaded(Cell *cell_ptr) const {
  return loaded_cells.find(cell_ptr) != loaded_cells.end();
}

template <class T> void Automaton<T>::load_cell(Cell *cell_ptr) {
  if (!is_loaded(cell_ptr)) {
    loaded_cells.insert(cell_ptr);
  }
}

template <class T>
void Automaton<T>::set_cell_value(Cell *cell_ptr, const T value) {
  if (cell_ptr->value == value)
    return;
  cell_ptr->generation = generation;
  cell_ptr->value = value;
  load_cell(cell_ptr);
  for (auto *neighbour : cell_ptr->nhood) {
    load_cell(neighbour);
  }
}
template <class T>
bool Automaton<T>::cell_unload_condition(const Cell *cell_ptr) const {
  if (generation - (cell_ptr)->generation < UNLOAD_AGE) {
    return false;
  }
  for (auto neighbour : cell_ptr->nhood) {
    if (generation - neighbour->generation < UNLOAD_AGE) {
      return false;
    }
  }
  return true;
}

template <class T> T Automaton<T>::get_cell_value(const Cell *cell_ptr) const {
  return cell_ptr->value;
}

template <class T> size_vector Automaton<T>::get_size() const { return size; }
template <class T> size_t Automaton<T>::get_cell_count() const {
  return cell_count;
}
template <class T> size_t Automaton<T>::get_loaded_cell_count() const {
  return loaded_cells.size();
}
template <class T> size_t Automaton<T>::get_generation() const {
  return generation;
}

template <class T> bool Automaton<T>::is_loaded(const size_t index) const {
  Cell *cell = cells + index;
  return is_loaded(cell);
}

template <class T>
void Automaton<T>::set_cell_value(const size_t index, const T value) {
  Cell *cell = cells + index;
  set_cell_value(cell, value);
}

template <class T> T Automaton<T>::get_cell_value(const size_t index) const {
  return cells[index].value;
}

template <class T> void Automaton<T>::step() {
  vector<pair<Cell *, const T>> new_values;
  auto it = loaded_cells.begin();
  while (it != loaded_cells.end()) {

    if (cell_unload_condition(*it)) {
      it = loaded_cells.erase(it);
      continue;
    }
    new_values.push_back({*it, cell_generation(**it)});
    it++;
  }
  for (auto it : new_values) {
    set_cell_value(get<0>(it), get<1>(it));
  }
  generation++;
}
