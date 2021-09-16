#ifndef PIET_COLOR_H
#define PIET_COLOR_H

#include <array>
#include <vector>
#include <typeinfo>
#include <memory>
#include <cassert>

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
        ~color_trait(){ std::cout<<"Destroying "<<*this<<std::endl; }

        static const color_trait<T, value_names_list...>& get_instance(unsigned int idx){
            if(instances.empty()){
                auto idx_seq = std::make_index_sequence<sizeof...(value_names_list)>();
                populate_instances(idx_seq);
            }
            color_trait<T, value_names_list...> *raw_ptr = instances[idx].get();
            return *raw_ptr;
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
        constexpr char STR_RED[] = "RED";
        constexpr char STR_YELLOW[] = "YELLOW";
        constexpr char STR_GREEN[] = "GREEN";
        constexpr char STR_CYAN[] = "CYAN";
        constexpr char STR_BLUE[] = "BLUE";
        constexpr char STR_MAGENTA[] = "MAGENTA";

        using hue_trait = piet::color_trait<const char*,
            piet::hue::STR_RED,
            piet::hue::STR_YELLOW,
            piet::hue::STR_GREEN,
            piet::hue::STR_CYAN,
            piet::hue::STR_BLUE,
            piet::hue::STR_MAGENTA>;

        constexpr int NUM_HUES = 6;

        const hue_trait& RED     = hue_trait::get_instance(0);
        const hue_trait& YELLOW  = hue_trait::get_instance(1);
        const hue_trait& GREEN   = hue_trait::get_instance(2);
        const hue_trait& CYAN    = hue_trait::get_instance(3);
        const hue_trait& BLUE    = hue_trait::get_instance(4);
        const hue_trait& MAGENTA = hue_trait::get_instance(5);
    }

    namespace brightness{
        constexpr char STR_DARK[] = "DARK";
        constexpr char STR_NORMAL[] = "NORMAL";
        constexpr char STR_BRIGHT[] = "BRIGHT";

        using brightness_trait = piet::color_trait<const char*,
            piet::brightness::STR_DARK,
            piet::brightness::STR_NORMAL,
            piet::brightness::STR_BRIGHT>;

        constexpr int NUM_BRIGHTNESS = 3;

        const brightness::brightness_trait& DARK      = piet::brightness::brightness_trait::get_instance(0);
        const brightness::brightness_trait& NORMAL    = piet::brightness::brightness_trait::get_instance(1);
        const brightness::brightness_trait& BRIGHT    = piet::brightness::brightness_trait::get_instance(2);
    }

    class color{
    public:
        enum class color_category{ WHITE, BLACK, COLOR };

        color(const piet::hue::hue_trait& hue,
               const piet::brightness::brightness_trait& brightness):
            category(piet::color::color_category::COLOR),
            hue(hue),
            brightness(brightness){}
        color(piet::color::color_category category):
            category(category),
            hue(hue::hue_trait::get_instance(0)),
            brightness(brightness::brightness_trait::get_instance(0)){
            assert(category != piet::color::color_category::COLOR);
        }

        friend std::ostream& operator<<(std::ostream& os, const piet::color& color){
            switch(color.category){
            case piet::color::color_category::COLOR:
                return os<<color.brightness<<" "<<color.hue;
            case piet::color::color_category::BLACK:
                return os<<"BLACK";
            case piet::color::color_category::WHITE:
                return os<<"WHITE";
            }
        }

        bool operator==(const piet::color::color_category& other) const {return category == other;}
        bool operator==(const piet::color& other) const {
            if(category != other.category) return false;
            if(category != piet::color::color_category::COLOR) return true;
            return hue == other.hue && brightness == other.brightness;
        }
    private:
        piet::color::color_category category;
        const hue::hue_trait& hue;
        const brightness::brightness_trait& brightness;
    };
}

#endif //PIET_COLOR_H
