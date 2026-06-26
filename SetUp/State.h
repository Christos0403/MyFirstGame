#define CHARACTER_SPEED 10
#define BASE_ATK 10
#define BASE_DEF 10
#define BASE_SPEED 10

#include <list>
#include <string>

// basic enums needed for the game to work
enum ObjectTypes{
    Character, NPC, Enemy, Item, Furniture, Wall, Summoned_Beast
};

enum GameState{
    Opening_menu, Playing, Options, Load_menu
};

enum PlayingState{
    Choose_race, Choose_class, Choose_deity_oath, Game, Game_Over, Paused
};

enum Directions{
    Right, Left, Up, Down
};
// customizable info inside the game

enum Weather{
    sunny_day, night, raining_day, cloudy_day, inside_building
};

enum Effects{
    Power, Protect, Recovery, Haste, Storage, 
};

enum GearType{
    Weapon, Chestplate, Leggings, Helmet, Boots, Shield
};

enum Race{
    Human, Elf, Dwarf, Demon, Angel, Giant, Dragonoid, Vampire
};

enum Classes{
    Warrior, Mage, Cleric, Berserk, Monk, Rogue, Paladin, Ranger, Warlock
};

enum PaladinOath{
    Strength, Vengeance, Peace, Justice, wealth, Protection, Faith, invincibility, bravery
};

enum Deities{
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

class Skill{
    private:
        std::string name;
        Effects effect;
        int Power_of_effect;
        int duration;
        int cooldown;
    public:
    Effects GetEffect(){return effect;};
    int GetEffectPower(){return Power_of_effect;};
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
        Classes Char_class;
        double Level;
        double Hp;
        double Mp_Sta;
        double Atk;
        double Def;
        double Range;
        double speed;
        double size;
        double karma;
        double regen;
        double crit_chance;
        int oath_deity;
        Directions Moving_Dir;
        std::list<Skill> skills;
    public:
        // constructor
        Character_Cl():
            PositionXY(GetScreenWidth()/2,GetScreenHeight()/2),
            type(Character),
            Char_Race(Human),
            Level(1),
            // using a modifier change basic values for each race
            Hp (100),
            Mp_Sta (100),
            Atk (BASE_ATK),
            Def (BASE_DEF),
            Range (5),//changes according to the class
            speed (BASE_SPEED),//also changes according class and race
            size (10),//changes according to race
            karma(0),
            regen (1),
            crit_chance(10),
            oath_deity(0),
            Moving_Dir(Right)
        {}

        void SetStatsModifier(Race char_race){
            Modifiers mod = GetModifiers(char_race);
            Hp *= mod.Hp;
            Mp_Sta *= mod.Mp_Sta;
            Atk *= mod.Atk;
            Def *= mod.Def;
            speed *= mod.speed;
            size *= mod.size;
            regen *= mod.regen;
        }

        Race GetCharacterRace(){
            return Char_Race;
        }

        Classes GetCharacterClass(){
            return Char_class;
        }

        void ChangeCharacter(Race new_race){
            Char_Race = new_race;
            SetStatsModifier(new_race);
        }

        void ChangeCharacter(Classes new_class){
            Char_class = new_class;
            // Range = GetClassRange(new_class);//a function that returns the class' range
        }

        void IncreaseKarma(int amount){
            karma += amount;
        }

        int GetKarma(){
            return karma;
        }

        void AddSkill(Skill skill){
            skills.push_back(skill);
        }

        int GetCharacterDeityOath(){
            return oath_deity;
        }

        void SetOathDeity(int Deity_Oath){
            oath_deity = Deity_Oath;
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
        PlayingState During_game_state;
        Weather Weather_state;
        Character_Cl *Player;
        std::list<MovingObject> Moving_Objects;
        std::list<StaticObjectGear> Static_Objects;
        
    public:
        // constructor
        State(){
            Game_State = Opening_menu;
            During_game_state = Choose_race;
            Weather_state = inside_building;
            Player = new Character_Cl();
            
        };

        GameState GetGameState(){
            return Game_State;
        }

        void SetGameState(GameState new_game_state){
            Game_State = new_game_state;
        }
        
        PlayingState GetPlayingState(){
            return During_game_state;
        }

        void SetPlayingState(PlayingState new_playing_state){
            During_game_state = new_playing_state;
        }

        Race GetRace(){
            return Player->GetCharacterRace();
        };

        void SetRace(Race new_race){
            Player->ChangeCharacter(new_race);
        }

        Classes GetClass(){
            return Player->GetCharacterClass();
        }

        void SetClass(Classes new_class){
            Player->ChangeCharacter(new_class);
        }

        int GetDeityOath(){
            return Player->GetCharacterDeityOath();
        }

        void SetDeityOath(int Deity_oath){
            Player->SetOathDeity(Deity_oath);
        }
};

// function for other files

void ClearState(State* state);
// 
// void RenderWindow(State state);
// 
// State StateUpdate();
// 
State* StateCreate();