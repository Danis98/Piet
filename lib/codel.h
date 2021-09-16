#ifndef PIET_CODEL_H
#define PIET_CODEL_H

#include <color.h>

namespace piet{
    class position{
    public:
        position(unsigned int row, unsigned int col): row(row), col(col){}
        friend std::ostream& operator<<(std::ostream& os, const piet::position& position){
            return os<<"("<<position.row<<", "<<position.col<<")";
        }
        bool operator==(const piet::position& other) const {return row == other.row && col == other.col;}
    private:
        unsigned int row, col;
    };

    class codel{
    public:
        codel():
            codel_position({0, 0}),
            codel_color(piet::color::color_category::BLACK),
            is_null_codel(true){}
        codel(piet::position position, piet::color color):
            codel_position(position),
            codel_color(color),
            is_null_codel(false){}

        bool operator==(const piet::color::color_category& other) const {return !is_null_codel && codel_color == other;}
        bool operator==(const piet::codel& other) const {
            return is_null_codel == other.is_null_codel &&
                    (is_null_codel || codel_position == other.codel_position && codel_color == other.codel_color);
        }

        friend std::ostream& operator<<(std::ostream& os, const piet::codel& codel){
            if(!codel.is_null_codel)
                return os<<"["<<codel.codel_position<<": "<<codel.codel_color<<"]";
            else return os<<"[NULL]";
        }
    private:
        piet::position codel_position;
        piet::color codel_color;
        bool is_null_codel;
    };

    const static piet::codel NULL_CODEL;
}

#endif //PIET_CODEL_H
