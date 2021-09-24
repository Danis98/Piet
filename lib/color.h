#ifndef PIET_COLOR_H
#define PIET_COLOR_H

#include <iostream>
#include <array>
#include <vector>
#include <typeinfo>
#include <memory>
#include <cassert>
#include <image.h>

namespace piet{
    template<typename T>
    concept printable = requires(T t) {
        { std::cout << t } -> std::same_as<std::ostream&>;
    };

    template<printable T, T... value_names_list>
    class color_trait{
    private:
        color_trait(unsigned int index) :
            index(index),
            value_names {{value_names_list...}}{}
        unsigned int index;
        static std::vector<std::shared_ptr<color_trait<T, value_names_list...>>> instances;

        template<size_t ...I>
        static void populate_instances(std::index_sequence<I...> seq){
            int i = 0;
            instances.resize(sizeof...(value_names_list));
            (void(instances[i++].reset(new color_trait<T, value_names_list...>(I))), ...);
        }
    public:
        const std::array<T, sizeof...(value_names_list)> value_names;

        color_trait(const piet::color_trait<T, value_names_list...>& trait) = delete;
        color_trait(piet::color_trait<T, value_names_list...>&& trait) = delete;
        void operator=(const piet::color_trait<T, value_names_list...>& trait) = delete;
        void operator=(piet::color_trait<T, value_names_list...>&& trait) = delete;
        ~color_trait(){ /*std::cout<<"[DEBUG] Destroying "<<*this<<" trait"<<std::endl*/; }

        static const std::shared_ptr<color_trait<T, value_names_list...>> get_instance(unsigned int idx){
            if(instances.empty()){
                auto idx_seq = std::make_index_sequence<sizeof...(value_names_list)>();
                populate_instances(idx_seq);
            }
            return instances[idx];
        }

        unsigned int operator-(const piet::color_trait<T, value_names_list...>& other) const{
            constexpr unsigned int num_values = sizeof...(value_names_list);
            int diff = index - other.index;
            return (diff + num_values) % num_values;
        }

        friend std::ostream& operator<<(std::ostream& os, const piet::color_trait<T, value_names_list...>& trait){
            return os<<trait.value_names[trait.index];
        }

        bool operator==(const piet::color_trait<T, value_names_list...>& other) const {return index == other.index;}
    };

    template<printable T, T ...value_names_list>
    std::vector<std::shared_ptr<color_trait<T, value_names_list...>>> color_trait<T, value_names_list...>::instances{};


    namespace hue{
        extern const char STR_RED[];
        extern const char STR_YELLOW[];
        extern const char STR_GREEN[];
        extern const char STR_CYAN[];
        extern const char STR_BLUE[];
        extern const char STR_MAGENTA[];

        using hue_trait = piet::color_trait<const char*,
            piet::hue::STR_RED,
            piet::hue::STR_YELLOW,
            piet::hue::STR_GREEN,
            piet::hue::STR_CYAN,
            piet::hue::STR_BLUE,
            piet::hue::STR_MAGENTA>;
        using hue_ptr = std::shared_ptr<hue_trait>;

        constexpr int NUM_HUES = 6;

        const hue_ptr RED     = hue_trait::get_instance(0);
        const hue_ptr YELLOW  = hue_trait::get_instance(1);
        const hue_ptr GREEN   = hue_trait::get_instance(2);
        const hue_ptr CYAN    = hue_trait::get_instance(3);
        const hue_ptr BLUE    = hue_trait::get_instance(4);
        const hue_ptr MAGENTA = hue_trait::get_instance(5);
    }

    namespace brightness{
        extern const char STR_DARK[];
        extern const char STR_NORMAL[];
        extern const char STR_BRIGHT[];

        using brightness_trait = piet::color_trait<const char*,
            piet::brightness::STR_DARK,
            piet::brightness::STR_NORMAL,
            piet::brightness::STR_BRIGHT>;
        using brightness_ptr = std::shared_ptr<brightness_trait>;

        constexpr int NUM_BRIGHTNESS = 3;

        const brightness::brightness_ptr DARK      = piet::brightness::brightness_trait::get_instance(0);
        const brightness::brightness_ptr NORMAL    = piet::brightness::brightness_trait::get_instance(1);
        const brightness::brightness_ptr BRIGHT    = piet::brightness::brightness_trait::get_instance(2);
    }

    class color{
    public:
        enum class color_category{ WHITE, BLACK, COLOR };
        static piet::color BLACK;
        static piet::color WHITE;

        color(piet::hue::hue_ptr hue,
               piet::brightness::brightness_ptr brightness):
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

        friend std::ostream& operator<<(std::ostream& os, const piet::color& color){
            const piet::hue::hue_trait& color_hue = *color.hue.get();
            const piet::brightness::brightness_trait& color_brightness = *color.brightness.get();
            switch(color.category){
            case piet::color::color_category::COLOR:
                return os<<color_brightness<<" "<<color_hue;
            case piet::color::color_category::BLACK:
                return os<<"BLACK";
            case piet::color::color_category::WHITE:
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

        piet::color::color_category get_color_category(uint32_t hex);
        piet::hue::hue_ptr get_color_hue(uint32_t hex);
        piet::brightness::brightness_ptr get_color_brightness(uint32_t hex);
    private:
        piet::color::color_category category;
        piet::hue::hue_ptr hue;
        piet::brightness::brightness_ptr brightness;
    };
}

#endif //PIET_COLOR_H
