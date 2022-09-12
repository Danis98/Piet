/**
 * When running the program, our execution state is given by the tuple
 * (DP, CC, position, attempts) and a stack of integers.
 * 
 * DP (Direction Pointer): Direction in which the execution moves. Can be any of
 * the 4 directions.
 * CC (Codel Chooser): Used to disambiguate which codel should be the next. Can
 * be left or right.
 * 
 * When the next codel is black or outside the image, DP and CC are modified.
 * If this happens for 8 attempts, the program terminates.
**/

#ifndef PIET_STATE_H
#define PIET_STATE_H

#include <stack>

#include "codel.h"

namespace piet{

// Both DP and CC can be represented by ints mod 4 and 2 respectively
template<unsigned int N>
class modular_counter{
public:
    modular_counter(): counter(0) {}
    modular_counter(unsigned int counter): counter(counter % N) {}

    modular_counter<N> operator++(){
        _counter = (_counter + 1) % N;
        return *this;
    }

    modular_counter<N> operator--(){
        _counter = (_counter + N - 1) % N;
        return *this;
    }

    int operator()(){
        return _counter;
    }

    bool operator==(const modular_counter<N>& other) const {
        return other._counter == _counter;
    }

private:
    unsigned int _counter;
};

using direction_pointer = modular_counter<4>;
using codel_chooser = modular_counter<2>;

// Package all direction info in one container for convenience
class direction_state{
public:
    direction_state(): dp(0), cc(0), attempts(0){}

    void operator++() {
        _attempts++;
        if(cc() == 1) ++_dp;
        ++_cc;
    }

    bool operator==(const direction_state& other) const {return _dp == other._dp && _cc == other._cc;}

private:
    direction_pointer _dp;
    codel_chooser _cc;
    int _attempts;
};

// Class representing the execution state
class execution_state{
private:
    codel& current_codel;
    direction_state ds;
    std::stack<int> stack;
};

}

#endif //PIET_STATE_H
