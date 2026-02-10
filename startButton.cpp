#include "startButton.h"
#include "variables.h"
#include <raylib.h>
#include <cmath>
StartButton::StartButton(float pos_x, float pos_y, float size, float width, float height, Color color){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->size = size;
    this->width = width;
    this->height = height;
    this->color = color;
}
void StartButton::DrawStartButton(const std::string& textString){

    float blink = 0.6f + 0.4f * sin(GetTime() * 4);
    Vector2 position = GetMousePosition();
    bool buttonPos = CheckCollisionPointRec(position, Rectangle{pos_x, pos_y, width, height});

    if (!buttonPos){
        DrawRectangleRounded(Rectangle{pos_x, pos_y, width, height}, 0.4f, 12, color);
    }
    else{
        DrawRectangleRounded(Rectangle{pos_x, pos_y, width, height}, 0.4f, 12,  Fade({
194, 97, 255, 255}, blink));
    }
    
         DrawRectangleRoundedLines(Rectangle{pos_x, pos_y, width, height}, 0.4f, 12, WHITE);

    int measure = MeasureText(textString.c_str(), size);

    DrawText(textString.c_str(), pos_x + (width - measure)/2, pos_y + (height - size)/2, size, {20, 71, 35, 255});
    DrawText(textString.c_str(), pos_x + (width - measure)/2 + 1, pos_y + (height - size)/2 + 1, size, {20, 71, 35, 255});


}
bool StartButton::checkClicked(bool& isClicked){
     Vector2 mousePosition = GetMousePosition();
    bool checkPos = CheckCollisionPointRec(mousePosition, Rectangle {pos_x, pos_y, width, height});
    bool pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (checkPos && pressed){
        isClicked = true;
        return true;
    }
    return false;
    
}