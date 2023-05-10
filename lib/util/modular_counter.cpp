#include "modular_counter.h"

template <unsigned int N>
inline bool operator==(const piet::modular_counter<N> lhs, const piet::modular_counter<N> rhs){
    return lhs.counter == rhs.counter;
}
