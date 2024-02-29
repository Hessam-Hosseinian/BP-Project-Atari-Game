#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
char name[20];
void savescore(char name1[20])
{

    FILE *filePointer;
    FILE *filePointer2;
    int score;
    char timeString[20];
    char timeString2[20];

    int seconde;
    int Level;

    filePointer2 = fopen("tmpscore.txt", "r");
    fscanf(filePointer2, "%d %s %s %d %d", &score, timeString, timeString2, &seconde, &Level);
    fclose(filePointer2);

    filePointer = fopen("scores.txt", "a");

    fprintf(filePointer, "%s%d %s %s %d %d\n", name1, score, timeString, timeString2, seconde, Level);

    fclose(filePointer);
}

void displayname()
{

    system("cls");
    printf("\n");
    printf("\n");

    printf("                                        .-.\n");
    printf("                                        |_:_|\n");
    printf("                                       /(_Y_)\\\n");
    printf("                  .                   ( \\/M\\/ )\n");
    printf("                   '.               _.'-/'-'\\-'._\n");
    printf("                     ':           _/.--'[[[[]'--.\\_\n");
    printf("                       ':        /_'  : |::\"| :  '.\\\n");
    printf("                         ':     //   ./ |oUU| \\'  :\\\n");
    printf("                           ':  _:'..' \\_|___|_/ :   :|\n");
    printf("                             ':.  .'  |_[___]_|  :.':\\\n");
    printf("                              [::\\ |  :  | |  :   ; : \\\n");
    printf("                               '-'   \\/'.| |.' \\  .;.' |\n");
    printf("                               |\\_    \\ '-'   :       |\n");
    printf("                               |  \\    \\ .:    :   |   |\n");
    printf("                               |   \\    | '.   :    \\  |\n");
    printf("                               /       \\   :. .;       |\n");
    printf("                              /     |   |  :__/     :  \\\\\n");
    printf("                             |  |   |    \\:   | \\   |   ||\n");
    printf("                            /    \\  : :  |:   /  |__|   /|\n");
    printf("                            |     : : :_/_|  /'._\\  '--|_\\\n");
    printf("                            /___.-/_|-'   \\  \\\n");
    printf("                                           '-'\n");

    printf("                                   Enter Your Name\n");
    printf("                                       ");
    SetColor(4);
    fgets(name, sizeof(name) - 2, stdin);
    SetColor(7);
    savescore(name);
    printf("                             ==========================\n");
}

void displayagain(int selectedOption)
{

    system("cls");
    printf("\n");
    printf("\n");

    printf("                                        .-.\n");
    printf("                                        |_:_|\n");
    printf("                                       /(_Y_)\\\n");
    printf("                  .                   ( \\/M\\/ )\n");
    printf("                   '.               _.'-/'-'\\-'._\n");
    printf("                     ':           _/.--'[[[[]'--.\\_\n");
    printf("                       ':        /_'  : |::\"| :  '.\\\n");
    printf("                         ':     //   ./ |oUU| \\'  :\\\n");
    printf("                           ':  _:'..' \\_|___|_/ :   :|\n");
    printf("                             ':.  .'  |_[___]_|  :.':\\\n");
    printf("                              [::\\ |  :  | |  :   ; : \\\n");
    printf("                               '-'   \\/'.| |.' \\  .;.' |\n");
    printf("                               |\\_    \\ '-'   :       |\n");
    printf("                               |  \\    \\ .:    :   |   |\n");
    printf("                               |   \\    | '.   :    \\  |\n");
    printf("                               /       \\   :. .;       |\n");
    printf("                              /     |   |  :__/     :  \\\\\n");
    printf("                             |  |   |    \\:   | \\   |   ||\n");
    printf("                            /    \\  : :  |:   /  |__|   /|\n");
    printf("                            |     : : :_/_|  /'._\\  '--|_\\\n");
    printf("                            /___.-/_|-'   \\  \\\n");
    printf("                                           '-'\n");

    printf("                       Do You Want to Challenge Yourself Again ?\n");
    SetColor(11);

    printf("                                       %s", name);
    SetColor(7);

    printf("                                  1. ");
    if (selectedOption == 1)
    {
        SetColor(10);
    }

    printf("Yes");
    printf("      ");

    SetColor(7);
    printf("2. ");
    if (selectedOption == 2)
    {
        SetColor(4);
    }
    printf("No\n");

    SetColor(7);

    printf("                             ==========================\n");
}

int main()
{
    int selectedOption = 1;
    char userInput;

    HideCursor();
    DisableFlickering();
    displayname();

    do
    {
        displayagain(selectedOption);
        fflush(stdout);

        userInput = getch();

        switch (userInput)
        {
        case 'a':
            if (selectedOption > 1)
                selectedOption--;
            break;
        case 'd':
            if (selectedOption < 2)
                selectedOption++;
            break;
        case '\r':
            if (selectedOption == 1)
            {

                system("start play.exe");
                exit(0);
            }
            else if (selectedOption == 2)
            {
                system("start menu.exe");
                exit(0);
            }

            break;
        }
    } while (userInput != 27);

    return 0;
}
