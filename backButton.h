#ifndef BACKBUTTON_H
#define BACKBUTTON_H
#include <raylib.h>


using namespace std;
class Ball;
class Paddle;
class AIPaddle;

class BackButton{
    private:
    float pos_x;
    float pos_y;
    float width;
    float height;
    float size;
    string text;
    Color color;

    public:
    BackButton(float pos_x, float pos_y, float width, float height, Color color, float size, string text);
    void goBack(float& countdown, int& player_point, int& computer_point, bool& isClicked, bool& isCountdown,Ball& ball, Paddle& paddle, AIPaddle& aiPaddle, float screen_width, float screen_height, float gapWall);
    void drawBackButton();
    
};
#endif