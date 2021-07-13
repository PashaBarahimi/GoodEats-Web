#ifndef ALGORITHM_SIDE_FUNCTIONS_HPP
#define ALGORITHM_SIDE_FUNCTIONS_HPP

template<typename T>
static bool compareByName(const T first, const T second) { return first->getName() < second->getName(); }

#endif
