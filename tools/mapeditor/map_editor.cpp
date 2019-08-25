#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/ActionMapper.h"
#include "gamelib/allegro/bmp/TileMapper.h"
#include "map/Action.h"
#include "map/Map.h"
#include "map/MapIO.h"
#include "map/TileType.h"
#include "util/Util.h"

#include <allegro.h>

#include <boost/filesystem.hpp>

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

namespace {
constexpr unsigned TILE_SIZE = 32;                                              ///< tile size in pixels
constexpr unsigned TILE_GAP = 10;                                               ///< space between tiles at tiles section
constexpr unsigned MAP_COLUMNS = 16;                                            ///< map section's number of columns
constexpr unsigned MAP_ROWS = 15;                                               ///< map section's number of rows
constexpr unsigned MAP_X0 = TILE_GAP;                                           ///< map section's left side
constexpr unsigned MAP_Y0 = TILE_GAP;                                           ///< map section's top side
constexpr unsigned MAP_W = TILE_SIZE * MAP_COLUMNS + TILE_GAP;                  ///< map section width
constexpr unsigned MAP_H = TILE_SIZE * MAP_ROWS + TILE_GAP;                     ///< map section height
constexpr unsigned MAP_STEP_X = TILE_SIZE * MAP_COLUMNS;                        ///< map section's horizontal page
constexpr unsigned MAP_STEP_Y = TILE_SIZE * MAP_ROWS;                           ///< map section's vertical page
constexpr unsigned TILES_COLUMNS = (MAP_W - TILE_GAP) / (TILE_SIZE + TILE_GAP); ///< tiles section's number of columns
constexpr unsigned TILES_X0 = MAP_X0;                                           ///< tiles section's left side
constexpr unsigned TILES_Y0 = MAP_Y0 + MAP_H;                                   ///< tiles section's top side
constexpr unsigned NUM_TYPES = util::from_Enum<unsigned>(map::TileType::LAST);  ///< number of types of tiles
static_assert(NUM_TYPES % TILES_COLUMNS != 0);                                  ///< for the +1 below
constexpr unsigned TILES_ROWS = NUM_TYPES / TILES_COLUMNS + 1;                  ///< tiles section's number of rows
constexpr unsigned TILES_W = MAP_W;                                             ///< tiles section's width
constexpr unsigned TILES_H = TILES_ROWS * (TILE_SIZE + TILE_GAP) + TILE_GAP;    ///< tiles section's height
constexpr unsigned HELP_X0 = MAP_X0;                                            ///< help section's left side
constexpr unsigned HELP_Y0 = TILES_Y0 + TILES_H;                                ///< help section's TOP side
constexpr unsigned HELP_W = MAP_W;                                              ///< help section's width
constexpr unsigned HELP_H = 350;                                                ///< help section's height
constexpr unsigned WINDOW_H = HELP_Y0 + HELP_H + TILE_GAP;                      ///< window height
constexpr unsigned ACTION_W = 180;                                              ///< action section's width
constexpr unsigned ACTION_H = WINDOW_H - 180;                                   ///< action section's height
constexpr unsigned ACTION_X0 = MAP_X0 + MAP_W;                                  ///< action section's left side
constexpr unsigned ACTION_Y0 = TILE_GAP;                                        ///< action section's top side
constexpr unsigned STATUS_X0 = ACTION_X0;                                       ///< status section's left side
constexpr unsigned STATUS_Y0 = ACTION_Y0 + ACTION_H;                            ///< status section's top side
constexpr unsigned STATUS_W = ACTION_W;                                         ///< status section's width
constexpr unsigned STATUS_H = WINDOW_H - (ACTION_Y0 + ACTION_H) - TILE_GAP;     ///< status section's height
constexpr unsigned WINDOW_W = ACTION_X0 + ACTION_W + TILE_GAP;                  ///< windows width

map::TileType g_cur_tile_type = map::TileType::GRASS;
map::Action g_cur_act = map::Action::NONE;
unsigned g_map_draw_x, g_map_draw_y;
unsigned g_max_i, g_max_j;
unsigned char g_default_tile;

int MAP_FG = 0;
int TILES_BG = 0;
int TILES_FG = 0;
int STATUS_BG = 0;
int STATUS_FG = 0;
int ACTION_BG = 0;
int ACTION_FG = 0;
int HELP_FG = 0;
int HELP_BG = 0;
int WINDOW_BG = 0;

struct point_t {
    unsigned x, y;
};

template <typename MAPPER>
struct mapper_t {
    using enum_type = typename MAPPER::enum_type;
    using pos_map = std::map<enum_type, point_t>;
    mapper_t(MAPPER m, pos_map p)
          : mapper(std::move(m)),
            pos(std::move(p)) {}

