#include "raylib.h"
#include "State.h"
#include <iostream>

#define TITLE_FONT 100
#define GAME_TITLE "Game Title"

#define BACKPACK_POSITION_X 1800
#define BACKPACK_POSITION_Y 50

#define COINS_POSITION_X 1700
#define COINS_POSITION_Y 50

#define FRAMES_FOR_BLINKING 30
long long frame_counter = 0;
bool visible = true;

class Cursor{
    private:
        std::pair<int, int> Position;
    public:

        Cursor(int x, int y): Position(x,y){};
        int GetCursorX(){
            return Position.first;
        }
        int GetCursorY(){
            return Position.second;
        }
        void SetCursorX(int newX){
            Position.first = newX;
        }
        void SetCursorY(int newY){
            Position.second = newY;
        }
};

// the cursor we will use to select things
Cursor cursor(0, 0);
// a flag for every instance we need it
bool flag = true;
// two variable that will be useful a lot later
int pos_X = 100;
int pos_Y = 100;

// The character Texture
Texture2D Character_Texture = LoadTexture("resources/Human.png");

int GetCenter(int font, const char *text){
    int Text_size = MeasureText(text, font);

    return (GetScreenWidth()- Text_size)/2;
}

Keys GetPressedKeys(){
    Keys Key_state = {false,false,false,false,false,false,false,false,false};
    if (IsKeyPressed(KEY_A)){
        Key_state.Key_A = true;
    }
    if (IsKeyPressed(KEY_W)){
        Key_state.Key_W = true;
    }
    if (IsKeyPressed(KEY_S)){
        Key_state.Key_S = true;
    }
    if (IsKeyPressed(KEY_D)){
        Key_state.Key_D = true;
    }
    if (IsKeyPressed(KEY_LEFT)){
        Key_state.Key_Left_Arrow = true;
    }
    if (IsKeyPressed(KEY_RIGHT)){
        Key_state.Key_Right_Arrow = true;
    }
    if (IsKeyPressed(KEY_UP)){
        Key_state.Key_Up_Arrow = true;
    }
    if (IsKeyPressed(KEY_DOWN)){
        Key_state.Key_Down_Arrow = true;
    }
    if (IsKeyPressed(KEY_ENTER)){
        Key_state.Key_Enter = true;
    }
    return Key_state;
}    

void OpenWindow(){
    InitWindow(GetScreenWidth(),GetScreenHeight(), "Game_title");
    SetTargetFPS(60);
    cursor.SetCursorX(GetScreenWidth()/3+100);
    cursor.SetCursorY(GetScreenHeight()/2+25);
}

void MyCloseWindow(){
    CloseWindow();
}

void DrawOpeningMenu(State* state, Keys Key_state){
    // we draw the title of the game in the opening menu
    DrawText(GAME_TITLE, GetCenter(TITLE_FONT, GAME_TITLE), GetScreenHeight()/5, TITLE_FONT, WHITE);

    // we make the basic menu appear
    DrawText("Start", GetCenter(50, "Start"), GetScreenHeight()/2, 50, WHITE);
    DrawText("Load", GetCenter(50, "Load"), (GetScreenHeight()/2) + 100,50, WHITE);
    DrawText("Options", GetCenter(50, "Options"), (GetScreenHeight()/2) + 200,50, WHITE);
    DrawText("Exit", GetCenter(50, "Exit"), (GetScreenHeight()/2) + 300,50, WHITE);

    if (visible){
        DrawCircle(cursor.GetCursorX(),cursor.GetCursorY(), 10, WHITE);
    }
        
    if ((Key_state.Key_Down_Arrow || Key_state.Key_S) && cursor.GetCursorY() != GetScreenHeight()/2+325){
        cursor.SetCursorY(cursor.GetCursorY() + 100);
    }
    if ((Key_state.Key_Up_Arrow || Key_state.Key_W) && cursor.GetCursorY() != GetScreenHeight()/2+25){
        cursor.SetCursorY(cursor.GetCursorY() -100);
    }

    if (Key_state.Key_Enter){
        if (cursor.GetCursorY() == GetScreenHeight()/2+25){
            state->SetGameState(Playing);
        } else if (cursor.GetCursorY() == GetScreenHeight()/2+125){
            state->SetGameState(Load_menu);
        } else if (cursor.GetCursorY() == GetScreenHeight()/2+225){
            state->SetGameState(Options);
        } else {
            exit(0);
        }
    }
}
// Race coosing functions
const char* RaceToText(Race race){
    switch (race){
    case Human:
        return "Human";
    case Elf:
        return "Elf";
    case Dwarf:
        return "Dwarf";
    case Giant:
        return "Giant";
    case Angel:
        return "Angel";
    case Demon:
        return "Demon";
    case Dragonoid:
        return "Dragonoid";
    default:
        return "Vampire";
    }
}

