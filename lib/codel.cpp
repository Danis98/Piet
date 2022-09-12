#include <queue>

#include "codel.h"
#include "image.h"

namespace piet{

codel_block codel_block::NULL_BLOCK{};
codel codel::NULL_CODEL{};

void codel_grid::explore_block(std::vector<std::vector<bool>>& added,
                   const image& image,
                   const position& start){
    color block_color = image.get_pixel(start.get_row(), start.get_col());
    std::queue<position> Q;
    Q.push(start);
    added[start.get_row()][start.get_col()] = true;
    while(!Q.empty()){
        position cur = Q.front();
        Q.pop();
        codels[cur.get_row()][cur.get_col()] = {cur, block_color};

    }
}

codel_grid::codel_grid(const image& image): height(image.get_height()), width(image.get_width()){
    codels.resize(height, std::vector<codel>(width));

    std::vector<std::vector<bool>> added(height, std::vector<bool>(width, false));

    for(unsigned int row=0;row<height;row++){
        for(unsigned int col=0;col<width;col++){
            if(added[row][col]) continue;
            explore_block(added, image, {row, col});
        }
    }
}

}