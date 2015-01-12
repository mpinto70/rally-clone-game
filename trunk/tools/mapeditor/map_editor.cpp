/*
 * TODO: Definir um header bonitinho.
 * NOTA: SUPER HIPER NÃO OPTIMIZADO, não tem que ser, ele só monta o mapa, não tem ação nenhuma nele.
*/

// T + MOUSE_1 - Seta tile como solido.
// F - Não mostra as informações sobre o tile (Numero da ação associada)
// G - Não mostra o grid
// Space - Não mostra os tiles, somente as ações
// O - Mostra offsetX dentro do tile atual (seta offset ao colocar ação)
// W S A D - Move uma tela por vez na direção norte sul lest oeste
// Left/Right/Up/Down - Move um tile por vez na direção obvia :D
// I - Mostra a ação no mapa para referencia (não considera o offset, usar tecla 'O' junto)
// Left SHIFT - Salva
// M - Mostra as ações sobre o mapa.
// CTRL+C + (MOUSE) - Seta pontos de inicio e fim para copia
// CTRL+V + (MOUSE) - Efetua copia partindo do ponto atual.
// CTRL+X - Desfaz seleção.

#include <allegro.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <vector>

// TODO:
// Usando os defines no megaman, temos que rever isso aqui.
// O jogo original tem uma resolução de 288 x 224, sugiro que a gente dobre: 576 x 448
// Verificar tamanho dos tiles e setar um novo pra gente.
constexpr int  TILE_SIZE = 32;
constexpr int  UTIL_W    = 512;
constexpr int  UTIL_H    = 480;
constexpr int  UTIL_H_EX = 420;
constexpr int  TS_X_TLS  = 15;
constexpr int  TILES_X   = UTIL_W / TILE_SIZE;
constexpr int  TILES_Y   = UTIL_H / TILE_SIZE;

typedef struct {
    unsigned char tile_number; // Indice na tabela de desenhos
    bool is_solid;             // Indica se o tile eh solido ou nao
    unsigned char action;      // Existe alguma acao associada? Criar inimigo, Criar pedra?
    int xOffset;               // Deslocamento dentro do tile da posicao x,y real do action (evitar restringir ao tilesize os alinhamentos)
} MAP_INFO;

// Y linhas com X colunas.
MAP_INFO **g_map;

int g_cur_tile = 0;
int g_cur_act  = 0;
int g_map_drawx, g_map_drawy;
int g_max_x, g_max_y;
unsigned char g_default_tile;

// Tabela de desenhos para a fase.
BITMAP * g_tileset;

struct point_t {
    int x, y;
};

struct tiles_t {
    std::vector<BITMAP*> tile_img;
    std::vector<point_t> xy_pos;
};
tiles_t g_tiles;

struct actions_t {
    BITMAP ** tile_img;
    point_t * coords;
};
actions_t g_actions;

// Variaveis usadas pelo CTRL+C CTRL+V
int g_cur_copy_point = 0;
point_t g_pt_ini_point;
point_t g_pt_end_point;
bool g_draw_selection = false;
bool g_take_shot = false;
MAP_INFO * g_selection_data = NULL;
BITMAP * g_selection_preview;

void map_save(char * filename) {
    FILE * fp = fopen(filename, "wb+");

    // Tamanho em x e y
    fwrite(&g_max_x, sizeof(int), 1, fp);
    fwrite(&g_max_y, sizeof(int), 1, fp);

    // Qual o tile default (valor usado para inicializar o mapa)
    fwrite(&g_default_tile, sizeof(unsigned char), 1, fp);

    for (int i = 0; i < g_max_y; i++) {
        fwrite(&g_map[i][0], sizeof(MAP_INFO), g_max_x, fp);
    }

    fclose(fp);
}