const char* GetRaceExplaination(Race race){
    switch(race){
        case Human:
        // 1, 1, 1, 1, 1, 1, 1, 1.2
            return "Humans are the most balanced of all races. They do not possess \nany kind of special power due to their bloodline. Despite that, \nthey manage to stand on equal level to the rest of the races \ndue to their fast growth.";
        case Elf:
        // 1, 1.4, 0.8, 1, 1.4, 1, 0.6, 1
            return "Elves are creatures of nature. They possess a large amount of \nenergy and high agility, but they tend to be weaker that other \nraces. Due to their nature they recover slower that other races.";
        case Dwarf:
        // 1.2, 1.3, 1, 1.1, 0.8, 0.7, 1, 1
            return "Dwarfs are masters of metal. They recover slowly and are shorter \nthat other races but the possess high muscle density, giving them \nhigher energy reserves, defense and lifepoints.";
        case Giant:
        // 1.6, 0.6, 1.8, 1.8, 0.5, 4, 0.4, 1
            return "Giants are the ultimate brawlers. The possess very small amount of \nenergy, they recover slowly and have large size that limits \ntheir mobility and exploration potential. Despite that they possess \nlifeforce, strength and defense beyond any other race.";
        case Angel:
        // 1, 1, 0.8, 1.4, 1, 1.1, 1.1, 1
            return "Angels are protectors of the world. They love to protect the world \naround them. They have decreased strength but have higher \ndefense and speed, allowing them to rech and protect the people \nthat need them. They are the complete opposite of Demons and \nDevils.";
        case Demon:
        // 1, 1, 1.6, 0.6, 1, 1, 0.8, 1
            return "Demons are destroyers. They destroy everything they can get \ntheir hands on. They have increased strength allowing them to \ndestroy things easily. They are the complete opposite of Angels.";
        case Dragonoid:
        // 1.5, 1.2, 1.1, 1.1, 0.8, 1.5, 0.7, 0.7
            return "Dragonoid are the ultimate fighters. They possess almost no \nweaknesses other than their slow recovery and slow growth rate. \nDespite that they dominate almost all fighting jobs due to their \ninsane power in all categories.";
        default:
        // 1, 1.1, 1.2, 0.5, 1.2, 1, 2, 1
            return "Vampires are perfect assassins. The re extremely effective in the \ndarkness since hey are fast, small and powerful. Despite that \nthey are extremely fragile due their extreme recovery speed.";
        // hp, mp, atk, def, speed, size, regen, exp_gain
    }
}

void PrintRaceDetails(Race race){
    DrawText(RaceToText(race), GetCenter(TITLE_FONT, RaceToText(race)),100,TITLE_FONT,WHITE);
    DrawText(GetRaceExplaination(race),500, 200, 40, WHITE);
}

void ChooseRace(State* state,Keys key_state){
    // variables we need
    pos_X = 100;
    pos_Y = 100;
    const char* race = "Error loading";
    Race new_race = Human;
    if (flag){
        cursor.SetCursorX(pos_X);
        cursor.SetCursorY(pos_Y);
        flag = false;
    }
    // basic code
    DrawRectangle(cursor.GetCursorX(),cursor.GetCursorY(),100,100,DARKBLUE);
    
    for (int i = 0; i < 8; i++){ 
        race = RaceToText(Race(i));
        DrawRectangleLines(pos_X,pos_Y, 100, 100, WHITE);
        DrawText(race,pos_X+50,pos_Y+50, 50, WHITE);
        pos_Y+=100;
    }
    if ((key_state.Key_S|| key_state.Key_Down_Arrow) && cursor.GetCursorY() !=100+700){
        cursor.SetCursorY(cursor.GetCursorY()+100);
    }
    if ((key_state.Key_W|| key_state.Key_Up_Arrow) && cursor.GetCursorY() !=100){
        cursor.SetCursorY(cursor.GetCursorY() -100);
    }

    PrintRaceDetails(Race(int((cursor.GetCursorY()-100)/100)));
    if (key_state.Key_Enter){
        new_race = Race((cursor.GetCursorY()-100)/100);
        state->SetRace(new_race);
        state->SetPlayingState(Choose_class);
        flag = true;
    }
    

}

