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
#include "util/modular_counter.h"

namespace piet{

using direction_pointer = piet::modular_counter<4>;
using codel_chooser = piet::modular_counter<2>;

class direction_state{
private:
    piet::direction_pointer dp;
    piet::codel_chooser cc;
    int tries;
public:
    direction_state(): dp(0), cc(0), tries(0){}

    void operator++() {
        ++tries;
        if(cc() == 1) ++dp;
        ++cc;
    }

    bool operator==(const piet::direction_state& other) const {return dp == other.dp && cc == other.cc;}
};

class execution_state{
private:
    piet::codel& current_codel;
    piet::direction_state ds;
    std::stack<int> stack;
};

} // namespace piet

#endif //PIET_STATE_H
