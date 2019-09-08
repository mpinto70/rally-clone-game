#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "map/Action.h"
#include "map/Map.h"
#include "map/MapIO.h"
#include "map/TileType.h"
#include "util/Util.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <boost/filesystem.hpp>

#include <cstdio>
#include <cstdlib>
#include <gamelib/allegro/bmp/CarMapper.h>
#include <gamelib/allegro/bmp/FuelMapper.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

namespace {
using gamelib::allegro::bmp::SIZE_MULTIPLIER;
constexpr unsigned TILE_SIZE = 24 * SIZE_MULTIPLIER;                          ///< tile size in pixels
constexpr unsigned FULL_MAP_COLUMNS = 32;                                     ///< full map number of columns
constexpr unsigned FULL_MAP_ROWS = 56;                                        ///< full map number of rows
constexpr unsigned MAP_X = 10;                                                ///< map view left side
constexpr unsigned MAP_Y = 10;                                                ///< map view top side
constexpr unsigned MAP_COLUMNS = 10;                                          ///< map view width in columns
constexpr unsigned MAP_ROWS = 10;                                             ///< map view height in columns
constexpr unsigned MAP_WIDTH = MAP_COLUMNS * TILE_SIZE;                       ///< map view width in pixels
constexpr unsigned MAP_HEIGHT = MAP_ROWS * TILE_SIZE;                         ///< map view height in pixels
constexpr unsigned MINIMAP_X = MAP_X + MAP_WIDTH + 5;                         ///< mini map view left side
constexpr unsigned MINIMAP_Y = MAP_Y;                                         ///< mini map view top side
constexpr unsigned MINIMAP_TILE_SIZE = 10;                                    ///< mini map tile size
constexpr unsigned MINIMAP_WIDTH = FULL_MAP_COLUMNS * MINIMAP_TILE_SIZE + 10; ///< mini map view width
constexpr unsigned MINIMAP_HEIGHT = FULL_MAP_ROWS * MINIMAP_TILE_SIZE + 10;   ///< mini map view height
constexpr unsigned TILES_X = MINIMAP_X;                                       ///< tiles view left side
constexpr unsigned TILES_Y = MINIMAP_Y + MINIMAP_HEIGHT + 5;                  ///< tiles view top side
constexpr unsigned TILES_WIDTH = MINIMAP_WIDTH;                               ///< map view width in pixels
constexpr unsigned TILES_HEIGHT = 7 * TILE_SIZE;                              ///< map view height in pixels
constexpr unsigned ACTIONS_X = MAP_X;                                         ///< actions view left side
constexpr unsigned ACTIONS_Y = MAP_Y + MAP_HEIGHT + 5;                        ///< actions view top side
constexpr unsigned ACTIONS_ROWS = 4;                                          ///< actions view height in columns
constexpr unsigned ACTIONS_WIDTH = MAP_WIDTH;                                 ///< actions view width in pixels
constexpr unsigned ACTIONS_HEIGHT = ACTIONS_ROWS * TILE_SIZE;                 ///< actions view height in pixels
constexpr unsigned HELP_X = MAP_X;                                            ///< help view left side
constexpr unsigned HELP_Y = ACTIONS_Y + ACTIONS_HEIGHT + 5;                   ///< help view top side
constexpr unsigned HELP_ROWS = 6;                                             ///< help view height in columns
constexpr unsigned HELP_WIDTH = MAP_WIDTH;                                    ///< help view width in pixels
constexpr unsigned HELP_HEIGHT = HELP_ROWS * TILE_SIZE;                       ///< help view height in pixels
constexpr unsigned STATUS_X = TILES_X;                                        ///< status view left side
constexpr unsigned STATUS_Y = TILES_Y + TILES_HEIGHT + 5;                     ///< status view top side
constexpr unsigned STATUS_WIDTH = TILES_WIDTH;                                ///< status view width in pixels
constexpr unsigned STATUS_HEIGHT = HELP_Y + HELP_HEIGHT - STATUS_Y;           ///< status view height in pixels
constexpr unsigned WINDOW_W = TILES_X + TILES_WIDTH + 10;                     ///< window width
constexpr unsigned WINDOW_H = HELP_Y + HELP_HEIGHT + 10;                      ///< window height

ALLEGRO_COLOR MAP_FG = {};
ALLEGRO_COLOR TILES_BG = {};
ALLEGRO_COLOR TILES_FG = {};
ALLEGRO_COLOR STATUS_BG = {};
ALLEGRO_COLOR STATUS_FG = {};
ALLEGRO_COLOR ACTION_BG = {};
ALLEGRO_COLOR ACTION_FG = {};
ALLEGRO_COLOR HELP_FG = {};
ALLEGRO_COLOR HELP_BG = {};
ALLEGRO_COLOR WINDOW_BG = {};
ALLEGRO_COLOR MINIMAP_BG = {};
ALLEGRO_COLOR MINIMAP_FG = {};

//void save(const std::string& file_name, const map::Map& stageMap) {
//    map::MapIO::write(file_name, stageMap);
//}

map::Map loadMap(const std::string& file_name) {
    const map::Map stage_map = map::MapIO::read(file_name);
    return stage_map;
}

map::Map createCleanMap() {
    const std::vector<map::Tile> tiles(FULL_MAP_COLUMNS * FULL_MAP_ROWS, map::Tile(map::TileType::GRASS, map::Action::NONE));
    return map::Map(FULL_MAP_COLUMNS, FULL_MAP_ROWS, tiles);
}

map::Map createOrLoadMap(const std::string& stagePath) {
    const std::string tmp = stagePath + "/stage.dat";
    boost::filesystem::path path_to_file(tmp);
    if (boost::filesystem::exists(path_to_file)) {
        return loadMap(tmp);
    } else {
        return createCleanMap();
    }
}

void drawGrid(const map::Map& gameMap,
      const int& x0,
      const int& y0) {
    for (map::map_dimension_t i = 0; i < gameMap.height(); ++i) {
        const int Y = i * TILE_SIZE - y0;
        if (Y > int(MAP_HEIGHT))
            break;
        if (Y < 0)
            continue;
        al_draw_line(0, Y, MAP_WIDTH, Y, MAP_FG, 1);
    }
    for (map::map_dimension_t x = 0; x < gameMap.width(); ++x) {
        const int X = x * TILE_SIZE - x0;
        if (X > int(MAP_WIDTH))
            break;
        if (X < 0)
            continue;

        al_draw_line(X, 0, X, MAP_HEIGHT, MAP_FG, 1);
    }
}

void drawMap(const map::Map& gameMap,
      const gamelib::allegro::bmp::TileMapper& tileMapper,
      const gamelib::allegro::bmp::ActionMapper&,
      const gamelib::allegro::bmp::CarMapper&,
      const gamelib::allegro::bmp::CarMapper&,
      const int& x0,
      const int& y0) {
    al_draw_filled_rectangle(0, 0, MAP_WIDTH, MAP_HEIGHT, MAP_FG);

    const unsigned begin_j = x0 < 0 ? 0 : x0 / (TILE_SIZE);
    const unsigned begin_i = y0 < 0 ? 0 : y0 / (TILE_SIZE);
    for (map::map_dimension_t i = begin_i; i < gameMap.height(); ++i) {
        const int Y = i * TILE_SIZE - y0;
        if (Y > int(MAP_HEIGHT))
            break;
        for (map::map_dimension_t x = begin_j; x < gameMap.width(); ++x) {
            const int X = x * TILE_SIZE - x0;
            if (X > int(MAP_WIDTH))
                break;
            const auto& tile = gameMap(x, i);
            const auto bmp = tileMapper[tile.type()];
            al_draw_bitmap(bmp, X, Y, 0);
        }
    }

    drawGrid(gameMap, x0, y0);
}

void drawMiniMap(const map::Map& gameMap) {
    al_draw_filled_rectangle(0, 0, MINIMAP_WIDTH, MINIMAP_HEIGHT, MINIMAP_BG);
    for (map::map_dimension_t y = 0; y < gameMap.height(); ++y) {
        for (map::map_dimension_t x = 0; x < gameMap.width(); ++x) {
            const auto& tile = gameMap(x, y);
            if (tile.type() == map::TileType::ROAD) {
                const auto X = x * MINIMAP_TILE_SIZE + 5;
                const auto Y = y * MINIMAP_TILE_SIZE + 5;

                al_draw_filled_rectangle(X, Y, X + MINIMAP_TILE_SIZE - 1, Y + MINIMAP_TILE_SIZE - 1, MINIMAP_FG);
            }
        }
    }
}

void drawActions(const gamelib::allegro::bmp::ActionMapper& actionMapper, const ALLEGRO_FONT& font) {
    al_draw_filled_rectangle(0, 0, ACTIONS_WIDTH, ACTIONS_HEIGHT, ACTION_BG);

    unsigned x = 5;
    unsigned y = 5;
    unsigned max_y = 0;
    for (auto e : util::EnumIterator<map::Action>()) {
        const auto action = actionMapper[e];
        const auto width = actionMapper.imageWidth(e);
        const auto height = actionMapper.imageHeight(e);
        if (x + width + 5 > ACTIONS_WIDTH) {
            x = 5;
            y += max_y + 5;
        }
        al_draw_bitmap(action, x, y, 0);
        if (e == map::Action::NONE) {
            al_draw_text(&font, ACTION_FG, x + width / 2, y + height / 2 - 10, ALLEGRO_ALIGN_CENTER, "None");
        }

        x += width + 5;
        max_y = std::max(max_y, height);
    }
}

void drawTiles(const gamelib::allegro::bmp::TileMapper& tilesMapper) {
    al_draw_filled_rectangle(0, 0, TILES_WIDTH, TILES_HEIGHT, TILES_BG);

    unsigned x = 5;
    unsigned y = 5;
    for (auto e : util::EnumIterator<map::TileType>()) {
        const auto tile = tilesMapper[e];
        if (x + TILE_SIZE + 5 > TILES_WIDTH) {
            x = 5;
            y += TILE_SIZE + 5;
        }
        al_draw_bitmap(tile, x, y, 0);

        x += TILE_SIZE + 5;
    }
}

void drawStatus(const ALLEGRO_FONT& font, const int& x0, const int& y0) {
    al_draw_filled_rectangle(0, 0, STATUS_WIDTH, STATUS_HEIGHT, STATUS_BG);

    al_draw_textf(&font, STATUS_FG, 10, 10, 0, "x0: %d", x0);
    al_draw_textf(&font, STATUS_FG, 10, 30, 0, "y0: %d", y0);
}

void drawHelp(const ALLEGRO_FONT& font) {
    al_draw_filled_rectangle(0, 0, HELP_WIDTH, HELP_HEIGHT, HELP_BG);

    const std::vector<std::string> manual = {
        "ESC - closes the editor",
        "Arrows - move map one tile at a time while pressed",
        "W A S D - move map one tile at a time",
        "Left click - select tile or put tile in map",
        "Right click - select action or put action in map",
        "Space - hide tiles and show only actios",
        "I - shows action position interactively (tied to tile)",
        "I+O - shows action position interactively (free positioning)",
        "F - hide action number from tile",
        "G - hide grid",
        "Left Shift - save",
        "Ctrl+C + left click - mark region for copy",
        "Ctrl+V + left click - paste copied region to point",
        "X - cancel region selected"
    };

    constexpr int STEP_Y = 22;
    for (size_t i = 0; i < manual.size(); ++i) {
        const unsigned y = (i + 1) * STEP_Y;

        al_draw_textf(&font, HELP_FG, 20, y, 0, "%s", manual[i].c_str());
    }
}

template <typename F, typename... ARGS>
void drawCanvas(ALLEGRO_BITMAP& canvas, F f, ARGS&... args) {
    al_set_target_bitmap(&canvas);
    f(std::forward<ARGS>(args)...);
}

void loop(map::Map& gameMap,
      const gamelib::allegro::bmp::TileMapper& tileMapper,
      const gamelib::allegro::bmp::ActionMapper& actionMapper,
      const gamelib::allegro::bmp::CarMapper& playerMapper,
      const gamelib::allegro::bmp::CarMapper& enemyMapper,
      const ALLEGRO_FONT& font,
      ALLEGRO_EVENT_QUEUE& event_queue,
      ALLEGRO_DISPLAY& display) {
    using gamelib::allegro::BITMAP_PTR;
    auto mapCanvas = BITMAP_PTR(al_create_bitmap(MAP_WIDTH, MAP_HEIGHT), al_destroy_bitmap);
    auto minimapCanvas = BITMAP_PTR(al_create_bitmap(MINIMAP_WIDTH, MINIMAP_HEIGHT), al_destroy_bitmap);
    auto actionsCanvas = BITMAP_PTR(al_create_bitmap(ACTIONS_WIDTH, ACTIONS_HEIGHT), al_destroy_bitmap);
    auto tilesCanvas = BITMAP_PTR(al_create_bitmap(TILES_WIDTH, TILES_HEIGHT), al_destroy_bitmap);
    auto statusCanvas = BITMAP_PTR(al_create_bitmap(STATUS_WIDTH, STATUS_HEIGHT), al_destroy_bitmap);
    auto helpCanvas = BITMAP_PTR(al_create_bitmap(HELP_WIDTH, HELP_HEIGHT), al_destroy_bitmap);

    drawCanvas(*helpCanvas, drawHelp, font); // this is cached, because it does not change

    enum Keys {
        K_UP,
        K_DOWN,
        K_RIGHT,
        K_LEFT,
        NUMBER_OF_KEYS
    };
    bool keys[NUMBER_OF_KEYS] = {};
    bool done = false;
    bool shouldDraw = true;
    constexpr int MIN_X0 = -10;
    constexpr int MIN_Y0 = -10;
    constexpr int MAX_X0 = (FULL_MAP_COLUMNS - MAP_COLUMNS) * TILE_SIZE + 10;
    constexpr int MAX_Y0 = (FULL_MAP_ROWS - MAP_ROWS) * TILE_SIZE + 10;
    int x0 = MIN_X0, y0 = MIN_Y0;

    ALLEGRO_EVENT ev;
    while (not done) {
        al_wait_for_event(&event_queue, &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                shouldDraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        keys[K_RIGHT] = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[K_LEFT] = true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        keys[K_DOWN] = true;
                        break;
                    case ALLEGRO_KEY_UP:
                        keys[K_UP] = true;
                        break;
                    case ALLEGRO_KEY_D:
                        x0 += TILE_SIZE;
                        break;
                    case ALLEGRO_KEY_A:
                        x0 -= TILE_SIZE;
                        break;
                    case ALLEGRO_KEY_S:
                        y0 += TILE_SIZE;
                        break;
                    case ALLEGRO_KEY_W:
                        y0 -= TILE_SIZE;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_RIGHT:
                        keys[K_RIGHT] = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        keys[K_LEFT] = false;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        keys[K_DOWN] = false;
                        break;
                    case ALLEGRO_KEY_UP:
                        keys[K_UP] = false;
                        break;
                }
                break;
        }

        if (shouldDraw) {
            shouldDraw = false;

            if (keys[K_RIGHT])
                x0 += TILE_SIZE;
            if (keys[K_LEFT])
                x0 -= TILE_SIZE;
            if (keys[K_DOWN])
                y0 += TILE_SIZE;
            if (keys[K_UP])
                y0 -= TILE_SIZE;

            if (x0 > MAX_X0)
                x0 = MAX_X0;
            if (x0 < MIN_X0)
                x0 = MIN_X0;
            if (y0 > MAX_Y0)
                y0 = MAX_Y0;
            if (y0 < MIN_Y0)
                y0 = MIN_Y0;

            drawCanvas(*mapCanvas, drawMap, gameMap, tileMapper, actionMapper, playerMapper, enemyMapper, x0, y0);
            drawCanvas(*minimapCanvas, drawMiniMap, gameMap);
            drawCanvas(*actionsCanvas, drawActions, actionMapper, font);
            drawCanvas(*tilesCanvas, drawTiles, tileMapper);
            drawCanvas(*statusCanvas, drawStatus, font, x0, y0);

            al_set_target_bitmap(al_get_backbuffer(&display));

            al_draw_bitmap(mapCanvas.get(), MAP_X, MAP_Y, 0);
            al_draw_bitmap(minimapCanvas.get(), MINIMAP_X, MINIMAP_Y, 0);
            al_draw_bitmap(actionsCanvas.get(), ACTIONS_X, ACTIONS_Y, 0);
            al_draw_bitmap(tilesCanvas.get(), TILES_X, TILES_Y, 0);
            al_draw_bitmap(statusCanvas.get(), STATUS_X, STATUS_Y, 0);
            al_draw_bitmap(helpCanvas.get(), HELP_X, HELP_Y, 0);

            al_flip_display();
            al_clear_to_color(WINDOW_BG);
        }
    }
}