int map_load(FILE * fp) {
    if (fread(&g_max_x, sizeof(int), 1, fp) != 1) return 1;
    if (fread(&g_max_y, sizeof(int), 1, fp) != 1) return 2;
    if (fread(&g_default_tile, sizeof(unsigned char), 1, fp) != 1) return 3;

    g_map = (MAP_INFO**) malloc(sizeof(MAP_INFO*) * g_max_y);
    for (int i = 0; i < g_max_y; i++) {
        g_map[i] = (MAP_INFO*) malloc(sizeof(MAP_INFO) * g_max_x);
        if (fread(&g_map[i][0], sizeof(MAP_INFO), g_max_x, fp) != (unsigned int) g_max_x) return 4;
    }

    fclose(fp);

    return 0;
}

void tile_draw(BITMAP * bmp, int tile_number, int x, int y) {
    draw_sprite(bmp, g_tiles.tile_img[tile_number], x, y);
}

// Desenha o mapa partindo do map_drawx, map_drawy.
// Se draw_actions = true, mostra as actions ao invez do desenho do tile.
// Se ignoreVoid = true, desenha as actios E o desenho dos tiles.
void map_draw(BITMAP * bmp, int map_drawx, int map_drawy, bool draw_actions, bool ignoreVoid) {
    int i, j;
    int mapx, mapy;
    int map_xoff, map_yoff;
    static int color[] = {makecol32(30, 30, 30), makecol32(255, 0, 0), makecol32(255, 255, 255)};

    mapx = map_drawx / TILE_SIZE;
    mapy = map_drawy / TILE_SIZE;

    map_xoff = map_drawx & (TILE_SIZE - 1);
    map_yoff = map_drawy & (TILE_SIZE - 1);

    int x, y;
    int xdisp = mapx + TILES_X == g_max_x ? 0 : 1;
    int ydisp = mapy + TILES_Y == g_max_y ? 0 : 1;
    for (i = 0; i < TILES_Y + ydisp; i++) {
        for (j = 0; j < TILES_X + xdisp; j++) {
            x = j * TILE_SIZE - map_xoff;
            y = i * TILE_SIZE - map_yoff;

            tile_draw(bmp, g_map[mapy + i][mapx + j].tile_number, x, y);
            if (ignoreVoid == true) {
                if (g_map[mapy + i][mapx + j].action != 0) {
                    x += g_map[mapy + i][mapx + j].xOffset;
                    draw_sprite(bmp, g_actions.tile_img[g_map[mapy + i][mapx + j].action], x, y);
                }
            } else if (draw_actions == true) {
                draw_sprite(bmp, g_actions.tile_img[g_map[mapy + i][mapx + j].action], x, y);
            }

            if (key[KEY_F] == 0 && g_take_shot == false) {
                if (g_map[mapy + i][mapx + j].is_solid == false) {
                    textprintf_ex(bmp, font, x, y, 0, color[2], "%02d", g_map[mapy + i][mapx + j].action);
                } else {
                    textprintf_ex(bmp, font, x, y, color[2], color[1], "%02d", g_map[mapy + i][mapx + j].action);
                }
            }
        }
    }
}

void draw_tilesbar(BITMAP * bmp, int tiles_num, int y) {
    rectfill(bmp, 0, y, 512, y + UTIL_H_EX, makecol(30, 40, 100));

    int x = 8;
    for (int i = 0, j = 0; i < tiles_num; i++) {
        g_tiles.xy_pos[i].x = x + 1;
        g_tiles.xy_pos[i].y = y + 8;
        draw_sprite(bmp, g_tiles.tile_img[i], g_tiles.xy_pos[i].x, g_tiles.xy_pos[i].y);
        x += 33;

        j++;
        if (j == TS_X_TLS) {
            j = 0;
            y += 33;
            x = 8;
        }
    }

    x = g_tiles.xy_pos[g_cur_tile].x;
    y = g_tiles.xy_pos[g_cur_tile].y;

    rect(bmp, x,  y,  x + 32, y + 32, makecol(255, 10, 10));
    rect(bmp, x - 1, y - 1, x + 33, y + 33, makecol(255, 255, 255));
}

