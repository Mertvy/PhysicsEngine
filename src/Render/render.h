//
// Created by Alex on 7/23/2023.
//

#ifndef PHYSICSENGINE_RENDER_H
#define PHYSICSENGINE_RENDER_H

#include "world.h"

void createCircle(float, float, float, float, float, World*);
void createLine(float, float, float, float, float, float, float, World*);
void drawCircle(float, float, float);
void drawLine(float, float, float, float, float, float);
void drawPoint(float, float);


#endif //PHYSICSENGINE_RENDER_H
