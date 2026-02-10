#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <string>
#include <raylib.h>

using namespace std;
class StartButton{
    private:
    float pos_x;
    float pos_y;
    float size;
    float width;
    float height;
    Color color;

public:
    StartButton(float pos_x, float pos_y, float size, float width, float height, Color color);
    void DrawStartButton(const std::string& textString);
    bool checkClicked(bool& isClicked);
};
#endif