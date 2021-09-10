#ifndef PIET_CODEL_H
#define PIET_CODEL_H

#include <color.h>

namespace codel{
    class position_type{
    public:
        position_type(unsigned int row, unsigned int col): row(row), col(col){}
        friend std::ostream& operator<<(std::ostream& os, const codel::position_type& position){
            return os<<"("<<position.row<<", "<<position.col<<")";
        }
        bool operator==(const codel::position_type& other) const {return row == other.row && col == other.col;}
    private:
        unsigned int row, col;
    };

    class codel_type{
    public:
        codel_type(color::color_type color): codel_position({0, 0}), codel_color(color){}
        codel_type(codel::position_type position, color::color_type color):
            codel_position(position), codel_color(color){}

        bool operator==(const color::color_type::color_category_type& other) const {return codel_color == other;}
        bool operator==(const codel::codel_type& other) const {
            return codel_position == other.codel_position && codel_color == other.codel_color;
        }

        friend std::ostream& operator<<(std::ostream& os, const codel::codel_type& codel){
            return os<<"["<<codel.codel_position<<": "<<codel.codel_color<<"]";
        }
    private:
        codel::position_type codel_position;
        color::color_type codel_color;

    };
}

#endif //PIET_CODEL_H
