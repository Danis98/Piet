#ifndef PIET_STATE_H
#define PIET_STATE_H

#include <stack>

#include "codel.h"

namespace piet{
    template<unsigned int N>
    class modular_counter{
    public:
        modular_counter(): counter(0) {}
        modular_counter(unsigned int counter): counter(counter % N) {}

        modular_counter<N> operator++(){
            counter = (counter + 1) % N;
            return *this;
        }

        modular_counter<N> operator--(){
            counter = (counter + N - 1) % N;
            return *this;
        }

        int operator()(){
            return counter;
        }

        bool operator==(const modular_counter<N>& other) const {
            return other.counter == counter;
        }

    private:
        unsigned int counter;
    };

    using direction_pointer = modular_counter<4>;
    using codel_chooser = modular_counter<2>;

    class direction_state{
    public:
        direction_state(): dp(0), cc(0), tries(0){}

        void operator++();

        bool operator==(const direction_state& other) const {return dp == other.dp && cc == other.cc;}
    
    private:
        direction_pointer dp;
        codel_chooser cc;
        int tries;
    };

    class execution_state{
    private:
        codel& current_codel;
        direction_state ds;
        std::stack<int> stack;
    };
}

#endif //PIET_STATE_H
