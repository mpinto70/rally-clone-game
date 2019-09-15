#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "map/Action.h"
#include "map/Map.h"
#include "map/MapIO.h"
#include "map/TileType.h"
#include "util/Singleton.h"
#include "util/Util.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <boost/filesystem.hpp>

#include <cstdio>
#include <gamelib/allegro/Graphic.h>
#include <gamelib/allegro/bmp/CarMapper.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

namespace {
using gamelib::allegro::bmp::TILE_SIZE;
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
constexpr unsigned ACTIONS_X = MINIMAP_X;                                     ///< tiles view left side
constexpr unsigned ACTIONS_Y = MINIMAP_Y + MINIMAP_HEIGHT + 5;                ///< tiles view top side
constexpr unsigned ACTIONS_WIDTH = MINIMAP_WIDTH;                             ///< map view width in pixels
constexpr unsigned ACTIONS_HEIGHT = 4 * TILE_SIZE;                            ///< map view height in pixels
constexpr unsigned TILES_X = MAP_X;                                           ///< actions view left side
constexpr unsigned TILES_Y = MAP_Y + MAP_HEIGHT + 5;                          ///< actions view top side
constexpr unsigned TILES_ROWS = 7;                                            ///< actions view height in columns
constexpr unsigned TILES_WIDTH = MAP_WIDTH;                                   ///< actions view width in pixels
constexpr unsigned TILES_HEIGHT = TILES_ROWS * TILE_SIZE;                     ///< actions view height in pixels
constexpr unsigned HELP_X = MAP_X;                                            ///< help view left side
constexpr unsigned HELP_Y = TILES_Y + TILES_HEIGHT + 5;                       ///< help view top side
constexpr unsigned HELP_LINES = 16;                                           ///< help view height in columns
constexpr unsigned HELP_WIDTH = MAP_WIDTH + MINIMAP_WIDTH + 5;                ///< help view width in pixels
constexpr unsigned HELP_HEIGHT = HELP_LINES * 22;                             ///< help view height in pixels
constexpr unsigned STATUS_X = ACTIONS_X;                                      ///< status view left side
constexpr unsigned STATUS_Y = ACTIONS_Y + ACTIONS_HEIGHT + 5;                 ///< status view top side
constexpr unsigned STATUS_WIDTH = ACTIONS_WIDTH;                              ///< status view width in pixels
constexpr unsigned STATUS_HEIGHT = HELP_Y - STATUS_Y - 5;                     ///< status view height in pixels
constexpr unsigned WINDOW_W = ACTIONS_X + ACTIONS_WIDTH + 10;                 ///< window width
constexpr unsigned WINDOW_H = HELP_Y + HELP_HEIGHT + 10;                      ///< window height

ALLEGRO_COLOR MAP_FG = {};
ALLEGRO_COLOR TILES_BG = {};
ALLEGRO_COLOR TILES_FG = {};
ALLEGRO_COLOR STATUS_BG = {};
ALLEGRO_COLOR STATUS_FG = {};
ALLEGRO_COLOR ACTIONS_BG = {};
ALLEGRO_COLOR ACTIONS_FG = {};
ALLEGRO_COLOR HELP_FG = {};
ALLEGRO_COLOR HELP_BG = {};
ALLEGRO_COLOR WINDOW_BG = {};
ALLEGRO_COLOR MINIMAP_BG = {};
ALLEGRO_COLOR MINIMAP_FG = {};
ALLEGRO_COLOR SELECTION_FG = {};

map::Action selectedAction = map::Action::NONE;
map::TileType selectedTile = map::TileType::ROAD;

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

map::Map createOrLoadMap(const std::string& mapPath) {
    boost::filesystem::path path_to_file(mapPath);
    if (boost::filesystem::exists(path_to_file)) {
        return loadMap(mapPath);
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

void drawMap(const map::Map& gameMap, const int& x0, const int& y0) {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    al_draw_filled_rectangle(0, 0, MAP_WIDTH, MAP_HEIGHT, MAP_FG);

    const unsigned begin_j = x0 < 0 ? 0 : x0 / (TILE_SIZE);
    const unsigned begin_i = y0 < 0 ? 0 : y0 / (TILE_SIZE);
    for (map::map_dimension_t i = begin_i; i < gameMap.height(); ++i) {
        const int Y = i * TILE_SIZE - y0;
        if (Y > int(MAP_HEIGHT))
            break;
        for (map::map_dimension_t j = begin_j; j < gameMap.width(); ++j) {
            const int X = j * TILE_SIZE - x0;
            if (X > int(MAP_WIDTH))
                break;
            const auto& tile = gameMap(j, i);
            const auto bmp = graphic.tileMapper()[tile.type()];
            al_draw_bitmap(bmp, X, Y, 0);
            if (tile.action() != map::Action::NONE) {
                auto actionImg = graphic.actionMapper()[tile.action()];
                const int XA = X + (TILE_SIZE - graphic.actionMapper().imageWidth(tile.action())) / 2;
                const int YA = Y + (TILE_SIZE - graphic.actionMapper().imageHeight(tile.action())) / 2;
                al_draw_bitmap(actionImg, XA, YA, 0);
            }
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

                al_draw_filled_rectangle(X, Y, X + MINIMAP_TILE_SIZE, Y + MINIMAP_TILE_SIZE, MINIMAP_FG);
            }
        }
    }
}

void drawActions() {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    al_draw_filled_rectangle(0, 0, ACTIONS_WIDTH, ACTIONS_HEIGHT, ACTIONS_BG);

    unsigned x = 5;
    unsigned y = 5;
    unsigned max_y = 0;
    for (auto e : util::EnumIterator<map::Action>()) {
        const auto action = graphic.actionMapper()[e];
        const auto width = graphic.actionMapper().imageWidth(e);
        const auto height = graphic.actionMapper().imageHeight(e);
        if (x + width + 5 > ACTIONS_WIDTH) {
            x = 5;
            y += max_y + 5;
        }
        al_draw_bitmap(action, x, y, 0);
        if (e == map::Action::NONE) {
            al_draw_text(&graphic.fontSystem(), ACTIONS_FG, x + width / 2, y + height / 2 - 10, ALLEGRO_ALIGN_CENTER, "None");
        }

        if (e == selectedAction) {
            al_draw_rectangle(x - 1, y - 1, x + width + 1, y + height + 1, SELECTION_FG, 2);
        }

        x += width + 5;
        max_y = std::max(max_y, height);
    }
}

void drawTiles() {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    al_draw_filled_rectangle(0, 0, TILES_WIDTH, TILES_HEIGHT, TILES_BG);

    unsigned x = 5;
    unsigned y = 5;
    for (auto e : util::EnumIterator<map::TileType>()) {
        const auto tile = graphic.tileMapper()[e];
        if (x + TILE_SIZE + 5 > TILES_WIDTH) {
            x = 5;
            y += TILE_SIZE + 5;
        }
        al_draw_bitmap(tile, x, y, 0);

        if (e == selectedTile) {
            al_draw_rectangle(x - 1, y - 1, x + TILE_SIZE + 1, y + TILE_SIZE + 1, SELECTION_FG, 2);
        }
        x += TILE_SIZE + 5;
    }
}

void drawStatus(const std::vector<std::string>& lines) {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    al_draw_filled_rectangle(0, 0, STATUS_WIDTH, STATUS_HEIGHT, STATUS_BG);

    int y = 10;
    for (const auto& line : lines) {
        al_draw_textf(&graphic.fontSystem(), STATUS_FG, 10, y, 0, "%s", line.c_str());
        y += 20;
    }
}

void drawHelp() {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    al_draw_filled_rectangle(0, 0, HELP_WIDTH, HELP_HEIGHT, HELP_BG);

    const std::vector<std::string> manual = {
        "ESC - closes the editor",
        "Arrows - move map one tile at a time while pressed",
        "W A S D - move map one tile at a time",
        "Left click - select tile or put tile in map",
        "Right click - select action or put action in map",
        "Space - hide tiles and show only actions",
        "G - hide grid",
        "R - save",
        "T - adjust tiles",
        "Ctrl+C + left click - mark region for copy",
        "Ctrl+V + left click - paste copied region to point",
        "X - cancel region selected"
    };

    constexpr int STEP_Y = 22;
    for (size_t i = 0; i < manual.size(); ++i) {
        const unsigned y = (i + 1) * STEP_Y;

        al_draw_textf(&graphic.fontSystem(), HELP_FG, 20, y, 0, "%s", manual[i].c_str());
    }
}

template <typename F, typename... ARGS>
void drawCanvas(ALLEGRO_BITMAP& canvas, F f, ARGS&&... args) {
    al_set_target_bitmap(&canvas);
    f(std::forward<ARGS>(args)...);
}

constexpr bool inRectangle(int x, int y, int x0, int y0, int x1, int y1) {
    return x >= x0 && x <= x1 && y >= y0 && y <= y1;
}

void handleLeftClickInTiles(const int X, const int Y) {
    int x = 5;
    int y = 5;
    for (auto e : util::EnumIterator<map::TileType>()) {
        if (x + TILE_SIZE + 5 > TILES_WIDTH) {
            x = 5;
            y += TILE_SIZE + 5;
        }
        if (inRectangle(X, Y, x, y, x + TILE_SIZE, y + TILE_SIZE)) {
            selectedTile = e;
            return;
        }

        x += TILE_SIZE + 5;
    }
}

void handleRightClickInActions(const int X, const int Y) {
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    unsigned x = 5;
    unsigned y = 5;
    unsigned max_y = 0;
    for (auto e : util::EnumIterator<map::Action>()) {
        const auto width = graphic.actionMapper().imageWidth(e);
        const auto height = graphic.actionMapper().imageHeight(e);
        if (x + width + 5 > ACTIONS_WIDTH) {
            x = 5;
            y += max_y + 5;
        }
        if (inRectangle(X, Y, x, y, x + width, y + height)) {
            selectedAction = e;
            return;
        }

        x += width + 5;
        max_y = std::max(max_y, height);
    }
}

void handleLeftClickInMap(map::Map& gameMap, int x, int y) {
    const int j = x / TILE_SIZE;
    const int i = y / TILE_SIZE;

    if (j < 0 || i < 0 || j >= int(gameMap.width()) || i >= int(gameMap.height()))
        return;

    if (gameMap(j, i).type() != selectedTile) {
        gameMap(j, i) = map::Tile(selectedTile);
    }
}

void handleRightClickInMap(map::Map& gameMap, int x, int y) {
    const int j = x / TILE_SIZE;
    const int i = y / TILE_SIZE;

    if (j < 0 || i < 0 || j >= int(gameMap.width()) || i >= int(gameMap.height()))
        return;

    if (gameMap(j, i).type() == map::TileType::ROAD) {
        gameMap(j, i).action(selectedAction);
    }
}

void handleLeftClick(map::Map& gameMap,
      int x0,
      int y0,
      int x,
      int y) {
    if (inRectangle(x, y, TILES_X, TILES_Y, TILES_X + TILES_WIDTH, TILES_Y + TILES_HEIGHT))
        handleLeftClickInTiles(x - TILES_X, y - TILES_Y);
    else if (inRectangle(x, y, MAP_X, MAP_Y, MAP_X + MAP_WIDTH, MAP_Y + MAP_HEIGHT))
        handleLeftClickInMap(gameMap, x - MAP_X + x0, y - MAP_Y + y0);
}

void handleRightClick(map::Map& gameMap,
      int x0,
      int y0,
      int x,
      int y) {
    if (inRectangle(x, y, ACTIONS_X, ACTIONS_Y, ACTIONS_X + ACTIONS_WIDTH, ACTIONS_Y + ACTIONS_HEIGHT))
        handleRightClickInActions(x - ACTIONS_X, y - ACTIONS_Y);
    else if (inRectangle(x, y, MAP_X, MAP_Y, MAP_X + MAP_WIDTH, MAP_Y + MAP_HEIGHT))
        handleRightClickInMap(gameMap, x - MAP_X + x0, y - MAP_Y + y0);
}

void loop(map::Map& gameMap,
      const std::string& stagePath) {
    using gamelib::allegro::BITMAP_PTR;
    using gamelib::allegro::make_destroyer;
    auto& graphic = util::Singleton<gamelib::allegro::Graphic>::instance();
    auto mapCanvas = BITMAP_PTR(al_create_bitmap(MAP_WIDTH, MAP_HEIGHT), make_destroyer(al_destroy_bitmap));
    auto minimapCanvas = BITMAP_PTR(al_create_bitmap(MINIMAP_WIDTH, MINIMAP_HEIGHT), make_destroyer(al_destroy_bitmap));
    auto actionsCanvas = BITMAP_PTR(al_create_bitmap(ACTIONS_WIDTH, ACTIONS_HEIGHT), make_destroyer(al_destroy_bitmap));
    auto tilesCanvas = BITMAP_PTR(al_create_bitmap(TILES_WIDTH, TILES_HEIGHT), make_destroyer(al_destroy_bitmap));
    auto statusCanvas = BITMAP_PTR(al_create_bitmap(STATUS_WIDTH, STATUS_HEIGHT), make_destroyer(al_destroy_bitmap));
    auto helpCanvas = BITMAP_PTR(al_create_bitmap(HELP_WIDTH, HELP_HEIGHT), make_destroyer(al_destroy_bitmap));
    std::vector<std::string> status_lines;

    drawCanvas(*helpCanvas, drawHelp); // this is cached, because it does not change

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
        status_lines.clear();
        al_wait_for_event(&graphic.eventQueue(), &ev);

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
                    case ALLEGRO_KEY_R:
                        map::MapIO::write(stagePath, gameMap);
                        break;
                    case ALLEGRO_KEY_T:
                        gameMap.adjustTiles();
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
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (ev.mouse.button & 1) {
                    handleLeftClick(gameMap, x0, y0, ev.mouse.x, ev.mouse.y);
                }
                if (ev.mouse.button & 2) {
                    handleRightClick(gameMap, x0, y0, ev.mouse.x, ev.mouse.y);
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                if (ev.mouse.dz != 0) {
                    y0 -= ev.mouse.dz * int(TILE_SIZE / 3);
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

            status_lines.push_back("x0: " + std::to_string(x0));
            status_lines.push_back("y0: " + std::to_string(y0));
            status_lines.push_back("Selected tile: " + map::to_string(selectedTile));
            status_lines.push_back("Selected action: " + map::to_string(selectedAction));

            drawCanvas(*mapCanvas, drawMap, gameMap, x0, y0);
            drawCanvas(*minimapCanvas, drawMiniMap, gameMap);
            drawCanvas(*actionsCanvas, drawActions);
            drawCanvas(*tilesCanvas, drawTiles);
            drawCanvas(*statusCanvas, drawStatus, status_lines);

            al_set_target_bitmap(al_get_backbuffer(&graphic.display()));

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
    ACTIONS_BG = al_map_rgb(0x4d, 0x80, 0x55);
    ACTIONS_FG = al_map_rgb(0xec, 0xf3, 0xec);
    HELP_FG = al_map_rgb(0x1a, 0x44, 0x80);
    HELP_BG = al_map_rgb(0xd9, 0xe8, 0xf6);
    MINIMAP_BG = al_map_rgb(0x16, 0x2e, 0x51);
    MINIMAP_FG = al_map_rgb(0xff, 0xbf, 0x00);
    WINDOW_BG = al_map_rgb(0x3d, 0x45, 0x51);
    SELECTION_FG = al_map_rgb(0xff, 0x00, 0xff);
}
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <path to stages> <path to sprites>\n";
        return -1;
    }

    const std::string stagePath = argv[1] + std::string("/stage.dat");
    const std::string spritePath = argv[2];
    const std::string spritesFile = spritePath + "/Rally-general-sprites.png";

    try {
        using gamelib::allegro::Graphic;
        util::Singleton<Graphic>::create(std::make_unique<Graphic>(spritePath,
              WINDOW_W,
              WINDOW_H,
              gamelib::allegro::bmp::TileSource::GREEN,
              gamelib::allegro::bmp::CarSource::PLAYER_1,
              gamelib::allegro::bmp::CarSource::ENEMY_1));
        auto& graphic = util::Singleton<Graphic>::instance();

        map::Map gameMap = createOrLoadMap(stagePath);

        const auto fullImage = gamelib::allegro::bmp::SpriteReader::readFullImage(spritesFile);

        initialize_colors();

        using gamelib::allegro::make_destroyer;
        using gamelib::allegro::TIMER_PTR;
        auto timer = TIMER_PTR(al_create_timer(1.0 / 30.0), make_destroyer(al_destroy_timer));
        if (timer == nullptr)
            tools::throw_allegro_error("could not create timer");
        al_register_event_source(&graphic.eventQueue(), al_get_timer_event_source(timer.get()));
        al_start_timer(timer.get());

        loop(gameMap, stagePath);
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
