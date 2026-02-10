#include <iostream>
#include <raylib.h>
#include "ball.h"
#include "startButton.h"
#include "paddle.h"
#include "aiPaddle.h"
#include "variables.h"
#include "backButton.h"

using namespace std;

int main() {
    const float screen_width = 1400.0f;
    const float screen_height = 800.0f;
    const float gap_wall = 15.0f;

    Color background = {21, 17, 94, 255};
    Color fadeBg = {65, 63, 158, 255};
    Color color_ball = {242, 178, 247, 255};

    Paddle paddle1(gap_wall, screen_height / 2 - 65, 25, 130, {198, 255, 112, 255}, 15);
    AIPaddle paddle2(screen_width - gap_wall - 25, screen_height / 2 - 65, 25, 130, {198, 255, 112, 255}, 12);
    Ball ball(screen_width / 2, screen_height / 2, 20, color_ball, 10, 12);
    StartButton startButton(screen_width / 2 - 60, screen_height / 2 - 25, 25, screen_width / 10, screen_height / 10, {211, 255, 87, 255});
    BackButton backButton(screen_width / 2 - screen_width / 14, screen_height / 2 + 300, screen_width / 7, screen_height / 11, {252, 99, 255, 255}, 20, "GO BACK");

    InitWindow((int)screen_width, (int)screen_height, "Pong game");
   
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(background);

        DrawRectangle(300, 260, (int)(screen_width - 600), (int)(screen_height - 520), fadeBg);
        DrawLineEx(Vector2{screen_width / 2, 0}, Vector2{screen_width / 2, screen_height}, 5.0f, WHITE);

        DrawRectangleLinesEx(Rectangle{296, 256, screen_width - 592, screen_height - 512}, 16.0f, Fade(SKYBLUE, 0.2f));
        DrawRectangleLinesEx(Rectangle{300, 260, screen_width - 600, screen_height - 520}, 4.0f, SKYBLUE);

        // Draw paddles and ball
        ball.DrawBall();
        paddle1.DrawPaddles();
        paddle2.DrawPaddles();

        // Score boxes
        float boxWidth = screen_width / 4;
        float boxHeight = screen_height / 15;
        float boxY = 20;

        float boxX1 = screen_width / 4 - boxWidth / 2;
        float boxX2 = 3 * screen_width / 4 - boxWidth / 2;

        // Gradients
        for (int i = 0; i < (int)boxHeight; i++) {
            float alpha = 0.2f + 0.8f * i / boxHeight;
            DrawRectangle((int)boxX1, (int)(boxY + i), (int)boxWidth, 1, Color{82, 255, 255, (unsigned char)(alpha * 255)});
            DrawRectangle((int)boxX2, (int)(boxY + i), (int)boxWidth, 1, Color{82, 255, 255, (unsigned char)(alpha * 255)});
        }

        DrawRectangleLinesEx(Rectangle{boxX1, boxY, boxWidth, boxHeight}, 3.0f, WHITE);
        DrawRectangleLinesEx(Rectangle{boxX2, boxY, boxWidth, boxHeight}, 3.0f, WHITE);

        float fontSize = 50;
        DrawText(TextFormat("%i", player_point),
                 (int)(boxX1 + boxWidth / 2 - MeasureText(TextFormat("%i", player_point), (int)fontSize) / 2),
                 (int)(boxY + boxHeight / 2 - fontSize / 2),
                 (int)fontSize, WHITE);

        DrawText(TextFormat("%i", computer_point),
                 (int)(boxX2 + boxWidth / 2 - MeasureText(TextFormat("%i", computer_point), (int)fontSize) / 2),
                 (int)(boxY + boxHeight / 2 - fontSize / 2),
                 (int)fontSize, WHITE);

        // Start / game logic
        if (!isClicked) {
            startButton.DrawStartButton("START");
            startButton.checkClicked(isClicked);
        } else {
            backButton.drawBackButton();
            backButton.goBack(countdown, player_point, computer_point, isClicked, isCountdown, ball, paddle1, paddle2, screen_width, screen_height, gap_wall);

            if (isCountdown) {
                countdown -= GetFrameTime();
                DrawText(TextFormat("%i", (int)countdown), (int)(screen_width / 2 - 20), (int)(screen_height / 2 - 40), 80, WHITE);
                if (countdown <= 0) isCountdown = false;
            } else {
                if (CheckCollisionCircleRec(Vector2{ball.getPositionX(), ball.getPositionY()}, ball.getRadius(),
                                            Rectangle{paddle1.getPositionX(), paddle1.getPositionY(), paddle1.getWidth(), paddle1.getHeight()})) {
                    ball.setPositionX(ball.getPositionY(), ball.getPositionX(), paddle1.getPositionX(), paddle1.getPositionY(), paddle1.getWidth(), paddle1.getHeight());
                    ball.StartExplosion();
                }

                if (CheckCollisionCircleRec(Vector2{ball.getPositionX(), ball.getPositionY()}, ball.getRadius(),
                                            Rectangle{paddle2.getPositionX(), paddle2.getPositionY(), paddle2.getWidth(), paddle2.getHeight()})) {
                    ball.setPositionX(ball.getPositionY(), ball.getPositionX(), paddle2.getPositionX(), paddle2.getPositionY(), paddle2.getWidth(), paddle2.getHeight());
                    ball.StartExplosion();
                }

                float deltaTime = GetFrameTime();
                ball.UpdateExplosion(deltaTime);
                ball.MoveBall(screen_width, screen_height, paddle1, paddle2, gap_wall);

                paddle1.Move(screen_height);
                paddle2.AutoMove(ball.getPositionY(), screen_height);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
