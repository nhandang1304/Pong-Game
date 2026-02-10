#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <raylib.h>
#include <string.h>
#include <cmath>
#include <deque>
#include <vector>

using namespace std;
class Paddle;
class AIPaddle;

class Ball{
    private:
    struct ExplosionParticle{
        float x,y;
        
        float radius;
        float speedX, speedY;
        float alpha;

    };
    std::vector <ExplosionParticle> explosionParticles;
    bool isHit = false;       
    float hitTimer = 0.0f;    
    const float hitDuration = 0.6f; 
    float pos_x;
    float pos_y;
    float radius;
    float move_x;
    float move_y;
    Color color;
    deque<Vector2> trailPositions; 
    const int maxTrail = 15;

public:
    Ball(float pos_x, float pos_y, float radius, Color color, float move_x,float move_y);
    void StartExplosion();

    void UpdateExplosion(float deltaTime);
    void DrawBall();
    
    void MoveBall(float screen_width, float screen_height, Paddle& paddle, AIPaddle& computer, float gap_wall);
   
    void ResetBall(float screen_width, float screen_height);
    
    float getPositionY();
    float getPositionX();
    float getRadius();
    
    void setPositionX(float positionY, float positionX, float paddleX, float paddleY, float paddleWidth, float paddleHeight);
    void clearTrail();
  
};

#endif 