    [[nodiscard]] const point_t& position(enum_type type) const {
        const auto it = pos.find(type);
        if (it == pos.end()) {
            throw std::invalid_argument("position of "
                                        + std::string(typeid(MAPPER).name())
                                        + " for type "
                                        + map::to_string(type)
                                        + " not found");
        }
        return it->second;
    }
    MAPPER mapper;
    pos_map pos;
};

using tiles_t = mapper_t<gamelib::allegro::bmp::TileMapper>;
using actions_t = mapper_t<gamelib::allegro::bmp::ActionMapper>;

// Variables used by CTRL+C CTRL+V
bool g_copy_selection_on = false;
point_t g_copy_ini_point;
point_t g_copy_end_point;
bool g_draw_selection = false;
bool g_take_shot = false;
BITMAP* g_selection_preview;

void map_save(const std::string& file_name, const map::Map& stageMap) {
    map::MapIO::write(file_name, stageMap);
}

map::Map map_load(const std::string& file_name) {
    const map::Map stage_map = map::MapIO::read(file_name);

    g_max_i = stage_map.width();
    g_max_j = stage_map.height();
    g_default_tile = 6;

    return stage_map;
}

map::Map create_clean_map(const int max_x,
      const int max_y,
      const int default_tile) {
    g_max_i = max_x * MAP_COLUMNS;
    g_max_j = max_y * MAP_ROWS;
    if (g_max_i == 0 || g_max_j == 0) {
        exit(-1);
    }
    g_default_tile = default_tile;
    const std::vector<map::Tile> tiles(g_max_i * g_max_j, map::Tile(map::TileType::GRASS, map::Action::NONE));

    return map::Map(g_max_i, g_max_j, tiles);
}

template <typename MAPPER>
void mapper_draw(BITMAP* bmp,
      const MAPPER& mapper,
      const typename MAPPER::enum_type type,
      const int x,
      const int y) {
    const auto sub_bmp = mapper[type];
    draw_sprite(bmp, sub_bmp, x, y);
}

void draw_tile(BITMAP* bmp,
      const gamelib::allegro::bmp::TileMapper& mapper,
      const map::TileType type,
      const int x,
      const int y) {
    mapper_draw(bmp, mapper, type, x, y);
}

void draw_action(BITMAP* bmp,
      const gamelib::allegro::bmp::ActionMapper& mapper,
      const map::Action action,
      const int x,
      const int y) {
    mapper_draw(bmp, mapper, action, x, y);
}

// Draws the map from (map_draw_x, map_draw_y).
// If draw_actions == true, shows the actions instead of the tiles.
// If ignoreVoid == true, draws action AND tiles.
void draw_map(BITMAP* bmp,
      const map::Map& stage_map,
      const tiles_t& tile_mapper,
      const actions_t& action_mapper,
      const int map_draw_x,
      const int map_draw_y,
      const bool draw_actions) {
    const unsigned map_i = map_draw_x / TILE_SIZE;
    const unsigned map_j = map_draw_y / TILE_SIZE;

    const unsigned i_disp = map_i + MAP_COLUMNS == g_max_i ? 0 : 1;
    const unsigned j_disp = map_j + MAP_ROWS == g_max_j ? 0 : 1;
    for (unsigned i = 0; i < MAP_ROWS + j_disp; ++i) {
        for (unsigned j = 0; j < MAP_COLUMNS + i_disp; ++j) {
            const unsigned x = j * TILE_SIZE + MAP_X0;
            const unsigned y = i * TILE_SIZE + MAP_Y0;

            const auto I = map_i + j;
            const auto J = map_j + i;

            const auto& tile = stage_map(I, J);
            draw_tile(bmp, tile_mapper.mapper, tile.type(), x, y);
            if (draw_actions) {
                draw_action(bmp, action_mapper.mapper, tile.action(), x, y);
            }

            if (key[KEY_F] == 0 && not g_take_shot) {
                textprintf_ex(bmp, font, x + 2, y + 2, 0, MAP_FG, "%02d", map::from_EAction<int>(tile.action()));
            }
        }
    }
}

void draw_tiles_bar(BITMAP* bmp, const tiles_t& tile_mapper) {
    rectfill(bmp, TILES_X0, TILES_Y0, TILES_X0 + TILES_W, MAP_H + HELP_H, TILES_BG);
    for (const auto type : util::EnumIterator<map::TileType>()) {
        const auto& pos = tile_mapper.position(type);
        draw_tile(bmp, tile_mapper.mapper, type, pos.x, pos.y);
    }

    const auto& pos = tile_mapper.position(g_cur_tile_type);
    const auto x = pos.x;
    const auto y = pos.y;

    const auto gap = TILE_GAP - 2;
    rect(bmp, x - gap, y - gap, x + TILE_SIZE + gap - 1, y + TILE_SIZE + gap - 1, TILES_FG);
}

bool mouse_in_map() {
    const auto x = static_cast<unsigned>(mouse_x);
    if (x < MAP_X0)
        return false;
    if (x >= MAP_X0 + MAP_W)
        return false;

    const auto y = static_cast<unsigned>(mouse_y);
    if (y < MAP_Y0)
        return false;
    return y < MAP_Y0 + MAP_H;
}

void draw_status_bar(BITMAP* bmp) {
    const auto POS_LT_X = STATUS_X0 + 5;
    const auto POS_LT_Y = STATUS_Y0 + 5;

    rectfill(bmp, STATUS_X0, STATUS_Y0, STATUS_X0 + STATUS_W, STATUS_Y0 + STATUS_H, STATUS_BG);

    const int x = mouse_x - MAP_X0;
    if (mouse_in_map()) {
        const int y = mouse_y - MAP_Y0;
        const int i = x / TILE_SIZE;
        const int j = y / TILE_SIZE;
        char tmp[80];
        snprintf(tmp, sizeof(tmp), "mouse: (%3d,%3d)", x, y);
        textprintf_ex(bmp, font, POS_LT_X, POS_LT_Y, STATUS_FG, STATUS_BG, "%-20s", tmp);
        snprintf(tmp, sizeof(tmp), "tile:  (%3d,%3d)", i, j);
        textprintf_ex(bmp, font, POS_LT_X, POS_LT_Y + 10, STATUS_FG, STATUS_BG, "%-20s", tmp);
    }

    if (key[KEY_O])
        textprintf_ex(bmp, font, POS_LT_X, POS_LT_Y + 20, STATUS_FG, STATUS_BG, "OFFSET: %02u", x % TILE_SIZE);

    if (g_draw_selection)
        textprintf_ex(bmp, font, POS_LT_X, POS_LT_Y + 30, STATUS_FG, STATUS_BG, "SELECTION ON-SCROLL OFF");
}

void draw_actions_bar(BITMAP* bmp, const actions_t& action_mapper) {
    rectfill(bmp, ACTION_X0, ACTION_Y0, ACTION_X0 + ACTION_W, ACTION_Y0 + ACTION_H, ACTION_BG);

    for (auto act : util::EnumIterator<map::Action>()) {
        const auto& pos = action_mapper.position(act);
        draw_action(bmp, action_mapper.mapper, act, pos.x, pos.y);

        if (g_cur_act == act) {
            rect(bmp,
                  pos.x - 2,
                  pos.y - 2,
                  pos.x + TILE_SIZE + 2,
                  pos.y + TILE_SIZE + 2,
                  ACTION_FG);
        }
    }

    draw_status_bar(bmp);
}

void draw_help(BITMAP* canvas) {
    constexpr int step_y = 15;
    rectfill(canvas, HELP_X0, HELP_Y0, HELP_X0 + HELP_W, HELP_Y0 + HELP_H, HELP_BG);

    const std::vector<std::string> manual = {
        "ESC - closes the editor",
        "Arrows - move map one tile at a time",
        "W A S D - move map one page at a time",
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
    for (size_t i = 0; i < manual.size(); ++i) {
        textprintf_ex(canvas, font, HELP_X0 + 20, (i + 1) * step_y + HELP_Y0, HELP_FG, HELP_BG, "%s", manual[i].c_str());
    }
}

/// handle clicks inside bar
template <typename MAPPER>
void handle_bar(typename MAPPER::enum_type& cur,
      const MAPPER& mapper,
      const int mouse_button) {
    if (mouse_b & mouse_button) {
        const unsigned y = mouse_y;
        const unsigned x = mouse_x;
        for (const auto type : util::EnumIterator<typename MAPPER::enum_type>()) {
            const auto& pos = mapper.position(type);
            if ((x >= pos.x)
                  && (x <= pos.x + TILE_SIZE)
                  && (y >= pos.y)
                  && (y <= pos.y + TILE_SIZE)) {
                cur = type;
                break;
            }
        }
    }
}

/// handle clicks inside tile bar
void handle_tile_bar(const tiles_t& tile_mapper) {
    handle_bar(g_cur_tile_type, tile_mapper, 1);
}

/// handle clicks inside action bar
void handle_action_bar(const actions_t& action_mapper) {
    handle_bar(g_cur_act, action_mapper, 2);
}

std::pair<point_t, point_t> define_region(point_t p1, point_t p2) {
    if (p2.x < p1.x)
        std::swap(p2.x, p1.x);
    if (p2.y < p1.y)
        std::swap(p2.y, p1.y);

    return std::make_pair(p1, p2);
}

void handle_CtrlC_CtrlV(map::Map& stage_map,
      const size_t x,
      const size_t y) {
    if (key[KEY_C]) {
        if (not g_copy_selection_on) {
            clear_bitmap(g_selection_preview);

            g_copy_ini_point.x = x;
            g_copy_ini_point.y = y;
            g_copy_end_point.x = x;
            g_copy_end_point.y = y;
            g_copy_selection_on = true;
            g_draw_selection = false;
        } else {
            g_copy_end_point.x = x;
            g_copy_end_point.y = y;
            g_take_shot = true;
            g_draw_selection = true;
        }
    } else if (key[KEY_V] && g_copy_selection_on) {
        const auto region = define_region(g_copy_ini_point, g_copy_end_point);
        const point_t pt_data_len = {
            (region.second.x - region.first.x) + 1,
            (region.second.y - region.first.y) + 1
        };

        std::vector<map::Tile> selection_data(pt_data_len.x * pt_data_len.y, map::Tile(map::TileType::GRASS));

        for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
            for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                selection_data.at(ys * (pt_data_len.x) + xs) = stage_map(region.first.x + xs, region.first.y + ys);
            }
        }

        for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
            for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                stage_map(x + xs, y + ys) = selection_data.at(ys * (pt_data_len.x) + xs);
            }
        }

        g_draw_selection = false;
        g_copy_selection_on = false;
    }
}

