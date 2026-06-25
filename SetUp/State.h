#define CHARACTER_SPEED 5
#define GRAVITY 1
#define BASE_ATK 10
#define BASE_DEF 1
#define BASE_SPEED 10

#include <list>
#include <string>

// basic enums needed for the game to work
enum ObjectTypes{
    Character, NPC, Enemy, Item, Furniture, Wall, Summoned_Beast
};

enum GameState{
    Opening_menu, Game, Paused, Game_over
};

enum Directions{
    Right, Left, Up, Down
};
// customizable info inside the game
enum Effects{
    Power, Protection, Recovery, Haste, Storage, 
};

enum GearType{
    Weapon, Chestplate, Leggings, Helmet, Boots, Shield
};

enum Race{
    Human, Elf, Dwarf, Demon, Angel, Giant, Dragonoid, Vampire
};

enum Classes{
    Warrior, Mage, Priest, Berserk, Monk, Rogue, Paladin, Ranger, Warlock
};

enum WarlockDeities{
    Sun, Moon, Blood, Time, Space, Death, Fire, Water, Arch_Devil
};
// Abilities: 
/*
Sun: Light, healing
Moon: Darkness, stealth
Blood: More kills more atk 
Time: Faster Regeneration, speed
Space: Fast travel
Death: Bone spells
Fire: fire(duh!)
water: Water(duh!)
Lucifer: Devil summoning
*/


// we need enemy types
enum EnemyTypes{
    Slime, Skeleton, Devil, Insect, Bandit, IRS
};

struct Modifiers{
    float Hp;
    float Mp_Sta;
    float Atk;
    float Def;
    float speed;
    float size;
    float regen;
    float exp_gain;
};

//helper functions 
 Modifiers GetModifiers(Race race);

// Object classes
class Object{
    protected:
    ObjectTypes type;
    std::pair<int, int> PositionXY;
    std::string id;
    public:
// recheck how to make constructors, this is used in java not c++
    Object(ObjectTypes new_type,int new_x, int new_y, std::string new_id): type(new_type), PositionXY(new_x, new_y), id(new_id){}

    ~Object(){};

    int getX() const {
        return PositionXY.first;
    }

    int getY() const{
        return PositionXY.second;
    }

    ObjectTypes GetType(){
        return type;
    }

    std::string Get_id(){
        return id;
    }
};


class StaticObjectGear: public Object{
    private:
    
    public:
        // constructor
        StaticObjectGear(ObjectTypes type, int x, int y,std::string& id): Object(type,x,y, id){
        };
};

class Gear{
    protected:
        // a single list for every kind of gear(null if no gear)
        std::list<std::pair<GearType, StaticObjectGear>> All_Gear;

    public:

    Gear(){};
    ~Gear(){};

    std::list<std::pair<GearType, StaticObjectGear>>& GetGear(){
        return All_Gear;
    }
};

class Character_Cl: public Gear {
    private:
        std::pair<int, int>PositionXY;
        ObjectTypes type;
        Race Char_Race;
        double Level;
        double Hp;
        double Mp_Sta;
        double Atk;
        double Def;
        double Range;
        double speed;
        double size;
        double kill_count;
        double regen;
        Directions Moving_Dir;
    public:
        // constructor
        Character_Cl(Race char_race):
            PositionXY(GetScreenWidth()/2,GetScreenHeight()/2),
            type(Character),
            Char_Race(char_race),
            Level(1),
            // using a modifier change basic values for each race
            Hp (100),
            Mp_Sta (100),
            Atk (BASE_ATK),
            Def (BASE_DEF),
            Range (5),//changes according to the class
            speed (BASE_SPEED),//also changes according class and race
            size (10),//changes according to race
            kill_count(0),
            regen (1),
            Moving_Dir(Right)
        {
            Modifiers mod = GetModifiers(char_race);
            Hp *= mod.Hp;
            Mp_Sta *= mod.Mp_Sta;
            Atk *= mod.Atk;
            Def *= mod.Def;
            speed *= mod.speed;
            size *= mod.size;
            regen *= mod.regen;
        }
    };

class MovingObject: public Object, public Gear{
    private:
        double Hp;
        double Atk;
        double Def;
        double Range;
        double Speed;
        double size;
        Directions Moving_Dir;
    public:
        // constructor
        MovingObject(double new_range, ObjectTypes type, int x, int y,const std::string& id): Object(type,x,y, id), Hp(100), Atk(BASE_ATK), Def(BASE_DEF), Range(new_range), Speed(BASE_SPEED), size(10), Moving_Dir(Right){
        };
};

class State{
    private:
        GameState Game_State;
        Character_Cl *Player;
        std::list<MovingObject> Moving_Objects;
        std::list<StaticObjectGear> Static_Objects;
        
    public:
        // constructor
        State(Race char_race){
            Game_State = Opening_menu;
            Player = new Character_Cl(char_race);
            
        };

        GameState GetGameState(){
            return Game_State;
        }
};




// function for other files

// void ClearState();
// 
// void RenderWindow(State state);
// 
// State StateUpdate();
// 
// State* StateCreate();