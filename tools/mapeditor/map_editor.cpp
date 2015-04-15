/*
 * TODO: Definir um header bonitinho.
 * NOTA: SUPER HIPER N�O OPTIMIZADO, n�o tem que ser, ele s� monta o mapa, n�o tem a��o nenhuma nele.
*/

// T + MOUSE_1 - Seta tile como solido.
// F - N�o mostra as informa��es sobre o tile (Numero da a��o associada)
// G - N�o mostra o grid
// Space - N�o mostra os tiles, somente as a��es
// O - Mostra offsetX dentro do tile atual (seta offset ao colocar a��o)
// W S A D - Move uma tela por vez na dire��o norte sul lest oeste
// Left/Right/Up/Down - Move um tile por vez na dire��o obvia :D
// I - Mostra a a��o no mapa para referencia (n�o considera o offset, usar tecla 'O' junto)
// Left SHIFT - Salva
// M - Mostra as a��es sobre o mapa.
// CTRL+C + (MOUSE) - Seta pontos de inicio e fim para copia
// CTRL+V + (MOUSE) - Efetua copia partindo do ponto atual.
// CTRL+X - Desfaz sele��o.

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

// TODO:
// Usando os defines no megaman, temos que rever isso aqui.
// O jogo original tem uma resolu��o de 288 x 224, sugiro que a gente dobre: 576 x 448
// Verificar tamanho dos tiles e setar um novo pra gente.
static constexpr unsigned TILE_SIZE     = 32;                               ///< tile size in pixels
static constexpr unsigned TILE_GAP      = 4;                                ///< space around a tile at the tiles bar
static constexpr unsigned TILE_SPACE    = TILE_SIZE + 2 * TILE_GAP;         ///< total space used by a tile
static constexpr unsigned UTIL_COLUMNS  = 16;                               ///< number of rows of tiles that are shown in the window
static constexpr unsigned UTIL_ROWS     = 15;                               ///< number of columns of tiles that are shown in the window
static constexpr unsigned UTIL_W        = TILE_SIZE * UTIL_COLUMNS + 10;    ///< map window width
static constexpr unsigned UTIL_H        = TILE_SIZE * UTIL_ROWS + 10;       ///< map window height
static constexpr unsigned UTIL_H_EX     = 250;                              ///< ?
static constexpr unsigned TILES_X       = UTIL_W / TILE_SIZE;               ///< number of whole tiles in the horizontal direction
static constexpr unsigned TILES_Y       = UTIL_H / TILE_SIZE;               ///< number of whole tiles in the vertical direction
static constexpr unsigned STEP_X        = TILE_SIZE * TILES_X;              ///< ?
static constexpr unsigned STEP_Y        = TILE_SIZE * TILES_Y;              ///< ?

static map::ETileType g_cur_tile_type = map::ETileType::GRASS;
static map::EAction g_cur_act = map::EAction::NONE;
static unsigned g_map_drawx, g_map_drawy;
static unsigned g_max_x, g_max_y;
static unsigned char g_default_tile;

constexpr unsigned char ROAD_CONSTANT = 6;

struct point_t {
    unsigned x, y;
};

struct tiles_t {
    std::vector<point_t> xy_pos;
};
static tiles_t g_tiles;

struct actions_t {
    std::vector<BITMAP *> tile_img;
    point_t * coords;
};
static actions_t g_actions;

// Variaveis usadas pelo CTRL+C CTRL+V
static int g_cur_copy_point = 0;
static point_t g_pt_ini_point;
static point_t g_pt_end_point;
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

static void tile_draw(BITMAP * bmp,
                      const gamelib::allegro::bmp::CTileMapper & mapper,
                      const map::ETileType type,
                      const int x,
                      const int y) {
    const auto tile_bmp = mapper[type];
    draw_sprite(bmp, tile_bmp, x, y);
}

// Desenha o mapa partindo do map_drawx, map_drawy.
// Se draw_actions = true, mostra as actions ao invez do desenho do tile.
// Se ignoreVoid = true, desenha as actios E o desenho dos tiles.
static void map_draw(BITMAP * bmp,
                     const map::CMap & stageMap,
                     const gamelib::allegro::bmp::CTileMapper & tileMapper,
                     const int map_drawx,
                     const int map_drawy,
                     const bool draw_actions,
                     const bool ignoreVoid) {
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
            tile_draw(bmp, tileMapper, tile.type(), x, y);
            if (ignoreVoid == true) {
                if (tile.action() != map::EAction::NONE) {
                    draw_sprite(bmp, g_actions.tile_img[map::from_EAction<size_t>(tile.action())], x, y);
                }
            } else if (draw_actions == true) {
                draw_sprite(bmp, g_actions.tile_img[map::from_EAction<size_t>(tile.action())], x, y);
            }

            if (key[KEY_F] == 0 && g_take_shot == false) {
                textprintf_ex(bmp, font, x, y, 0, color[2], "%02d", map::from_EAction<int>(stageMap(X, Y).action()));
            }
        }
    }
}

