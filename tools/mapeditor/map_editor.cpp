/*
 * TODO: Definir um header bonitinho.
 * NOTA: SUPER HIPER NÃO OPTIMIZADO, não tem que ser, ele só monta o mapa, não tem ação nenhuma nele.
*/

#include "../tools/util/helpers.h"

#include "gamelib/allegro/bmp/CTileMapper.h"
#include "gamelib/allegro/bmp/CActionMapper.h"
#include "map/CMap.h"
#include "map/CMapIO.h"
#include "util/EUtil.h"

#include <allegro.h>

#include <boost/filesystem.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeinfo>

// TODO:
// Usando os defines no megaman, temos que rever isso aqui.
// O jogo original tem uma resolução de 288 x 224, sugiro que a gente dobre: 576 x 448
// Verificar tamanho dos tiles e setar um novo pra gente.
static constexpr unsigned TILE_SIZE     = 32;                               ///< tile size in pixels
static constexpr unsigned TILE_GAP      = 4;                                ///< space around a tile at the tiles bar
static constexpr unsigned TILE_SPACE    = TILE_SIZE + 2 * TILE_GAP;         ///< total space used by a tile
static constexpr unsigned UTIL_COLUMNS  = 16;                               ///< number of rows of tiles that are shown in the window
static constexpr unsigned UTIL_ROWS     = 15;                               ///< number of columns of tiles that are shown in the window
static constexpr unsigned UTIL_W        = TILE_SIZE * UTIL_COLUMNS + 10;    ///< map window width
static constexpr unsigned UTIL_H        = TILE_SIZE * UTIL_ROWS + 10;       ///< map window height
static constexpr unsigned UTIL_H_EX     = 350;                              ///< ?
static constexpr unsigned TILES_X       = UTIL_W / TILE_SIZE;               ///< number of whole tiles in the horizontal direction
static constexpr unsigned TILES_Y       = UTIL_H / TILE_SIZE;               ///< number of whole tiles in the vertical direction
static constexpr unsigned TILES_MARGIN  = 8;
static constexpr unsigned STEP_X        = TILE_SIZE * TILES_X;              ///< ?
static constexpr unsigned STEP_Y        = TILE_SIZE * TILES_Y;              ///< ?
static constexpr unsigned ACTION_X0     = UTIL_W + 10;                      ///< base distance of action from left border
static constexpr unsigned ACTION_MAX_X  = ACTION_X0 + 180;                  ///< maximum distance of action from left border
static constexpr unsigned ACTION_Y0     = 10;                               ///< base distance of action from top border
static constexpr unsigned ACTION_SPACE  = 40;                               ///< distance between the beginning of two consecutive actions
static constexpr unsigned WINDOW_WIDTH  = ACTION_MAX_X + ACTION_SPACE + 10;
static constexpr unsigned WINDOW_HEIGHT = UTIL_H + UTIL_H_EX;

static map::ETileType g_cur_tile_type = map::ETileType::GRASS;
static map::EAction g_cur_act = map::EAction::NONE;
static unsigned g_map_drawx, g_map_drawy;
static unsigned g_max_x, g_max_y;
static unsigned char g_default_tile;

struct point_t {
    unsigned x, y;
};

