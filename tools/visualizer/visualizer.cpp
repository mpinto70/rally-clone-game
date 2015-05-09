
#include "../tools/util/helpers.h"
#include "gamelib/allegro/bmp/CCarMapper.h"
#include "gamelib/allegro/bmp/CActionMapper.h"
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

template <typename MAPPER>
void show(MAPPER & mapper,
                BITMAP * canvas) {
    util::CWait wait(50);
    util::CWait miniWait(10);
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
        draw_full_image(canvas, mapper.fullBmp(), X_IMAGES, 60);
        draw_tile(canvas, mapper[cur_tile], X_IMAGES, 150);

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

int main(int argc, char *argv[]) {
    try {
        if (argc != 4) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/file.png> <width of image> <car|action>");
        }

        const std::string file_name = argv[1];
        const unsigned width_of_image = std::stoul(argv[2]);
        const std::string type = argv[3];

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_W, WINDOW_H, 0, 0) != 0)
            tools::throw_allegro_error("set_gfx_mode");

        BITMAP * canvas    = create_bitmap(SCREEN_W, SCREEN_H);

        if (type == "car") {
            gamelib::allegro::bmp::CCarMapper carMapper(argv[1], width_of_image, width_of_image, 1);
            show(carMapper, canvas);
        } else if (type == "action") {
            gamelib::allegro::bmp::CActionMapper actionMapper(argv[1], width_of_image, width_of_image, 1);
            show(actionMapper, canvas);
        }

        return 0;
    } catch (std::exception & e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()

