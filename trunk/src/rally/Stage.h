#pragma once

#include <string>
#include <vector>
#include <map>

#include "camera.h"
#include "character.h"

class Stage {
    public:
        Stage(std::string stage_path);
        ~Stage();

        void createEnemies();
        Character * createCharacter(unsigned int TYPE, int x, int y);
        // Set character screenX, screenY based on camera x,y.
        void calcScreenCoords(Character * character);

        // before move any character test if collide with map, character call these ones.
        bool collisionVer(double x, double y, int &tilecoordx, int &tilecoordy);
        bool collisionHor(double x, double y, int &tilecoordx, int &tilecoordy);

        void draw(BITMAP * bmp);

        // keeps the camera centered on player
        void doCamera(Character & player);

        // max x,y for scroll.
        int maxX, maxY;

    private:
        struct MAP_INFO {
            unsigned char tile_number;
            unsigned char action;
            int xOffset;
            unsigned char isForeground;
        };
        MAP_INFO ** map;

        struct waypoint_t {
            int x, y;
        };
        waypoint_t waypoint;

        struct tiles_t {
            std::vector<BITMAP*> tile_img;
            std::vector<int> x_pos;
        };
        tiles_t tiles;

        BITMAP * tileset;

        int defaultTile;

        std::map<unsigned int, AnimSequence *> preLoadedSprites;

        std::map<int, int> offsetMap;

        void loadTiles(const std::string & stage_file);
        int load(const std::string & stage_path);
        int unload();
};
