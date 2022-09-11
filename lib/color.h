#ifndef PIET_COLOR_H
#define PIET_COLOR_H

#include <iostream>
#include <cassert>

#include "image.h"

namespace piet {
    template<class trait_names>
    class color_trait {
    public:
        color_trait(unsigned int index)
            : _index(index % std::size(trait_names::names))
        {}

        unsigned int operator-(const color_trait<trait_names>& other) const{
            std::size_t N = std::size(trait_names::names);
            return (_index + N - other._index) % N;
        }

        friend std::ostream& operator<<(std::ostream& os, color_trait<trait_names> trait){
            return os<<trait.get_value();
        }

        inline std::string_view get_value(){
            return trait_names::names[_index];
        }

        bool operator==(color_trait<trait_names> other) const {
            return _index == other._index;
        }
     private:
        unsigned int _index;
    };

    constexpr unsigned int NUM_HUES = 7;

    struct hue_names {
        static constexpr std::string_view names[NUM_HUES] = {
            "RED",
            "YELLOW",
            "GREEN",
            "CYAN",
            "BLUE",
            "MAGENTA",
            "?"
        };
    };

    using hue_trait = color_trait<hue_names>;

    namespace hue {
    const static hue_trait RED    (0);
    const static hue_trait YELLOW (1);
    const static hue_trait GREEN  (2);
    const static hue_trait CYAN   (3);
    const static hue_trait BLUE   (4);
    const static hue_trait MAGENTA(5);
    const static hue_trait INVALID(6);
    }


    constexpr unsigned int NUM_BRIGHT = 4;

    struct brightness_names {
        static constexpr std::string_view names[NUM_BRIGHT] = {
            "DARK",
            "NORMAL",
            "BRIGHT",
            "?"
        };
    };

    using brightness_trait = color_trait<brightness_names>;

    namespace brightness {
    const static brightness_trait DARK   (0);
    const static brightness_trait NORMAL (1);
    const static brightness_trait BRIGHT (2);
    const static brightness_trait INVALID(3);
    }

    class color{
    public:
        enum class color_category{ WHITE, BLACK, COLOR };

        static color BLACK;
        static color WHITE;

        color(hue_trait hue,
            brightness_trait brightness)
            : category(color_category::COLOR)
            , hue(hue)
            , brightness(brightness)
        {}

        color(color_category category)
            : category(category)
            , hue(hue::INVALID)
            , brightness(brightness::INVALID)
        {
            assert(category != color_category::COLOR);
        }

        color(piet::pixel pixel): color(pixel.hex()){}

        color(uint32_t hex):
            category(get_color_category(hex)),
            hue(get_color_hue(hex)),
            brightness(get_color_brightness(hex)){}

        friend std::ostream& operator<<(std::ostream& os, const color& color){
            switch(color.category){
            case color_category::COLOR:
                return os<<color.brightness<<" "<<color.hue;
            case color_category::BLACK:
                return os<<"BLACK";
            case color_category::WHITE:
                return os<<"WHITE";
            default:
                return os<<"???";
            }
        }

        bool operator==(color_category other) const {return category == other;}
        bool operator==(const color& other) const {
            if(category != other.category) return false;
            if(category != color_category::COLOR) return true;
            return hue == other.hue && brightness == other.brightness;
        }

        color_category get_color_category(uint32_t hex);
        hue_trait get_color_hue(uint32_t hex);
        brightness_trait get_color_brightness(uint32_t hex);
    private:
        color_category category;
        hue_trait hue;
        brightness_trait brightness;
    };
}

#endif //PIET_COLOR_H
