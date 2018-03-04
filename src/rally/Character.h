#pragma once

#include "gamelib/AnimationSequence.h"

#include <allegro.h>

class Character {
public:
    Character(const Stage& stage, unsigned int TYPE);
    Character();
    virtual ~Character();

    // There will be code here, so it's not pure virtual.
    virtual void doLogic();

    // Draw itself to bmp, move to stage?
    virtual void drawCharacter(BITMAP* bmp);

    // In case we move draw code to stage, this call will return character current sprite.
    BITMAP* getFrame();

    // Decides based on curState which animation should be used. Also update animation frame.
    virtual bool handleAnimation();

    // This is only relevant to player, maybe move it from here.
    virtual void hit(Character* pCharacter);

    // Reset inicial x,y, inicial animation and such...
    virtual void respawn();

    double x, y;
    double oldX, oldY;
    double velX, velX;
    int screenX, screenY;

    int curState;
    int lastState;

    int colorOffset;

    AnimationSequence* spriteSheet;

    //TODO: In order to implement A* we need to know map geometry and such... move to stage like:
    // vector<points> path = stage.createPath(point 1, point 2, bool avoid rocks);
    // ? :)
};
