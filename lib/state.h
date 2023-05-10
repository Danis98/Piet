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
