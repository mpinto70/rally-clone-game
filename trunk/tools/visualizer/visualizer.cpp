
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

// TODO:
// Usando os defines no megaman, temos que rever isso aqui.
// O jogo original tem uma resolução de 288 x 224, sugiro que a gente dobre: 576 x 448
// Verificar tamanho dos tiles e setar um novo pra gente.
static constexpr unsigned WINDOW_W  = 500;  ///< map window width
static constexpr unsigned WINDOW_H  = 400;  ///< map window height

struct MAP_INFO {
    unsigned char tile_number; // index to the drawing table
    unsigned char is_solid;    // is it solid?
    unsigned char action;      // is there an associated action? Create enemy, create rock?
    int xOffset;               // Deslocamento dentro do tile da posicao x,y real do action (evitar restringir ao tilesize os alinhamentos)
};


static unsigned g_map_drawx, g_map_drawy;

// Tabela de desenhos para a fase.
static BITMAP * g_images;

struct point_t {
    unsigned x, y;
};

struct tiles_t {
    std::vector<BITMAP*> tile_img;
    std::vector<point_t> xy_pos;
};
static tiles_t g_tiles;

// Variaveis usadas pelo CTRL+C CTRL+V
static BITMAP * g_selection_preview;

std::string get_error_message() {
    return std::to_string(errno) + " " + std::string(strerror(errno));
}

void throw_file_error(const std::string & filename) {
    const std::string msg = std::string(filename) + " " + get_error_message();
    throw std::runtime_error(msg);
}

void throw_allegro_error(const std::string & filename) {
    const std::string msg = std::string(filename) + " " + allegro_error;
    throw std::runtime_error(msg);
}

static void draw_tiles(BITMAP * canvas) {
    draw_sprite(canvas, g_images, 10, 30);
}

/// loads all tiles from file.
static void load_images(const std::string & full_path,
                        const unsigned tile_width,
                        unsigned & num_tiles) {
    g_images = load_bitmap(full_path.c_str(), nullptr);

    if (g_images == nullptr) {
        throw_allegro_error("could not load " + full_path);
    }

    const unsigned w = g_images->w;
    const unsigned h = g_images->h;
    constexpr unsigned GAP = 1;
    if (w % (tile_width + GAP) != 0)
        throw_allegro_error("The image (" + full_path + " - " + std::to_string(w) + ") has not space for images of size (" + std::to_string(tile_width) + ")");

    num_tiles = w / (tile_width + GAP);

    for (unsigned x = 0, i = 0; i < num_tiles; ++i, x += tile_width + GAP) {
        // Um subbitmap meio que compartilha a memória do bitmap pai.
        BITMAP * sub = create_sub_bitmap(g_images, x, GAP, tile_width, h - GAP);
        if (sub == nullptr)
            throw_allegro_error(full_path + " " + std::to_string(x));
        g_tiles.tile_img.push_back(sub);
        point_t xy = {0, 0};
        g_tiles.xy_pos.push_back(xy);
    }

    printf("TILESET loaded! w = %d h = %d num_tiles = %d tiles = %lu\n", w, h, num_tiles, g_tiles.tile_img.size());
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

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            exit_visualizer("usage\npath/to/visualizer.exe <path/to/images/file.png> <width of image>");
        }

        const std::string file_name = argv[1];
        const unsigned width_of_image = std::stoul(argv[2]);
        unsigned num_of_tiles = 0;

        g_map_drawx = g_map_drawy = 0;

        allegro_init();
        install_mouse();
        install_keyboard();
        install_timer();

        set_color_depth(32);
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, WINDOW_W, WINDOW_H, 0, 0) != 0)
            throw_allegro_error("set_gfx_mode");

        BITMAP * carnvas    = create_bitmap(SCREEN_W, SCREEN_H);
        g_selection_preview = create_bitmap(185, 150);

        clear_bitmap(g_selection_preview);

        load_images(argv[1], width_of_image, num_of_tiles);

        //exit_visualizer("leaving for no reason");

        util::CWait wait(50);
        unsigned cur_tile = 0;
        while (!key[KEY_ESC]) {
            rectfill(carnvas, 0, 0, WINDOW_W, WINDOW_H, makecol(0xDE, 0x97, 0x47));
            draw_tile(carnvas, g_tiles.tile_img[cur_tile], 40, 150);
            draw_tiles(carnvas);
            vsync();
            blit(carnvas, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            clear_bitmap(carnvas);

            wait.reset();
            if (key[KEY_RIGHT]) {
                ++cur_tile;
                if (cur_tile == num_of_tiles)
                    cur_tile = 0;

                wait.wait();
            } else if (key[KEY_LEFT]) {
                --cur_tile;
                if (cur_tile > num_of_tiles) // overflow
                    cur_tile = num_of_tiles - 1;

                wait.wait();
            }
        }

        return 0;
    } catch (std::exception & e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return 1;
    }
}
END_OF_MAIN()