// Class choosing Functions
const char* ClassToText(Classes Cur_class){
    switch (Cur_class){
    case Warrior:
        return "Warrior";
    case Mage:
        return "Mage";
    case Cleric:
        return "Cleric";
    case Berserk:
        return "Berserk";
    case Monk:
        return "Monk";
    case Rogue:
        return "Rogue";
    case Paladin:
        return "Paladin";
    case Ranger:
        return "Ranger";
    default:
        return "Warlock";
    }
}

const char* GetClassExplaination(Classes Cur_class){
    switch (Cur_class){
        // hp, mp, atk,def, speed
    case Warrior:
        return "Warriors are people that have given up upon magic and choosen to \nwalk the path of a weapon. They fight in the frontlines, usually using \na sword and a shield. The use all the mana they have to enhance \ntheir weapons to deal extra damage.\n\n\n\n\nOn Level Up Increase: \nHp: +50 \nMp: +5 \nAtk: +20 \nDef: +20 \nSpeed: +15 \nInherect Skill: Slash";
    case Mage:
        return "Mages are people that have given up upon their physical bodies and \nhave choosen to use the energy they possess to alter the world \naround them to attack their foes. They usually fight in the rear \naway from any direct danger. Due to their possision they are unable to \nequip armor because they would be crushed under it's weight.\n\n\n\n\nOnLevel Up Increase: \nHp: +20 \nMp: +65 \nAtk: +10 \nDef: +5 \nSpeed: +5 \nInherent Skill: Fireball";
    case Cleric:
        return "Clerics are people that have given up entirely on attacking \nand chosen to servce one of the world's deities in return for \nhealing, enhancement and Deterioration magic. Due to their position in \nthe rear and their importance they are prime targets for attacks\n\n\n\n\nOn Level Up Increase: \nHp: +25 \nMp: +70 \nAtk: +0 \nDef: +0 \nSpeed: +10 \nInherent Skill: Heal, Drain";
    case Berserk:
        return "Berserkers are people that have given up on their body and mind \nand traded everything for pure power. They fight in the \nfrontlines usually alone, rushing into enemy lines without \ncaring about injuries.\n\n\n\n\nOn Level Up Incease: \nHp: +40 \nMp: +10 \nAtk: +40 \nDef: +5 \nSpeed: +10 \nInherent Skill: Rage";
    case Monk:
        return "Monks are people that have given up on weapons and decided \nto turn themselves into a weapon. The fight in the frontlines \nusing their bare hands to tear their enemies apart. Despite their \nway of fighting they are known to be peaceful people that would \nprefer avoiding battle when possible. \n\n\n\n\nOn Level Up Increase: \nHp: +30 \nMp: +5 \nAtk: +40 \nDef: +10 \nSpeed: +10 \nInherent Skill: Power Punch";
    case Rogue:
        return "Rogues are people that have given up on team fights and decided to \ntake down all enemies with one attack one at a time. They specialize \nin stealth and agility giving them the skills necessary to dodge \nattacks. Due to their style, they are not able to block attacks. \n\n\n\n\nOn Level Up Increase: \nHp: +20 \nMp: +10 \nAtk: +30 \nDef: +5 \nSpeed: +40 \nInherent Skill: Stealth";
    case Paladin:
        return "Paladins are people that have given an oath to themselves and \nfollow them to the end. They obtain immense power by following said \noath but lose it the moment they lose themselves. They fight in the \nfrontlines while dealing high damage and absorbing enemy damage, \ndespite that they are quite slow. \n\n\n\n\nOn Level Up Increase: \nHp: +30 \nMp:+30 \nAtk: +20 \nDef: +20 \nSpeed: +5 \nInherent Skill: Divine Sense, Judgement";
    case Ranger:
        return "Rangers are people that have given up on close combat and \ndecided that keeping their distance is the best action. \nThey tend to fight in the rear although they can fight in close \nrange. They specialize in speed while ignoring power and \ndefense. They are reliant on their weapon to deal \nlarge amount of damage.\n\n\n\n\nOn Level Up Increase: \nHp: +25 \nMp: +10 \nAtk: +20 \nDef: +10 \nSpeed: +40 \nInherent Skill: Multishot";
    default:
        return "Warlocks are people that have created contracts with otherworldly \nbeings in exchange for power. They can fight both in close \nrange and long range combat but they tend to specialize \nin one of them. Most Contracts come with steep prices according \nto the deity each person chooses to make a contract with. \n\n\n\n\nOn Level Up Increase: \nHp:+20 \nMp: +20 \nAtk: +25 \nDef: +20 \nSpeed: +20 \nInherect Skill:(Depend of the being you contract)";
    }
}

