
#include "../tools/util/helpers.h"
#include "util/CWait.h"

#include <allegro.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

static constexpr unsigned WINDOW_W  = 500;  ///< map window width
static constexpr unsigned WINDOW_H  = 400;  ///< map window height
static constexpr unsigned X_IMAGES  = 30;

struct tile_set_t {
    BITMAP * full_image;
    std::vector<BITMAP*> tiles;
    tile_set_t(BITMAP * img, const std::vector<BITMAP*> & tls) : full_image(img), tiles(tls) {}
};

static void draw_full_image(BITMAP * canvas, BITMAP * img, unsigned x, unsigned y) {
    draw_sprite(canvas, img, x, y);
}

/// loads all tiles from file.
static tile_set_t load_images(const std::string & full_path,
                              const unsigned tile_width) {
    BITMAP * full_image = load_bitmap(full_path.c_str(), nullptr);

    if (full_image == nullptr) {
        tools::throw_allegro_error("could not load " + full_path);
    }

    const unsigned w = full_image->w;
    const unsigned h = full_image->h;
    constexpr unsigned GAP = 1;
    const unsigned tile_height = h - 2 * GAP;
    if ((w - GAP) % (tile_width + GAP) != 0)
        tools::throw_allegro_error("The image (" + full_path + " - " + std::to_string(w) + ") has not space for images of size (" + std::to_string(tile_width) + ")");

    const unsigned num_tiles = (w - GAP) / (tile_width + GAP);

    std::vector<BITMAP *> tiles;
    for (unsigned x = 1, i = 0; i < num_tiles; ++i, x += tile_width + GAP) {
        // Um subbitmap meio que compartilha a mem�ria do bitmap pai.
        BITMAP * sub = create_sub_bitmap(full_image, x, GAP, tile_width, tile_height);
        if (sub == nullptr)
            tools::throw_allegro_error(full_path + " " + std::to_string(x));
        tiles.push_back(sub);
    }

    printf("TILESET loaded! w = %d h = %d num_tiles = %d tiles = %lu\n", w, h, num_tiles, tiles.size());
    return tile_set_t(full_image, tiles);
}

static void draw_tile(BITMAP * canvas,
                      BITMAP * tile,
                      const int x,
                      const int y) {
    draw_sprite(canvas, tile, x, y);
}


static void exit_visualizer(const std::string & msg) {
    std::cout << msg << std::endl;
    exit(1);
}

static void move_right(unsigned & cur_tile, const unsigned max) {
    ++cur_tile;
    if (cur_tile == max)
        cur_tile = 0;
}

static void move_left(unsigned & cur_tile, const unsigned max) {
    --cur_tile;
    if (cur_tile > max) // overflow
        cur_tile = max - 1;
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/file.png> <width of image>");
        }

        const std::string file_name = argv[1];
        const unsigned width_of_image = std::stoul(argv[2]);

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_W, WINDOW_H, 0, 0) != 0)
            tools::throw_allegro_error("set_gfx_mode");

        BITMAP * canvas    = create_bitmap(SCREEN_W, SCREEN_H);

        auto set = load_images(argv[1], width_of_image);

        //exit_visualizer("leaving for no reason");

        util::CWait wait(50);
        unsigned cur_tile = 0;
        const int bg = makecol(0xDE, 0x97, 0x47);
        while (!key[KEY_ESC]) {
            rectfill(canvas, 0, 0, WINDOW_W, WINDOW_H, bg);
            textprintf_ex(canvas, font, X_IMAGES, 40, 0, bg, "number of tiles: %lu / tile size: (%02d x %02d)", set.tiles.size(), set.tiles[cur_tile]->w, set.tiles[cur_tile]->h);
            draw_full_image(canvas, set.full_image, X_IMAGES, 60);
            draw_tile(canvas, set.tiles[cur_tile], X_IMAGES, 150);
            vsync();
            blit(canvas, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            clear_bitmap(canvas);

            wait.reset();
            if (key[KEY_RIGHT]) {
                move_right(cur_tile, set.tiles.size());
                wait.wait();
            } else if (key[KEY_LEFT]) {
                move_left(cur_tile, set.tiles.size());
                wait.wait();
            } else if (key[KEY_D]) {
                move_right(cur_tile, set.tiles.size());
                tools::hold_while_pressed(KEY_D);
            } else if (key[KEY_A]) {
                move_left(cur_tile, set.tiles.size());
                tools::hold_while_pressed(KEY_A);
            }
        }

        return 0;
    } catch (std::exception & e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()

