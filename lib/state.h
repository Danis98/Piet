#ifndef PIET_STATE_H
#define PIET_STATE_H

#include <codel.h>

namespace piet{
    template<unsigned int N>
    class modular_counter{
    private:
        unsigned int counter;
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
    };

    using direction_pointer = piet::modular_counter<4>;
    using codel_chooser = piet::modular_counter<2>;

    class execution_state{
    private:
        piet::codel& current_codel;
        piet::direction_pointer dp;
        piet::codel_chooser cc;
        std::stack<int> stack;

        execution_state(){}
    };
}

#endif //PIET_STATE_H