void PrintClassDetails(Classes Cur_class){
    DrawText(ClassToText(Cur_class), GetCenter(TITLE_FONT, ClassToText(Cur_class)),100, TITLE_FONT, WHITE);
    DrawText(GetClassExplaination(Cur_class), 500, 200, 40, WHITE);
}

void ChooseClass(State* state, Keys key_state){
    pos_X = 100;
    pos_Y = 100;
    const char* Class = "Error loading";
    Classes new_class = Warrior;
    if (flag){
        cursor.SetCursorX(pos_X);
        cursor.SetCursorY(pos_Y);
        flag = false;
    }
    // basic code
    DrawRectangle(cursor.GetCursorX(),cursor.GetCursorY(),100,100,DARKBLUE);
    
    for (int i = 0; i < 9; i++){ 
        Class = ClassToText(Classes(i));
        DrawRectangleLines(pos_X,pos_Y, 100, 100, WHITE);
        DrawText(Class,pos_X+50,pos_Y+50, 50, WHITE);
        pos_Y+=100;
    }
    if ((key_state.Key_S|| key_state.Key_Down_Arrow) && cursor.GetCursorY() !=100+800){
        cursor.SetCursorY(cursor.GetCursorY()+100);
    }
    if ((key_state.Key_W|| key_state.Key_Up_Arrow) && cursor.GetCursorY() !=100){
        cursor.SetCursorY(cursor.GetCursorY() -100);
    }

    PrintClassDetails(Classes(int((cursor.GetCursorY()-100)/100)));
    if (key_state.Key_Enter){
        new_class = Classes((cursor.GetCursorY()-100)/100);
        state->SetClass(new_class);
        if (new_class == Paladin || new_class == Cleric || new_class == Warlock){
            state->SetPlayingState(Choose_deity_oath);
        } else {
            state->SetPlayingState(Game);
        }
        flag = true;
    }
}

