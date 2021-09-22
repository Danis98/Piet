#include <codel.h>
#include <image.h>

piet::codel_block piet::codel_block::NULL_BLOCK{};
piet::codel piet::codel::NULL_CODEL{};

void explore_block(const std::vector<std::vector<bool>>& added, const piet::image& image, piet::position start){
    piet::color block_color = image.get_pixel(start.get_row(), start.get_col());
}

piet::codel_grid::codel_grid(const piet::image& image): height(image.get_height()), width(image.get_width()){
    codels.resize(height, std::vector<piet::codel>(width));

    std::vector<std::vector<bool>> added(height, std::vector<bool>(width, false));

    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){

        }
    }
}
