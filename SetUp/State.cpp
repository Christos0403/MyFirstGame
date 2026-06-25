#include "raylib.h"
#include "State.h"
#include <set>
#include <iostream>

// 
//          All helper function go here
// 
Modifiers GetModifiers(Race race){
    switch (race){
        // hp, mp, atk, def, speed, size, regen, exp_gain
        case Vampire:
        return{1, 1.1, 1.2, 0.5, 1.2, 1, 2, 1};
        case Human:
        return{1, 1, 1, 1, 1, 1, 1, 1.2};
        case Elf:
        return {1, 1.4, 0.8, 1, 1.4, 1, 0.6, 1};
        case Dwarf:
        return{1.2, 1.3, 1, 1.1, 0.8, 0.7, 1, 1};
        case Demon:
        return {1, 1, 1.6, 0.6, 1, 1, 1.1, 1};
        case Angel:
        return{1, 1, 0.8, 1.4, 1, 1.1, 0.8, 1};
        case Giant:
        return{1.6, 0.6, 1.8, 1.8, 0.5, 4, 0.4, 1};
        default:
        return{1.5, 1.2, 1.1, 1.1, 0.8, 1.5, 0.7, 0.7};
    };
 }

// void move(Directions dir, int distance){
    // 
// }

// Race GetRace(){
// 
// };

void RenderWindow(State state){
    if (state.GetGameState() == Opening_menu){
        DrawText("Hello World!",GetScreenWidth()/2,GetScreenHeight()/2, 50, WHITE);
    }

}
// 
//          Basic Code
// 

// this must obtain the inputs from the user and make the starting state. This info will be saved in a json file for save/load function.
// State* StateCreate(){
    // State* state = new State(race);
    // return state;
// }

// this will be used to update the frames(careful with the loops, this will run 60 times per sec. complicated algorithms will ruin everything.)
// void StateUpdate(State state){
    // 
// }



// delete State and free memory

// void ClearState(){
// 
// }