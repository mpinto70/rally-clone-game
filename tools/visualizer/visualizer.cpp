#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/CarMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "util/Wait.h"
#include "util/Util.h"

#include <allegro.h>

#include <cstdio>
#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>

namespace {
constexpr unsigned WINDOW_W = 800;                            ///< map window width
constexpr unsigned WINDOW_H = 400;                            ///< map window height
constexpr unsigned SUB_SIZE = 32;                             ///< size of images
constexpr unsigned IMAGES_X = 30;                             ///< images left position
constexpr unsigned IMAGES_Y = 60;                             ///< images top position
constexpr unsigned TITLE_Y = 40;                              ///< title text top position
constexpr unsigned ARROW_Y = IMAGES_Y + SUB_SIZE + 10;        ///< arrow top position
constexpr unsigned ARROW_H = 10;                              ///< arrow height
constexpr unsigned CURRENT_Y = ARROW_Y + ARROW_H + 10;        ///< current image top position
constexpr unsigned DESCRIPTION_Y = CURRENT_Y + SUB_SIZE + 10; ///< description top position

int ARROW_FG = 0;
int WINDOW_BG = 0;
int TEXT_FG = 0;

struct tile_set_t {
    BITMAP* full_image;
    std::vector<BITMAP*> tiles;
    tile_set_t(BITMAP* img, std::vector<BITMAP*> tls)
          : full_image(img), tiles(std::move(tls)) {}
};

void draw_arrow(BITMAP* canvas,
      const unsigned cur_tile,
      const unsigned gap) {
    const unsigned y = ARROW_Y;
    const unsigned x = IMAGES_X + cur_tile * (SUB_SIZE + gap) + SUB_SIZE / 2;

    rectfill(canvas, x - 1, y, x, y + ARROW_H, ARROW_FG);
    line(canvas, x - 1, y, x - 4, y + 3, ARROW_FG);
    line(canvas, x, y, x + 3, y + 3, ARROW_FG);
}

template <typename MAPPER>
void draw_full_image(BITMAP* canvas, const MAPPER& mapper) {
    textprintf_ex(canvas,
          font,
          IMAGES_X,
          TITLE_Y,
          TEXT_FG,
          WINDOW_BG,
          "number of tiles: %lu",
          mapper.numBmps());
    draw_sprite(canvas, mapper.fullBmp(), IMAGES_X, IMAGES_Y);
}

template <typename MAPPER>
void draw_curr_tile(BITMAP* canvas, const MAPPER& mapper, unsigned cur_tile) {
    const auto type = util::to_Enum<typename MAPPER::enum_type>(cur_tile);
    textprintf_ex(canvas,
          font,
          IMAGES_X,
          DESCRIPTION_Y,
          TEXT_FG,
          WINDOW_BG,
          "current tile: %2u / type: %-30s / tile size: (%2d x %2d)",
          cur_tile,
          to_string(type).c_str(),
          mapper[cur_tile]->w,
          mapper[cur_tile]->h);
    draw_sprite(canvas, mapper[cur_tile], IMAGES_X, CURRENT_Y);
    draw_arrow(canvas, cur_tile, mapper.gap());
}

void exit_visualizer(const std::string& msg) {
    std::cout << msg << std::endl;
    exit(1);
}

void move_right(unsigned& cur_tile, const unsigned max) {
    ++cur_tile;
    if (cur_tile == max)
        cur_tile = 0;
}

void move_left(unsigned& cur_tile, const unsigned max) {
    --cur_tile;
    if (cur_tile > max) // overflow
        cur_tile = max - 1;
}

template <typename MAPPER>
void show(BITMAP* canvas, const MAPPER& mapper) {
    util::Wait wait(50);
    unsigned cur_tile = 0;
    while (!key[KEY_ESC]) {
        rectfill(canvas, 0, 0, WINDOW_W, WINDOW_H, WINDOW_BG);

        int key_wait = 0;
        bool should_wait = false;
        wait.reset();
        if (key[KEY_RIGHT]) {
            move_right(cur_tile, mapper.numBmps());
            should_wait = true;
        } else if (key[KEY_LEFT]) {
            should_wait = true;
            move_left(cur_tile, mapper.numBmps());
        } else if (key[KEY_D]) {
            move_right(cur_tile, mapper.numBmps());
            key_wait = KEY_D;
        } else if (key[KEY_A]) {
            move_left(cur_tile, mapper.numBmps());
            key_wait = KEY_A;
        }

        draw_full_image(canvas, mapper);
        draw_curr_tile(canvas, mapper, cur_tile);

        vsync();
        blit(canvas, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear_bitmap(canvas);

        if (key_wait != 0)
            tools::hold_while_pressed(key_wait);
        else if (should_wait)
            wait.wait();
    }
}

void initialize_colors() {
    ARROW_FG = makecol(0x00, 0x00, 0x00);
    WINDOW_BG = makecol(0xf8, 0xdf, 0xe2);
    TEXT_FG = makecol(0x00, 0x00, 0x00);
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/file> <car|action|tile>");
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

        initialize_colors();

        BITMAP* canvas = create_bitmap(SCREEN_W, SCREEN_H);

        if (type == "car") {
            using gamelib::allegro::bmp::CarMapper;
            const CarMapper mapper(file_name, 32, 32, 1);
            show(canvas, mapper);
        } else if (type == "action") {
            using gamelib::allegro::bmp::ActionMapper;
            const ActionMapper mapper(file_name, 32, 32, 1);
            show(canvas, mapper);
        } else if (type == "tile") {
            using gamelib::allegro::bmp::TileMapper;
            const TileMapper mapper(file_name, 32, 32, 2);
            show(canvas, mapper);
        }

        return 0;
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()
