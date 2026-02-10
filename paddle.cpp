
#include "paddle.h"
#include <iostream>
#include <raylib.h>
#include <cmath>


using namespace std;

Paddle::Paddle(float pos_x, float pos_y, float width, float height, Color color, float speed){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->height = height;
    this->width = width;
    this->color = color;
    this->speed = speed;
}
void Paddle::DrawPaddles(){
    
    float alphaBlink = 0.6f + 0.4f * (sinf(GetTime() * 6) + 1) / 2;

        DrawRectangle(pos_x - 20, pos_y - 20, width + 40, height + 40,
                    Fade(color, alphaBlink * 0.1f));

        DrawRectangle(pos_x - 15, pos_y - 15, width + 30, height + 30,
                    Fade(color, alphaBlink * 0.3f));

        DrawRectangle(pos_x - 5, pos_y - 5, width + 10, height + 10,
                    Fade(color, alphaBlink * 0.4f));

        DrawRectangle(pos_x - 3, pos_y - 3, width + 7, height + 7,
                    Fade(color, alphaBlink * 0.6f));

        DrawRectangle(pos_x, pos_y, width, height, color);


}
void Paddle::setPosX(float x ){
        pos_x = x;
    }
void Paddle::setPosY(float y ){
    pos_y = y;
}

void Paddle::RangeMove(float screen_height){
    if (pos_y <= 0){
        pos_y = 0;
    }
    if (pos_y + height >= screen_height){
        pos_y = screen_height - height;
    }
}

void Paddle::Move(float screen_height){
    if (IsKeyDown(KEY_UP)){
        pos_y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)){
        pos_y += speed;
    }
    RangeMove(screen_height);
}
float Paddle::getPositionX(){
    return pos_x;
}
float Paddle::getPositionY(){
    return pos_y;
}
float Paddle::getWidth(){
    return width;
}
float Paddle::getHeight(){
    return height;
}