/// treats clicks inside map area
void handle_click(map::Map& stage_map,
      const int X,
      const int Y,
      const int button) {
    // apply screen displacement and normalize mouse's x,y to TILE_SIZE units
    const size_t x = (X + g_map_draw_x) / TILE_SIZE;
    const size_t y = (Y + g_map_draw_y) / TILE_SIZE;

    if (x >= stage_map.width() || y >= stage_map.height())
        return; // out of map
    switch (button) {
        case 1:
            if (!key[KEY_LCONTROL]) { // CTRL is not pressed.
                stage_map(x, y).type(g_cur_tile_type);
            } else { // CTRL is pressed.
                if (key[KEY_C] || key[KEY_V]) {
                    handle_CtrlC_CtrlV(stage_map, x, y);
                }
            }
            break;
        case 2:
            // only ROADS may receive actions
            if (stage_map(x, y).type() == map::TileType::ROAD)
                stage_map(x, y).action(g_cur_act);
            break;
        default:
            break;
    }
}

/// loads all actions from file.
actions_t load_actions(const std::string& file_name) {
    std::map<map::Action, point_t> pos;
    unsigned x = ACTION_X0 + TILE_GAP;
    unsigned y = ACTION_Y0 + TILE_GAP;

    for (auto act : util::EnumIterator<map::Action>()) {
        pos.insert(std::make_pair(act, point_t{ x, y }));

        x += TILE_SIZE + TILE_GAP;
        if (x + TILE_SIZE > ACTION_X0 + ACTION_W) {
            x = ACTION_X0 + TILE_GAP;
            y += TILE_SIZE + TILE_GAP;
        }
    }

    constexpr unsigned GAP = 1;

    printf("ACTIONS loaded!\n");

    return actions_t(gamelib::allegro::bmp::ActionMapper(file_name, TILE_SIZE, TILE_SIZE, GAP), pos);
}