// Oath/DeitySelection
const char* GetDeityOathExplanation(Classes Cur_class, int Deity_Oath){
    if (Cur_class == Paladin){
        switch(PaladinOath(Deity_Oath)){
            // Strength, Vengeance, Peace, Justice, wealth, Protection, Faith, invincibility, bravery
            case Strength:
            return "Advantage: +2 Atk for each LevelUp \n\n\nDisadvantage: Loses the ability to deceive";
            case Vengeance:
            return "Advantage: +10%% Exp per kill \n\n\nDisadvantage: One random character is chosen to become your lethal enemy, you don't know which one.";
            case Peace:
            return "Advantage: +100 Karma \n\n\nDisadvantage: You are not allowed to start a fight with a non-Enemy";
            case Justice:
            return "Advantage: Your Karma cannot go below 0.\n\n\nDisadvantage: You are not allowed be unjust. If you are your Karma decreases by 100";
            case wealth:
            return "Advantage: Increased coin gain per kill\n\n\nDisadvantage: You are not allowed to waste money in unimportant things(including weapons and armor if you have equipped ones.)";
            case Protection:
            return "Advantage: +5 Def per Level during in a fight\n\n\nDisadvantage: Any party members that reach lower than 30%% Hp have to be saved. If not you lose 5 Def";
            case Faith:
            return "Advantage: +5 Mp per Level during a fight\n\n\nDisadvantage: if you forget to visit a church and pray to your god, when you reach a town you lose 5 Mp";
            case invincibility:
            return "Advantage: +5 Atk per Level during a fight\n\n\nDisadvantage: You are not allowed to take damage. Each time you take you lose 5 Atk.";
            default:
            return "Advantage: +2 Speed per Level during a fight \n\n\nDisadvantage: You are not allowed to run from a fight. If you do you lose 2 speed";
        }
    } else {
        switch(Deities(Deity_Oath)){
            // Sun, Moon, Blood, Time, Space, Death, Fire, Water, Arch_Devil
            case Sun:
            return "Advantage: \nSkill tree: Light/Sun\n\n\nWeakness: Loses access to skills from other deities.";
            case Moon:
            return "Advantage: \nSkill tree: Darkness/Moon\n\n\nWeakness: Loses access to skills from other deities.";
            case Blood:
            return "Advantage: \nSkill tree: Blood\n\n\nWeakness: Loses access to skills from other deities.";
            case Time:
            return "Advantage: \nSkill tree: Time\n\n\nWeakness: Loses access to skills from other deities.";
            case Space:
            return "Advantage: \nkeill tree: Space\n\n\nWeakness: Loses access to skills from other deities.";
            case Death:
            return "Advantage: \nSkill tree: Necromancy\n\n\nWeakness: Loses access to skills from other deities.";
            case Fire:
            return "Advantage: \nSkill tree: Fire\n\n\nWeakness: Loses access to skills from other deities.";
            case Water:
            return "Advantage: \nSkill tree: Water\n\n\nWeakness: Loses access to skills from other deities.";
            default:
            return "Advantage: \nSkill tree: summoning\n\n\nWeakness: Loses access to skills from other deities.";
        }
    }
}

const char* DeityOathToText(Classes Cur_class, int Deity_Oath){
    if (Cur_class == Paladin){
        switch(PaladinOath(Deity_Oath)){
            // Strength, Vengeance, Peace, Justice, wealth, Protection, Faith, invincibility, bravery
            case Strength:
            return "Strength";
            case Vengeance:
            return "Vengeance";
            case Peace:
            return "Peace";
            case Justice:
            return "Justice";
            case wealth:
            return "wealth";
            case Protection:
            return "Protection";
            case Faith:
            return "Faith";
            case invincibility:
            return "invincibility";
            default:
            return "bravery";
        }
    } else {
        switch(Deities(Deity_Oath)){
            // Sun, Moon, Blood, Time, Space, Death, Fire, Water, Arch_Devil
            case Sun:
            return "Sun";
            case Moon:
            return "Moon";
            case Blood:
            return "Blood";
            case Time:
            return "Time";
            case Space:
            return "Space";
            case Death:
            return "Death";
            case Fire:
            return "Fire";
            case Water:
            return "Water";
            default:
            return "Arch_Devil";
        }
    }
};

void PrintDeityOathDetails(Classes Cur_class, int Deity_Oath){
   DrawText(DeityOathToText(Cur_class,Deity_Oath),GetCenter(TITLE_FONT,DeityOathToText(Cur_class,Deity_Oath)),100, TITLE_FONT, WHITE);
   DrawText(GetDeityOathExplanation(Cur_class, Deity_Oath),500,200, 40, WHITE);
}

