#ifndef PADDLE_H
#define PADDLE_H 

#include <raylib.h>



class Paddle{
    protected:
    float pos_x;
    float pos_y;
    float width;
    float height;
    float speed;
    Color color;

public:
    Paddle(float pos_x, float pos_y, float width, float height, Color color, float speed);
    void DrawPaddles();
    void setPosX(float x );
    void setPosY(float y );
protected:
    void RangeMove(float screen_height);
public:
    void Move(float screen_height);
    float getPositionX();
    float getPositionY();
    float getWidth();
    float getHeight();
};

#endif 