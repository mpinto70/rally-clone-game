#include "../tools/util/helpers.h"

#include "gamelib/allegro/AllegroUtil.h"
#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/CarMapper.h"
#include "gamelib/allegro/bmp/MiniMapMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "util/Util.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <util/Singleton.h>
#include <gamelib/allegro/Graphic.h>

namespace {
constexpr unsigned WINDOW_W = 800; ///< map window width
constexpr unsigned WINDOW_H = 800; ///< map window height
constexpr unsigned IMAGES_X = 30;  ///< images left position
constexpr unsigned IMAGES_Y = 60;  ///< images top position
constexpr unsigned IMAGES_DY = 30; ///< vertical distance of images that don't feet the window
constexpr unsigned TITLE_Y = 30;   ///< title text top position
constexpr unsigned IMAGE_GAP = 1;  ///< distance between images

ALLEGRO_COLOR ARROW_FG = {};
ALLEGRO_COLOR WINDOW_BG = {};
ALLEGRO_COLOR TEXT_FG = {};
ALLEGRO_COLOR FRAME_FG = {};
enum KEY {
    LEFT,
    RIGHT,
    NUM_KEYS,
};

bool keys[NUM_KEYS] = {};

struct ImagePosition {
    unsigned x, y, maxY;
};

template <typename MAPPER>
ImagePosition position(const MAPPER& mapper, unsigned cur_tile) {
    auto x = IMAGES_X;
    auto y = IMAGES_Y;
    unsigned max_y = mapper.imageHeight(0);
    using enum_type = typename MAPPER::enum_type;
    for (auto i = util::from_Enum<size_t>(enum_type::FIRST); i <= cur_tile; ++i) {
        if (x + mapper.imageWidth(i) + IMAGES_X + IMAGE_GAP > WINDOW_W) {
            x = IMAGES_X;
            y += max_y + IMAGES_DY;
            max_y = mapper.imageHeight(i);
        }
        if (i == cur_tile)
            break;

        x += mapper.imageWidth(i) + IMAGE_GAP;
        max_y = std::max(max_y, mapper.imageHeight(i));
    }

    return ImagePosition{ x, y, max_y };
}

template <typename MAPPER>
void draw_arrow(const MAPPER& mapper, unsigned cur_tile) {
    auto pos = position(mapper, cur_tile);
    auto x = pos.x + mapper.imageWidth(cur_tile) / 2;
    auto y = pos.y + mapper.imageHeight(cur_tile) + 2;

    al_draw_filled_triangle(x, y, x - 5, y + 5, x + 5, y + 5, ARROW_FG);
}

template <typename MAPPER>
void draw_full_image(const MAPPER& mapper, const ALLEGRO_FONT* font) {
    al_draw_textf(font, TEXT_FG, IMAGES_X, TITLE_Y, 0, "number of tiles: %lu", mapper.numImages());

    using enum_type = typename MAPPER::enum_type;
    for (auto i = util::from_Enum<size_t>(enum_type::FIRST); i < util::from_Enum<size_t>(enum_type::LAST); ++i) {
        const auto pos = position(mapper, i);
        const auto x = pos.x;
        const auto y = pos.y;

        al_draw_rectangle(x, y, x + mapper.imageWidth(i) + 1, y + mapper.imageHeight(i) + 1, FRAME_FG, 1);
        al_draw_bitmap(mapper[i], x, y, 0);
    }
}

template <typename MAPPER>
void draw_curr_tile(const MAPPER& mapper, const ALLEGRO_FONT* font, unsigned cur_tile) {
    const auto pos = position(mapper, mapper.numImages() - 1);
    auto y = pos.y + pos.maxY + IMAGES_DY;

    al_draw_bitmap(mapper[cur_tile], IMAGES_X, y, 0);

    y += pos.maxY + IMAGES_DY;

    const auto type = util::to_Enum<typename MAPPER::enum_type>(cur_tile);
    al_draw_textf(font,
          TEXT_FG,
          IMAGES_X,
          y,
          0,
          "current tile: %2u / tile size: (%u x %u) / type: %s",
          cur_tile,
          mapper.imageWidth(cur_tile),
          mapper.imageHeight(cur_tile),
          to_string(type).c_str());

    draw_arrow(mapper, cur_tile);
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
void show(const MAPPER& mapper,
      const ALLEGRO_FONT* font,
      ALLEGRO_EVENT_QUEUE* event_queue) {
    unsigned cur_tile = 0;
    bool done = false;
    bool draw = true;
    ALLEGRO_EVENT ev;
    while (not done) {
        al_wait_for_event(event_queue, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                draw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = true;
                        break;
                    case ALLEGRO_KEY_D:
                        move_right(cur_tile, mapper.numImages());
                        break;
                    case ALLEGRO_KEY_A:
                        move_left(cur_tile, mapper.numImages());
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = false;
                        break;
                }
                break;
        }

        if (draw) {
            draw = false;
            if (keys[RIGHT])
                move_right(cur_tile, mapper.numImages());
            if (keys[LEFT])
                move_left(cur_tile, mapper.numImages());

            draw_full_image(mapper, font);
            draw_curr_tile(mapper, font, cur_tile);

            al_flip_display();
            al_clear_to_color(WINDOW_BG);
        }
    }
}

void initialize_colors() {
    ARROW_FG = al_map_rgb(0x00, 0x00, 0x00);
    WINDOW_BG = al_map_rgb(0xf8, 0xdf, 0xe2);
    TEXT_FG = al_map_rgb(0x00, 0x00, 0x00);
    FRAME_FG = al_map_rgb(0xff, 0x00, 0x00);
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/root> <car|action|tile|minimap>\n");
        }

        const std::string filePath = argv[1];
        const std::string type = argv[2];

        using gamelib::allegro::Graphic;
        util::Singleton<Graphic>::create(std::make_unique<Graphic>(filePath, WINDOW_W, WINDOW_H));
        auto &graphic = util::Singleton<Graphic>::instance();

        initialize_colors();

        auto timer = gamelib::allegro::TIMER_PTR(al_create_timer(1.0 / 30.0), al_destroy_timer);
        if (timer == nullptr)
            tools::throw_allegro_error("could not create timer");


        al_register_event_source(graphic.eventQueue().get(), al_get_timer_event_source(timer.get()));

        al_start_timer(timer.get());
        if (type == "car") {
            show(graphic.carMapper(), graphic.fontSystem().get(), graphic.eventQueue().get());
        } else if (type == "minimap") {
            using gamelib::allegro::bmp::createMiniMapMapper;
            using gamelib::allegro::bmp::MiniMapMapper;
            const auto mapper = createMiniMapMapper(graphic.fullImage());
            show(mapper, graphic.fontSystem().get(), graphic.eventQueue().get());
        } else if (type == "action") {
            show(graphic.actionMapper(), graphic.fontSystem().get(), graphic.eventQueue().get());
        } else if (type == "tile") {
            show(graphic.tileMapper(), graphic.fontSystem().get(), graphic.eventQueue().get());
        }

        al_stop_timer(timer.get());

        return 0;
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
