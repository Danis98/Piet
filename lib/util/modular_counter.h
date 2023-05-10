#ifndef PIET_MODULAR_COUNTER_H
#define PIET_MODULAR_COUNTER_H

#include "enum_cast.h"

namespace piet{

template<unsigned int N>
class modular_counter{
private:
    unsigned int counter;
public:
    modular_counter(): counter(0) {}
    modular_counter(unsigned int counter): counter(counter % N) {}

    template <derived_integral T>
    modular_counter(T counter): counter(std::abs(to_underlying(counter)) % N) {}

    modular_counter<N>& operator++(){
        counter = (counter + 1) % N;
        return *this;
    }

    modular_counter<N> operator++(int){
        modular_counter<N> tmp(*this);
        operator++();
        return tmp;
    }

    modular_counter<N>& operator--(){
        counter = (counter + N - 1) % N;
        return *this;
    }

    modular_counter<N> operator--(int){
        modular_counter<N> tmp(*this);
        operator--();
        return tmp;
    }

    unsigned int operator()() const{
        return counter;
    }
};

template <unsigned int N>
inline bool operator==(const modular_counter<N> lhs, const modular_counter<N> rhs);

} // namespace piet

#endif