void ChooseDeityOath(State* state, Keys key_state){
    pos_X = 100;
    pos_Y = 100;
    const char* Deity_Oath = "Error loading";
    if (flag){
        cursor.SetCursorX(pos_X);
        cursor.SetCursorY(pos_Y);
        flag = false;
    }
    // basic code
    DrawRectangle(cursor.GetCursorX(),cursor.GetCursorY(),100,100,DARKBLUE);
    
    for (int i = 0; i < 9; i++){ 
        Deity_Oath = DeityOathToText(state->GetClass(),i);
        DrawRectangleLines(pos_X,pos_Y, 100, 100, WHITE);
        DrawText(Deity_Oath,pos_X+50,pos_Y+50, 50, WHITE);
        pos_Y+=100;
    }
    if ((key_state.Key_S|| key_state.Key_Down_Arrow) && cursor.GetCursorY() !=100+800){
        cursor.SetCursorY(cursor.GetCursorY()+100);
    }
    if ((key_state.Key_W|| key_state.Key_Up_Arrow) && cursor.GetCursorY() !=100){
        cursor.SetCursorY(cursor.GetCursorY() -100);
    }

    PrintDeityOathDetails(state->GetClass(),int((cursor.GetCursorY()-100)/100));
    if (key_state.Key_Enter){
        state->SetDeityOath((cursor.GetCursorY()-100)/100);
        state->SetPlayingState(Game);
        flag = true;
    }
}
// Basic Prints
void PrintBasicMenus(State* state){
    DrawTexture(LoadTexture("resources/backpack.png"),BACKPACK_POSITION_X, BACKPACK_POSITION_Y, WHITE);
    DrawText("[I]",BACKPACK_POSITION_X+26,BACKPACK_POSITION_Y + 70, 15, WHITE );

    DrawTexture(LoadTexture("resources/Coins.png"),COINS_POSITION_X, COINS_POSITION_Y, WHITE);
    DrawText(TextFormat("%d",state->GetCoins()),COINS_POSITION_X+26, COINS_POSITION_Y+70, 15, WHITE );
    
    DrawText(TextFormat("Level: %d", state->GetLevel()),100, 20, 20, WHITE);

    DrawRectangle(100,50,500,20, RED);
    DrawText("Hp:", 60, 50, 20, WHITE);

    DrawRectangle(100, 80, 500, 20, BLUE);
    DrawText("Mp:", 60, 80, 20, WHITE);

}

void DrawCharacterTexture(State* State){
    switch(State->GetRace()){
        case Human:
        Character_Texture = LoadTexture("resources/Human.png");
        break;
        case Elf:
        Character_Texture = LoadTexture("resources/Elf.png");
        break;
        case Dwarf:
        Character_Texture = LoadTexture("resources/Dwarf.png");
        break;
        case Demon:
        Character_Texture = LoadTexture("resources/Demon.png");
        break;
        case Angel:
        Character_Texture = LoadTexture("resources/Angel.png");
        break;
        case Giant:
        Character_Texture = LoadTexture("resources/Giant.png");
        break;
        case Vampire:
        Character_Texture = LoadTexture("resources/Vampire.png");
        break;
        default:
        Character_Texture = LoadTexture("resources/Dragonoid.png");
        break;
    }
    DrawTexture(Character_Texture,(GetScreenWidth()/2)-64,(GetScreenHeight()/2)-64,WHITE);
}

// BasicGame function
void PlayGame(State* state, Keys key_state){
    PrintBasicMenus(state);
    DrawCharacterTexture(state);
    
    key_state = key_state;
    // StateUpdate(state, key_state);
}

//main function.
// The place where the game get loaded.
int main(){
    OpenWindow();
    State* state = StateCreate();

    while(!WindowShouldClose()){ //This runs every frame
        frame_counter++;
        BeginDrawing();
        ClearBackground(BLACK);

        //we obtain all keys the user pressed
        Keys Key_state = GetPressedKeys();
        // if we are in the opening menu we print it
        if (state->GetGameState() == Opening_menu){   
            DrawOpeningMenu(state, Key_state);
        } else if (state->GetGameState() == Playing){
            if (state->GetPlayingState() == Choose_race){
                ChooseRace(state, Key_state);
            } else if(state->GetPlayingState() == Choose_class){
                ChooseClass(state, Key_state);
            } else if (state->GetPlayingState() == Choose_deity_oath){
                ChooseDeityOath(state, Key_state);
            } else if (state->GetPlayingState() == Game){
                PlayGame(state, Key_state);
            }
        }
        //we end the drawing and move to the next itteration
        EndDrawing();
        if (frame_counter % FRAMES_FOR_BLINKING==0){
            visible = !visible;
        }
        if (frame_counter==__LONG_LONG_MAX__){
            frame_counter = 0;
        }
    }


    // delete state;
    ClearState(state);
    MyCloseWindow();
}