/// loads all tiles from file.
tiles_t load_tiles(const std::string& file_name) {
    constexpr unsigned GAP = 2;
    std::map<map::TileType, point_t> pos;

    unsigned x = TILES_X0 + TILE_GAP;
    unsigned y = TILES_Y0 + TILE_GAP;
    for (const auto type : util::EnumIterator<map::TileType>()) {
        if (x + TILE_SIZE > TILES_X0 + TILES_W) {
            x = TILES_X0 + TILE_GAP;
            y += TILE_SIZE + TILE_GAP;
        }
        pos.insert(std::make_pair(type, point_t{ x, y }));
        x += TILE_SIZE + TILE_GAP;
    }

    printf("TILESET loaded!\n");

    return tiles_t(gamelib::allegro::bmp::TileMapper(file_name, TILE_SIZE, TILE_SIZE, GAP), pos);
}

void clear_window(BITMAP* bmp) {
    rectfill(bmp, 0, 0, WINDOW_W, WINDOW_H, WINDOW_BG);
}

void draw_grid(BITMAP* bmp) {
    for (unsigned x = MAP_X0; x < MAP_X0 + MAP_W; x += TILE_SIZE) {
        vline(bmp, x, MAP_Y0, MAP_Y0 + MAP_H, MAP_FG);
    }
    for (unsigned y = MAP_Y0; y < MAP_Y0 + MAP_H; y += TILE_SIZE) {
        hline(bmp, MAP_X0, y, MAP_X0 + MAP_W, MAP_FG);
    }
}