static void draw_tilesbar(BITMAP * bmp,
                          const gamelib::allegro::bmp::CTileMapper & tileMapper,
                          const int tiles_num,
                          int y) {
    rectfill(bmp, 0, y, UTIL_W, y + UTIL_H_EX, makecol(30, 40, 100));
    constexpr unsigned MARGIN = 8;
    unsigned x = MARGIN;
    for (int i = 0; i < tiles_num; ++i) {
        if (x + TILE_SPACE > UTIL_W) {
            x = MARGIN;
            y += TILE_SPACE;
        }
        g_tiles.xy_pos[i].x = x + TILE_GAP;
        g_tiles.xy_pos[i].y = y + MARGIN;
        tile_draw(bmp, tileMapper, map::to_ETile(i), g_tiles.xy_pos[i].x, g_tiles.xy_pos[i].y);
        x += TILE_SPACE;
    }

    x = g_tiles.xy_pos[map::from_ETile<int>(g_cur_tile_type)].x;
    y = g_tiles.xy_pos[map::from_ETile<int>(g_cur_tile_type)].y;

    rect(bmp, x - TILE_GAP, y - TILE_GAP, x + TILE_SPACE - TILE_GAP, y + TILE_SPACE - TILE_GAP, makecol(255, 255, 255));
}

// Desenha painel das actions
static void draw_actionsbar(BITMAP *bmp,
                            const unsigned act_num,
                            const unsigned x) {
    rectfill(bmp, x, 0, x + 200, SCREEN_H, makecol(255, 255, 255));
    rectfill(bmp, x + 4, 4, x + 196, SCREEN_H - 4, makecol(0, 50, 50));

    for (unsigned i = 0; i < act_num; ++i) {
        draw_sprite(bmp, g_actions.tile_img[i], x + g_actions.coords[i].x, g_actions.coords[i].y);
        if (g_cur_act == map::to_EAction(i)) {
            rect(bmp, (x + g_actions.coords[i].x) - 2,
                 g_actions.coords[i].y - 2,
                 (x + g_actions.coords[i].x) + 33,
                 g_actions.coords[i].y + 33,
                 makecol(255, 50, 50));
        }
    }

    if ((unsigned) mouse_x < UTIL_W && (unsigned) mouse_y < UTIL_H) {
        int mx = mouse_x / TILE_SIZE;
        int my = mouse_y / TILE_SIZE;
        char tmp[80];
        int bg, fg;
        bg = makecol(255, 255, 255);
        fg = makecol(0, 50, 200);
        sprintf(tmp, "mouse_x: [%02d]", mouse_x);
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 36, fg, bg, "%-20s", tmp);
        sprintf(tmp, "mouse_y: [%02d]", mouse_y);
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 28, fg, bg, "%-20s", tmp);
        sprintf(tmp, "mapx: [%02d]", mx);
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 20, fg, bg, "%-20s", tmp);
        sprintf(tmp, "mapy: [%02d]", my);
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 12, fg, bg, "%-20s", tmp);
    }

    if (key[KEY_O])
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 50, makecol(0, 50, 200), makecol(255, 255, 255), "OFFSET: %02u", (unsigned) mouse_x % TILE_SIZE);

    if (g_draw_selection == true)
        textprintf_ex(bmp, font, x + 8, SCREEN_H - 80, makecol(255, 0, 0), 0, "SELECTION ON-SCROLL OFF");
}

// Captura qual tile deve ser o corrente.
static void handle_tilebar(int tiles_num) {
    if (mouse_b & 1) {
        if ((unsigned) mouse_y >= UTIL_H) {
            const unsigned y = mouse_y;
            const unsigned x = mouse_x;
            for (int i = 0; i < tiles_num; ++i) {
                if ((x >= g_tiles.xy_pos[i].x)    &&
                        (x <= g_tiles.xy_pos[i].x + TILE_SIZE) &&
                        (y >= g_tiles.xy_pos[i].y)    &&
                        (y <= g_tiles.xy_pos[i].y + TILE_SIZE)) {
                    g_cur_tile_type = map::to_ETile(i);
                    break;
                }
            }
        }
    }
}

