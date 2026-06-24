#include "raylib.h"
#include "State.h"
#include <set>
#include <iostream>

class Object{
    protected:
    ObjectTypes type;
    std::pair<int, int> PositionXY;
    std::string id;
    public:

    Object(ObjectTypes new_type,int new_x, int new_y){
        PositionXY.first = new_x;
        PositionXY.second = new_y;
        type = new_type;
    }

    int getX(){
        return PositionXY.first;
    }

    int getY(){
        return PositionXY.second;
    }
};









void StateUpdate(){
    
}