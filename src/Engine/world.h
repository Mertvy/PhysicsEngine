//
// Created by Nicholas Weiss on 7/18/2023.
//

#ifndef PHYSICSENGINE_WORLD_H
#define PHYSICSENGINE_WORLD_H

struct Object;
class world {
public:
    void addObject(Object* obj);

    void removeObject(Object* obj);

    void updateObject(Object* obj, float dt);

    void update();
    };



#endif //PHYSICSENGINE_WORLD_H
