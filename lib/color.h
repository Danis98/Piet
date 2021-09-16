#ifndef PIET_COLOR_H
#define PIET_COLOR_H

#include <array>
#include <vector>
#include <typeinfo>
#include <memory>
#include <cassert>

namespace color{
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

        color_trait(const color::color_trait<T, value_names_list...>& trait) = delete;
        color_trait(color::color_trait<T, value_names_list...>&& trait) = delete;
        void operator=(const color::color_trait<T, value_names_list...>& trait) = delete;
        void operator=(color::color_trait<T, value_names_list...>&& trait) = delete;
        ~color_trait(){ std::cout<<"Destroying "<<*this<<std::endl; }

        static const color_trait<T, value_names_list...>& get_instance(unsigned int idx){
            if(instances.empty()){
                auto idx_seq = std::make_index_sequence<sizeof...(value_names_list)>();
                populate_instances(idx_seq);
            }
            color_trait<T, value_names_list...> *raw_ptr = instances[idx].get();
            return *raw_ptr;
        }

        unsigned int operator-(const color::color_trait<T, value_names_list...>& other) const{
            constexpr unsigned int num_values = sizeof...(value_names_list);
            int diff = index - other.index;
            return (diff + num_values) % num_values;
        }

        friend std::ostream& operator<<(std::ostream& os, const color::color_trait<T, value_names_list...>& trait){
            return os<<trait.value_names[trait.index];
        }

        bool operator==(const color::color_trait<T, value_names_list...>& other) const {return index == other.index;}
    };

    template<printable T, T ...value_names_list>
    std::vector<std::shared_ptr<color_trait<T, value_names_list...>>> color_trait<T, value_names_list...>::instances{};

}

namespace hue{
    constexpr char STR_RED[] = "RED";
    constexpr char STR_YELLOW[] = "YELLOW";
    constexpr char STR_GREEN[] = "GREEN";
    constexpr char STR_CYAN[] = "CYAN";
    constexpr char STR_BLUE[] = "BLUE";
    constexpr char STR_MAGENTA[] = "MAGENTA";

    using hue_type = color::color_trait<const char*,
        hue::STR_RED,
        hue::STR_YELLOW,
        hue::STR_GREEN,
        hue::STR_CYAN,
        hue::STR_BLUE,
        hue::STR_MAGENTA>;

    constexpr int NUM_HUES = 6;

    const hue::hue_type& RED     = hue_type::get_instance(0);
    const hue::hue_type& YELLOW  = hue_type::get_instance(1);
    const hue::hue_type& GREEN   = hue_type::get_instance(2);
    const hue::hue_type& CYAN    = hue_type::get_instance(3);
    const hue::hue_type& BLUE    = hue_type::get_instance(4);
    const hue::hue_type& MAGENTA = hue_type::get_instance(5);
}

namespace brightness{
    constexpr char STR_DARK[] = "DARK";
    constexpr char STR_NORMAL[] = "NORMAL";
    constexpr char STR_BRIGHT[] = "BRIGHT";

    using brightness_type = color::color_trait<const char*,
        brightness::STR_DARK,
        brightness::STR_NORMAL,
        brightness::STR_BRIGHT>;

    constexpr int NUM_BRIGHTNESS = 3;

    const brightness::brightness_type& DARK      = brightness::brightness_type::get_instance(0);
    const brightness::brightness_type& NORMAL    = brightness::brightness_type::get_instance(1);
    const brightness::brightness_type& BRIGHT    = brightness::brightness_type::get_instance(2);
}

namespace color{

    class color_type{
    public:
        enum class color_category_type{ WHITE, BLACK, COLOR };

        color_type(const hue::hue_type& hue,
                   const brightness::brightness_type& brightness):
            category(color::color_type::color_category_type::COLOR),
            hue(hue),
            brightness(brightness){}
        color_type(color::color_type::color_category_type category):
            category(category),
            hue(hue::hue_type::get_instance(0)),
            brightness(brightness::brightness_type::get_instance(0)){
            assert(category != color::color_type::color_category_type::COLOR);
        }

        friend std::ostream& operator<<(std::ostream& os, const color::color_type& color){
            switch(color.category){
            case color::color_type::color_category_type::COLOR:
                return os<<color.brightness<<" "<<color.hue;
            case color::color_type::color_category_type::BLACK:
                return os<<"BLACK";
            case color::color_type::color_category_type::WHITE:
                return os<<"WHITE";
            }
        }

        bool operator==(const color::color_type::color_category_type& other) const {return category == other;}
        bool operator==(const color::color_type& other) const {
            if(category != other.category) return false;
            if(category != color::color_type::color_category_type::COLOR) return true;
            return hue == other.hue && brightness == other.brightness;
        }
    private:
        color::color_type::color_category_type category;
        const hue::hue_type& hue;
        const brightness::brightness_type& brightness;
    };
}

#endif //PIET_COLOR_H
