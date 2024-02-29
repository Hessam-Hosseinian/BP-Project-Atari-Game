#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX_LINES 600
#define MAX_LENGTH 100

// todo---------------------------------------------------------------------
//!-------------------------------------------------------------------------
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
////////////////////////////////////////////////////////////////////////////
void DisableFlickering()
{
    SetConsoleOutputCP(437);
}
////////////////////////////////////////////////////////////////////////////
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
////////////////////////////////////////////////////////////////////////////
int countLines(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Go And Take Some Fun");
        Sleep(2000);
        system("start menu.exe");
        return -1;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }
    fclose(file);
    return count;
}
////////////////////////////////////////////////////////////////////////////
// todo---------------------------------------------------------------------
//!-------------------------------------------------------------------------
int main()
{
    HideCursor();
    DisableFlickering();
    int currentLine = 0;
    int cursorPosition = 0;

    int key;

    FILE *file = fopen("scores.txt", "r");

    if (file == NULL || countLines("scores.txt") == 0)
    {
        SetColor(1);
        printf("                                Go And Take Some Fun");
        Sleep(2000);
        system("start menu.exe");
        exit(0);
    }

    char lines[MAX_LINES][MAX_LENGTH];

    char tmpstring[MAX_LINES][MAX_LENGTH];
    int line_count = countLines("scores.txt") - 1;
    int line_count2 = countLines("scores.txt") - 1;

    while (line_count2 < MAX_LINES && fgets(lines[line_count2], sizeof(lines[line_count2]), file))
    {
        line_count2--;
    }

    fclose(file);

    while (1)
    {
        DisableFlickering();
        system("cls");
        DisableFlickering();
        SetColor(10);
        printf("                            UserName\n");
        printf("                            Score Date Time SecondeYouPlay Level\n\n");
        SetColor(4);
        printf("                            Enter E for Back To Menu\n\n");

        SetColor(7);
        for (int i = currentLine; i < line_count && i < currentLine + 16; i += 2)
        {
            if (i == cursorPosition)
            {
                SetColor(11);
                printf("                            > ");
                printf("%s", lines[i + 1]);
                printf("                            %s", lines[i]);
            }
            else
            {
                printf("                            %s", lines[i + 1]);
                printf("                            %s", lines[i]);
            }

            if (i == cursorPosition)
            {
                SetColor(7);
            }
        }

        key = getch();

        if (key == 'w' && cursorPosition > 0)
        {
            cursorPosition -= 2;
            if (cursorPosition < currentLine)
            {
                currentLine -= 2;
            }
        }
        else if (key == 's' && cursorPosition < line_count - 1)
        {
            cursorPosition += 2;
            if (cursorPosition >= currentLine + 16)
            {
                currentLine += 2;
            }
        }
        else if (key == 'e')
        {
            break;
        }
    }
    system("start menu.exe");
    return 0;
}
////////////////////////////////////////////////////////////////////////////
// todo---------------------------------------------------------------------
//!-------------------------------------------------------------------------
