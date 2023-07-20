//
// Created by Nicholas Weiss on 7/18/2023.
//

#ifndef PHYSICSENGINE_WORLD_H
#define PHYSICSENGINE_WORLD_H

#include "../util/Vector3D.h"
#include <vector>

struct Object;
class World {
private:
    std::vector<Object*> objects;
    float dt;
    Vector3D* gravity;
public:
    World(float dt, Vector3D* gravity);

    void addObject(Object* obj);

    void removeObject(Object* obj);

    void updateObject(Object* obj, float dt);

    void update();
    };



#endif //PHYSICSENGINE_WORLD_H