map::Map create_or_load_map(int argc, char** argv) {
    const std::string tmp = std::string(argv[1] + std::string("/stage.dat"));
    boost::filesystem::path path_to_file(tmp);
    if (boost::filesystem::exists(path_to_file)) {
        return map_load(tmp);
    } else {
        if (argc < 5) {
            exit(-1);
        }
        const auto max_x = std::stoi(argv[2]);
        const auto max_y = std::stoi(argv[3]);
        const auto default_tile = std::stoi(argv[4]);
        return create_clean_map(max_x, max_y, default_tile);
    }
}

void initialize_colors() {
    MAP_FG = makecol32(0xff, 0xff, 0xff);
    TILES_BG = makecol(0x2e, 0x62, 0x76);
    TILES_FG = makecol(0xe7, 0xf6, 0xf8);
    STATUS_BG = makecol(0xf8, 0xdf, 0xe2);
    STATUS_FG = makecol(0x8b, 0x13, 0x03);
    ACTION_BG = makecol(0x4d, 0x80, 0x55);
    ACTION_FG = makecol(0xec, 0xf3, 0xec);
    HELP_FG = makecol(0x1a, 0x44, 0x80);
    HELP_BG = makecol(0xd9, 0xe8, 0xf6);
    WINDOW_BG = makecol(0x3d, 0x45, 0x51);
}

}

