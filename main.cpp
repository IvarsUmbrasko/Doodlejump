#include <iostream>
#include <raylib.h>
#include <cmath>
#include <vector>

using namespace std;

int screenWidth = 500;
int screenHeight = 700;
Color blue = {153, 255, 255};

class Platform
{
public:
    Texture2D platformTexture;
    Vector2 position = {0, 0};
    int width = 90;
    int height = 20;
    Image platform;

    Platform()
    {
        platform = LoadImage("Platform.png");
        platformTexture = LoadTextureFromImage(platform);
        UnloadImage(platform);
    }

    Platform(float x, float y)
    {
        position.x = x;
        position.y = y;
        platform = LoadImage("Platform.png");
        platformTexture = LoadTextureFromImage(platform);
        UnloadImage(platform);
    }

    void Draw()
    {
        DrawTexture(platformTexture, position.x, position.y, WHITE);
    }
};

class Doodle
{
public:
    Image doodle;
    Texture2D doodleTexture;
    Vector2 position = {200, 300};
    float dY = 0;
    bool isFalling = false;

    Doodle()
    {
        doodle = LoadImage("Doodle.png");
        doodleTexture = LoadTextureFromImage(doodle);
    }

    ~Doodle()
    {
        UnloadImage(doodle);
        UnloadTexture(doodleTexture);
    }

    void Draw()
    {
        DrawTexture(doodleTexture, position.x, position.y, WHITE);
    }
};

int main()
{
    srand(time(0));

    InitWindow(screenWidth, screenHeight, "Doodle Jump");
    SetTargetFPS(60);

    std::vector<Platform> platVec;

    Doodle doodle = Doodle();
    for (int i = 0; i < 10; ++i)
    {
        float randX = rand() % screenWidth;
        float randY = rand() % screenHeight;
        platVec.push_back(Platform(randX, randY));
    }

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(blue);
        for (int i = 0; i < 10; ++i)
        {
            platVec[i].Draw();
        }
        doodle.dY += 0.1;
        doodle.position.y += doodle.dY;
        if (doodle.position.y < 400)
        {

            for (int i = 0; i < 10; ++i)
            {
                platVec[i].position.y -= doodle.dY;
            }
        }
        if (doodle.position.y > screenHeight)
        {
            for (int i = 0; i < 10; ++i)
            {
                platVec[i].position.y = 0;
                platVec[i].position.x = rand() % screenWidth;
            }
        }

        for (int i = 0; i < 10; ++i)
        {
            Rectangle doodleRect = {doodle.position.x, doodle.position.y, 100, 100};
            Rectangle platRect = {platVec[i].position.x, platVec[i].position.y, 90, 20};
            if (CheckCollisionRecs(doodleRect, platRect))
            {
                doodle.dY -= 2;
            }
        }
        if (doodle.position.y > 600)
        {
            doodle.dY -= 2;
        }
        if (doodle.position.x > screenWidth)
        {
            doodle.position.x = -100;
        }
        if (doodle.position.x < -100)
        {
            doodle.position.x = screenWidth;
        }
        if (IsKeyDown(KEY_A))
        {
            doodle.position.x -= 5;
        }
        if (IsKeyDown(KEY_D))
        {
            doodle.position.x += 5;
        }
        doodle.Draw();
        EndDrawing();
    }
    CloseWindow();
}