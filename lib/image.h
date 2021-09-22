#ifndef PIET_IMAGE_READ_H
#define PIET_IMAGE_READ_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

namespace piet{
    struct pixel{
        uint8_t R, G, B;
        bool operator==(const piet::pixel& other) const {
            return R == other.R && G == other.G && B == other.B;
        }

        friend std::ostream& operator<<(std::ostream& os, const piet::pixel& pixel) {
            return os<<"("<<(int)pixel.R<<","<<(int)pixel.G<<","<<(int)pixel.B<<")";
        }

        uint32_t hex(){ return R << 16 | G << 8 | B; }
    };

    class image{
    private:
        unsigned int width, height;
        std::vector<std::vector<piet::pixel>> pixels;
    public:
        image(): width(0), height(0){}
        image(unsigned int width, unsigned int height):
            width(width),
            height(height),
            pixels(std::vector<std::vector<piet::pixel>>(height, std::vector<piet::pixel>(width))){}

        const piet::pixel& get_pixel(unsigned int row, unsigned int col) const{
            assert(row >= 0 && row < height && col >= 0 && col < width);
            return pixels[row][col];
        }

        void set_pixel(unsigned int row, unsigned int col, uint8_t R, uint8_t G, uint8_t B){
            assert(row >= 0 && row < height && col >= 0 && col < width);
            pixels[row][col] = {R, G, B};
        }

        bool operator==(const piet::image& other) const {
            if(width != other.width || height != other.height) return false;
            return pixels == other.pixels;
        }

        unsigned int get_height() const { return height; }
        unsigned int get_width() const { return width; }
    };

    const image EMPTY_IMAGE = piet::image();

    image read_image(const std::string& fname);
    image png_read(const std::string& fname);
}

#endif //PIET_IMAGE_READ_H
