#include <image.h>

#include <png.h>

bool has_ending (std::string const &full_string, std::string const &ending) {
    if (full_string.length() >= ending.length()) {
        return (0 == full_string.compare (full_string.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

piet::image piet::read_image(const std::string& fname){
    if(has_ending(fname, ".png") || has_ending(fname, ".PNG")) return piet::png_read(fname);
    else return piet::EMPTY_IMAGE;
}

piet::image piet::png_read(const std::string &fname) {
    FILE *fp = fopen(R"(C:\Users\danie\CLionProjects\Piet\samples\Piet_hello.png)", "rb");
    if (!fp){
        std::cerr<<"Can't open file\n";
        return piet::EMPTY_IMAGE;
    }
    png_structp png;
    png_infop info_ptr;
    png_bytep *row_pointers = NULL;
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png == NULL) {
        fclose(fp);
        return piet::EMPTY_IMAGE;
    }

    info_ptr = png_create_info_struct(png);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png, NULL, NULL);
        return piet::EMPTY_IMAGE;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info_ptr, NULL);
        fclose(fp);
        return piet::EMPTY_IMAGE;
    }

    png_init_io(png, fp);

//    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_SWAP_ALPHA | PNG_TRANSFORM_EXPAND, NULL);
    png_infop info = png_create_info_struct(png);
    png_read_info(png, info);

    png_uint_32 width      = png_get_image_width(png, info);
    png_uint_32 height     = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth  = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    if (row_pointers) abort();

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    piet::image img(width, height);
    for(int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            // Do something awesome for each pixel here...
//            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
            img.set_pixel(y, x, px[0], px[1], px[2]);
        }
    }

    return img;
}