
#include "aiPaddle.h"
#include <iostream>
#include <raylib.h>


AIPaddle::AIPaddle(float pos_x, float pos_y, float width, float height, Color color, float speed): Paddle(pos_x, pos_y, width, height, color, speed){};

void AIPaddle::AutoMove(float pos_ball, float screen_height){
    float center_estimated = pos_y + height/2 + 20;
    if (center_estimated > pos_ball){
        pos_y -= speed;
    }
    else if (center_estimated < pos_ball){
        pos_y += speed;
    }
    RangeMove(screen_height);
}
