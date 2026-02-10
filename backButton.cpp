#include <raylib.h>
#include "startButton.h"
#include "paddle.h"
#include "aiPaddle.h"
#include "backButton.h"
#include "ball.h"
#include "variables.h"
#include <cmath>
using namespace std;
BackButton::BackButton(float pos_x, float pos_y, float width, float height, Color color, float size, string text){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
    this->size = size;
    this->text = text;
    this->color = color;
}
void BackButton::goBack(float& countdown, int& player_point, int& computer_point, bool& isClicked, bool& isCountdown,Ball& ball, Paddle& paddle, AIPaddle& aiPaddle, float screen_width, float screen_height, float gapWall){
        Vector2 position = GetMousePosition();
        bool pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        bool collision = CheckCollisionPointRec(position, Rectangle{pos_x, pos_y, width, height} );
        if (pressed && collision){
            ball.ResetBall(screen_width, screen_height);
            player_point = 0;
            computer_point = 0;
            paddle.setPosX(gapWall);
            paddle.setPosY(screen_height/2 - 65);
            aiPaddle.setPosX(screen_width - gapWall - 25);
            aiPaddle.setPosY(screen_height/2 - 65);
            ball.clearTrail();
            isClicked = false;
            countdown = 6.0;
           isCountdown = true;
        }
        
    }
void BackButton::drawBackButton(){
    Rectangle rec = {pos_x, pos_y, width, height};
    float measureText = MeasureText(text.c_str(), size);
    float blink = 0.6f + 0.4f * sin(GetTime() * 3);
    Vector2 position = GetMousePosition();

    bool collision = CheckCollisionPointRec(position, rec);

    if (!collision){
        DrawRectangleRounded(rec, 0.4f, 12, color);
    }
    else{
         DrawRectangleRounded(rec, 0.4f, 12, Fade({186, 97, 250, 255}, blink));
    }

    DrawRectangleRoundedLines(rec, 0.4f,12, WHITE);
    DrawText(text.c_str(), pos_x + (width-measureText)/2, pos_y + (height-size)/2, size, {224, 255, 249, 255});
    DrawText(text.c_str(), pos_x + (width-measureText)/2 + 1, pos_y + (height-size)/2 + 1, size, {224, 255, 249, 255});
} 

