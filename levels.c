#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
//!----------------------------------------------------------------------------------------
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
////////////////////////////////////////////////////////////////////////////////////
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
////////////////////////////////////////////////////////////////////////////////////

void DisableFlickering()
{
    SetConsoleOutputCP(437);
}
////////////////////////////////////////////////////////////////////////////////////

void displayMenu(int selectedOption)
{
    system("cls");
    printf("                           ========== LEVELS ==========\n");
    printf("                           1. ");
    if (selectedOption == 1)
    {
        SetColor(3);
    }
    printf("Easy\n");
    SetColor(7);
    printf("                           2. ");
    if (selectedOption == 2)
    {
        SetColor(3);
    }
    printf("Medium\n");
    SetColor(7);
    printf("                           3. ");
    if (selectedOption == 3)
    {
        SetColor(3);
    }
    printf("Hard\n");
    SetColor(7);
    printf("                           4. ");
    if (selectedOption == 4)
    {
        SetColor(3);
    }
    printf("Insane\n");
    SetColor(7);
    printf("                           ============================\n");
}
////////////////////////////////////////////////////////////////////////////////////

void showLoading()
{
    printf("                           Loading: ");
    for (int i = 0; i <= 100; i += 10)
    {
        printf("%d%% ", i);
        fflush(stdout);
        Sleep(150);
    }
    printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////

void saveDifficultyToFile(int selectedOption)
{
    FILE *file = fopen("selected_difficulty.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "%d", selectedOption);
        fclose(file);
    }
}
////////////////////////////////////////////////////////////////////////////////////

int loadDifficultyFromFile()
{
    FILE *file = fopen("selected_difficulty.txt", "r");
    int selectedOption = 1;
    if (file != NULL)
    {
        fscanf(file, "%d", &selectedOption);
        fclose(file);
    }

    return selectedOption;
}
//!----------------------------------------------------------------------------------------
int main()
{

    DisableFlickering();
    HideCursor();
    int choice;
    int selectedOption = loadDifficultyFromFile();
    char userInput;

    do
    {
        displayMenu(selectedOption);
        fflush(stdout);

        userInput = getch();

        switch (userInput)
        {
        case 'w':
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 's':
            if (selectedOption < 4)
                selectedOption++;
            break;
        case '\r':
            saveDifficultyToFile(selectedOption);

            printf("                           Difficulty sets\n");
            Sleep(1000);
            system("start menu.exe");
            exit(0);
            break;
        }

    } while (userInput != 27);

    return 0;
}
//!----------------------------------------------------------------------------------------