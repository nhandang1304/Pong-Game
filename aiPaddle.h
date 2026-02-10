#ifndef AIPADDLE_H
#define AIPADDLE_H

#include "paddle.h"
#include <raylib.h>

class AIPaddle: public Paddle{
    public:
    AIPaddle(float pos_x, float pos_y, float width, float height, Color color, float speed);

    public: 
    void AutoMove(float pos_ball, float screen_height);
};
#endif