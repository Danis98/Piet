#include "state.h"

void piet::direction_state::operator++() {
    tries++;
    if(cc() == 1) ++dp;
    ++cc;
}
