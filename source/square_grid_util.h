#ifndef __SQUARE_GRID_UTILS_H__
#define __SQUARE_GRID_UTILS_H__
#include <vector>

typedef std::vector<std::size_t> size_vector;

std::size_t wrap_around(const long &value, const long &max);

std::size_t get_index(const std::vector<long> &pos, const size_vector &size);
size_vector get_pos(std::size_t index, const size_vector &size);
std::vector<std::size_t> get_square_grid_nhood(const std::size_t &index,
                                               const size_vector &size);
std::vector<std::size_t> get_square_grid_4nhood(const std::size_t &index,
                                                const size_vector &size);
#endif
