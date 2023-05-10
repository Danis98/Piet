/**
 * Container representing the raw image data.
 * This will be used to generate the codel grid.
**/

#ifndef PIET_IMAGE_READ_H
#define PIET_IMAGE_READ_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

namespace piet{

// Container for RGB values
struct pixel{
    uint8_t R, G, B;
    bool operator==(const pixel& other) const {
        return R == other.R && G == other.G && B == other.B;
    }

    friend std::ostream& operator<<(std::ostream& os, const pixel& pixel) {
        return os<<"("<<(int)pixel.R<<","<<(int)pixel.G<<","<<(int)pixel.B<<")";
    }

    uint32_t hex(){ return R << 16 | G << 8 | B; }
};

// Image data container
class image{
public:
    image(): width(0), height(0){}
    image(unsigned int width, unsigned int height):
        width(width),
        height(height),
        pixels(std::vector<std::vector<pixel>>(height, std::vector<pixel>(width))){}

    const pixel& get_pixel(unsigned int row, unsigned int col) const{
        assert(row >= 0 && row < height && col >= 0 && col < width);
        return pixels[row][col];
    }

    void set_pixel(unsigned int row, unsigned int col, uint8_t R, uint8_t G, uint8_t B){
        assert(row >= 0 && row < height && col >= 0 && col < width);
        pixels[row][col] = {R, G, B};
    }

    bool operator==(const image& other) const {
        if(width != other.width || height != other.height) return false;
        return pixels == other.pixels;
    }

    unsigned int get_height() const { return height; }
    unsigned int get_width() const { return width; }
private:
    unsigned int width, height;
    std::vector<std::vector<pixel>> pixels;
};

const image EMPTY_IMAGE = image();

image read_image(const std::string& fname);
}

#endif //PIET_IMAGE_READ_H