// Desenha painel das actions
void draw_actionsbar(BITMAP *bmp, int act_num, int x) {
    rectfill(bmp, x, 0, x + 200, SCREEN_H, makecol(255, 255, 255));
    rectfill(bmp, x + 4, 4, x + 196, SCREEN_H - 4, makecol(0, 50, 50));

    for (int i = 0; i < act_num; i++) {
        draw_sprite(bmp, g_actions.tile_img[i], x + g_actions.coords[i].x, g_actions.coords[i].y);
        if (g_cur_act == i) {
            rect(bmp, (x + g_actions.coords[i].x) - 2,
                            g_actions.coords[i].y - 2,
                 (x + g_actions.coords[i].x) + 33,
                 g_actions.coords[i].y + 33,
                 makecol(255, 50, 50));
        }
    }

    if (mouse_x < UTIL_W && mouse_y < UTIL_H) {
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
        textprintf_ex(bmp, font, x + 20, SCREEN_H - 50, makecol(0, 50, 200), makecol(255, 255, 255), "OFFSET: %02d", mouse_x % TILE_SIZE);

    if (g_draw_selection == true)
        textprintf_ex(bmp, font, x + 8, SCREEN_H - 80, makecol(255, 0, 0), 0, "SELECTION ON-SCROLL OFF");
}

// Captura qual tile deve ser o corrente.
void handle_tilebar(int tiles_num) {
    if (mouse_b & 1) {
        if (mouse_y >= 480) {
            int x = mouse_x;
            int y = mouse_y;
            for (int i = 0; i < tiles_num; i++) {
                if ((x >= g_tiles.xy_pos[i].x)    &&
                        (x <= g_tiles.xy_pos[i].x + 33) &&
                        (y >= g_tiles.xy_pos[i].y)    &&
                        (y <= g_tiles.xy_pos[i].y + 33))
                { g_cur_tile = i; break; }
            }
        }
    }
}

// Cuida do mouse sobre o painel de actions.
void handle_actbar(int act_num) {
    // botão da direita do mouse precionado.
    if (mouse_b & 2) {
        if (mouse_x >= 512) {
            int x = mouse_x;
            int y = mouse_y;
            for (int i = 0; i < act_num; i++) {
                if (x >= g_actions.coords[i].x + 512 &&
                        x <= g_actions.coords[i].x + 512 + 40 &&
                        y >= g_actions.coords[i].y &&
                        y <= g_actions.coords[i].y + 40) {
                    g_cur_act = i;
                    break;
                }
            }
        }
    }
}

// Cuida de clique na area do mapa.
void handle_click(int x, int y, int button) {
    // normaliza o x,y do mouse para unidades de TILE_SIZE
    x = x / TILE_SIZE;
    y = y / TILE_SIZE;

    // Adiciona o deslocamento (scroll) do mapa.
    // De forma que os indices corretos do mapa sejam acessados.
    x += (g_map_drawx >> 5);
    y += (g_map_drawy >> 5);

    switch (button) {
        case 1: {
            // CTRL não está precionado.
            if (!key[KEY_LCONTROL]) {
                g_map[y][x].tile_number = g_cur_tile;
            } else {
                if (key[KEY_C]) {
                    if (g_cur_copy_point == 0) {
                        free(g_selection_data);
                        clear_bitmap(g_selection_preview);
                        g_selection_data = NULL;

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

                    if (g_selection_data == NULL) {
                        g_selection_data = (MAP_INFO*) malloc(sizeof(MAP_INFO) * (pt_data_len.x * pt_data_len.y));

                        for (int ys = 0; ys < pt_data_len.y; ++ys) {
                            for (int xs = 0; xs < pt_data_len.x; ++xs) {
                                g_selection_data[ys * (pt_data_len.x) + xs] = g_map[g_pt_ini_point.y + ys][g_pt_ini_point.x + xs];
                            }
                        }
                    }

                    for (int ys = 0; ys < pt_data_len.y; ++ys) {
                        for (int xs = 0; xs < pt_data_len.x; ++xs) {
                            g_map[y + ys][x + xs] = g_selection_data[ys * (pt_data_len.x) + xs];
                        }
                    }

                    g_draw_selection = false;
                    g_cur_copy_point = 0;
                }
            }
        }
        break;
        case 2: {
            g_map[y][x].action = g_cur_act;
            // Se tecla O precionada durante esse evento, seta o deslocamento da action em relacao ao tile.
            if (key[KEY_O]) {
                int offset = mouse_x % TILE_SIZE;
                g_map[y][x].xOffset = offset;
            } else {
                g_map[y][x].xOffset = 0;
            }

            // Se T precionado seta tile como sólido.
            if (key[KEY_T]) {
                g_map[y][x].is_solid = true;
            } else {
                g_map[y][x].is_solid = false;
            }
        }
        break;
    }
}

// Carrega as actions;
void load_actions(char * path, int num_actions) {
    g_actions.tile_img = (BITMAP **) malloc(sizeof(BITMAP*)*num_actions);
    g_actions.coords = new point_t[num_actions];
    int x = 20, y = 10;

    char img_name[80];
    for (int i = 0; i < num_actions; i++) {
        sprintf(img_name, "%s/%02d.bmp", path, i);
        printf("carregando action [%s]\n", img_name);

        g_actions.tile_img[i] = load_bitmap(img_name, NULL);
        g_actions.coords[i].x = x;
        g_actions.coords[i].y = y;

        x += 40;
        if (x >= 180) { x = 20; y += 40; }
    }
}

// Carrega todos os tiles do arquivo de imagens.
void load_tiles(char * dir, int & tiles_num) {
    char tile_name[80];
    sprintf(tile_name, "%s/tileset.bmp", dir);
    g_tileset = load_bitmap(tile_name, NULL);

    if (g_tileset == NULL) {
        fprintf(stderr, "TILESET image not found! [%s]\n", dir);
        exit(-1);
    }

    int w, h;

    w = g_tileset->w;
    h = g_tileset->h;

    for (int y = 2; y < (h - TILE_SIZE); y += 34) {
        for (int x = 2; x < (w - TILE_SIZE); x += 34) {
            // Um subbitmap meio que compartilha a memória do bitmap pai.
            g_tiles.tile_img.push_back(create_sub_bitmap(g_tileset, x, y, TILE_SIZE, TILE_SIZE));
            point_t xy = {0, 0};
            g_tiles.xy_pos.push_back(xy);
        }
    }

    tiles_num = g_tiles.tile_img.size();

    fprintf(stderr, "TILESET loaded!\n");
}

void draw_grid(BITMAP * bmp) {
    int color = makecol(255, 255, 255);
    for (int i = 0; i < SCREEN_W; i += TILE_SIZE)
        vline(bmp, i, 0, SCREEN_H, color);

    for (int i = 0; i < SCREEN_H; i += TILE_SIZE)
        hline(bmp, 0, i, SCREEN_W, color);
}

int main(int argc, char *argv[]) {
    BITMAP * buffer;
    int tiles_num = 0;
    int act_num = 7;
    FILE *fp;

    g_map_drawx = g_map_drawy = 0;

    allegro_init();
    install_mouse();
    install_keyboard();
    install_timer();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, UTIL_W + 200, UTIL_H + UTIL_H_EX, 0, 0);

    buffer            = create_bitmap(SCREEN_W, SCREEN_H);
    g_selection_preview = create_bitmap(185, 150);

    clear_bitmap(g_selection_preview);

    char tmp[80] = {};
    if (argc > 1) {
        sprintf(tmp, "%s/stage.dat", argv[1]);
    } else {
        exit(-1);
    }

    if ((fp = fopen(tmp, "rb")) != NULL) {
        map_load(fp);
    } else {
        if (argc < 5) {
            exit(-1);
        }

        g_max_x = atoi(argv[2]) * TILES_X;
        g_max_y = atoi(argv[3]) * TILES_Y;
        if (g_max_x == 0 || g_max_y == 0) {
            exit(-1);
        }
        g_default_tile = atoi(argv[4]);

        g_map = (MAP_INFO**) malloc(sizeof(MAP_INFO*) * g_max_y);
        for (int i = 0; i < g_max_y; i++)
            g_map[i] = (MAP_INFO*) malloc(sizeof(MAP_INFO) * g_max_x);

        for (int i = 0; i < g_max_y; i++)
            for (int j = 0; j < g_max_x; j++) {
                g_map[i][j].tile_number = g_default_tile;
                g_map[i][j].action = 0;
                g_map[i][j].xOffset = 0;
                g_map[i][j].is_solid = false;
            }
    }

    load_actions((char*)"./actions", act_num);
    load_tiles(argv[1], tiles_num);

    int stepx = TILE_SIZE * TILES_X;
    int stepy = TILE_SIZE * TILES_Y;
    bool draw_actions = false;
    bool ignoreVoid   = false;
    while (!key[KEY_ESC]) {
        handle_tilebar(tiles_num);
        handle_actbar(act_num);

        if (mouse_x < UTIL_W && mouse_y < UTIL_H) {
            if (mouse_b & 1) handle_click(mouse_x, mouse_y, 1);
            if (mouse_b & 2) handle_click(mouse_x, mouse_y, 2);
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
            g_map_drawx += stepx;
            if (g_map_drawx / TILE_SIZE >= (g_max_x - TILES_X))
                g_map_drawx = (g_max_x - TILES_X) * TILE_SIZE;

            while (key[KEY_D]);
        } else if (key[KEY_A] && g_draw_selection == false) {
            g_map_drawx -= stepx;
            if (g_map_drawx < 0)
                g_map_drawx = 0;

            while (key[KEY_A]);
        }

        if (key[KEY_W] && g_draw_selection == false) {
            g_map_drawy -= stepy;
            if (g_map_drawy < 0)
                g_map_drawy = 0;

            while (key[KEY_W]);
        } else if (key[KEY_S] && g_draw_selection == false) {
            g_map_drawy += stepy;
            if (g_map_drawy / TILE_SIZE >= (g_max_y - TILES_Y))
                g_map_drawy = (g_max_y - TILES_Y) * TILE_SIZE;

            while (key[KEY_S]);
        }

        if (key[KEY_LSHIFT]) {
            map_save(tmp);
            // Evita que fique salvando loucamente o mapa, segura até o sujeito soltar a tecla.
            while (key[KEY_LSHIFT]);
        }

        if (key[KEY_SPACE]) {
            draw_actions = true;
        } else draw_actions = false;

        if (key[KEY_M])
            ignoreVoid = true;
        else
            ignoreVoid = false;

        if (key[KEY_X]) {
            g_cur_copy_point = 0;
            g_draw_selection = false;
        }

        map_draw(buffer, g_map_drawx, g_map_drawy, draw_actions, ignoreVoid);

        if (!key[KEY_G]) {
            if (g_take_shot == false)
                draw_grid(buffer);
        }
        draw_tilesbar(buffer, tiles_num, UTIL_H);
        draw_actionsbar(buffer, act_num, UTIL_W);

        if (key[KEY_I]) {
            int xpos, ypos;
            xpos = mouse_x / TILE_SIZE * TILE_SIZE;
            if (key[KEY_O]) xpos += mouse_x % TILE_SIZE;
            ypos = mouse_y / TILE_SIZE * TILE_SIZE;
            draw_sprite(buffer, g_actions.tile_img[g_cur_act], xpos, ypos);
        } else if (g_take_shot == false) {
            circlefill(buffer, mouse_x, mouse_y, 5, 0);
            circlefill(buffer, mouse_x, mouse_y, 3,  makecol(255, 255, 255));
        }

        if (g_draw_selection == true) {
            int xini, yini, xend, yend;

            xini = (g_pt_ini_point.x << 5) - g_map_drawx;
            yini = g_pt_ini_point.y << 5;
            xend = ((g_pt_end_point.x << 5) + TILE_SIZE) - g_map_drawx;
            yend = (g_pt_end_point.y << 5) + TILE_SIZE;

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
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            rectfill(buffer, xini, yini, xend, yend, makecol(30, 30, 255));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
            rect(buffer, xini, yini, xend, yend, 0);
            rect(buffer, xini + 1, yini + 1, xend - 1, yend - 1, 0);
        }

        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear_bitmap(buffer);
    }

    return 0;
}
END_OF_MAIN()