template<typename MAPPER>
struct mapper_t {
    typedef typename MAPPER::enum_type enum_type;
    typedef std::map<enum_type, point_t> pos_map;
    mapper_t(MAPPER && m,
             const pos_map & p)
        : mapper(std::move(m)),
          pos(p) {
    }
    const point_t & position(enum_type type) const {
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

typedef mapper_t<gamelib::allegro::bmp::CTileMapper> tiles_t;
typedef mapper_t<gamelib::allegro::bmp::CActionMapper> actions_t;

// Variaveis usadas pelo CTRL+C CTRL+V
static bool g_copy_selection_on = false;
static point_t g_copy_ini_point;
static point_t g_copy_end_point;
static bool g_draw_selection = false;
static bool g_take_shot = false;
static BITMAP * g_selection_preview;

static void map_save(const std::string & filename,
                     const map::CMap & stageMap) {
    map::CMapIO::write(filename, stageMap);
}

static map::CMap map_load(const std::string & filename) {
    const map::CMap stageMap = map::CMapIO::read(filename);

    g_max_x = stageMap.width();
    g_max_y = stageMap.height();
    g_default_tile = 6;

    return stageMap;
}

static map::CMap create_clean_map(const int max_x,
                                  const int max_y,
                                  const int default_tile) {
    g_max_x = max_x * TILES_X;
    g_max_y = max_y * TILES_Y;
    if (g_max_x == 0 || g_max_y == 0) {
        exit(-1);
    }
    g_default_tile = default_tile;
    const std::vector<map::CTile> tiles(g_max_x * g_max_y, map::CTile(map::ETileType::GRASS, map::EAction::NONE));

    return map::CMap(g_max_x, g_max_y, tiles);
}

template <typename MAPPER>
static void mapper_draw(BITMAP * bmp,
                        const MAPPER & mapper,
                        const typename MAPPER::enum_type type,
                        const int x,
                        const int y) {
    const auto sub_bmp = mapper[type];
    draw_sprite(bmp, sub_bmp, x, y);
}

static void tile_draw(BITMAP * bmp,
                      const gamelib::allegro::bmp::CTileMapper & mapper,
                      const map::ETileType type,
                      const int x,
                      const int y) {
    mapper_draw(bmp, mapper, type, x, y);
}

static void action_draw(BITMAP * bmp,
                        const gamelib::allegro::bmp::CActionMapper & mapper,
                        const map::EAction action,
                        const int x,
                        const int y) {
    mapper_draw(bmp, mapper, action, x, y);
}

// Desenha o mapa partindo do map_drawx, map_drawy.
// Se draw_actions = true, mostra as actions ao invez do desenho do tile.
// Se ignoreVoid = true, desenha as actios E o desenho dos tiles.
static void map_draw(BITMAP * bmp,
                     const map::CMap & stageMap,
                     const tiles_t & tileMapper,
                     const actions_t & actionMapper,
                     const int map_drawx,
                     const int map_drawy,
                     const bool draw_actions) {
    static int color[] = { makecol32(30, 30, 30), makecol32(255, 0, 0), makecol32(255, 255, 255) };

    const unsigned mapx = map_drawx / TILE_SIZE;
    const unsigned mapy = map_drawy / TILE_SIZE;

    const unsigned map_xoff = map_drawx & (TILE_SIZE - 1);
    const unsigned map_yoff = map_drawy & (TILE_SIZE - 1);

    const unsigned xdisp = mapx + TILES_X == g_max_x ? 0 : 1;
    const unsigned ydisp = mapy + TILES_Y == g_max_y ? 0 : 1;
    for (unsigned v = 0; v < TILES_Y + ydisp; ++v) {
        for (unsigned h = 0; h < TILES_X + xdisp; ++h) {
            const unsigned x = h * TILE_SIZE - map_xoff;
            const unsigned y = v * TILE_SIZE - map_yoff;

            const auto X = mapx + h;
            const auto Y = mapy + v;

            const auto & tile = stageMap(X, Y);
            tile_draw(bmp, tileMapper.mapper, tile.type(), x, y);
            if (draw_actions == true) {
                action_draw(bmp, actionMapper.mapper, tile.action(), x, y);
            }

            if (key[KEY_F] == 0 && g_take_shot == false) {
                textprintf_ex(bmp, font, x, y, 0, color[2], "%02d", map::from_EAction<int>(stageMap(X, Y).action()));
            }
        }
    }
}

static void draw_tilesbar(BITMAP * bmp,
                          const tiles_t & tileMapper,
                          const int tiles_num) {
    rectfill(bmp, 0, UTIL_H, UTIL_W, UTIL_H + UTIL_H_EX, makecol(30, 40, 100));
    for (const auto type : util::CEnumIterator<map::ETileType>()) {
        const auto & pos = tileMapper.position(type);
        tile_draw(bmp, tileMapper.mapper, type, pos.x, pos.y);
    }

    const auto & pos = tileMapper.position(g_cur_tile_type);
    const auto x = pos.x;
    const auto y = pos.y;

    rect(bmp, x - TILE_GAP, y - TILE_GAP, x + TILE_SPACE - TILE_GAP, y + TILE_SPACE - TILE_GAP, makecol(255, 255, 255));
}

// Desenha painel das actions
static void draw_actionsbar(BITMAP *bmp,
                            const actions_t & actionMapper,
                            const unsigned act_num) {
    rectfill(bmp, UTIL_W, 0, WINDOW_WIDTH, SCREEN_H, makecol(255, 255, 255));
    rectfill(bmp, UTIL_W + 4, 4, WINDOW_WIDTH - 4, SCREEN_H - 4, makecol(0, 50, 50));

    for (auto act : util::CEnumIterator<map::EAction>()) {
        const auto & pos = actionMapper.position(act);
        action_draw(bmp, actionMapper.mapper, act, pos.x, pos.y);

        if (g_cur_act == act) {
            rect(bmp,
                 pos.x - 2,
                 pos.y - 2,
                 pos.x + TILE_SIZE + 2,
                 pos.y + TILE_SIZE + 2,
                 makecol(255, 50, 50));
        }
    }

    static const auto POS_LT_X = UTIL_W + 10;
    static const auto POS_LT_Y = SCREEN_H - 50;
    static const auto POS_RB_X = SCREEN_W - 10;
    static const auto POS_RB_Y = SCREEN_H - 10;

    rectfill(bmp, POS_LT_X, POS_LT_Y, POS_RB_X, POS_RB_Y, makecol(255, 255, 255));

    if ((unsigned) mouse_x < UTIL_W && (unsigned) mouse_y < UTIL_H) {
        int mx = mouse_x / TILE_SIZE;
        int my = mouse_y / TILE_SIZE;
        char tmp[80];
        int bg, fg;
        bg = makecol(255, 255, 255);
        fg = makecol(0, 50, 200);
        snprintf(tmp, sizeof(tmp), "mouse: (%3d,%3d)", mouse_x, mouse_y);
        textprintf_ex(bmp, font, POS_LT_X + 5, POS_LT_Y + 5, fg, bg, "%-20s", tmp);
        snprintf(tmp, sizeof(tmp), "tile:  (%3d,%3d)", mx, my);
        textprintf_ex(bmp, font, POS_LT_X + 5, POS_LT_Y + 15, fg, bg, "%-20s", tmp);
    }

    if (key[KEY_O])
        textprintf_ex(bmp, font, UTIL_W + 20, SCREEN_H - 50, makecol(0, 50, 200), makecol(255, 255, 255), "OFFSET: %02u", (unsigned) mouse_x % TILE_SIZE);

    if (g_draw_selection == true)
        textprintf_ex(bmp, font, UTIL_W + 8, SCREEN_H - 80, makecol(255, 0, 0), 0, "SELECTION ON-SCROLL OFF");
}

static void draw_manual(BITMAP * canvas) {
    constexpr int STEP_Y = 15;
    int y0 = UTIL_H + 2 * TILE_SPACE + 10;
    rectfill(canvas, 0, y0, UTIL_W, UTIL_H + UTIL_H_EX, makecol(255, 255, 255));
    const int bg = makecol(255, 255, 255);
    const int fg = makecol(0, 50, 200);

    static std::vector<std::string> manual = {
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
        "Left Shift - salva",
        "Ctrl+C + left click - mark region for copy",
        "Ctrl+V + left click - paste copied region to point",
        "X - cancel region selected"
    };
    for (size_t i = 0; i < manual.size(); ++i) {
        textprintf_ex(canvas, font, 20, (i + 1) * STEP_Y + y0, fg, bg, "%s", manual[i].c_str());
    }
}

/// handle clicks inside bar
template<typename MAPPER>
static void handle_bar(typename MAPPER::enum_type & cur,
                       const MAPPER & mapper,
                       const int mouse_button,
                       const std::string & function) {
    if (mouse_b & mouse_button) {
        const unsigned y = mouse_y;
        const unsigned x = mouse_x;
        for (const auto type : util::CEnumIterator<typename MAPPER::enum_type>()) {
            const auto & pos = mapper.position(type);
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
static void handle_tilebar(const tiles_t & tileMapper) {
    handle_bar(g_cur_tile_type, tileMapper, 1, "handle_tilebar");
}

/// handle clicks inside action bar
static void handle_actbar(const actions_t & actionMapper) {
    handle_bar(g_cur_act, actionMapper, 2, "handle_actbar");
}

static std::pair<point_t, point_t> define_region(point_t p1,
                                                 point_t p2) {
    if (p2.x < p1.x)
        std::swap(p2.x, p1.x);
    if (p2.y < p1.y)
        std::swap(p2.y, p1.y);

    return std::make_pair(p1, p2);
}

static void handle_CtrlC_CtrlV(map::CMap & stageMap,
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

        std::vector<map::CTile> selection_data(pt_data_len.x * pt_data_len.y, map::CTile(map::ETileType::GRASS));

        for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
            for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                selection_data.at(ys * (pt_data_len.x) + xs) = stageMap(region.first.x + xs, region.first.y + ys);
            }
        }

        for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
            for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                stageMap(x + xs, y + ys) = selection_data.at(ys * (pt_data_len.x) + xs);
            }
        }

        g_draw_selection = false;
        g_copy_selection_on = false;
    }
}

