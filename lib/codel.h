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
        codel_type():
            codel_position({0, 0}),
            codel_color(color::color_type::color_category_type::BLACK),
            is_null_codel(true){}
        codel_type(codel::position_type position, color::color_type color):
            codel_position(position),
            codel_color(color),
            is_null_codel(false){}

        bool operator==(const color::color_type::color_category_type& other) const {return !is_null_codel && codel_color == other;}
        bool operator==(const codel::codel_type& other) const {
            return is_null_codel == other.is_null_codel &&
                    (is_null_codel || codel_position == other.codel_position && codel_color == other.codel_color);
        }

        friend std::ostream& operator<<(std::ostream& os, const codel::codel_type& codel){
            if(!codel.is_null_codel)
                return os<<"["<<codel.codel_position<<": "<<codel.codel_color<<"]";
            else return os<<"[NULL]";
        }
    private:
        codel::position_type codel_position;
        color::color_type codel_color;
        bool is_null_codel;
    };

    const static codel::codel_type NULL_CODEL;
}

#endif //PIET_CODEL_H
