/**
 * This header has a bunch of container classes that exist mainly for clarity
 * and convenience purposes.
 * They mostly add formatting and some metadata.
**/

#ifndef PIET_CODEL_H
#define PIET_CODEL_H

#include <map>

#include "color.h"
#include "image.h"

namespace piet{

// This class is a glorified pair of uints, just wanted to
// use row, col instead of first, second and have nice formatting
class position{
public:
    position(): row(0), col(0){}
    position(unsigned int row, unsigned int col): row(row), col(col){}
    friend std::ostream& operator<<(std::ostream& os, const position& position){
        return os<<"("<<position.row<<", "<<position.col<<")";
    }

    unsigned int get_row() const { return row; }
    unsigned int get_col() const { return col; }

    bool operator==(const position& other) const {return row == other.row && col == other.col;}
private:
    unsigned int row, col;
};

// A codel has a position and a color.
class codel{
public:
    static codel NULL_CODEL;

    codel():
        is_null_codel(true),
        codel_position({0, 0}),
        codel_color(hue::INVALID, brightness::INVALID){}
    codel(position position, color color):
        codel_position(position),
        codel_color(color),
        is_null_codel(false){}
    codel(const codel& other):
        codel_position(other.codel_position),
        codel_color(other.codel_color),
        is_null_codel(other.is_null_codel){}

    bool operator==(const color::color_category& other) const {return !is_null_codel && codel_color == other;}
    bool operator==(const codel& other) const {
        return is_null_codel == other.is_null_codel &&
                (is_null_codel || codel_position == other.codel_position && codel_color == other.codel_color);
    }

    friend std::ostream& operator<<(std::ostream& os, const codel& codel){
        if(!codel.is_null_codel)
            return os<<"["<<codel.codel_position<<": "<<codel.codel_color<<"]";
        else return os<<"[NULL]";
    }
private:
    position codel_position;
    color codel_color;
    bool is_null_codel;
};

// Codel block, has cached data on which codel should be next
class codel_block{
private:
    color block_color;
    // doing search on the grid is expensive, we cache the next codel pos
    // based on DP and CC values when the block is created
    position next_codels[4][2];
public:
    static codel_block NULL_BLOCK;

    codel_block(): block_color(hue::INVALID, brightness::INVALID){}
    codel_block(color block_color): block_color(block_color) {}
};

// The actual representation of our Piet program.
// Contains the raw grid of codels, from which it constructs
// the layout of codel blocks.
class codel_grid{
public:
    codel_grid(const image& image);
    void explore_block(std::vector<std::vector<bool>>& added,
                        const image& image,
                        const position& start);

    const codel& get(unsigned int row, unsigned int col){ return codels[row][col]; }

private:
    unsigned int height, width;
    std::vector<std::vector<codel>> codels;
    std::vector<codel_block> blocks;
    codel_block& start_block = codel_block::NULL_BLOCK;
};

}

#endif //PIET_CODEL_H