/// treats clicks inside map area
static void handle_click(map::CMap & stageMap,
                         const int X,
                         const int Y,
                         const int button) {
    // aplica o deslocamento da tela e normaliza o x,y do mouse para unidades de TILE_SIZE
    const size_t x = (X + g_map_drawx) / TILE_SIZE;
    const size_t y = (Y + g_map_drawy) / TILE_SIZE;

    if (x >= stageMap.width() || y >= stageMap.height())
        return; // out of map
    switch (button) {
        case 1: {
            if (!key[KEY_LCONTROL]) { // CTRL is not pressed.
                stageMap(x, y).type(g_cur_tile_type);
            } else { // CTRL is pressed.
                if (key[KEY_C] || key[KEY_V]) {
                    handle_CtrlC_CtrlV(stageMap, x, y);
                }
            }
        }
        break;
        case 2: {
            // only ROADS may receive actions
            if (stageMap(x, y).type() == map::ETileType::ROAD)
                stageMap(x, y).action(g_cur_act);
        }
        break;
    }
}

/// loads all actions from file.
static actions_t load_actions(const std::string & file_name,
                              const unsigned actions_num) {
    std::map<map::EAction, point_t> pos;
    unsigned x = ACTION_X0, y = ACTION_Y0;

    for (auto act : util::CEnumIterator<map::EAction>()) {
        pos.insert(std::make_pair(act, point_t{x, y}));

        x += ACTION_SPACE;
        if (x >= ACTION_MAX_X) {
            x = ACTION_X0;
            y += ACTION_SPACE;
        }
    }


    constexpr unsigned GAP = 1;

    printf("ACTIONS loaded!\n");

    return actions_t(gamelib::allegro::bmp::CActionMapper(file_name, TILE_SIZE, TILE_SIZE, GAP), pos);
}

