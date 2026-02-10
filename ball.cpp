#include "ball.h"
#include <iostream>
#include "paddle.h"
#include "aiPaddle.h"
#include "variables.h"
#include <raylib.h>
#include <string.h>
#include <cmath>
#include <deque>
#include <vector>

using namespace std;

float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
Ball::Ball(float pos_x, float pos_y, float radius, Color color, float move_x,float move_y){
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->radius = radius;
        this->color = color;
        this->move_x = move_x;
        this->move_y = move_y;
    }

void Ball::clearTrail(){
    trailPositions.clear();
}
void Ball::StartExplosion() {
    isHit = true;
    hitTimer = hitDuration;
    explosionParticles.clear();

  
    int particleCount = 15;
    for (int i = 0; i < particleCount; i++) {
        float angle = (360.0f / particleCount) * i * (3.14159f / 180.0f); 
        float speed = GetRandomValue(50, 150) / 100.0f; 
        ExplosionParticle p;
        p.x = pos_x;
        p.y = pos_y;
        p.radius = GetRandomValue(2, 5);
        p.speedX = cos(angle) * speed * 200;
        p.speedY = sin(angle) * speed * 200;
        p.alpha = 1.0f;
        explosionParticles.push_back(p);
    }
}


void Ball::UpdateExplosion(float deltaTime) {
    if (!isHit) return;

    hitTimer -= deltaTime;
    if (hitTimer <= 0) {
        isHit = false;
        explosionParticles.clear();
        return;
    }

    
    for (auto &p : explosionParticles) {
        p.x += p.speedX * deltaTime;
        p.y += p.speedY * deltaTime;
        p.alpha -= deltaTime * 0.009f; 
        if (p.alpha < 0) p.alpha = 0;
    }
}

void Ball::DrawBall(){
    Color glowColor = {252, 255, 92, 255}; 
    Color hitColor = {107, 248, 255, 255};
    float alphaBlink = 0.5f + 0.2f * (sin(GetTime() * 6) + 1) / 2; 

    if (isHit) {
        
        DrawCircle(pos_x, pos_y, radius + 40, Fade(glowColor, alphaBlink * 0.15f));
        DrawCircle(pos_x, pos_y, radius + 30, Fade(glowColor, alphaBlink * 0.2f));
        DrawCircle(pos_x, pos_y, radius + 10, Fade(glowColor, alphaBlink * 0.4f));
        DrawCircle(pos_x, pos_y, radius + 7,  Fade(glowColor, alphaBlink * 0.6f));
        
        DrawCircle(pos_x, pos_y, radius, glowColor); 
        for (auto &p : explosionParticles) {
            DrawCircle(p.x, p.y, p.radius, {135, 253, 255, 255});
        }
    }
    else{
        

        int i = 0;
            for (auto& pos : trailPositions) {
                float alpha = 0.05f + 0.02f * i + 0.01;
                DrawCircleV(pos, radius, Fade(hitColor, alpha));
                i++;
            }
        DrawCircle(pos_x, pos_y, radius + 40, Fade(hitColor, alphaBlink * 0.15f));
        DrawCircle(pos_x, pos_y, radius + 30, Fade(hitColor, alphaBlink * 0.2f));
        DrawCircle(pos_x, pos_y, radius + 10, Fade(hitColor, alphaBlink * 0.4f));
        DrawCircle(pos_x, pos_y, radius + 7,  Fade(hitColor, alphaBlink * 0.6f));


            DrawCircle(pos_x, pos_y, radius, hitColor); 
    }

}

void Ball::MoveBall(float screen_width, float screen_height, Paddle& paddle, AIPaddle& computer, float gap_wall){
        trailPositions.push_back(Vector2{pos_x, pos_y});
    if (trailPositions.size() > maxTrail){
        trailPositions.pop_front();
    }
    pos_x += move_x;
    pos_y += move_y;
    
    
    if (pos_x + radius >= screen_width){
        player_point += 1;
        countdown = 6.0;
        paddle.setPosX(gap_wall);
        paddle.setPosY(screen_height/2 - 65);
        computer.setPosX(screen_width - gap_wall - 25);
        computer.setPosY(screen_height/2 - 65);
        
        isCountdown = true;
        clearTrail();
        ResetBall(screen_width, screen_height);
        
    }
    if(pos_x - radius <= 0) {
        computer_point += 1;
        countdown = 6.0;
        paddle.setPosX(gap_wall);
        paddle.setPosY(screen_height/2 - 65);
        computer.setPosX(screen_width - gap_wall - 25);
        computer.setPosY(screen_height/2 - 65);
        isCountdown = true;
        clearTrail();
        ResetBall(screen_width, screen_height);
        
    }
    if (pos_y + radius >= screen_height || pos_y - radius <= 0){
        move_y *= -1;
    }
}

void Ball::ResetBall(float screen_width, float screen_height){
    isCountdown = true;
    pos_x = screen_width/2;
    pos_y = screen_height/2;

    int choice[2] = {1, -1};

    move_x *= choice[GetRandomValue(0, 1)];
    move_y *= choice[GetRandomValue(0, 1)];
}

float Ball::getPositionY(){
    return pos_y;
}
float Ball::getPositionX(){
    return pos_x;
}
float Ball::getRadius(){
    return radius;
}
void Ball::setPositionX(float positionY, float positionX, float paddleX, float paddleY, float paddleWidth, float paddleHeight){
    
  float paddleCenterY = paddleY + paddleHeight / 2.0f; 
    float distance = positionY - paddleCenterY;

    float normalized = distance / (paddleHeight / 2.0f);
    normalized = Clamp(normalized, -1.0f, 1.0f);

    float maxAngle = 50.0f * DEG2RAD;
    const float MIN_ANGLE = 25.0f * DEG2RAD;
    float angle = normalized * maxAngle;
if (fabs(angle) < MIN_ANGLE)
{
    angle = (angle < 0 ? -1 : 1) * MIN_ANGLE;
}

    

    float speed = 19.f;

    move_x = speed * cos(angle);
    move_y = speed * sin(angle);
    

    if (paddleX < positionX) {   
        move_x = fabs(move_x);
    } else {  
        move_x = -fabs(move_x);
    }
   
}