int main(int argc, char* argv[]) {
    try {
        g_map_draw_x = g_map_draw_y = 0;

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_W, WINDOW_H, 0, 0);

        initialize_colors();

        gamelib::allegro::BITMAP_PTR buffer(create_bitmap(SCREEN_W, SCREEN_H), destroy_bitmap);
        g_selection_preview = create_bitmap(185, 150);

        clear_bitmap(g_selection_preview);

        if (argc <= 1) {
            fprintf(stderr, "ERROR - usage: %s <path to stages>", argv[0]);
            exit(-1);
        }
        const std::string tmp = argv[1] + std::string("/stage.dat");

        map::Map stage_map = create_or_load_map(argc, argv);

        const auto tile_mapper(load_tiles(RALLY_ROOT "/Stuff/tileset.bmp"));
        const auto action_mapper(load_actions(RALLY_ROOT "/Stuff/actions.bmp"));

        while (!key[KEY_ESC]) {
            handle_tile_bar(tile_mapper);
            handle_action_bar(action_mapper);

            if ((unsigned) mouse_x < MAP_W && (unsigned) mouse_y < MAP_H) {
                if (mouse_b & 1)
                    handle_click(stage_map, mouse_x, mouse_y, 1);
                if (mouse_b & 2)
                    handle_click(stage_map, mouse_x, mouse_y, 2);
            }

            if (key[KEY_RIGHT] && not g_draw_selection) {
                if ((g_map_draw_x / TILE_SIZE) < (g_max_i - MAP_COLUMNS)) {
                    g_map_draw_x += TILE_SIZE;
                }
            } else if (key[KEY_LEFT] && not g_draw_selection) {
                if (g_map_draw_x > 0) {
                    g_map_draw_x -= TILE_SIZE;
                }
            }

            if (key[KEY_UP] && not g_draw_selection) {
                if (g_map_draw_y > 0) {
                    g_map_draw_y -= TILE_SIZE;
                }
            } else if (key[KEY_DOWN] && not g_draw_selection) {
                if ((g_map_draw_y / TILE_SIZE) < (g_max_j - MAP_ROWS)) {
                    g_map_draw_y += TILE_SIZE;
                }
            }

            if (key[KEY_D] && not g_draw_selection) {
                g_map_draw_x += MAP_STEP_X;
                if (g_map_draw_x / TILE_SIZE >= (g_max_i - MAP_COLUMNS))
                    g_map_draw_x = (g_max_i - MAP_COLUMNS) * TILE_SIZE;

                tools::hold_while_pressed(KEY_D);
            } else if (key[KEY_A] && not g_draw_selection) {
                if (g_map_draw_x < MAP_STEP_X)
                    g_map_draw_x = 0;
                else
                    g_map_draw_x -= MAP_STEP_X;

                tools::hold_while_pressed(KEY_A);
            }

            if (key[KEY_W] && not g_draw_selection) {
                if (g_map_draw_y < MAP_STEP_Y)
                    g_map_draw_y = 0;
                else
                    g_map_draw_y -= MAP_STEP_Y;

                tools::hold_while_pressed(KEY_W);
            } else if (key[KEY_S] && not g_draw_selection) {
                g_map_draw_y += MAP_STEP_Y;
                if (g_map_draw_y / TILE_SIZE >= (g_max_j - MAP_ROWS))
                    g_map_draw_y = (g_max_j - MAP_ROWS) * TILE_SIZE;

                tools::hold_while_pressed(KEY_S);
            }

            if (key[KEY_LSHIFT]) {
                map_save(tmp, stage_map);
                // Evita que fique salvando loucamente o mapa, segura at� o sujeito soltar a tecla.
                tools::hold_while_pressed(KEY_LSHIFT);
            }

            if (key[KEY_X]) {
                g_copy_selection_on = false;
                g_draw_selection = false;
            }

            const bool draw_actions = key[KEY_SPACE];

            clear_window(&(*buffer));

            draw_map(&(*buffer), stage_map, tile_mapper, action_mapper, g_map_draw_x, g_map_draw_y, draw_actions);

            if (!key[KEY_G]) {
                if (not g_take_shot)
                    draw_grid(&(*buffer));
            }
            draw_tiles_bar(&(*buffer), tile_mapper);
            draw_actions_bar(&(*buffer), action_mapper);
            draw_help(&(*buffer));

            if (key[KEY_I]) {
                int xpos, ypos;
                xpos = mouse_x / TILE_SIZE * TILE_SIZE;
                if (key[KEY_O])
                    xpos += mouse_x % TILE_SIZE - TILE_SIZE / 2;
                ypos = mouse_y / TILE_SIZE * TILE_SIZE;
                if (key[KEY_O])
                    ypos += mouse_y % TILE_SIZE - TILE_SIZE / 2;
                draw_action(&(*buffer), action_mapper.mapper, g_cur_act, xpos, ypos);
            } else if (not g_take_shot) {
                circlefill(&(*buffer), mouse_x, mouse_y, 5, 0);
                circlefill(&(*buffer), mouse_x, mouse_y, 3, makecol(255, 255, 255));
            }

            if (g_draw_selection) {
                const auto region = define_region(g_copy_ini_point, g_copy_end_point);
                const auto x_ini = (region.first.x * TILE_SIZE) - g_map_draw_x;
                const auto y_ini = (region.first.y * TILE_SIZE) - g_map_draw_y;
                const auto x_end = ((region.second.x + 1) * TILE_SIZE) - g_map_draw_x;
                const auto y_end = ((region.second.y + 1) * TILE_SIZE) - g_map_draw_y;

                if (g_take_shot) {
                    stretch_blit(&(*buffer),
                          g_selection_preview,
                          x_ini,
                          y_ini,
                          x_end - x_ini,
                          y_end - y_ini,
                          0,
                          0,
                          g_selection_preview->w,
                          g_selection_preview->h);
                    g_take_shot = false;
                }
                rect(&(*buffer),
                      SCREEN_W - 194,
                      SCREEN_H - 392,
                      SCREEN_W - 194 + g_selection_preview->w + 3,
                      SCREEN_H - 392 + g_selection_preview->h + 3,
                      makecol(255, 255, 255));

                blit(g_selection_preview,
                      &(*buffer),
                      0,
                      0,
                      SCREEN_W - 192,
                      SCREEN_H - 390,
                      g_selection_preview->w,
                      g_selection_preview->h);

                set_trans_blender(128, 128, 128, 128);
                drawing_mode(DRAW_MODE_TRANS, nullptr, 0, 0);
                rectfill(&(*buffer), x_ini, y_ini, x_end, y_end, makecol(30, 30, 255));
                drawing_mode(DRAW_MODE_SOLID, nullptr, 0, 0);
                rect(&(*buffer), x_ini, y_ini, x_end, y_end, 0);
                rect(&(*buffer), x_ini + 1, y_ini + 1, x_end - 1, y_end - 1, 0);
            }

            vsync();
            blit(&(*buffer), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            clear_bitmap(&(*buffer));
        }
        return 0;
    } catch (std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()
