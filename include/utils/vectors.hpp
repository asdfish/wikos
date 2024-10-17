#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

template <typename T>
void vector_append(std::vector<T>* into, std::vector<T>* from) {
  for(unsigned int i = 0; i < from->size(); i ++)
    into->push_back(from->at(i));
}

template <typename T>
T vector_pop(std::vector<T>* from) {
  T return_buffer = from->at(from->size() - 1);
  from->pop_back();
  return return_buffer;
}

#endif
