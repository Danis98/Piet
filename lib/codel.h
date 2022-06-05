#ifndef PIET_CODEL_H
#define PIET_CODEL_H

#include <map>

#include <color.h>
#include <image.h>

namespace piet{
    class position{
    public:
        position(): row(0), col(0){}
        position(unsigned int row, unsigned int col): row(row), col(col){}
        friend std::ostream& operator<<(std::ostream& os, const piet::position& position){
            return os<<"("<<position.row<<", "<<position.col<<")";
        }

        unsigned int get_row() const { return row; }
        unsigned int get_col() const { return col; }

        bool operator==(const piet::position& other) const {return row == other.row && col == other.col;}
    private:
        unsigned int row, col;
    };

    class codel_block{
    private:
        piet::color block_color;
        piet::position next_codels[4][2];
    public:
        static codel_block NULL_BLOCK;

        codel_block(): block_color(piet::color::BLACK){}
        codel_block(piet::color block_color): block_color(block_color) {}
    };

    class codel{
    public:
        static piet::codel NULL_CODEL;

        codel():
            is_null_codel(true),
            codel_position({0, 0}),
            codel_color(piet::color::BLACK){}
        codel(piet::position position, piet::color color):
            codel_position(position),
            codel_color(color),
            is_null_codel(false){}
        codel(const codel& other):
            codel_position(other.codel_position),
            codel_color(other.codel_color),
            is_null_codel(other.is_null_codel){}

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

    class codel_grid{
    private:
        unsigned int height, width;
        std::vector<std::vector<piet::codel>> codels;
        std::map<piet::position, piet::codel_block> block_map;
    public:
        codel_grid(const piet::image& image);
        void explore_block(std::vector<std::vector<bool>>& added,
                            const piet::image& image,
                            const piet::position& start);

        const piet::codel& get(unsigned int row, unsigned int col){ return codels[row][col]; }
    };
}

#endif //PIET_CODEL_H
