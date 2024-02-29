#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
// todo-------------------------------------------------------------------------------------

void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void DisableFlickering()
{
    SetConsoleOutputCP(437);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
// todo-------------------------------------------------------------------------------------

void displayMenu(int selectedOption)
{

    system("cls");
    SetColor(15);
    printf("                           _______              _______\n");
    printf("                          /\\:::::/\\            /\\:::::/\\\n");
    printf("                         /::\\:::/::\\          /==\\:::/::\\\n");
    printf("                        /::::\\_/::::\\   .--. /====\\_/::::\\\n");
    printf("                       /_____/ \\_____\\-' .-.`-----' \\_____\\\n");
    printf("                       \\:::::\\_/:::::/-. `-'.-----._/:::::/\n");
    printf("                        \\::::/:\\::::/   `--' \\::::/:\\::::/\n");
    printf("                         \\::/:::\\::/          \\::/:::\\::/\n");
    printf("                          \\/:::::\\/            \\/:::::\\/\n");
    printf("                           \"\"\"\"\"\"\"              \"\"\"\"\"\"\"\n");

    SetColor(7);

    printf("                       1. ");
    if (selectedOption == 1)
    {

        SetColor(10);
        printf("Play");
        SetColor(7);
        printf(" ---------- ");
        SetColor(11);
        printf("Start playing the game\n");
    }

    else
    {
        printf("Play\n");
    }

    SetColor(7);
    printf("                       2. ");
    if (selectedOption == 2)
    {

        SetColor(10);
        printf("Logs");
        SetColor(7);
        printf(" ---------- ");
        SetColor(11);
        printf("View logs and records\n");
    }

    else
    {
        printf("Logs\n");
    }

    SetColor(7);

    printf("                       3. ");
    if (selectedOption == 3)
    {

        SetColor(10);
        printf("Levels");
        SetColor(7);
        printf(" ---------- ");
        SetColor(11);
        printf("Adjust game levels\n");
    }

    else
    {
        printf("Levels\n");
    }
    SetColor(7);

    printf("                       4. ");
    if (selectedOption == 4)
    {

        SetColor(4);
        printf("Exit");
        SetColor(7);
        printf(" ---------- ");
        SetColor(11);
        printf("Exit the program\n");
    }

    else
    {
        printf("Exit\n");
    }

    SetColor(7);
    printf("                       ==========================\n");
}
// todo-------------------------------------------------------------------------------------

void showLoading()
{

    printf("                       Loading: ");

    for (int i = 0; i <= 200; i += 10)
    {

        printf("%c", 987);
        fflush(stdout);
        usleep(1000);
    }

    printf("\n");
}
// todo-------------------------------------------------------------------------------------

int main()
{
    HideCursor();
    DisableFlickering();
    int selectedOption = 1;
    char userInput;

    do
    {

        DisableFlickering();
        displayMenu(selectedOption);
        fflush(stdout);

        userInput = getch();

        switch (userInput)
        {
        case 'w':
            if (selectedOption > 1)
            {
                selectedOption--;
            }
            break;
        case 's':
            if (selectedOption < 4)
            {
                selectedOption++;
            }
            break;
        case '\r':
            if (selectedOption == 1)
            {

                printf("                       Opening program...\n");
                showLoading();

                system("start play.exe");
                exit(0);
            }
            else if (selectedOption == 2)
            {

                system("start logs.exe");
                exit(0);
            }
            else if (selectedOption == 3)
            {

                system("start levels.exe");
                exit(0);
            }
            else if (selectedOption == 4)
            {

                printf("                       Exiting program...\n");
                Sleep(500);

                printf("                       Saving data...\n");
                Sleep(500);
                showLoading();

                printf("                       Data saved...\n");
                Sleep(500);

                printf("                       Wish you have a good day\n");
                Sleep(1500);
                exit(0);
            }
            break;
        }

    } while (userInput != 27);

    return 0;
}
// todo-------------------------------------------------------------------------------------
