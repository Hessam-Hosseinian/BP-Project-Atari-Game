#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
// todo--------------------------------------------------------------------------------
#define MAX_X 75
#define MAX_Y 28
/////////////////////
#define MAX_BULLETS 5
/////////////////////
#define MAX_MINES 2
#define Mine_Speed 0.2
/////////////////////
#define MAX_BARSHIP 2
#define Barship_Speed 0.4
/////////////////////
#define MAX_Item 2
#define Item_Speed 0.3
/////////////////////
#define MAX_FIGHTERS 2
#define Fighter_Speed 0.4
#define MAX_FIGHTER_BULLETS 2
#define FighterBullet_Speed 1
/////////////////////
#define MAX_DRONE 2
#define DRONE_Speed 0.4
/////////////////////
#define MAX_BOMBER 1
#define bomber_Speed 0.2
#define MAX_bomber_BULLETS 1
#define bombBullet_Speed 1

//////////////////////
#define boss_Speed 1
#define gama_Speed 0.4
#define MAX_gama 5
// todo--------------------------------------------------------------------------------

#define mine1
#define barship1
#define fighter1
#define drone1
#define bomber1
#define boss1

// todo--------------------------------------------------------------------------------

struct Mine
{
    int x;
    float y;
    int active;
    int exploded;
};
/////////////////////
struct barship
{
    int x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct Item
{
    float x;
    float y;
    int active;
    int type;
};
/////////////////////
struct fighter
{
    int x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct fighterBullet
{
    int x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct drone
{
    float x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct bomber
{
    float x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct bomb
{
    float x;
    float y;
    int active;
    int HEALTH;
};
/////////////////////
struct boss
{
    int x;
    int y;
    int active;
    int HEALTH;
};
/////////////////////
struct gama
{
    float x;
    float y;
    int active;
    int HEALTH;
};
// todo--------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisableFlickering()
{
    SetConsoleOutputCP(437);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int checkCollision(int x1, int y1, int w1, int h1, int x2, int y2)
{

    return (x2 >= x1 && x2 <= x1 + w1 && y2 >= y1 && y2 <= y1 + h1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void savescore(int score, int seconde, int Level)
{

    FILE *filePointer;
    time_t rawTime;
    struct tm *timeInfo;
    char timeString[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

    filePointer = fopen("tmpscore.txt", "w");

    fprintf(filePointer, "%d %s %d %d", score, timeString, seconde, Level);

    fclose(filePointer);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void LevelSelect(int *Level, float *level_max, float *level_speed)
{
    FILE *file;

    file = fopen("selected_difficulty.txt", "r");

    if (file == NULL)
    {
        *Level = 1;
    }

    fscanf(file, "%d", Level);

    fclose(file);
    switch (*Level)
    {
    case 1:
        *level_max = 0;
        *level_speed = 0;
        gotoxy(MAX_X / 2 + 2, MAX_Y / 2);
        SetColor(4);
        printf("Easy\n");
        SetColor(7);
        break;

    case 2:
        *level_max = 0;
        *level_speed = 0.2;
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2);
        SetColor(4);
        printf("Medium\n");
        SetColor(7);
        break;

    case 3:
        *level_max = 1;
        *level_speed = 0.2;
        gotoxy(MAX_X / 2 + 3, MAX_Y / 2);
        SetColor(4);
        printf("Hard\n");
        SetColor(7);
        break;

    case 4:
        *level_max = 1;
        *level_speed = 0.4;
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2);
        SetColor(4);
        printf("Insane\n");
        SetColor(7);
        break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void logo(int x, int y, int usleep1)
{
    gotoxy(x, y);
    printf("%c", 219);
    usleep(usleep1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void printlogo()
{
    for (int i = 1; i >= 1; i--)
    {
        logo(37, 24, 1000);
    }
    for (int i = 37; i >= 31; i--)
    {
        logo(i, 23, 1000);
    }
    for (int i = 23; i >= 16; i--)
    {
        logo(31, i, 1000);
    }
    for (int i = 31; i <= 50; i++)
    {
        logo(i, 16, 1000);
    }
    for (int i = 16; i <= 23; i++)
    {
        logo(50, i, 1000);
    }
    for (int i = 50; i >= 44; i--)
    {
        logo(i, 23, 1000);
    }
    for (int i = 23; i <= 25; i++)
    {
        logo(44, i, 1000);
    }
    for (int i = 44; i <= 52; i++)
    {
        logo(i, 25, 1000);
    }
    for (int i = 52; i >= 29; i--)
    {
        logo(i, 25, 1000);
    }
    Sleep(800);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//?------------------------------------------------------------------------------------------------------------------------------

int main()
{
    HideCursor();
    DisableFlickering();

    srand(time(NULL));

    char ship[] = "|-o-|";
    char shipbaby11[] = "/^\\";
    char shipbaby21[] = "/^\\";
    int shipX = MAX_X / 2 + 2, shipY = MAX_Y - 3;
    int health = 3;
    int score = 0;
    int seconde = 0;
    int lastSecond = 0;
    int playing = 1;
    int specialBullets = 0;

    int bulletX[MAX_BULLETS];
    int bulletY[MAX_BULLETS];
    int bulletbaby1X[MAX_BULLETS / 2];
    int bulletbaby1Y[MAX_BULLETS / 2];
    int bulletbaby2X[MAX_BULLETS / 2];
    int bulletbaby2Y[MAX_BULLETS / 2];
    int bulletCount = 0;
    int bulletCount1 = 0;
    int bulletCount2 = 0;
    int itemDrop = 0;
    int isPaused = 0;
    float level_max;
    float level_speed;
    int Level;

    int BossFightl = 0;
    int shipbaby1 = 0;
    int shipbaby2 = 0;
    //?------------------------------------------------------------------------------------------------------------------------------

    LevelSelect(&Level, &level_max, &level_speed);
    printlogo();
    //?------------------------------------------------------------------------------------------------------------------------------
    int tmp = MAX_MINES + level_max;
    struct Mine mines[tmp];
    /////////////////////////////////
    tmp = MAX_FIGHTERS + level_max;
    struct fighter fighter[tmp];
    tmp = MAX_FIGHTER_BULLETS + level_max;
    struct fighterBullet fighterBullet[tmp];
    /////////////////////////////////
    tmp = MAX_BOMBER;
    struct bomber bomber[tmp];
    struct bomb bomb[1];
    /////////////////////////////////
    tmp = MAX_BARSHIP + level_max;
    struct barship barship[tmp];
    struct Item item[MAX_Item];
    /////////////////////////////////
    tmp = MAX_DRONE + level_max;
    struct drone drone[tmp];
    /////////////////////////////////
    struct boss boss[1];
    tmp = MAX_gama + level_max;
    struct gama gama[tmp];
    /////////////////////////////////
    for (int i = 0; i < MAX_MINES + level_max; i++)
    {
        mines[i].active = 0;
        mines[i].exploded = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_BARSHIP + level_max; i++)
    {
        barship[i].active = 0;
        barship[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_Item; i++)
    {
        item[i].active = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_FIGHTERS + level_max; i++)
    {
        fighter[i].active = 0;
        fighter[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_FIGHTER_BULLETS + level_max; i++)
    {
        fighterBullet[i].active = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_DRONE + level_max; i++)
    {
        drone[i].active = 0;
        drone[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_BOMBER; i++)
    {
        bomber[i].active = 0;
        bomber[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < 1; i++)
    {
        bomb[i].active = 0;
        bomb[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < 1; i++)
    {
        boss[i].active = 0;
        boss[i].HEALTH = 0;
    }
    /////////////////////////////////
    for (int i = 0; i < MAX_gama + level_max; i++)
    {
        gama[i].active = 0;
        gama[i].HEALTH = 0;
    }

    //!--------------------------------------------------------------------------------------------------------------------------------
    //*-------------------------------------------------------------------------------------------------------------------------------
    while (playing)
    {

        DisableFlickering();
        system("cls");
        float ingame_speed = (score / 200) / 10.0;

        gotoxy(shipX, shipY);
        printf("%s", ship);
        if (shipbaby1 == 1)
        {
            SetColor(13);
            gotoxy(shipX + 5, shipY + 1);
            printf("%s", shipbaby21);
            SetColor(7);
        }
        if (shipbaby2 == 1)
        {
            SetColor(13);
            gotoxy(shipX - 3, shipY + 1);
            printf("%s", shipbaby11);
            SetColor(7);
        }

        // todo-------------------------------------------------------------------------------------------------------------------Bulltes

        for (int i = 0; i < bulletCount; i++)
        {
            gotoxy(bulletX[i], bulletY[i]);
            SetColor(10);

            if (specialBullets > 0)
            {
                SetColor(9);

                specialBullets--;

                if (specialBullets == 0)
                {
                    SetColor(12);
                    bulletY[i]++;
                }
            }

            printf("|");
            SetColor(7);

            if (bulletY[i] > 0)
            {
                bulletY[i]--;
            }
            else
            {

                for (int j = i; j < bulletCount - 1; j++)
                {
                    bulletX[j] = bulletX[j + 1];
                    bulletY[j] = bulletY[j + 1];
                }
                bulletCount--;
            }
        }
        if (shipbaby1 == 1)
        {
            for (int i = 0; i < bulletCount1; i++)
            {
                gotoxy(bulletbaby1X[i], bulletbaby1Y[i]);
                SetColor(10);

                if (specialBullets > 0)
                {
                    SetColor(9);

                    specialBullets--;

                    if (specialBullets == 0)
                    {
                        SetColor(12);
                        bulletbaby1Y[i]++;
                    }
                }

                printf(".");
                SetColor(7);

                if (bulletbaby1Y[i] > 0)
                {
                    bulletbaby1Y[i]--;
                }
                else
                {

                    for (int j = i; j < bulletCount1 - 1; j++)
                    {
                        bulletbaby1X[j] = bulletbaby1X[j + 1];
                        bulletbaby1Y[j] = bulletbaby1Y[j + 1];
                    }
                    bulletCount1--;
                }
            }
        }
        if (shipbaby2 == 1)
        {

            for (int i = 0; i < bulletCount2; i++)
            {
                gotoxy(bulletbaby2X[i], bulletbaby2Y[i]);
                SetColor(10);

                if (specialBullets > 0)
                {
                    SetColor(9);

                    specialBullets--;

                    if (specialBullets == 0)
                    {
                        SetColor(12);
                        bulletbaby2Y[i]++;
                    }
                }

                printf(".");
                SetColor(7);

                if (bulletbaby2Y[i] > 0)
                {
                    bulletbaby2Y[i]--;
                }
                else
                {

                    for (int j = i; j < bulletCount2 - 1; j++)
                    {
                        bulletbaby2X[j] = bulletbaby2X[j + 1];
                        bulletbaby2Y[j] = bulletbaby2Y[j + 1];
                    }
                    bulletCount2--;
                }
            }
        }

        // todo----------------------------------------------------------------------------------------------------------------mines
#ifdef mine1
        if (score > 4 && BossFightl == 0)
        {
            for (int i = 0; i < MAX_MINES + level_max; i++)
            {
                if (mines[i].active && !mines[i].exploded)
                {

                    gotoxy(mines[i].x, mines[i].y);
                    SetColor(11);
                    printf("*");
                    SetColor(7);

                    if (mines[i].y < MAX_Y)
                    {
                        mines[i].y += Mine_Speed + level_speed + ingame_speed;
                    }
                    else
                    {

                        mines[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (!mines[i].exploded && checkCollision(mines[i].x, mines[i].y - 1, 0, 1, bulletX[j], bulletY[j] + 1))
                        {

                            mines[i].exploded = 1;
                            gotoxy(mines[i].x, mines[i].y);
                            SetColor(4);
                            printf("X");
                            SetColor(7);

                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;

                            score += 3;

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount; j++)
                        {
                            if (!mines[i].exploded && checkCollision(mines[i].x, mines[i].y - 1, 0, 1, bulletbaby1X[j], bulletbaby1Y[j] + 1))
                            {

                                mines[i].exploded = 1;
                                gotoxy(mines[i].x, mines[i].y);
                                SetColor(4);
                                printf("X");
                                SetColor(7);

                                for (int k = j; k < bulletCount - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;

                                score += 3;

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount; j++)
                        {
                            if (!mines[i].exploded && checkCollision(mines[i].x, mines[i].y - 1, 0, 1, bulletbaby2X[j], bulletbaby2Y[j] + 1))
                            {

                                mines[i].exploded = 1;
                                gotoxy(mines[i].x, mines[i].y);
                                SetColor(4);
                                printf("X");
                                SetColor(7);

                                for (int k = j; k < bulletCount - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;

                                score += 3;

                                break;
                            }
                        }
                    }
                    if (!mines[i].exploded && (checkCollision(shipX, shipY, 4, 1, mines[i].x, mines[i].y)))
                    {
                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            mines[i].active = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            mines[i].active = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }

                            mines[i].active = 0;
                        }
                    }
                }
                else
                {
                    if (rand() % 100 < 3)
                    {
                        mines[i].active = 1;
                        mines[i].exploded = 0;
                        mines[i].x = rand() % MAX_X;
                        mines[i].y = 0;
                    }
                }
            }
        }
#endif
        // todo------------------------------------------------------------------------------------------------------------------barship
#ifdef barship1
        if (score > 10 && BossFightl == 0)
        {
            for (int i = 0; i < MAX_BARSHIP + level_max; i++)
            {

                if (barship[i].active && barship[i].HEALTH)
                {
                    gotoxy((int)barship[i].x, (int)barship[i].y);
                    if (barship[i].HEALTH == 2)
                    {
                        SetColor(6);
                        printf("--$--");
                        SetColor(7);
                    }
                    else if (barship[i].HEALTH == 1)
                    {
                        SetColor(14);
                        printf("--$--");
                        SetColor(7);
                    }

                    float barshipPosY = barship[i].y;
                    if (barshipPosY < MAX_Y)
                    {
                        barship[i].y += Barship_Speed + level_speed + ingame_speed;
                    }
                    else
                    {

                        barship[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (barship[i].HEALTH && checkCollision((int)barship[i].x, (int)barship[i].y, 4, 1, bulletX[j], bulletY[j] + 2))
                        {

                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;
                            if (specialBullets > 0)
                            {
                                barship[i].HEALTH -= 2;
                            }
                            else
                            {
                                barship[i].HEALTH--;
                            }
                            if (barship[i].HEALTH <= 0)
                            {
                                barship[i].active = 0;
                                score += 5;
                            }

                            if (!barship[i].HEALTH && rand() % 100 < 75)
                            {

                                item[i].active = 1;
                                item[i].type = rand() % 4;
                                item[i].x = barship[i].x;
                                item[i].y = barship[i].y;
                                itemDrop = 1;
                            }

                            break;
                        }
                    }

                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (barship[i].HEALTH && checkCollision((int)barship[i].x, (int)barship[i].y, 4, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;
                                if (specialBullets > 0)
                                {
                                    barship[i].HEALTH -= 2;
                                }
                                else
                                {
                                    barship[i].HEALTH--;
                                }
                                if (barship[i].HEALTH <= 0)
                                {
                                    barship[i].active = 0;
                                    score += 5;
                                }

                                if (!barship[i].HEALTH && rand() % 100 < 75)
                                {

                                    item[i].active = 1;
                                    item[i].type = rand() % 4;
                                    item[i].x = barship[i].x;
                                    item[i].y = barship[i].y;
                                    itemDrop = 1;
                                }

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (barship[i].HEALTH && checkCollision((int)barship[i].x, (int)barship[i].y, 4, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;
                                if (specialBullets > 0)
                                {
                                    barship[i].HEALTH -= 2;
                                }
                                else
                                {
                                    barship[i].HEALTH--;
                                }
                                if (barship[i].HEALTH <= 0)
                                {
                                    barship[i].active = 0;
                                    score += 5;
                                }

                                if (!barship[i].HEALTH && rand() % 100 < 75)
                                {

                                    item[i].active = 1;
                                    item[i].type = rand() % 4;
                                    item[i].x = barship[i].x;
                                    item[i].y = barship[i].y;
                                    itemDrop = 1;
                                }

                                break;
                            }
                        }
                    }
                    if (barship[i].HEALTH && (checkCollision((int)barship[i].x, (int)barship[i].y, 4, 1, shipX, shipY + 1) ||
                                              checkCollision((int)barship[i].x, (int)barship[i].y, 4, 1, shipX + 4, shipY + 1)))
                    {

                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            barship[i].active = 0;
                            barship[i].HEALTH = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            barship[i].active = 0;
                            barship[i].HEALTH = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }
                            barship[i].HEALTH = 0;
                            barship[i].active = 0;
                        }
                    }
                }
                else
                {

                    if (rand() % 100 < 100)
                    {
                        barship[i].active = 1;
                        barship[i].HEALTH = 2;
                        barship[i].x = rand() % MAX_X;
                        barship[i].y = 0;
                    }
                }
            }
        }

        // todo---------------------------------------------------------------------------------------------------------------items
        if (score > 20 && BossFightl == 0)
        {
            for (int i = 0; i < MAX_Item; i++)
            {
                if (item[i].active)
                {
                    gotoxy((int)item[i].x + 2, (int)item[i].y);
                    if (item[i].type == 0)
                    {
                        SetColor(10);
                        printf("H");
                    }
                    else if (item[i].type == 1)
                    {
                        SetColor(14);
                        printf("P");
                    }
                    else if (item[i].type == 2)
                    {
                        SetColor(14);
                        printf("B");
                    }
                    else if (item[i].type == 3)
                    {
                        SetColor(14);
                        printf("K");
                    }

                    SetColor(7);

                    int itemPosY = item[i].y;
                    if (itemPosY < MAX_Y)
                    {
                        item[i].y += 0.5;
                    }
                    else
                    {

                        item[i].active = 0;
                    }

                    if (checkCollision(shipX - 2, shipY, 4, 1, (int)item[i].x, (int)item[i].y + 1))
                    {
                        if (item[i].type == 0)
                        {

                            health++;

                            if (health > 4)
                            {
                                health = 4;
                            }
                        }
                        else if (item[i].type == 1)
                        {

                            score += 10;

                            specialBullets = 200;
                        }

                        else if (item[i].type == 2)
                        {

                            score += 10;

                            for (int i = 0; i < MAX_MINES + level_max; i++)
                            {

                                mines[i].active = 0;
                                mines[i].exploded = 0;
                            }

                            for (int i = 0; i < MAX_BARSHIP + level_max; i++)
                            {
                                barship[i].active = 0;
                                barship[i].HEALTH = 0;
                            }

                            for (int i = 0; i < MAX_FIGHTERS + level_max; i++)
                            {
                                fighter[i].active = 0;
                                fighter[i].HEALTH = 0;
                            }

                            for (int i = 0; i < MAX_DRONE + level_max; i++)
                            {
                                drone[i].active = 0;
                                drone[i].HEALTH = 0;
                            }
                            Sleep(100);
                            gotoxy(33, 10);
                            printf("_.-^^---....,,--");
                            gotoxy(29, 11);
                            printf("_--                  --_");
                            gotoxy(28, 12);
                            printf("<                        >)");
                            gotoxy(28, 13);
                            printf("|                         |");
                            gotoxy(29, 14);
                            printf("\\._                   _./");
                            gotoxy(32, 15);
                            printf("```--. . , ; .--'''");
                            gotoxy(38, 16);
                            printf("| |   |");
                            gotoxy(35, 17);
                            printf(".-=||  | |=-.");
                            gotoxy(35, 18);
                            printf("`-=#$%%&%%$#=-'");
                            gotoxy(38, 19);
                            printf("| ;  :|");
                            gotoxy(29, 20);
                            printf("_____.,-#%&$@%#&#~,._____");
                            Sleep(200);
                        }
                        else if (item[i].type == 3)
                        {
                            if (shipbaby1 == 0)
                            {
                                shipbaby1 = 1;
                            }
                            else if (shipbaby2 == 0 && shipbaby1 == 1)
                            {
                                shipbaby2 = 1;
                            }

                            score += 10;
                        }

                        item[i].active = 0;
                    }
                }
            }
        }
#endif
        // todo------------------------------------------------------------------------------------------------------------------Fighters
#ifdef fighter1
        if (score > 100 && BossFightl == 0)
        {
            for (int i = 0; i < MAX_FIGHTERS + level_max; i++)
            {
                if (fighter[i].active && fighter[i].HEALTH)
                {
                    gotoxy((int)fighter[i].x, (int)fighter[i].y);
                    if (fighter[i].HEALTH > 1)
                    {
                        SetColor(4);
                        printf("<)8(>");
                        SetColor(7);
                    }
                    else
                    {
                        SetColor(12);
                        printf("<)8(>");
                        SetColor(7);
                    }

                    float fighterPosY = fighter[i].y;
                    if (fighterPosY < MAX_Y)
                    {
                        fighter[i].y += Fighter_Speed + level_speed + ingame_speed;
                        if (rand() % 100 < 25 && fighterBullet[i].active == 0)
                        {
                            fighterBullet[i].active = 1;
                            fighterBullet[i].x = (int)fighter[i].x + 2;
                            fighterBullet[i].y = (int)fighter[i].y + 1;
                        }
                    }
                    else
                    {
                        fighter[i].active = 0;
                        fighter[i].HEALTH = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (fighter[i].HEALTH && checkCollision((int)fighter[i].x, (int)fighter[i].y, 4, 1, bulletX[j], bulletY[j] + 2))
                        {
                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;
                            if (specialBullets > 0)
                            {
                                fighter[i].HEALTH -= 2;
                            }
                            else
                            {
                                fighter[i].HEALTH--;
                            }
                            if (fighter[i].HEALTH == 0)
                            {
                                fighter[i].active = 0;
                                score += 10;
                            }

                            break;
                        }
                    }

                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (fighter[i].HEALTH && checkCollision((int)fighter[i].x, (int)fighter[i].y, 4, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;
                                if (specialBullets > 0)
                                {
                                    fighter[i].HEALTH -= 2;
                                }
                                else
                                {
                                    fighter[i].HEALTH--;
                                }
                                if (fighter[i].HEALTH == 0)
                                {
                                    fighter[i].active = 0;
                                    score += 10;
                                }

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (fighter[i].HEALTH && checkCollision((int)fighter[i].x, (int)fighter[i].y, 4, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;
                                if (specialBullets > 0)
                                {
                                    fighter[i].HEALTH -= 2;
                                }
                                else
                                {
                                    fighter[i].HEALTH--;
                                }
                                if (fighter[i].HEALTH == 0)
                                {
                                    fighter[i].active = 0;
                                    score += 10;
                                }

                                break;
                            }
                        }
                    }

                    if (fighter[i].HEALTH && (checkCollision((int)fighter[i].x, (int)fighter[i].y, 4, 1, shipX, shipY + 1) ||
                                              checkCollision((int)fighter[i].x, (int)fighter[i].y, 4, 1, shipX + 4, shipY + 1)))
                    {
                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            fighter[i].active = 0;
                            fighter[i].HEALTH = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            fighter[i].active = 0;
                            fighter[i].HEALTH = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }
                            fighter[i].HEALTH = 0;
                            fighter[i].active = 0;
                        }
                    }
                }
                else
                {

                    if (rand() % 100 < 1)
                    {
                        fighter[i].active = 1;
                        fighter[i].HEALTH = 2;
                        fighter[i].x = rand() % MAX_X;
                        fighter[i].y = 0;
                    }
                }
            }

            for (int i = 0; i < MAX_FIGHTER_BULLETS; i++)
            {
                if (fighterBullet[i].active)
                {
                    gotoxy(fighterBullet[i].x, (int)fighterBullet[i].y);
                    SetColor(7);
                    printf("|");
                    SetColor(7);
                    int fighterBulletPos = fighterBullet[i].y;
                    if (fighterBulletPos < MAX_Y)
                    {
                        fighterBullet[i].y += FighterBullet_Speed + level_speed + ingame_speed;

                        if (checkCollision(shipX, shipY, 4, 1, fighterBullet[i].x, (int)fighterBullet[i].y))
                        {
                            if (shipbaby2 == 1)
                            {
                                shipbaby2 = 0;
                                fighterBullet[i].active = 0;
                            }
                            else if (shipbaby1 == 1)
                            {
                                shipbaby1 = 0;

                                fighterBullet[i].active = 0;
                            }
                            else
                            {
                                health--;

                                if (health <= 0)
                                {

                                    system("cls");

                                    savescore(score, seconde, Level);
                                    playing = 0;
                                }

                                fighterBullet[i].active = 0;
                            }
                        }
                    }
                    else
                    {
                        fighterBullet[i].active = 0;
                    }
                }
            }
        }
#endif
        // todo--------------------------------------------------------------------------------------------------------------------Drones
#ifdef drone1
        if (score > 150 && BossFightl == 0)
        {
            for (int i = 0; i < MAX_DRONE + level_max; i++)
            {
                if (drone[i].active && drone[i].HEALTH)
                {
                    float dronePosY = drone[i].y;
                    gotoxy((int)drone[i].x, (int)drone[i].y);
                    if (dronePosY < shipY)
                    {

                        SetColor(3);

                        printf("-v-");

                        SetColor(7);
                    }

                    else if (dronePosY > shipY)
                    {

                        SetColor(3);

                        printf("-^-");

                        SetColor(7);
                    }

                    if (dronePosY < MAX_Y)
                    {
                        if (drone[i].y < shipY)
                        {

                            drone[i].y += DRONE_Speed + level_speed + ingame_speed;
                        }
                        if (drone[i].y > shipY)
                        {

                            drone[i].y -= DRONE_Speed + level_speed + ingame_speed;
                        }
                        if (drone[i].x - 2 < shipX)
                        {

                            drone[i].x += DRONE_Speed + level_speed + ingame_speed;
                        }

                        if (drone[i].x - 2 >= shipX)
                        {
                            drone[i].x -= DRONE_Speed + level_speed + ingame_speed;
                        }
                    }
                    else
                    {
                        drone[i].HEALTH = 0;
                        drone[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (drone[i].HEALTH && checkCollision((int)drone[i].x, (int)drone[i].y, 2, 1, bulletX[j], bulletY[j] + 2))
                        {

                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;

                            drone[i].HEALTH = 0;

                            score += 10;

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (drone[i].HEALTH && checkCollision((int)drone[i].x, (int)drone[i].y, 2, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;

                                drone[i].HEALTH = 0;

                                score += 10;

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (drone[i].HEALTH && checkCollision((int)drone[i].x, (int)drone[i].y, 2, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;

                                drone[i].HEALTH = 0;

                                score += 10;

                                break;
                            }
                        }
                    }

                    if (drone[i].HEALTH && (checkCollision((int)drone[i].x, (int)drone[i].y, 2, 1, shipX, shipY) ||
                                            checkCollision((int)drone[i].x, (int)drone[i].y, 2, 1, shipX, shipY - 1) ||
                                            checkCollision((int)drone[i].x, (int)drone[i].y, 3, 1, shipX + 4, shipY)))
                    {

                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            drone[i].HEALTH = 0;
                            drone[i].active = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            drone[i].HEALTH = 0;
                            drone[i].active = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }
                            drone[i].HEALTH = 0;
                            drone[i].active = 0;
                        }
                    }
                }
                else
                {

                    if (rand() % 100 < 5)
                    {
                        drone[i].active = 1;
                        drone[i].HEALTH = 1;
                        drone[i].x = rand() % MAX_X;
                        drone[i].y = 0;
                    }
                }
            }
        }
#endif
// todo------------------------------------------------------------------------------------------------------------------ Bombers
#ifdef bomber1
        if (score > 300 && BossFightl == 0)
        {

            for (int i = 0; i < MAX_BOMBER; i++)
            {
                if (bomber[i].active && bomber[i].HEALTH)
                {

                    gotoxy((int)bomber[i].x, (int)bomber[i].y);
                    SetColor(13);
                    printf("|~{\\^/}~|");
                    SetColor(7);

                    if (bomber[i].x > 0 && bomber[i].y < MAX_Y)

                    {
                        bomber[i].x -= (bomber_Speed + level_speed + ingame_speed);
                        bomber[i].y += (bomber_Speed + level_speed + ingame_speed) / 5.0;

                        if (rand() % 100 < 20 && bomb[i].active == 0)
                        {
                            bomb[i].active = 1;
                            bomb[i].HEALTH = 2;
                            bomb[i].x = (int)bomber[i].x + 4;
                            bomb[i].y = (int)bomber[i].y + 1;
                        }
                    }
                    else
                    {
                        bomber[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (bomber[i].HEALTH && checkCollision((int)bomber[i].x, (int)bomber[i].y, 8, 1, bulletX[j], bulletY[j] + 1))
                        {
                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;
                            if (specialBullets > 0)
                            {
                                bomber[i].HEALTH -= 2;
                            }
                            else
                            {
                                bomber[i].HEALTH--;
                            }
                            if (bomber[i].HEALTH == 0)
                            {
                                bomber[i].active = 0;
                                score += 50;
                            }

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (bomber[i].HEALTH && checkCollision((int)bomber[i].x, (int)bomber[i].y, 8, 1, bulletbaby1X[j], bulletbaby1Y[j] + 1))
                            {
                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;
                                if (specialBullets > 0)
                                {
                                    bomber[i].HEALTH -= 2;
                                }
                                else
                                {
                                    bomber[i].HEALTH--;
                                }
                                if (bomber[i].HEALTH == 0)
                                {
                                    bomber[i].active = 0;
                                    score += 50;
                                }

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (bomber[i].HEALTH && checkCollision((int)bomber[i].x, (int)bomber[i].y, 8, 1, bulletbaby2X[j], bulletbaby2Y[j] + 1))
                            {
                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;
                                if (specialBullets > 0)
                                {
                                    bomber[i].HEALTH -= 2;
                                }
                                else
                                {
                                    bomber[i].HEALTH--;
                                }
                                if (bomber[i].HEALTH == 0)
                                {
                                    bomber[i].active = 0;
                                    score += 50;
                                }

                                break;
                            }
                        }
                    }

                    if (bomber[i].HEALTH && (checkCollision((int)bomber[i].x, (int)bomber[i].y, 4, 1, shipX, shipY + 3) ||
                                             checkCollision((int)bomber[i].x, (int)bomber[i].y, 4, 1, shipX + 4, shipY + 3)))
                    {
                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            bomber[i].HEALTH = 0;
                            bomber[i].active = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            bomber[i].HEALTH = 0;
                            bomber[i].active = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }
                            bomber[i].HEALTH = 0;
                            bomber[i].active = 0;
                        }
                    }
                }
                else
                {

                    if (rand() % 100 < 1)
                    {
                        bomber[i].active = 1;
                        bomber[i].HEALTH = 32;
                        bomber[i].y = rand() % (MAX_Y / 5);
                        bomber[i].x = MAX_X - 7;
                    }
                }
            }

            for (int i = 0; i < 1; i++)
            {
                if (bomb[i].active && bomb[i].HEALTH)
                {
                    gotoxy((int)bomb[i].x, (int)bomb[i].y);
                    SetColor(2);
                    printf("@");
                    gotoxy((int)bomb[i].x - 1, (int)bomb[i].y + 1);

                    printf("@@@");
                    SetColor(7);

                    if (bomb[i].y < MAX_Y)
                    {

                        bomb[i].y += (bombBullet_Speed + level_speed + ingame_speed) / 2;

                        if (checkCollision(shipX - 2, shipY, 6, 1, bomb[i].x - 1, bomb[i].y + 1))
                        {
                            if (shipbaby2 == 1)
                            {
                                shipbaby2 = 0;
                                shipbaby1 = 0;
                                bomb[i].HEALTH = 0;
                                bomb[i].active = 0;
                            }
                            else if (shipbaby1 == 1)
                            {
                                shipbaby1 = 0;
                                health--;
                                bomb[i].HEALTH = 0;
                                bomb[i].active = 0;
                            }
                            else
                            {
                                health -= 2;

                                if (health <= 0)
                                {

                                    system("cls");

                                    savescore(score, seconde, Level);
                                    playing = 0;
                                }
                                bomb[i].HEALTH = 0;
                                bomb[i].active = 0;
                            }
                        }
                    }
                    else
                    {
                        bomb[i].HEALTH = 0;
                        bomb[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (bomb[i].HEALTH && checkCollision((int)bomb[i].x - 1, (int)bomb[i].y, 2, 2, bulletX[j], bulletY[j] + 2))
                        {
                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;
                            if (specialBullets > 0)
                            {
                                bomb[i].HEALTH -= 2;
                            }
                            else
                            {
                                bomb[i].HEALTH--;
                            }
                            if (bomb[i].HEALTH <= 0)
                            {
                                bomb[i].active = 0;
                                score += 5;
                            }

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (bomb[i].HEALTH && checkCollision((int)bomb[i].x - 1, (int)bomb[i].y, 2, 2, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;
                                if (specialBullets > 0)
                                {
                                    bomb[i].HEALTH -= 2;
                                }
                                else
                                {
                                    bomb[i].HEALTH--;
                                }
                                if (bomb[i].HEALTH <= 0)
                                {
                                    bomb[i].active = 0;
                                    score += 5;
                                }

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (bomb[i].HEALTH && checkCollision((int)bomb[i].x - 1, (int)bomb[i].y, 2, 2, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;
                                if (specialBullets > 0)
                                {
                                    bomb[i].HEALTH -= 2;
                                }
                                else
                                {
                                    bomb[i].HEALTH--;
                                }
                                if (bomb[i].HEALTH <= 0)
                                {
                                    bomb[i].active = 0;
                                    score += 5;
                                }

                                break;
                            }
                        }
                    }
                }
            }
        }
#endif
        // todo---------------------------------------------------------------------------------------------------------------- boss
#ifdef boss1
        if (score >= 500 && 0 <= score % 500 && score % 500 <= 100)
        {
            BossFightl = 1;
            for (int i = 0; i < MAX_MINES + level_max; i++)
            {
                mines[i].active = 0;
                mines[i].exploded = 0;
            }

            for (int i = 0; i < MAX_BARSHIP + level_max; i++)
            {
                barship[i].active = 0;
                barship[i].HEALTH = 0;
            }

            for (int i = 0; i < MAX_FIGHTERS + level_max; i++)
            {
                fighter[i].active = 0;
                fighter[i].HEALTH = 0;
            }

            for (int i = 0; i < MAX_DRONE + level_max; i++)
            {
                drone[i].active = 0;
                drone[i].HEALTH = 0;
            }

            for (int i = 0; i < MAX_BOMBER; i++)
            {
                bomber[i].active = 0;
                bomber[i].HEALTH = 0;
            }
        }

        if (BossFightl == 1)
        {
            for (int i = 0; i < 1; i++)
            {
                if (boss[0].active && boss[0].HEALTH)
                {

                    if (boss[0].HEALTH >= 35)
                    {
                        gotoxy(boss[0].x, boss[0].y);
                        SetColor(4);
                        printf("_____");
                        gotoxy(boss[0].x - 4, boss[0].y + 1);
                        printf("___/O   O\\____");
                        gotoxy(boss[0].x - 5, boss[0].y + 2);
                        printf("/ O        O   \\");
                        gotoxy(boss[0].x - 5, boss[0].y + 3);
                        printf("\\______________/");
                        gotoxy(boss[0].x - 10, boss[0].y + 4);
                        printf("-===|____\\///\\\\\\/_____");
                        gotoxy(boss[0].x - 6, boss[0].y + 5);
                        printf("\\----------------/");
                        gotoxy(boss[0].x - 5, boss[0].y + 6);
                        printf("\\______________/  \\/");
                        gotoxy(boss[0].x - 4, boss[0].y + 7);
                        printf("/\\__________/    //");
                        gotoxy(boss[0].x - 11, boss[0].y + 8);
                        printf(">=o\\  // //\\\\   || \\\\  //");
                        gotoxy(boss[0].x - 8, boss[0].y + 9);
                        printf("\\\\o/ //  \\o  ||  \\o//");
                        gotoxy(boss[0].x - 4, boss[0].y + 10);
                        printf("//    || ||");
                        gotoxy(boss[0].x - 8, boss[0].y + 11);
                        printf("/o==o     |o \\o==o");
                        gotoxy(boss[0].x - 9, boss[0].y + 12);
                        printf("//         //     \\\\");
                        gotoxy(boss[0].x - 9, boss[0].y + 13);
                        printf("/\\        //       /\\");
                        gotoxy(boss[0].x + 1, boss[0].y + 14);
                        printf("/\\");
                        SetColor(7);
                    }
                    else if (boss[0].HEALTH >= 20)
                    {
                        gotoxy(boss[0].x, boss[0].y);
                        SetColor(5);
                        printf("_____");
                        gotoxy(boss[0].x - 4, boss[0].y + 1);
                        printf("___/O   O\\____");
                        gotoxy(boss[0].x - 5, boss[0].y + 2);
                        printf("/ O        O   \\");
                        gotoxy(boss[0].x - 5, boss[0].y + 3);
                        printf("\\______________/");
                        gotoxy(boss[0].x - 10, boss[0].y + 4);
                        printf("-===|____\\///\\\\\\/_____");
                        gotoxy(boss[0].x - 6, boss[0].y + 5);
                        printf("\\----------------/");
                        gotoxy(boss[0].x - 5, boss[0].y + 6);
                        printf("\\______________/");
                        gotoxy(boss[0].x - 4, boss[0].y + 7);
                        printf("/\\__________/");
                        gotoxy(boss[0].x - 11, boss[0].y + 8);
                        printf(">=o\\  // //\\\\   || ");
                        gotoxy(boss[0].x - 8, boss[0].y + 9);
                        printf("\\\\o/ //  \\o  ||");
                        gotoxy(boss[0].x - 4, boss[0].y + 10);
                        printf("//    || ||");
                        gotoxy(boss[0].x - 8, boss[0].y + 11);
                        printf("/o==o     |o \\o==o");
                        gotoxy(boss[0].x - 9, boss[0].y + 12);
                        printf("//         //     \\\\");
                        gotoxy(boss[0].x - 9, boss[0].y + 13);
                        printf("/\\        //       /\\");
                        gotoxy(boss[0].x + 1, boss[0].y + 14);
                        printf("/\\");
                        SetColor(7);
                    }
                    else if (boss[0].HEALTH >= 0)
                    {
                        gotoxy(boss[0].x, boss[0].y);
                        SetColor(4);
                        printf("_____");
                        gotoxy(boss[0].x - 4, boss[0].y + 1);
                        printf("___/O   O\\____");
                        gotoxy(boss[0].x - 5, boss[0].y + 2);
                        printf("/ O        O   \\");
                        gotoxy(boss[0].x - 5, boss[0].y + 3);
                        printf("\\______________/");
                        gotoxy(boss[0].x - 10, boss[0].y + 4);
                        printf("-===|____\\///\\\\\\/_____");
                        gotoxy(boss[0].x - 6, boss[0].y + 5);
                        printf("\\----------------/");
                        gotoxy(boss[0].x - 5, boss[0].y + 6);
                        printf("\\______________/");
                        gotoxy(boss[0].x - 4, boss[0].y + 7);
                        printf(" \\__________/");
                        gotoxy(boss[0].x - 11, boss[0].y + 8);
                        printf("         //\\\\   || ");
                        gotoxy(boss[0].x - 8, boss[0].y + 9);
                        printf("     //  \\o  ||");
                        gotoxy(boss[0].x - 4, boss[0].y + 10);
                        printf("//    || ||");
                        gotoxy(boss[0].x - 8, boss[0].y + 11);
                        printf("/o==o     |o \\o==o");
                        gotoxy(boss[0].x - 9, boss[0].y + 12);
                        printf("//         //     \\\\");
                        gotoxy(boss[0].x - 9, boss[0].y + 13);
                        printf("/\\        //       /\\");
                        gotoxy(boss[0].x + 1, boss[0].y + 14);
                        printf("/\\");
                        SetColor(7);
                    }

                    if (boss[0].y < 2)

                    {

                        boss[0].y += boss_Speed;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (boss[0].HEALTH && checkCollision(boss[0].x - 11, boss[0].y + 8, 25, 1, bulletX[j], bulletY[j] + 2) ||
                            checkCollision(boss[0].x - 9, boss[0].y + 13, 2, 1, bulletX[j], bulletY[j] + 2) ||
                            checkCollision(boss[0].x - 7, boss[0].y + 11, 4, 1, bulletX[j], bulletY[j] + 2) ||
                            checkCollision(boss[0].x + 1, boss[0].y + 14, 2, 1, bulletX[j], bulletY[j] + 2) ||
                            checkCollision(boss[0].x + 5, boss[0].y + 11, 4, 1, bulletX[j], bulletY[j] + 2) ||
                            checkCollision(boss[0].x + 10, boss[0].y + 13, 2, 1, bulletX[j], bulletY[j] + 2))
                        {
                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;
                            if (specialBullets > 0)
                            {
                                boss[0].HEALTH -= 2;
                            }
                            else
                            {
                                boss[0].HEALTH--;
                            }
                            if (boss[0].HEALTH <= 0)
                            {
                                boss[0].active = 0;
                                score += 100;
                                BossFightl = 0;
                            }

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (boss[0].HEALTH && checkCollision(boss[0].x - 11, boss[0].y + 8, 25, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2) ||
                                checkCollision(boss[0].x - 9, boss[0].y + 13, 2, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2) ||
                                checkCollision(boss[0].x - 7, boss[0].y + 11, 4, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2) ||
                                checkCollision(boss[0].x + 1, boss[0].y + 14, 2, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2) ||
                                checkCollision(boss[0].x + 5, boss[0].y + 11, 4, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2) ||
                                checkCollision(boss[0].x + 10, boss[0].y + 13, 2, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;
                                if (specialBullets > 0)
                                {
                                    boss[0].HEALTH -= 2;
                                }
                                else
                                {
                                    boss[0].HEALTH--;
                                }
                                if (boss[0].HEALTH <= 0)
                                {
                                    boss[0].active = 0;
                                    score += 100;
                                    BossFightl = 0;
                                }

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (boss[0].HEALTH && checkCollision(boss[0].x - 11, boss[0].y + 8, 25, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2) ||
                                checkCollision(boss[0].x - 9, boss[0].y + 13, 2, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2) ||
                                checkCollision(boss[0].x - 7, boss[0].y + 11, 4, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2) ||
                                checkCollision(boss[0].x + 1, boss[0].y + 14, 2, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2) ||
                                checkCollision(boss[0].x + 5, boss[0].y + 11, 4, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2) ||
                                checkCollision(boss[0].x + 10, boss[0].y + 13, 2, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {
                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;
                                if (specialBullets > 0)
                                {
                                    boss[0].HEALTH -= 2;
                                }
                                else
                                {
                                    boss[0].HEALTH--;
                                }
                                if (boss[0].HEALTH <= 0)
                                {
                                    boss[0].active = 0;
                                    score += 100;
                                    BossFightl = 0;
                                }

                                break;
                            }
                        }
                    }
                }
                else
                {

                    if (1)
                    {
                        boss[0].active = 1;
                        boss[0].HEALTH = 50;
                        boss[0].y = 0;
                        boss[0].x = MAX_X / 2 + 2;
                    }
                }
            }
        }
        if (boss[0].active)
        {
            for (int i = 0; i < MAX_gama + level_max; i++)
            {
                if (gama[i].active && gama[i].HEALTH)
                {
                    float gamaPosY = gama[i].y;
                    gotoxy((int)gama[i].x, (int)gama[i].y);
                    if (gamaPosY < shipY)
                    {

                        SetColor(8);

                        printf("-v-");

                        SetColor(7);
                    }

                    else if (gamaPosY > shipY)
                    {

                        SetColor(8);

                        printf("-^-");

                        SetColor(7);
                    }

                    if (gamaPosY < MAX_Y)
                    {
                        if (gama[i].y < shipY)
                        {

                            gama[i].y += gama_Speed + level_speed + ingame_speed;
                        }
                        if (gama[i].y > shipY)
                        {

                            gama[i].y -= gama_Speed + level_speed + ingame_speed;
                        }
                        if (gama[i].x - 2 < shipX)
                        {

                            gama[i].x += gama_Speed + level_speed + ingame_speed;
                        }

                        if (gama[i].x - 2 >= shipX)
                        {
                            gama[i].x -= gama_Speed + level_speed + ingame_speed;
                        }
                    }
                    else
                    {
                        gama[i].HEALTH = 0;
                        gama[i].active = 0;
                    }

                    for (int j = 0; j < bulletCount; j++)
                    {
                        if (gama[i].HEALTH && checkCollision((int)gama[i].x, (int)gama[i].y, 2, 1, bulletX[j], bulletY[j] + 2))
                        {

                            for (int k = j; k < bulletCount - 1; k++)
                            {
                                bulletX[k] = bulletX[k + 1];
                                bulletY[k] = bulletY[k + 1];
                            }
                            bulletCount--;

                            gama[i].HEALTH = 0;

                            break;
                        }
                    }
                    if (shipbaby1 == 1)
                    {
                        for (int j = 0; j < bulletCount1; j++)
                        {
                            if (gama[i].HEALTH && checkCollision((int)gama[i].x, (int)gama[i].y, 2, 1, bulletbaby1X[j], bulletbaby1Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount1 - 1; k++)
                                {
                                    bulletbaby1X[k] = bulletbaby1X[k + 1];
                                    bulletbaby1Y[k] = bulletbaby1Y[k + 1];
                                }
                                bulletCount1--;

                                gama[i].HEALTH = 0;

                                break;
                            }
                        }
                    }
                    if (shipbaby2 == 1)
                    {
                        for (int j = 0; j < bulletCount2; j++)
                        {
                            if (gama[i].HEALTH && checkCollision((int)gama[i].x, (int)gama[i].y, 2, 1, bulletbaby2X[j], bulletbaby2Y[j] + 2))
                            {

                                for (int k = j; k < bulletCount2 - 1; k++)
                                {
                                    bulletbaby2X[k] = bulletbaby2X[k + 1];
                                    bulletbaby2Y[k] = bulletbaby2Y[k + 1];
                                }
                                bulletCount2--;

                                gama[i].HEALTH = 0;

                                break;
                            }
                        }
                    }

                    if (gama[i].HEALTH && (checkCollision((int)gama[i].x, (int)gama[i].y, 2, 1, shipX, shipY) ||
                                           checkCollision((int)gama[i].x, (int)gama[i].y, 2, 1, shipX, shipY - 1) ||
                                           checkCollision((int)gama[i].x, (int)gama[i].y, 3, 1, shipX + 4, shipY)))
                    {

                        if (shipbaby2 == 1)
                        {
                            shipbaby2 = 0;
                            gama[i].HEALTH = 0;
                            gama[i].active = 0;
                        }
                        else if (shipbaby1 == 1)
                        {
                            shipbaby1 = 0;
                            gama[i].HEALTH = 0;
                            gama[i].active = 0;
                        }
                        else
                        {
                            health--;

                            if (health <= 0)
                            {

                                system("cls");

                                savescore(score, seconde, Level);
                                playing = 0;
                            }
                            gama[i].HEALTH = 0;
                            gama[i].active = 0;
                        }
                    }
                }
                else
                {

                    if (rand() % 100 < 5)
                    {
                        gama[i].active = 1;
                        gama[i].HEALTH = 1;
                        gama[i].x = boss[0].x + 2;
                        gama[i].y = boss[0].y + 1;
                    }
                }
            }
        }
#endif
        //!---------------------------------------------------------------------------------------------------------------------------

        if (time(NULL) - lastSecond >= 1)
        {
            score++;
            seconde++;

            lastSecond = time(NULL);
        }

        if (GetAsyncKeyState('A') & 0x8000)
        {
            if (shipbaby2 == 1)
            {

                if (shipX > 4)
                {
                    shipX--;
                }
            }
            else
            {
                if (shipX > 0)
                {
                    shipX--;
                }
            }
        }
        if (GetAsyncKeyState('D') & 0x8000)
        {
            if (shipbaby1 == 1)
            {
                if (shipX < MAX_X - 1)
                {
                    shipX++;
                }
            }
            else
            {
                if (shipX < MAX_X)
                {
                    shipX++;
                }
            }
        }

        if (GetAsyncKeyState('W') & 0x8000)
        {
            if (shipY > 0)
            {
                shipY--;
            }
        }
        if (GetAsyncKeyState('S') & 0x8000)
        {
            if (shipY < MAX_Y)
            {
                shipY++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8001)
        {

            if (bulletCount < MAX_BULLETS)
            {

                bulletX[bulletCount] = shipX + 2;
                bulletY[bulletCount] = shipY - 1;
                bulletCount++;
            }

            if (bulletCount1 < MAX_BULLETS / 2 && shipbaby1 == 1)
            {

                bulletbaby1X[bulletCount1] = shipX + 6;
                bulletbaby1Y[bulletCount1] = shipY;
                bulletCount1++;
            }
            if (bulletCount2 < MAX_BULLETS / 2 && shipbaby2 == 1)
            {

                bulletbaby2X[bulletCount2] = shipX - 2;
                bulletbaby2Y[bulletCount2] = shipY;
                bulletCount2++;
            }
        }
        if (GetAsyncKeyState('P') & 0x8001)
        {
            isPaused = 1;
            gotoxy(MAX_X / 2 - 1, MAX_Y / 2);
            SetColor(4);
            printf("Game Paused");
            SetColor(7);
            while (isPaused)
            {
                if (GetAsyncKeyState('O') & 0x8001)
                {
                    isPaused = 0;
                    gotoxy(MAX_X / 2 - 1, MAX_Y / 2);
                    printf("              ");
                    break;
                }
                Sleep(100);
            }
        }

        gotoxy(2, 2);
        printf("Health: ");
        for (int i = 0; i < health; i++)
        {
            if (i < 3)
            {

                SetColor(10);
                printf("H ");
            }
            else
            {
                SetColor(9);
                printf("H ");
            }
        }
        for (int i = 0; i < 3 - health; i++)
        {
            SetColor(4);
            printf("X ");
        }

        gotoxy(2, 3);
        SetColor(7);
        printf("Score: %d", score);

        if (BossFightl == 1)
        {
            gotoxy(2, 5);
            SetColor(7);
            printf("BossFight Health %d: ", boss[0].HEALTH);
        }

        Sleep(50);
    }
    system("cls");

    gotoxy(MAX_X / 2 + 3, MAX_Y / 2);
    SetColor(10);
    printf("%d", score);
    SetColor(7);
    if (score < 500)
    {
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2 + 2);
        SetColor(11);
        printf("NOT BAD");
        SetColor(7);
    }
    else if (score < 1000)
    {
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2 + 2);
        SetColor(11);
        printf("GOOD JOB");
        SetColor(7);
    }
    else if (score < 1500)
    {
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2 + 2);
        SetColor(11);
        printf("VERY GOOD");
        SetColor(7);
    }
    else
    {
        gotoxy(MAX_X / 2 + 1, MAX_Y / 2 + 2);
        SetColor(11);
        printf("EXCELENT");
        SetColor(7);
    }

    Sleep(2000);

    system("start gameover.exe");
    return 0;
}
//!------------------------------------------------------------------------------------------------------
