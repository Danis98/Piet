#ifndef PIET_IMAGE_READ_H
#define PIET_IMAGE_READ_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

namespace image{
    struct pixel_type{
        uint8_t R, G, B;
        bool operator==(const image::pixel_type& other) const {
            return R == other.R && G == other.G && B == other.B;
        }

        friend std::ostream& operator<<(std::ostream& os, const image::pixel_type& pixel) {
            return os<<"("<<(int)pixel.R<<","<<(int)pixel.G<<","<<(int)pixel.B<<")";
        }
    };

    class image_type{
    private:
        unsigned int width, height;
        std::vector<std::vector<image::pixel_type>> pixels;
    public:
        image_type(): width(0), height(0){}
        image_type(unsigned int width, unsigned int height):
            width(width),
            height(height),
            pixels(std::vector<std::vector<image::pixel_type>>(height, std::vector<image::pixel_type>(width))){}

        const image::pixel_type& get_pixel(unsigned int row, unsigned int col) const{
            assert(row >= 0 && row < height && col >= 0 && col < width);
            return pixels[row][col];
        }

        void set_pixel(unsigned int row, unsigned int col, uint8_t R, uint8_t G, uint8_t B){
            assert(row >= 0 && row < height && col >= 0 && col < width);
            pixels[row][col] = {R, G, B};
        }

        bool operator==(const image::image_type& other) const {
            if(width != other.width || height != other.height) return false;
            return pixels == other.pixels;
        }

        unsigned int get_height(){ return height; }
        unsigned int get_width(){ return width; }
    };

    const image::image_type EMPTY_IMAGE = image::image_type();

    image::image_type read(const std::string& fname);
    image::image_type png_read(const std::string& fname);
}

#endif //PIET_IMAGE_READ_H
