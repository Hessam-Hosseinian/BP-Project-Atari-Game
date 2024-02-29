#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
// todo-------------------------------------------------------------------------------------
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//////////////////////////////////////////////////////////
void DisableFlickering()
{
    SetConsoleOutputCP(437);
}
// ///////////////////////////////////////////////////////
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
// todo-------------------------------------------------------------------------------------
void displayIntro()
{
    system("cls");

    printf("                                                        ____________\n");
    printf("                                         --)-----------|____________|\n");
    printf("                                                       ,\'       ,\'\n");
    printf("                         -)------========            ,\'  ____ ,\'\n");
    printf("                                  `.    `.         ,\'  ,\'__ ,\'\n");
    printf("                                    `.    `.     ,\'       ,\'\n");
    printf("                                      `.    `._,'_______,'__\n");
    printf("                                        [._ _| ^--      || |\n");
    printf("                                ____,...-----|__________ll_|\\\n");
    printf("               ,.,..-------\"\"\"\"\"     \"----\'                 ||\n");
    printf("           .-\"\"  |=========================== ______________ |\n");
    printf("            \"-...l_______________________    |  |\'      || |_]\n");
    printf("                                         [`-.|__________ll_|      \n");
    printf("                                       ,\'    ,\' `.        `.\n");
    printf("                                     ,\'    ,\'     `.    ____`.\n");
    printf("                         -)---------========        `.  `.____`.\n");
    printf("                                                      `.        `.\n");
    printf("                                                        `.________`.\n");
    printf("                                        --)-------------|___________|\n");

    printf("\n");
    printf("\n");
    printf("\n");

    printf("        ____       _            _   _        _____                 _          \n");
    printf("       / ___| __ _| | __ _  ___| |_(_) ___  | ____|_ __ ___  _ __ (_)_ __ ___ \n");
    printf("      | |  _ / _` | |/ _` |/ __| __| |/ __| |  _| | '_ ` _ \\| '_ \\| | '__/ _ \\ \n");
    printf("      | |_| | (_| | | (_| | (__| |_| | (__  | |___| | | | | | |_) | | | |  __/\n");
    printf("       \\____|\\__,_|_|\\__,_|\\___|\\__|_|\\___| |_____|_| |_| |_| .__/|_|_|  \\___|\n");
    printf("                                                            |_|               \n");

    fflush(stdout);

    while (getch() != '\r')
        ;
}
// todo-------------------------------------------------------------------------------------

int main()
{
    HideCursor();
    DisableFlickering();
    displayIntro();

    system("start menu.exe");

    return 0;
}