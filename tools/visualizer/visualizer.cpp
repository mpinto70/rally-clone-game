
#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/CarMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "util/Wait.h"

#include <allegro.h>

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

static constexpr unsigned WINDOW_W = 800; ///< map window width
static constexpr unsigned WINDOW_H = 400; ///< map window height
static constexpr unsigned SUB_SIZE = 32;  ///< size of images
static constexpr unsigned X_IMAGES = 30;
static constexpr unsigned Y_FULL = 60;
static constexpr unsigned Y_SUB = 150;

struct tile_set_t {
    BITMAP* full_image;
    std::vector<BITMAP*> tiles;
    tile_set_t(BITMAP* img, const std::vector<BITMAP*>& tls)
          : full_image(img), tiles(tls) {}
};

static void draw_arrow(BITMAP* canvas,
      const unsigned cur_tile,
      const unsigned gap) {
    const unsigned y = Y_FULL + SUB_SIZE + 2 * gap + 4;
    const unsigned x = X_IMAGES + cur_tile * (SUB_SIZE + gap) + SUB_SIZE / 2;
    const int color = makecol(0x00, 0x00, 0x00);

    rectfill(canvas, x - 1, y, x, y + 10, color);
    line(canvas, x - 1, y, x - 4, y + 3, color);
    line(canvas, x, y, x + 3, y + 3, color);
}

static void exit_visualizer(const std::string& msg) {
    std::cout << msg << std::endl;
    exit(1);
}

static void move_right(unsigned& cur_tile, const unsigned max) {
    ++cur_tile;
    if (cur_tile == max)
        cur_tile = 0;
}

static void move_left(unsigned& cur_tile, const unsigned max) {
    --cur_tile;
    if (cur_tile > max) // overflow
        cur_tile = max - 1;
}

template <typename MAPPER>
void show(BITMAP* canvas,
      const std::string& file_name,
      unsigned gap_size) {
    const MAPPER mapper(file_name, 32, 32, gap_size);
    util::Wait wait(50);
    util::Wait miniWait(10);
    unsigned cur_tile = 0;
    const int bg = makecol(0xDE, 0x97, 0x47);
    while (!key[KEY_ESC]) {
        miniWait.reset();
        rectfill(canvas, 0, 0, WINDOW_W, WINDOW_H, bg);

        int keyWait = 0;
        bool shouldWait = false;
        wait.reset();
        if (key[KEY_RIGHT]) {
            move_right(cur_tile, mapper.numBmps());
            shouldWait = true;
        } else if (key[KEY_LEFT]) {
            shouldWait = true;
            move_left(cur_tile, mapper.numBmps());
        } else if (key[KEY_D]) {
            move_right(cur_tile, mapper.numBmps());
            keyWait = KEY_D;
        } else if (key[KEY_A]) {
            move_left(cur_tile, mapper.numBmps());
            keyWait = KEY_A;
        }

        textprintf_ex(canvas,
              font,
              X_IMAGES,
              40,
              0,
              bg,
              "number of tiles: %lu / tile size: (%02d x %02d)",
              mapper.numBmps(),
              mapper[cur_tile]->w,
              mapper[cur_tile]->h);
        draw_sprite(canvas, mapper.fullBmp(), X_IMAGES, Y_FULL);
        draw_sprite(canvas, mapper[cur_tile], X_IMAGES, Y_SUB);
        draw_arrow(canvas, cur_tile, gap_size);

        vsync();
        blit(canvas, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear_bitmap(canvas);

        if (keyWait != 0)
            tools::hold_while_pressed(keyWait);
        else if (shouldWait)
            wait.wait();

        miniWait.wait();
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/file.png> <car|action|tile>");
        }

        const std::string file_name = argv[1];
        const std::string type = argv[2];

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_W, WINDOW_H, 0, 0) != 0)
            tools::throw_allegro_error("set_gfx_mode");

        BITMAP* canvas = create_bitmap(SCREEN_W, SCREEN_H);

        if (type == "car") {
            show<gamelib::allegro::bmp::CarMapper>(canvas, file_name, 1);
        } else if (type == "action") {
            show<gamelib::allegro::bmp::ActionMapper>(canvas, file_name, 1);
        } else if (type == "tile") {
            show<gamelib::allegro::bmp::TileMapper>(canvas, file_name, 2);
        }

        return 0;
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()