// Cuida do mouse sobre o painel de actions.
static void handle_actbar(int act_num) {
    // bot�o da direita do mouse precionado.
    if (mouse_b & 2) {
        if (mouse_x >= 512) {
            const unsigned x = mouse_x;
            const unsigned y = mouse_y;
            for (int i = 0; i < act_num; ++i) {
                if (x >= g_actions.coords[i].x + 512 &&
                        x <= g_actions.coords[i].x + 512 + 40 &&
                        y >= g_actions.coords[i].y &&
                        y <= g_actions.coords[i].y + 40) {
                    g_cur_act = map::to_EAction(i);
                    break;
                }
            }
        }
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
            static std::vector<map::CTile> g_selection_data;
            // CTRL n�o est� pressionado.
            if (!key[KEY_LCONTROL]) {
                stageMap(x, y).type(g_cur_tile_type);
            } else {
                if (key[KEY_C]) {
                    if (g_cur_copy_point == 0) {
                        g_selection_data.clear();
                        clear_bitmap(g_selection_preview);

                        g_pt_ini_point.x = x;
                        g_pt_ini_point.y = y;
                        g_cur_copy_point = 1;
                        g_draw_selection = false;
                    } else {
                        g_pt_end_point.x = x;
                        g_pt_end_point.y = y;
                        if (g_pt_end_point.x < g_pt_ini_point.x || g_pt_end_point.y < g_pt_ini_point.y) {
                            point_t temp = g_pt_ini_point;
                            g_pt_ini_point = g_pt_end_point;
                            g_pt_end_point = temp;
                        }
                        g_take_shot = true;
                        g_draw_selection = true;
                    }
                } else if (key[KEY_V]) {
                    point_t pt_data_len;
                    pt_data_len.x = (g_pt_end_point.x - g_pt_ini_point.x) + 1;
                    pt_data_len.y = (g_pt_end_point.y - g_pt_ini_point.y) + 1;

                    if (g_selection_data.empty()) {
                        g_selection_data.resize(pt_data_len.x * pt_data_len.y, map::CTile(map::ETileType::GRASS));

                        for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
                            for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                                g_selection_data.at(ys * (pt_data_len.x) + xs) = stageMap(g_pt_ini_point.x + xs, g_pt_ini_point.y + ys);
                            }
                        }
                    }

                    for (unsigned ys = 0; ys < pt_data_len.y; ++ys) {
                        for (unsigned xs = 0; xs < pt_data_len.x; ++xs) {
                            stageMap(x + xs, y + ys) = g_selection_data.at(ys * (pt_data_len.x) + xs);
                        }
                    }

                    g_draw_selection = false;
                    g_cur_copy_point = 0;
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

/// loads actions
static void load_actions(const int num_actions,
                         const std::string & path) {
    g_actions.tile_img = std::vector<BITMAP *>(num_actions, nullptr);
    g_actions.coords = new point_t[num_actions];
    int x = 20, y = 10;

    char img_name[16];
    for (int i = 0; i < num_actions; ++i) {
        sprintf(img_name, "/%02d.bmp", i);
        const std::string full_name = path + img_name;
        printf("carregando action [%s]\n", full_name.c_str());

        BITMAP * tile = load_bitmap(full_name.c_str(), nullptr);
        if (tile == nullptr)
            tools::throw_allegro_error(full_name);
        g_actions.tile_img[i] = tile;
        g_actions.coords[i].x = x;
        g_actions.coords[i].y = y;

        x += 40;
        if (x >= 180) { x = 20; y += 40; }
    }
}

/// loads all tiles from file.
static gamelib::allegro::bmp::CActionMapper load_actions(const std::string & dir,
                                                         const unsigned actions_num) {
    const std::string actionst_name = dir + "/actions.bmp";
    constexpr unsigned GAP = 1;

    printf("ACTIONS loaded!\n");

    return gamelib::allegro::bmp::CActionMapper(actionst_name, TILE_SIZE, TILE_SIZE, GAP);
}

/// loads all tiles from file.
static gamelib::allegro::bmp::CTileMapper load_tiles(const std::string & dir,
                                                     const unsigned tiles_num) {
    const std::string tile_name = dir + "/tileset.bmp";
    constexpr unsigned GAP = 2;
    constexpr point_t xy = {0, 0};
    g_tiles.xy_pos = std::vector<point_t>(tiles_num, xy);

    printf("TILESET loaded!\n");

    return gamelib::allegro::bmp::CTileMapper(tile_name, TILE_SIZE, TILE_SIZE, GAP);
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
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, UTIL_W + 200, UTIL_H + UTIL_H_EX, 0, 0);

        BITMAP * buffer     = create_bitmap(SCREEN_W, SCREEN_H);
        g_selection_preview = create_bitmap(185, 150);

        clear_bitmap(g_selection_preview);

        if (argc <= 1) {
            exit(-1);
        }
        const std::string tmp = argv[1] + std::string("/stage.dat");

        map::CMap stageMap = createOrLoadMap(argc, argv);

        load_actions(act_num, "./actions");
        const gamelib::allegro::bmp::CTileMapper tileMapper(load_tiles(RALLY_ROOT "/Stuff", tiles_num));
        const gamelib::allegro::bmp::CActionMapper actionMapper(load_actions(RALLY_ROOT "/Stuff", act_num));

        bool draw_actions = false;
        bool ignoreVoid   = false;
        while (!key[KEY_ESC]) {
            handle_tilebar(tiles_num);
            handle_actbar(act_num);

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
                // Evita que fique salvando loucamente o mapa, segura at� o sujeito soltar a tecla.
                tools::hold_while_pressed(KEY_LSHIFT);
            }

            if (key[KEY_SPACE]) {
                draw_actions = true;
            } else {
                draw_actions = false;
            }

            if (key[KEY_M])
                ignoreVoid = true;
            else
                ignoreVoid = false;

            if (key[KEY_X]) {
                g_cur_copy_point = 0;
                g_draw_selection = false;
            }

            map_draw(buffer, stageMap, tileMapper, g_map_drawx, g_map_drawy, draw_actions, ignoreVoid);

            if (!key[KEY_G]) {
                if (g_take_shot == false)
                    draw_grid(buffer);
            }
            draw_tilesbar(buffer, tileMapper, tiles_num, UTIL_H);
            draw_actionsbar(buffer, act_num, UTIL_W);

            if (key[KEY_I]) {
                int xpos, ypos;
                xpos = mouse_x / TILE_SIZE * TILE_SIZE;
                if (key[KEY_O]) xpos += mouse_x % TILE_SIZE;
                ypos = mouse_y / TILE_SIZE * TILE_SIZE;
                draw_sprite(buffer, g_actions.tile_img[map::from_EAction<int>(g_cur_act)], xpos, ypos);
            } else if (g_take_shot == false) {
                circlefill(buffer, mouse_x, mouse_y, 5, 0);
                circlefill(buffer, mouse_x, mouse_y, 3,  makecol(255, 255, 255));
            }

            if (g_draw_selection == true) {
                int xini, yini, xend, yend;

                xini = (g_pt_ini_point.x * TILE_SIZE) - g_map_drawx;
                yini = g_pt_ini_point.y * TILE_SIZE;
                xend = xini + TILE_SIZE - g_map_drawx;
                yend = yini + TILE_SIZE;

                if (g_take_shot == true) {
                    stretch_blit(buffer, g_selection_preview, xini, yini, xend - xini, yend - yini,
                                 0, 0, g_selection_preview->w, g_selection_preview->h);
                    g_take_shot = false;
                }
                rect(buffer, SCREEN_W - 194, SCREEN_H - 392,
                     SCREEN_W - 194 + g_selection_preview->w + 3, SCREEN_H - 392 + g_selection_preview->h + 3,
                     makecol(255, 255, 255));

                blit(g_selection_preview, buffer, 0, 0, SCREEN_W - 192, SCREEN_H - 390, g_selection_preview->w, g_selection_preview->h);

                set_trans_blender(128, 128, 128, 128);
                drawing_mode(DRAW_MODE_TRANS, nullptr, 0, 0);
                rectfill(buffer, xini, yini, xend, yend, makecol(30, 30, 255));
                drawing_mode(DRAW_MODE_SOLID, nullptr, 0, 0);
                rect(buffer, xini, yini, xend, yend, 0);
                rect(buffer, xini + 1, yini + 1, xend - 1, yend - 1, 0);
            }

            vsync();
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            clear_bitmap(buffer);
        }
        return 0;
    } catch (std::exception & e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()

