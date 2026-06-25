#include "raylib.h"
#include "State.h"

#define TITLE_FONT 100
#define GAME_TITLE "Game Title"

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

int GetCenter(int font, const char *text){
    int Text_size = MeasureText(text, font);

    return (GetScreenWidth()- Text_size)/2;
}


void OpenWindow(){
    InitWindow(GetScreenWidth(),GetScreenHeight(), "Game_title");
    SetTargetFPS(60);
}

void MyCloseWindow(){
    CloseWindow();
}

void DrawOpeningMenu(){
    DrawText("Start", GetCenter(50, "Start"), GetScreenHeight()/2, 50, WHITE);
    DrawText("Load", GetCenter(50, "Load"), (GetScreenHeight()/2) + 100,50, WHITE);
    DrawText("Options", GetCenter(50, "Options"), (GetScreenHeight()/2) + 200,50, WHITE);
    DrawText("Exit", GetCenter(50, "Exit"), (GetScreenHeight()/2) + 300,50, WHITE);
}

int main(){
    OpenWindow();
    // State* state = StateCreate();
    Cursor cursor(100, 100);
    while(!WindowShouldClose()){
        frame_counter++;
        BeginDrawing();
        ClearBackground(BLACK);
        
        // we draw the title of the game in the opening menu
        DrawText(GAME_TITLE, GetCenter(TITLE_FONT, GAME_TITLE), GetScreenHeight()/5, TITLE_FONT, WHITE);

        // we make the basic menu appear
        DrawOpeningMenu();
        
        // the cursor we will use to select things
        cursor.SetCursorX(GetScreenWidth()/3+100);
        cursor.SetCursorY(GetScreenHeight()/2+25);
        if (visible){
            DrawCircle(cursor.GetCursorX(),cursor.GetCursorY(), 10, WHITE);
        }
        

        //we end the drawing and move to the next itteration
        // DrawText(TextFormat("%d",GetScreenWidth()),200,200,100,WHITE);
        EndDrawing();
        if (frame_counter % FRAMES_FOR_BLINKING==0){
            visible = !visible;
        }
        if (frame_counter==__LONG_LONG_MAX__){
            frame_counter = 0;
        }
    }


    // delete state;
    // ClearState();
    MyCloseWindow();
}