void initialize_colors() {
    MAP_FG = al_map_rgb(0xff, 0xff, 0xff);
    TILES_BG = al_map_rgb(0x2e, 0x62, 0x76);
    TILES_FG = al_map_rgb(0xe7, 0xf6, 0xf8);
    STATUS_BG = al_map_rgb(0xf8, 0xdf, 0xe2);
    STATUS_FG = al_map_rgb(0x8b, 0x13, 0x03);
    ACTION_BG = al_map_rgb(0x4d, 0x80, 0x55);
    ACTION_FG = al_map_rgb(0xec, 0xf3, 0xec);
    HELP_FG = al_map_rgb(0x1a, 0x44, 0x80);
    HELP_BG = al_map_rgb(0xd9, 0xe8, 0xf6);
    MINIMAP_BG = al_map_rgb(0x16, 0x2e, 0x51);
    MINIMAP_FG = al_map_rgb(0xff, 0xbf, 0x00);
    WINDOW_BG = al_map_rgb(0x3d, 0x45, 0x51);
}
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <path to stages> <path to sprites>\n";
        return -1;
    }

    const std::string stagePath = argv[1];
    const std::string spritePath = argv[2];

    try {
        if (not al_init())
            tools::throw_allegro_error("could not init Allegro");

        al_init_font_addon();
        al_init_ttf_addon();
        al_init_primitives_addon();
        al_init_image_addon();
        al_install_keyboard();

        map::Map gameMap = createOrLoadMap(stagePath);

        const auto tileMapper = [=]() {
            using gamelib::allegro::bmp::createTileMapper;
            using gamelib::allegro::bmp::TileMapper;
            using gamelib::allegro::bmp::TileSource;
            return createTileMapper(spritePath, TileSource::BROWN);
        }();

        const auto actionMapper = [=]() {
            using gamelib::allegro::bmp::ActionMapper;
            using gamelib::allegro::bmp::createActionMapper;
            return createActionMapper(spritePath);
        }();

        auto createCarMapper = [=](gamelib::allegro::bmp::CarSource carSource) {
            using gamelib::allegro::bmp::CarMapper;
            using gamelib::allegro::bmp::CarSource;
            return gamelib::allegro::bmp::createCarMapper(spritePath, carSource);
        };
        const auto playerMapper = createCarMapper(gamelib::allegro::bmp::CarSource::PLAYER_1);
        const auto enemyMapper = createCarMapper(gamelib::allegro::bmp::CarSource::ENEMY_1);

        auto display = gamelib::allegro::DISPLAY_PTR(al_create_display(WINDOW_W, WINDOW_H), al_destroy_display);
        if (display == nullptr)
            tools::throw_allegro_error("could not create display");

        auto timer = gamelib::allegro::TIMER_PTR(al_create_timer(1.0 / 30.0), al_destroy_timer);
        if (timer == nullptr)
            tools::throw_allegro_error("could not create timer");

        initialize_colors();

        auto font = gamelib::allegro::FONT_PTR(al_load_font("./Stuff/font.ttf", 20, 0), al_destroy_font);
        if (font == nullptr)
            tools::throw_allegro_error("could not load font");

        auto event_queue = gamelib::allegro::EVENT_QUEUE_PTR(al_create_event_queue(), al_destroy_event_queue);
        if (event_queue == nullptr)
            tools::throw_allegro_error("could not create event queue");

        al_register_event_source(event_queue.get(), al_get_keyboard_event_source());
        al_register_event_source(event_queue.get(), al_get_display_event_source(display.get()));
        al_register_event_source(event_queue.get(), al_get_timer_event_source(timer.get()));

        al_start_timer(timer.get());

        loop(gameMap, tileMapper, actionMapper, playerMapper, enemyMapper, *font, *event_queue, *display);
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
