/**
 * In Piet, colors are defined by hue & brightness.
 * Hue can be red, yellow, green, cyan, blue and magenta.
 * Brightness can be dark, normal or bright.
 * There are also special white and black colors.
 * 
 * Instructions in Piet are defined by the delta of hue & brightness
 * when we go from one codel block to another.
 * Therefore, we need to be able to "subtract" colors: for example
 * NORMAL GREEN - DARK RED = (1, 1)
**/

#ifndef PIET_COLOR_H
#define PIET_COLOR_H

#include <iostream>
#include <cassert>
#include <array>

#include "image.h"
#include "util/modular_counter.h"

namespace piet::hue {

enum class Hue {
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA
};

constexpr unsigned short NUM_HUE = 6;

constexpr std::array<std::string_view, NUM_HUE> HUE_NAMES{
    "RED",
    "YELLOW",
    "GREEN",
    "CYAN",
    "BLUE",
    "MAGENTA"
};

using hue_trait = modular_counter<NUM_HUE>;

const hue_trait RED(to_underlying<Hue>(Hue::RED));
const hue_trait YELLOW(to_underlying<Hue>(Hue::YELLOW));
const hue_trait GREEN(to_underlying<Hue>(Hue::GREEN));
const hue_trait CYAN(to_underlying<Hue>(Hue::CYAN));
const hue_trait BLUE(to_underlying<Hue>(Hue::BLUE));
const hue_trait MAGENTA(to_underlying<Hue>(Hue::MAGENTA));

} // namespace piet::hue

namespace piet::brightness{

enum class Brightness {
    DARK,
    NORMAL,
    BRIGHT,
};

constexpr unsigned short NUM_BRIGHTNESS = 3;

constexpr std::array<std::string_view, NUM_BRIGHTNESS> BRIGHTNESS_NAMES{
    "DARK",
    "NORMAL",
    "BRIGHT"
};

using brightness_trait = modular_counter<NUM_BRIGHTNESS>;

const brightness_trait DARK(to_underlying<Brightness>(Brightness::DARK));
const brightness_trait NORMAL(to_underlying<Brightness>(Brightness::NORMAL));
const brightness_trait BRIGHT(to_underlying<Brightness>(Brightness::BRIGHT));

} // namespace piet::brightness

namespace piet{

class color{
public:
    enum class color_category{ WHITE, BLACK, COLOR };
    static piet::color BLACK;
    static piet::color WHITE;

    color(piet::hue::hue_trait& hue,
            piet::brightness::brightness_trait& brightness):
        category(piet::color::color_category::COLOR),
        hue(hue),
        brightness(brightness){}
    color(piet::color::color_category category):
        category(category),
        hue(hue::MAGENTA), // placeholder, not used
        brightness(brightness::DARK){ // placeholder, not used
        assert(category != piet::color::color_category::COLOR);
    }
    color(piet::pixel pixel): color(pixel.hex()){}
    color(uint32_t hex):
        category(get_color_category(hex)),
        hue(get_color_hue(hex)),
        brightness(get_color_brightness(hex)){}

    friend std::ostream& operator<<(std::ostream& os, const color& color){
        const hue::hue_trait& color_hue = color.hue;
        const brightness::brightness_trait& color_brightness = color.brightness;
        switch(color.category){
        case color::color_category::COLOR:
            return os<<brightness::BRIGHTNESS_NAMES[color_brightness()]<<" "<<hue::HUE_NAMES[color_hue()];
        case color::color_category::BLACK:
            return os<<"BLACK";
        case color::color_category::WHITE:
            return os<<"WHITE";
        default:
            return os<<"???";
        }
    }

    bool operator==(const piet::color::color_category& other) const {return category == other;}
    bool operator==(const piet::color& other) const {
        if(category != other.category) return false;
        if(category != piet::color::color_category::COLOR) return true;
        return hue == other.hue && brightness == other.brightness;
    }

    const color::color_category get_color_category(uint32_t hex);
    const hue::hue_trait& get_color_hue(uint32_t hex);
    const brightness::brightness_trait& get_color_brightness(uint32_t hex);
private:
    color::color_category category;
    hue::hue_trait hue;
    brightness::brightness_trait brightness;
};

} // namespace piet

#endif //PIET_COLOR_H