/// loads all tiles from file.
static tiles_t load_tiles(const std::string & file_name,
                          const unsigned tiles_num) {
    constexpr unsigned GAP = 2;
    std::map<map::ETileType, point_t> pos;

    unsigned x = TILES_MARGIN;
    unsigned y = UTIL_H;
    for (const auto type : util::CEnumIterator<map::ETileType>()) {
        if (x + TILE_SPACE > UTIL_W) {
            x = TILES_MARGIN;
            y += TILE_SPACE;
        }
        pos.insert(std::make_pair(type, point_t{x + TILE_GAP, y + TILES_MARGIN}));
        x += TILE_SPACE;
    }

    printf("TILESET loaded!\n");

    return tiles_t(gamelib::allegro::bmp::CTileMapper(file_name, TILE_SIZE, TILE_SIZE, GAP), pos);
}

static void draw_grid(BITMAP * bmp) {
    static const int color = makecol(255, 255, 255);
    for (int i = 0; i < SCREEN_W; i += TILE_SIZE)
        vline(bmp, i, 0, SCREEN_H, color);

    for (int i = 0; i < SCREEN_H; i += TILE_SIZE)
        hline(bmp, 0, i, SCREEN_W, color);
}

map::CMap createOrLoadMap(int argc, char *argv[]) {
    const std::string tmp = std::string(argv[1] + std::string("/stage.dat"));
    boost::filesystem::path pathToFile(tmp);
    if (boost::filesystem::exists(pathToFile)) {
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

int main(int argc, char *argv[]) {
    try {
        const auto tiles_num = map::from_ETile<unsigned int>(map::ETileType::LAST);
        const auto act_num = map::from_EAction<unsigned int>(map::EAction::LAST);

        g_map_drawx = g_map_drawy = 0;

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

        gamelib::allegro::BITMAP_PTR buffer(create_bitmap(SCREEN_W, SCREEN_H), destroy_bitmap);
        g_selection_preview = create_bitmap(185, 150);

        clear_bitmap(g_selection_preview);

        if (argc <= 1) {
            exit(-1);
        }
        const std::string tmp = argv[1] + std::string("/stage.dat");

        map::CMap stageMap = createOrLoadMap(argc, argv);

        const auto tileMapper(load_tiles(RALLY_ROOT "/Stuff/tileset.bmp", tiles_num));
        const auto actionMapper(load_actions(RALLY_ROOT "/Stuff/actions.bmp", act_num));

        while (!key[KEY_ESC]) {
            handle_tilebar(tileMapper);
            handle_actbar(actionMapper);

            if ((unsigned) mouse_x < UTIL_W && (unsigned) mouse_y < UTIL_H) {
                if (mouse_b & 1) handle_click(stageMap, mouse_x, mouse_y, 1);
                if (mouse_b & 2) handle_click(stageMap, mouse_x, mouse_y, 2);
            }

            if (key[KEY_RIGHT] && g_draw_selection == false) {
                if ((g_map_drawx / TILE_SIZE) < (g_max_x - TILES_X)) {
                    g_map_drawx += TILE_SIZE;
                }
            } else if (key[KEY_LEFT] && g_draw_selection == false) {
                if (g_map_drawx > 0) {
                    g_map_drawx -= TILE_SIZE;
                }
            }

            if (key[KEY_UP] && g_draw_selection == false) {
                if (g_map_drawy > 0) {
                    g_map_drawy -= TILE_SIZE;
                }
            } else if (key[KEY_DOWN] && g_draw_selection == false) {
                if ((g_map_drawy / TILE_SIZE) < (g_max_y - TILES_Y)) {
                    g_map_drawy += TILE_SIZE;
                }
            }

            if (key[KEY_D] && g_draw_selection == false) {
                g_map_drawx += STEP_X;
                if (g_map_drawx / TILE_SIZE >= (g_max_x - TILES_X))
                    g_map_drawx = (g_max_x - TILES_X) * TILE_SIZE;

                tools::hold_while_pressed(KEY_D);
            } else if (key[KEY_A] && g_draw_selection == false) {
                if (g_map_drawx < STEP_X)
                    g_map_drawx = 0;
                else
                    g_map_drawx -= STEP_X;

                tools::hold_while_pressed(KEY_A);
            }

            if (key[KEY_W] && g_draw_selection == false) {
                if (g_map_drawy < STEP_Y)
                    g_map_drawy = 0;
                else
                    g_map_drawy -= STEP_Y;


                tools::hold_while_pressed(KEY_W);
            } else if (key[KEY_S] && g_draw_selection == false) {
                g_map_drawy += STEP_Y;
                if (g_map_drawy / TILE_SIZE >= (g_max_y - TILES_Y))
                    g_map_drawy = (g_max_y - TILES_Y) * TILE_SIZE;

                tools::hold_while_pressed(KEY_S);
            }

            if (key[KEY_LSHIFT]) {
                map_save(tmp, stageMap);
                // Evita que fique salvando loucamente o mapa, segura até o sujeito soltar a tecla.
                tools::hold_while_pressed(KEY_LSHIFT);
            }

            if (key[KEY_X]) {
                g_copy_selection_on = false;
                g_draw_selection = false;
            }

            const bool draw_actions = key[KEY_SPACE];

            map_draw(buffer.get(), stageMap, tileMapper, actionMapper, g_map_drawx, g_map_drawy, draw_actions);

            if (!key[KEY_G]) {
                if (g_take_shot == false)
                    draw_grid(buffer.get());
            }
            draw_tilesbar(buffer.get(), tileMapper, tiles_num);
            draw_actionsbar(buffer.get(), actionMapper, act_num);
            draw_manual(buffer.get());

            if (key[KEY_I]) {
                int xpos, ypos;
                xpos = mouse_x / TILE_SIZE * TILE_SIZE;
                if (key[KEY_O]) xpos += mouse_x % TILE_SIZE - TILE_SIZE / 2;
                ypos = mouse_y / TILE_SIZE * TILE_SIZE;
                if (key[KEY_O]) ypos += mouse_y % TILE_SIZE - TILE_SIZE / 2;
                action_draw(buffer.get(), actionMapper.mapper, g_cur_act, xpos, ypos);
            } else if (g_take_shot == false) {
                circlefill(buffer.get(), mouse_x, mouse_y, 5, 0);
                circlefill(buffer.get(), mouse_x, mouse_y, 3,  makecol(255, 255, 255));
            }

            if (g_draw_selection == true) {
                const auto region = define_region(g_copy_ini_point, g_copy_end_point);
                const auto xini = (region.first.x * TILE_SIZE) - g_map_drawx;
                const auto yini = (region.first.y * TILE_SIZE) - g_map_drawy;
                const auto xend = ((region.second.x + 1) * TILE_SIZE) - g_map_drawx;
                const auto yend = ((region.second.y + 1) * TILE_SIZE) - g_map_drawy;

                if (g_take_shot == true) {
                    stretch_blit(buffer.get(), g_selection_preview, xini, yini, xend - xini, yend - yini,
                                 0, 0, g_selection_preview->w, g_selection_preview->h);
                    g_take_shot = false;
                }
                rect(buffer.get(),
                     SCREEN_W - 194, SCREEN_H - 392,
                     SCREEN_W - 194 + g_selection_preview->w + 3, SCREEN_H - 392 + g_selection_preview->h + 3,
                     makecol(255, 255, 255));

                blit(g_selection_preview, buffer.get(), 0, 0, SCREEN_W - 192, SCREEN_H - 390, g_selection_preview->w, g_selection_preview->h);

                set_trans_blender(128, 128, 128, 128);
                drawing_mode(DRAW_MODE_TRANS, nullptr, 0, 0);
                rectfill(buffer.get(), xini, yini, xend, yend, makecol(30, 30, 255));
                drawing_mode(DRAW_MODE_SOLID, nullptr, 0, 0);
                rect(buffer.get(), xini, yini, xend, yend, 0);
                rect(buffer.get(), xini + 1, yini + 1, xend - 1, yend - 1, 0);
            }

            vsync();
            blit(buffer.get(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            clear_bitmap(buffer.get());
        }
        return 0;
    } catch (std::exception & e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()

