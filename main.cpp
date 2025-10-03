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

    ~Platform()
    {
        // UnloadTexture(platformTexture);
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
    float dY = 5;
    bool isFalling = true;

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

class Game
{
public:
    Doodle doodle = Doodle();
    std::vector<Platform> platVec;

    void initPlatforms()
    {
        for (int i = 0; i < 10; ++i)
        {
            float randX = rand() % screenWidth;
            float randY = rand() % screenHeight;
            platVec.push_back(Platform(randX, randY));
        }
    }

    void movePlatforms()
    {
        for (int i = 0; i < 10; ++i)
        {
            if (platVec[i].position.y > screenHeight)
            {
                platVec[i].position.y = 0;
                platVec[i].position.x = rand() % screenWidth;
            }
        }
    }

    void spawnNewPlatforms()
    {
        if (doodle.position.y < 450)
        {
            for (int i = 0; i < 10; ++i)
            {
                platVec[i].position.y -= doodle.dY;
            }
        }
    }

    void objectCollision()
    {
        Rectangle doodleRect = {doodle.position.x, doodle.position.y, 100, 100};
        for (int i = 0; i < 10; ++i)
        {
            Rectangle platRect = {platVec[i].position.x, platVec[i].position.y, 90, 20};
            if (CheckCollisionRecs(doodleRect, platRect))
            {
                if (doodle.position.y + 100 <= platVec[i].position.y + doodle.dY)
                {
                    doodle.dY = -10;
                    doodle.position.y -= 10;
                    doodle.position.y = platVec[i].position.y - 100;
                    std::cout << "X: " << doodle.position.x << " Y: " << doodle.position.y << std::endl;
                    doodle.isFalling = false;
                    break;
                }
            }
        }
    }

    void doodleMovement()
    {
        if (doodle.position.x > screenWidth)
        {
            doodle.position.x = -100;
        }
        if (doodle.position.x < -100)
        {
            doodle.position.x = screenWidth;
        }
    }

    void Update()
    {
        std::cout << doodle.isFalling << std::endl;
        if (doodle.isFalling)
        {
            objectCollision();
        }
        std::cout << doodle.isFalling << std::endl;
        doodleMovement();
        doodle.position.y += doodle.dY;
        doodle.Draw();
        for (int i = 0; i < 10; ++i)
        {
            platVec[i].Draw();
        }
        std::cout << "dY: " << doodle.dY << std::endl;
    }
};

int main()
{
    srand(time(0));

    InitWindow(screenWidth, screenHeight, "Doodle Jump");
    SetTargetFPS(60);

    Game game = Game();

    game.initPlatforms();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(blue);

        game.spawnNewPlatforms();
        game.movePlatforms();

        if (IsKeyDown(KEY_A))
        {
            game.doodle.position.x -= 5;
        }
        if (IsKeyDown(KEY_D))
        {
            game.doodle.position.x += 5;
        }
        game.Update();
        EndDrawing();
    }
    CloseWindow();
}