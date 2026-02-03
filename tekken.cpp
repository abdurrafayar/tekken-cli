#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <ctime>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

string getField(string record, int field);

void playFightSound()
{
    PlaySound(TEXT("./sounds/fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playPunch1Sound()
{
    PlaySound(TEXT("./sounds/punch1.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playPunch2Sound()
{
    PlaySound(TEXT("./sounds/punch2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playKickSound()
{
    PlaySound(TEXT("./sounds/kick.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playSwordSound()
{
    PlaySound(TEXT("./sounds/sword.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playMenuMoveSound()
{
    PlaySound(TEXT("./sounds/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void playMenuEnterSound()
{
    PlaySound(TEXT("./sounds/enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void showCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setConsoleSize()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT windowSize = {0, 0, 176, 45};
    COORD bufferSize = {177, 46};
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void printMenuDecorations()
{
    setColor(6);
    for (int x = 0; x < 177 - 0; x++)
    {
        gotoxy(x, 0);
        if (x % 3 == 0)
        {
            cout << "▄";
        }
        else if (x % 5 == 0)
        {
            cout << "▀";
        }
        else
        {
            cout << "─";
        }
        gotoxy(x, 45);
        if (x % 3 == 0)
        {
            cout << "▄";
        }
        else if (x % 5 == 0)
        {
            cout << "▀";
        }
        else
        {
            cout << "─";
        }
    }

    for (int y = 0; y < 46; y++)
    {
        gotoxy(0, y);
        cout << "█";
        gotoxy(176, y);
        cout << "█";
    }

    for (int x = 2; x < 177 - 2; x++)
    {
        gotoxy(x, 1);
        cout << "▀";

        gotoxy(x, 45 - 1);
        cout << "▄";
    }

    for (int y = 1; y < 46 - 1; y++)
    {
        gotoxy(2, y);
        cout << "█";
        gotoxy(176 - 2, y);
        cout << "█";
    }
}

void initializeJinMoves(string jinModel[], string jinPunch1[], string jinPunch2[], string jinKick[], string jinHurt[])
{
    jinModel[0] = "      \\\\\\            ";
    jinModel[1] = "       \\\\\\\\          ";
    jinModel[2] = "        [@]          ";
    jinModel[3] = "     __/   \\__       ";
    jinModel[4] = "  __/         \\  /88/";
    jinModel[5] = " / /88/__/\\___/\\/  / ";
    jinModel[6] = "| /  \\___/\\__/ /  /  ";
    jinModel[7] = "|/  / \\__ __/\\/__/   ";
    jinModel[8] = "|__/  |\\___|         ";
    jinModel[9] = "      / / \\ \\        ";
    jinModel[10] = "     / /   \\ \\       ";
    jinModel[11] = "    / /     \\ \\      ";
    jinModel[12] = "    / |     | |      ";
    jinModel[13] = "    / |     | |      ";
    jinModel[14] = "    / |     | |      ";
    jinModel[15] = "    / |     | |      ";
    jinModel[16] = "    888\\    888\\     ";

    jinPunch1[0] = "      \\\\\\            ";
    jinPunch1[1] = "       \\\\\\\\          ";
    jinPunch1[2] = "        [@]          ";
    jinPunch1[3] = "     __/   \\____     ";
    jinPunch1[4] = "  __/           \\_________";
    jinPunch1[5] = " / /88/__/\\___/__________8";
    jinPunch1[6] = "| /  \\___/\\__/       ";
    jinPunch1[7] = "|/  / \\__ __/        ";
    jinPunch1[8] = "|__/  |\\___|         ";
    jinPunch1[9] = "      / / \\ \\        ";
    jinPunch1[10] = "     / /   \\ \\       ";
    jinPunch1[11] = "    / /     \\ \\      ";
    jinPunch1[12] = "    / |     | |      ";
    jinPunch1[13] = "    / |     | |      ";
    jinPunch1[14] = "    / |     | |      ";
    jinPunch1[15] = "    / |     | |      ";
    jinPunch1[16] = "    888\\    888\\     ";

    jinPunch2[0] = "      \\\\\\            ";
    jinPunch2[1] = "       \\\\\\\\          ";
    jinPunch2[2] = "        [@]          ";
    jinPunch2[3] = "     __/   \\__       ";
    jinPunch2[4] = "    /         \\_____________";
    jinPunch2[5] = "    \\  ___\\_\\______________8";
    jinPunch2[6] = "     \\ __/\\__/ /  /  ";
    jinPunch2[7] = "      \\__ __/\\/__/   ";
    jinPunch2[8] = "      |\\___|         ";
    jinPunch2[9] = "      / / \\ \\        ";
    jinPunch2[10] = "     / /   \\ \\       ";
    jinPunch2[11] = "    / /     \\ \\      ";
    jinPunch2[12] = "    / |     | |      ";
    jinPunch2[13] = "    / |     | |      ";
    jinPunch2[14] = "    / |     | |      ";
    jinPunch2[15] = "    / |     | |      ";
    jinPunch2[16] = "    888\\    888\\     ";

    jinKick[0] = "      \\\\\\            ";
    jinKick[1] = "       \\\\\\\\          ";
    jinKick[2] = "        [@]          ";
    jinKick[3] = "     __/   \\__       ";
    jinKick[4] = "  __/         \\  /88/";
    jinKick[5] = " / /88/__/\\___/\\/  / ";
    jinKick[6] = "| /  \\___/\\__/ /  /  ";
    jinKick[7] = "|/  / \\__ __/\\/__/         ||";
    jinKick[8] = "|__/  |\\___|_______________||";
    jinKick[9] = "      / /_______)__________88";
    jinKick[10] = "     / /             ";
    jinKick[11] = "    / /              ";
    jinKick[12] = "    / |              ";
    jinKick[13] = "    / |              ";
    jinKick[14] = "    / |              ";
    jinKick[15] = "    / |              ";
    jinKick[16] = "    888\\             ";

    jinHurt[0] = "      \\\\\\            ";
    jinHurt[1] = "       \\\\\\\\          ";
    jinHurt[2] = "        [X]          ";
    jinHurt[3] = "      __/  \\__       ";
    jinHurt[4] = "   __/        \\  /88/";
    jinHurt[5] = "  / /88/__/\\___/\\/  / ";
    jinHurt[6] = " | /  \\___/\\__/ /  /  ";
    jinHurt[7] = " |/  / \\__ __/\\/__/   ";
    jinHurt[8] = " |__/  |\\___|         ";
    jinHurt[9] = "       / / \\ \\        ";
    jinHurt[10] = "      / /   \\ \\       ";
    jinHurt[11] = "     / /     \\ \\      ";
    jinHurt[12] = "     / |     | |      ";
    jinHurt[13] = "     / |     | |      ";
    jinHurt[14] = "     / |     | |      ";
    jinHurt[15] = "     / |     | |      ";
    jinHurt[16] = "     888\\    888\\     ";
}

void initializeYoshimitsuMoves(string yoshiModel[], string yoshiPunch1[], string yoshiPunch2[], string yoshiKick[], string yoshiHurt[])
{
    yoshiModel[0] = "                   | ";
    yoshiModel[1] = "      ____         | ";
    yoshiModel[2] = "       \\  \\        | ";
    yoshiModel[3] = "     __/   |__     | ";
    yoshiModel[4] = "  __/         \\    | ";
    yoshiModel[5] = " / /77/__/\\___/\\ 7[+]";
    yoshiModel[6] = "| /  \\___/\\__/ /  /| ";
    yoshiModel[7] = "|/  / \\__ __/\\/__/   ";
    yoshiModel[8] = "|__/  |\\___|         ";
    yoshiModel[9] = "      / / \\ \\        ";
    yoshiModel[10] = "     / /   \\ \\       ";
    yoshiModel[11] = "    / /     \\ \\      ";
    yoshiModel[12] = "    \\ |     | |      ";
    yoshiModel[13] = "    / |     | |      ";
    yoshiModel[14] = "    \\ |     | |      ";
    yoshiModel[15] = "    / |     | |      ";
    yoshiModel[16] = "    877\\    877\\     ";

    yoshiPunch1[0] = "                     ";
    yoshiPunch1[1] = "      ____           ";
    yoshiPunch1[2] = "       \\  \\          ";
    yoshiPunch1[3] = "     __/   |___      ";
    yoshiPunch1[4] = "  __/          \\     ";
    yoshiPunch1[5] = " / /77/__/\\___/ \\  | ";
    yoshiPunch1[6] = "| /  \\___/\\__/__7/=+============>";
    yoshiPunch1[7] = "|/  / \\__ __/      |  ";
    yoshiPunch1[8] = "|__/  |\\___|         ";
    yoshiPunch1[9] = "      / / \\ \\        ";
    yoshiPunch1[10] = "     / /   \\ \\       ";
    yoshiPunch1[11] = "    / /     \\ \\      ";
    yoshiPunch1[12] = "    \\ |     | |      ";
    yoshiPunch1[13] = "    / |     | |      ";
    yoshiPunch1[14] = "    \\ |     | |      ";
    yoshiPunch1[15] = "    / |     | |      ";
    yoshiPunch1[16] = "    877\\    877\\     ";

    yoshiPunch2[0] = "                   | ";
    yoshiPunch2[1] = "      ____         | ";
    yoshiPunch2[2] = "       \\  \\        | ";
    yoshiPunch2[3] = "     __/   |__     | ";
    yoshiPunch2[4] = "    /         \\____|________";
    yoshiPunch2[5] = "    \\  ___\\_\\______________7";
    yoshiPunch2[6] = "     \\ __/\\__/ /  /  ";
    yoshiPunch2[7] = "      \\__ __/\\/__/   ";
    yoshiPunch2[8] = "      |\\___|         ";
    yoshiPunch2[9] = "      / / \\ \\        ";
    yoshiPunch2[10] = "     / /   \\ \\       ";
    yoshiPunch2[11] = "    / /     \\ \\      ";
    yoshiPunch2[12] = "    \\ |     | |      ";
    yoshiPunch2[13] = "    / |     | |      ";
    yoshiPunch2[14] = "    \\ |     | |      ";
    yoshiPunch2[15] = "    / |     | |      ";
    yoshiPunch2[16] = "    877\\    877\\     ";

    yoshiKick[0] = "                   | ";
    yoshiKick[1] = "      ____         | ";
    yoshiKick[2] = "       \\  \\        | ";
    yoshiKick[3] = "     __/   |__     | ";
    yoshiKick[4] = "  __/         \\    | ";
    yoshiKick[5] = " / /77/__/\\___/\\ 7[+]";
    yoshiKick[6] = "| /  \\___/\\__/ /  /| ";
    yoshiKick[7] = "|/  / \\__ __/\\/__/         /7";
    yoshiKick[8] = "|__/  |\\___|_______________|7";
    yoshiKick[9] = "      / /_______)__________77";
    yoshiKick[10] = "     / /             ";
    yoshiKick[11] = "    / /              ";
    yoshiKick[12] = "    \\ |              ";
    yoshiKick[13] = "    / |              ";
    yoshiKick[14] = "    \\ |              ";
    yoshiKick[15] = "    / |              ";
    yoshiKick[16] = "    877\\             ";

    yoshiHurt[0] = "                   | ";
    yoshiHurt[1] = "      ____         | ";
    yoshiHurt[2] = "       \\  \\        | ";
    yoshiHurt[3] = "      __/  |__     | ";
    yoshiHurt[4] = "   __/        \\    | ";
    yoshiHurt[5] = "  / /77/__/\\___/\\ 7[+]";
    yoshiHurt[6] = " | /  \\___/\\__/ /  /| ";
    yoshiHurt[7] = " |/  / \\__ __/\\/__/   ";
    yoshiHurt[8] = " |__/  |\\___|         ";
    yoshiHurt[9] = "       / / \\ \\        ";
    yoshiHurt[10] = "      / /   \\ \\       ";
    yoshiHurt[11] = "     / /     \\ \\      ";
    yoshiHurt[12] = "     \\ |     | |      ";
    yoshiHurt[13] = "     / |     | |      ";
    yoshiHurt[14] = "     \\ |     | |      ";
    yoshiHurt[15] = "     / |     | |      ";
    yoshiHurt[16] = "     877\\    877\\     ";
}

void initializePaulMoves(string paulModel[], string paulPunch1[], string paulPunch2[], string paulKick[], string paulHurt[])
{
    paulModel[0] = "        |||          ";
    paulModel[1] = "        |||          ";
    paulModel[2] = "        [&]          ";
    paulModel[3] = "     __/   \\__       ";
    paulModel[4] = "  __/         \\  /88/";
    paulModel[5] = " / /88/__/\\___/\\/  / ";
    paulModel[6] = "| /  \\___/\\__/ /  /  ";
    paulModel[7] = "|/  / \\__ __/\\/__/   ";
    paulModel[8] = "|__/  |\\___|         ";
    paulModel[9] = "      / / \\ \\        ";
    paulModel[10] = "     / /   \\ \\       ";
    paulModel[11] = "    / /     \\ \\      ";
    paulModel[12] = "    / |     | |      ";
    paulModel[13] = "    / |     | |      ";
    paulModel[14] = "    / |     | |      ";
    paulModel[15] = "    / |     | |      ";
    paulModel[16] = "    888\\    888\\     ";

    paulPunch1[0] = "        |||          ";
    paulPunch1[1] = "        |||          ";
    paulPunch1[2] = "        [&]          ";
    paulPunch1[3] = "     __/   \\____     ";
    paulPunch1[4] = "  __/           \\_________";
    paulPunch1[5] = " / /88/__/\\___/__________8";
    paulPunch1[6] = "| /  \\___/\\__/       ";
    paulPunch1[7] = "|/  / \\__ __/        ";
    paulPunch1[8] = "|__/  |\\___|         ";
    paulPunch1[9] = "      / / \\ \\        ";
    paulPunch1[10] = "     / /   \\ \\       ";
    paulPunch1[11] = "    / /     \\ \\      ";
    paulPunch1[12] = "    / |     | |      ";
    paulPunch1[13] = "    / |     | |      ";
    paulPunch1[14] = "    / |     | |      ";
    paulPunch1[15] = "    / |     | |      ";
    paulPunch1[16] = "    888\\    888\\     ";

    paulPunch2[0] = "        |||          ";
    paulPunch2[1] = "        |||          ";
    paulPunch2[2] = "        [&]          ";
    paulPunch2[3] = "     __/   \\__       ";
    paulPunch2[4] = "    /         \\_____________";
    paulPunch2[5] = "    \\  ___\\_\\______________8";
    paulPunch2[6] = "     \\ __/\\__/ /  /  ";
    paulPunch2[7] = "      \\__ __/\\/__/   ";
    paulPunch2[8] = "      |\\___|         ";
    paulPunch2[9] = "      / / \\ \\        ";
    paulPunch2[10] = "     / /   \\ \\       ";
    paulPunch2[11] = "    / /     \\ \\      ";
    paulPunch2[12] = "    / |     | |      ";
    paulPunch2[13] = "    / |     | |      ";
    paulPunch2[14] = "    / |     | |      ";
    paulPunch2[15] = "    / |     | |      ";
    paulPunch2[16] = "    888\\    888\\     ";

    paulKick[0] = "        |||          ";
    paulKick[1] = "        |||          ";
    paulKick[2] = "        [&]          ";
    paulKick[3] = "     __/   \\__       ";
    paulKick[4] = "  __/         \\  /88/";
    paulKick[5] = " / /88/__/\\___/\\/  / ";
    paulKick[6] = "| /  \\___/\\__/ /  /  ";
    paulKick[7] = "|/  / \\__ __/\\/__/         ||";
    paulKick[8] = "|__/  |\\___|_______________||";
    paulKick[9] = "      / /_______)__________88";
    paulKick[10] = "     / /             ";
    paulKick[11] = "    / /              ";
    paulKick[12] = "    / |              ";
    paulKick[13] = "    / |              ";
    paulKick[14] = "    / |              ";
    paulKick[15] = "    / |              ";
    paulKick[16] = "    888\\             ";

    paulHurt[0] = "        |||          ";
    paulHurt[1] = "        |||          ";
    paulHurt[2] = "        [X]          ";
    paulHurt[3] = "      __/  \\__       ";
    paulHurt[4] = "   __/        \\  /88/";
    paulHurt[5] = "  / /88/__/\\___/\\/  / ";
    paulHurt[6] = " | /  \\___/\\__/ /  /  ";
    paulHurt[7] = " |/  / \\__ __/\\/__/   ";
    paulHurt[8] = " |__/  |\\___|         ";
    paulHurt[9] = "       / / \\ \\        ";
    paulHurt[10] = "      / /   \\ \\       ";
    paulHurt[11] = "     / /     \\ \\      ";
    paulHurt[12] = "     / |     | |      ";
    paulHurt[13] = "     / |     | |      ";
    paulHurt[14] = "     / |     | |      ";
    paulHurt[15] = "     / |     | |      ";
    paulHurt[16] = "     888\\    888\\     ";
}

void printArena(int &arenaLeft, int &arenaRight, int &arenaTop, int &arenaBottom)
{
    setColor(6);

    gotoxy(arenaLeft, arenaTop);
    cout << "+";
    for (int i = arenaLeft + 1; i < arenaRight / 2 - 12; i++)
    {
        cout << "═";
    }
    gotoxy((arenaRight / 2 - 12) + 26, arenaTop);
    for (int i = arenaRight / 2 + 14; i < arenaRight; i++)
    {
        cout << "═";
    }
    cout << "+";

    for (int i = arenaTop + 1; i < arenaBottom; i++)
    {
        gotoxy(arenaLeft, i);
        cout << "║";
        gotoxy(arenaRight, i);
        cout << "║";
    }

    gotoxy(arenaLeft, arenaBottom);
    cout << "+";
    for (int i = arenaLeft + 1; i < arenaRight; i++)
    {
        cout << "═";
    }
    cout << "+";

    setColor(8);
    for (int i = arenaLeft + 1; i < arenaRight; i++)
    {
        gotoxy(i, arenaBottom - 1);
        cout << "_";
    }
}

void erasePlayer(int x, int y)
{
    for (int i = 0; i < 17; i++)
    {
        gotoxy(x - 5, y + i);
        cout << "                                                  ";
    }
}

void printSprite(string sprite[], int x, int y, bool reversed)
{
    for (int i = 0; i < 17; i++)
    {
        gotoxy(x, y + i);
        string row = sprite[i];
        if (reversed)
        {
            int j = (int)row.length() - 1;
            while (j >= 0)
            {
                char c = row[j];
                if (c == '/')
                {
                    c = '\\';
                }
                else if (c == '\\')
                {
                    c = '/';
                }
                else if (c == '[')
                {
                    c = ']';
                }
                else if (c == ']')
                {
                    c = '[';
                }
                else if (c == '(')
                {
                    c = ')';
                }
                else if (c == ')')
                {
                    c = '(';
                }
                else if (c == '<')
                {
                    c = '>';
                }
                else if (c == '>')
                {
                    c = '<';
                }
                cout << c;
                j = j - 1;
            }
        }
        else
        {
            cout << row;
        }
    }
}

void printHitEffect(int x, int y, int damage)
{
    setColor(7);
    gotoxy(x + 2, y + 2);
    cout << "\\\\\\|||///";
    gotoxy(x + 2, y + 3);
    cout << "==*WwW*==";
    gotoxy(x + 2, y + 4);
    cout << "///|||\\\\\\";
}

void eraseHitEffect(int x, int y)
{
    gotoxy(x + 5, y - 2);
    cout << "            ";
    gotoxy(x + 7, y - 1);
    cout << "   ";
    gotoxy(x + 2, y + 2);
    cout << "         ";
    gotoxy(x + 2, y + 3);
    cout << "         ";
    gotoxy(x + 2, y + 4);
    cout << "         ";
}

void showDamageEffect(int hitX, int hitY, int damage, string hurtSprite[], bool reversed)
{
    setColor(15);
    printSprite(hurtSprite, hitX, hitY, reversed);
    printHitEffect(hitX, hitY, damage);

    Sleep(10);

    eraseHitEffect(hitX, hitY);

    setColor(15);
    printSprite(hurtSprite, hitX, hitY, reversed);

    Sleep(10);

    setColor(15);
    printSprite(hurtSprite, hitX, hitY, reversed);

    Sleep(10);
}

void refreshCharacters(int &p1X, int &p1Y, int &p2X, int &p2Y,
                       string p1Model[], string p2Model[])
{
    setColor(11);
    printSprite(p1Model, p1X, p1Y, false);
    setColor(4);
    printSprite(p2Model, p2X, p2Y, true);
}

void timer0(int x, int y)
{
    gotoxy(x, y);
    cout << "    █████   ";
    gotoxy(x, y + 1);
    cout << "  ███░░░███ ";
    gotoxy(x, y + 2);
    cout << " ███   ░░███";
    gotoxy(x, y + 3);
    cout << "░███    ░███";
    gotoxy(x, y + 4);
    cout << "░███    ░███";
    gotoxy(x, y + 5);
    cout << "░░███   ███ ";
    gotoxy(x, y + 6);
    cout << " ░░░█████░  ";
    gotoxy(x, y + 7);
    cout << "   ░░░░░░   ";
}

void timer1(int x, int y)
{
    gotoxy(x, y);
    cout << "      ████  ";
    gotoxy(x, y + 1);
    cout << "      ░░███ ";
    gotoxy(x, y + 2);
    cout << "       ░███ ";
    gotoxy(x, y + 3);
    cout << "       ░███ ";
    gotoxy(x, y + 4);
    cout << "       ░███ ";
    gotoxy(x, y + 5);
    cout << "       ░███ ";
    gotoxy(x, y + 6);
    cout << "       █████";
    gotoxy(x, y + 7);
    cout << "      ░░░░░ ";
}

void timer2(int x, int y)
{
    gotoxy(x, y);
    cout << "   ████████ ";
    gotoxy(x, y + 1);
    cout << "  ███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░░░    ░███";
    gotoxy(x, y + 3);
    cout << "    ███████ ";
    gotoxy(x, y + 4);
    cout << "   ███░░░░  ";
    gotoxy(x, y + 5);
    cout << "  ███      █";
    gotoxy(x, y + 6);
    cout << " ░██████████";
    gotoxy(x, y + 7);
    cout << " ░░░░░░░░░░ ";
}

void timer3(int x, int y)
{
    gotoxy(x, y);
    cout << "   ████████ ";
    gotoxy(x, y + 1);
    cout << "  ███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░░░    ░███";
    gotoxy(x, y + 3);
    cout << "    ██████░ ";
    gotoxy(x, y + 4);
    cout << "   ░░░░░░███";
    gotoxy(x, y + 5);
    cout << "  ███   ░███";
    gotoxy(x, y + 6);
    cout << " ░░████████ ";
    gotoxy(x, y + 7);
    cout << "  ░░░░░░░░  ";
}

void timer4(int x, int y)
{
    gotoxy(x, y);
    cout << "  █████ ████";
    gotoxy(x, y + 1);
    cout << " ░░███ ░░███";
    gotoxy(x, y + 2);
    cout << "  ░███  ░███";
    gotoxy(x, y + 3);
    cout << "  ░█████████";
    gotoxy(x, y + 4);
    cout << "  ░░░░░░░███";
    gotoxy(x, y + 5);
    cout << "        ░███";
    gotoxy(x, y + 6);
    cout << "        ████";
    gotoxy(x, y + 7);
    cout << "       ░░░░ ";
}

void timer5(int x, int y)
{
    gotoxy(x, y);
    cout << "  ██████████";
    gotoxy(x, y + 1);
    cout << " ░███░░░░░░█";
    gotoxy(x, y + 2);
    cout << " ░███     ░ ";
    gotoxy(x, y + 3);
    cout << " ░█████████ ";
    gotoxy(x, y + 4);
    cout << " ░░░░░░░░███";
    gotoxy(x, y + 5);
    cout << "  ███   ░███";
    gotoxy(x, y + 6);
    cout << " ░░████████ ";
    gotoxy(x, y + 7);
    cout << "  ░░░░░░░░  ";
}

void timer6(int x, int y)
{
    gotoxy(x, y);
    cout << "   ████████ ";
    gotoxy(x, y + 1);
    cout << "  ███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░███   ░░░ ";
    gotoxy(x, y + 3);
    cout << " ░█████████ ";
    gotoxy(x, y + 4);
    cout << " ░███░░░░███";
    gotoxy(x, y + 5);
    cout << " ░███   ░███";
    gotoxy(x, y + 6);
    cout << " ░░████████ ";
    gotoxy(x, y + 7);
    cout << "  ░░░░░░░░  ";
}

void timer7(int x, int y)
{
    gotoxy(x, y);
    cout << "  ██████████";
    gotoxy(x, y + 1);
    cout << " ░███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░░░    ███ ";
    gotoxy(x, y + 3);
    cout << "       ███  ";
    gotoxy(x, y + 4);
    cout << "      ███   ";
    gotoxy(x, y + 5);
    cout << "     ███    ";
    gotoxy(x, y + 6);
    cout << "    ███     ";
    gotoxy(x, y + 7);
    cout << "   ░░░      ";
}

void timer8(int x, int y)
{
    gotoxy(x, y);
    cout << "   ████████ ";
    gotoxy(x, y + 1);
    cout << "  ███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░███   ░███";
    gotoxy(x, y + 3);
    cout << " ░░████████ ";
    gotoxy(x, y + 4);
    cout << "  ███░░░░███";
    gotoxy(x, y + 5);
    cout << " ░███   ░███";
    gotoxy(x, y + 6);
    cout << " ░░████████ ";
    gotoxy(x, y + 7);
    cout << "  ░░░░░░░░  ";
}

void timer9(int x, int y)
{
    gotoxy(x, y);
    cout << "   ████████ ";
    gotoxy(x, y + 1);
    cout << "  ███░░░░███";
    gotoxy(x, y + 2);
    cout << " ░███   ░███";
    gotoxy(x, y + 3);
    cout << " ░░█████████";
    gotoxy(x, y + 4);
    cout << "  ░░░░░░░███";
    gotoxy(x, y + 5);
    cout << "  ███   ░███";
    gotoxy(x, y + 6);
    cout << " ░░████████ ";
    gotoxy(x, y + 7);
    cout << "  ░░░░░░░░  ";
}

void displayTimerDigit(int digit, int x, int y)
{
    if (digit == 0)
    {
        timer0(x, y);
    }
    else if (digit == 1)
    {
        timer1(x, y);
    }
    else if (digit == 2)
    {
        timer2(x, y);
    }
    else if (digit == 3)
    {
        timer3(x, y);
    }
    else if (digit == 4)
    {
        timer4(x, y);
    }
    else if (digit == 5)
    {
        timer5(x, y);
    }
    else if (digit == 6)
    {
        timer6(x, y);
    }
    else if (digit == 7)
    {
        timer7(x, y);
    }
    else if (digit == 8)
    {
        timer8(x, y);
    }
    else if (digit == 9)
    {
        timer9(x, y);
    }
}

void displayGameTimer(int timeRemaining)
{
    setColor(6);

    for (int i = 0; i < 8; i++)
    {
        gotoxy(75, 1 + i);
        cout << "                         ";
    }

    int tens = timeRemaining / 10;
    int ones = timeRemaining % 10;

    displayTimerDigit(tens, 75, 1);
    displayTimerDigit(ones, 87, 1);

    setColor(7);
}

void updateHealthUI(int &p1Health, int &p2Health, int &p1Rounds, int &p2Rounds, int &currentRound, int &timeRemaining,
                    string &p1Name, string &p2Name)
{
    gotoxy(5, 2);
    setColor(11);
    cout << p1Name << " [WASD/E/Q/Z] HP: " << p1Health << "   ";
    gotoxy(5, 3);
    setColor(8);
    cout << "[";
    setColor(6);
    for (int i = 0; i < 40; i++)
    {
        int threshold = p1Health * 40;
        threshold = threshold / 100;
        if (i < threshold)
        {
            cout << "█";
        }
        else
        {
            cout << " ";
        }
    }
    setColor(8);
    cout << "]";

    gotoxy(83, 12);
    setColor(96);
    cout << " ROUND " << currentRound << " ";

    displayGameTimer(timeRemaining);

    gotoxy(75, 10);
    setColor(176);
    cout << " P1 Wins: " << p1Rounds << " ";
    setColor(7);
    cout << " ";
    setColor(64);
    cout << " P2 Wins: " << p2Rounds << " ";

    gotoxy(130, 2);
    setColor(4);
    cout << p2Name << " [ARROWS/7/8/4] HP: " << p2Health << "   ";
    gotoxy(130, 3);
    setColor(8);
    cout << "[";
    setColor(6);
    for (int i = 0; i < 40; i++)
    {
        int threshold = p2Health * 40;
        threshold = threshold / 100;
        if (i < threshold)
        {
            cout << "█";
        }
        else
        {
            cout << " ";
        }
    }
    setColor(8);
    cout << "]";
    setColor(7);
}

void executeAttack(int playerNum, int attackType, int &p1X, int &p1Y, int &p2X, int &p2Y,
                   int &p1Health, int &p2Health, int &p1Rounds, int &p2Rounds, int &currentRound, int &timeRemaining,
                   string p1Model[], string p1Punch1[], string p1Punch2[], string p1Kick[], string p1Hurt[],
                   string p2Model[], string p2Punch1[], string p2Punch2[], string p2Kick[], string p2Hurt[],
                   string &p1Name, string &p2Name, int p1Char, int p2Char)
{
    int damage = 0;
    int reach = 26;

    if (attackType == 1)
    {
        damage = 5;
        if (playerNum == 1 && p1Char == 1)
        {
            playSwordSound();
        }
        else if (playerNum == 2 && p2Char == 1)
        {
            playSwordSound();
        }
        else
        {
            playPunch1Sound();
        }
    }
    else if (attackType == 2)
    {
        damage = 7;
        playPunch2Sound();
    }
    else
    {
        damage = 10;
        reach = 30;
        playKickSound();
    }

    erasePlayer(p1X, p1Y);
    erasePlayer(p2X, p2Y);

    if (playerNum == 1)
    {
        setColor(11);
        if (attackType == 1)
        {
            printSprite(p1Punch1, p1X, p1Y, false);
        }
        else if (attackType == 2)
        {
            printSprite(p1Punch2, p1X, p1Y, false);
        }
        else
        {
            printSprite(p1Kick, p1X, p1Y, false);
        }
        setColor(4);
        printSprite(p2Model, p2X, p2Y, true);
        Sleep(10);

        int distance = p1X - p2X;
        if (distance < 0)
        {
            distance = distance * -1;
        }
        if (distance < reach)
        {
            p2Health = p2Health - damage;
            if (p2Health < 0)
            {
                p2Health = 0;
            }

            showDamageEffect(p2X, p2Y, damage, p2Hurt, true);
        }
    }
    else
    {
        setColor(4);
        if (attackType == 1)
        {
            printSprite(p2Punch1, p2X, p2Y, true);
        }
        else if (attackType == 2)
        {
            printSprite(p2Punch2, p2X, p2Y, true);
        }
        else
        {
            printSprite(p2Kick, p2X, p2Y, true);
        }
        setColor(11);
        printSprite(p1Model, p1X, p1Y, false);
        Sleep(10);

        int distance = p1X - p2X;
        if (distance < 0)
        {
            distance = distance * -1;
        }
        if (distance < reach)
        {
            p1Health = p1Health - damage;
            if (p1Health < 0)
            {
                p1Health = 0;
            }

            showDamageEffect(p1X, p1Y, damage, p1Hurt, false);
        }
    }

    updateHealthUI(p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Name, p2Name);
}

string getField(string record, int field)
{
    int commaCount = 1;
    string item = "";
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commaCount = commaCount + 1;
        }
        else if (commaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}

string getSaveNameInput()
{
    system("cls");
    setColor(96);
    gotoxy(70, 15);
    cout << " Enter Name For Your Saved Game ";

    setColor(7);
    gotoxy(70, 17);
    cout << "Save Name: ";

    showCursor();

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    string saveName;
    setColor(6);
    gotoxy(70, 18);
    cout << "╔══════════════════════════════╗";
    gotoxy(70, 19);
    cout << "║                              ║";
    gotoxy(70, 20);
    cout << "╚══════════════════════════════╝";
    gotoxy(72, 19); 
    getline(cin, saveName);
    setColor(7);

    if (saveName.empty() || saveName == " ")
    {
        saveName = "Untitled";
    }

    for (int i = 0; i < saveName.length(); i++)
    {
        if (saveName[i] == ',' || saveName[i] == '\n' || saveName[i] == '\r')
        {
            saveName[i] = '_';
        }
    }

    hideCursor();
    return saveName;
}

void saveGame(int &p1X, int &p1Y, int &p2X, int &p2Y, int &p1Health, int &p2Health,
              int &p1Rounds, int &p2Rounds, int &currentRound, int &timeRemaining,
              int &p1Char, int &p2Char)
{
    string saveName = getSaveNameInput();

    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);

    char timeStr[100];
    sprintf(timeStr, "%02d/%02d/%04d %02d:%02d",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min);

    string timestamp = timeStr;

    fstream file;
    file.open("tekken_saves.txt", ios::out | ios::app);

    if (file)
    {
        file << saveName << "," << timestamp << "," << p1X << "," << p1Y << "," << p2X << "," << p2Y << ","
             << p1Health << "," << p2Health << "," << p1Rounds << "," << p2Rounds << "," << currentRound << ","
             << timeRemaining << "," << p1Char << "," << p2Char << endl;
        file.close();
    }
}

struct SaveGame
{
    string name;
    string timestamp;
    int p1X, p1Y, p2X, p2Y;
    int p1Health, p2Health;
    int p1Rounds, p2Rounds;
    int currentRound, timeRemaining;
    int p1Char, p2Char;
};

int loadAllSaves(SaveGame saves[], int maxSaves)
{
    int saveCount = 0;
    string record;
    fstream file;
    file.open("tekken_saves.txt", ios::in);

    if (!file)
    {
        return 0;
    }

    while (getline(file, record) && saveCount < maxSaves)
    {
        if (record.length() > 0)
        {
            saves[saveCount].name = getField(record, 1);
            saves[saveCount].timestamp = getField(record, 2);
            saves[saveCount].p1X = stoi(getField(record, 3));
            saves[saveCount].p1Y = stoi(getField(record, 4));
            saves[saveCount].p2X = stoi(getField(record, 5));
            saves[saveCount].p2Y = stoi(getField(record, 6));
            saves[saveCount].p1Health = stoi(getField(record, 7));
            saves[saveCount].p2Health = stoi(getField(record, 8));
            saves[saveCount].p1Rounds = stoi(getField(record, 9));
            saves[saveCount].p2Rounds = stoi(getField(record, 10));
            saves[saveCount].currentRound = stoi(getField(record, 11));
            saves[saveCount].timeRemaining = stoi(getField(record, 12));
            saves[saveCount].p1Char = stoi(getField(record, 13));
            saves[saveCount].p2Char = stoi(getField(record, 14));

            saveCount++;
        }
    }
    file.close();
    return saveCount;
}

int showLoadGameMenu(int &p1X, int &p1Y, int &p2X, int &p2Y, int &p1Health, int &p2Health,
                     int &p1Rounds, int &p2Rounds, int &currentRound, int &timeRemaining,
                     int &p1Char, int &p2Char)
{
    SaveGame saves[50];
    int totalSaves = loadAllSaves(saves, 50);

    if (totalSaves == 0)
    {
        system("cls");
        setColor(4);
        gotoxy(75, 18);
        cout << "No saved games found!";
        setColor(7);
        gotoxy(70, 20);
        cout << "Press any key to return to main menu...";

        while (true)
        {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000 ||
                GetAsyncKeyState(VK_SPACE) & 0x8000)
            {
                while (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000 ||
                       GetAsyncKeyState(VK_SPACE) & 0x8000)
                {
                }
                return 0;
            }
        }
    }

    int selectedSave = 0;

    while (true)
    {
        system("cls");
        setColor(6);
        gotoxy(20, 7);
        cout << "SELECT SAVED GAME";

        setColor(8);
        gotoxy(20, 8);
        cout << "Use UP/DOWN to select, ENTER to load, ESC to cancel";

        for (int i = 0; i < totalSaves && i < 10; i++)
        {
            gotoxy(20, 12 + i * 3);
            if (i == selectedSave)
            {
                setColor(96);
                cout << " >> ";
            }
            else
            {
                setColor(7);
                cout << "    ";
            }

            cout << "Game: " << saves[i].name << " ";

            gotoxy(70, 12 + i * 3);
            setColor(14);
            cout << "Saved: " << saves[i].timestamp;

            gotoxy(20, 13 + i * 3);
            setColor(11);
            cout << "Round " << saves[i].currentRound << " | P1: " << saves[i].p1Health << "HP | P2: " << saves[i].p2Health << "HP | Time: " << saves[i].timeRemaining << "s";
        }

        bool keyPressed = false;
        while (!keyPressed)
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                selectedSave--;
                if (selectedSave < 0)
                    selectedSave = totalSaves - 1;
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_UP) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                selectedSave++;
                if (selectedSave >= totalSaves)
                    selectedSave = 0;
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                SaveGame selected = saves[selectedSave];
                p1X = selected.p1X;
                p1Y = selected.p1Y;
                p2X = selected.p2X;
                p2Y = selected.p2Y;
                p1Health = selected.p1Health;
                p2Health = selected.p2Health;
                p1Rounds = selected.p1Rounds;
                p2Rounds = selected.p2Rounds;
                currentRound = selected.currentRound;
                timeRemaining = selected.timeRemaining;
                p1Char = selected.p1Char;
                p2Char = selected.p2Char;

                playMenuEnterSound();
                while (GetAsyncKeyState(VK_RETURN) & 0x8000)
                {
                }
                return 1;
            }
            else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                {
                }
                return 0;
            }
        }
    }
}

void printMenuOption(int x, int y, string text, bool selected)
{
    gotoxy(x, y);
    if (selected)
    {
        setColor(96);
        cout << ">> ";
        cout << text;
        cout << " <<";
        setColor(7);
    }
    else
    {
        setColor(8);
        cout << "   " << text << "   ";
    }
}

void printCharacterOption(int x, int y, string name, bool selected, int color)
{
    gotoxy(x, y);
    if (selected)
    {
        setColor(color);
        cout << ">>>  " << name << "  <<<";
    }
    else
    {
        setColor(8);
        cout << "     " << name << "     ";
    }
}

int showPauseMenu()
{
    system("cls");

    int selectedOption = 0;
    int totalOptions = 3;

    while (true)
    {
        setColor(6);
        gotoxy(71, 9);
        cout << "             GAME PAUSED               ";
        gotoxy(71, 10);
        cout << "---------------------------------------";

        printMenuOption(75, 14, "     Continue Game     ", selectedOption == 0);
        printMenuOption(75, 16, "       Save Game       ", selectedOption == 1);
        printMenuOption(75, 18, "  Return to Main Menu  ", selectedOption == 2);

        bool keyPressed = false;
        while (keyPressed == false)
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                selectedOption = selectedOption - 1;
                if (selectedOption < 0)
                {
                    selectedOption = totalOptions - 1;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_UP) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                selectedOption = selectedOption + 1;
                if (selectedOption >= totalOptions)
                {
                    selectedOption = 0;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                playMenuEnterSound();
                while (GetAsyncKeyState(VK_RETURN) & 0x8000)
                {
                }
                if (selectedOption == 0)
                {
                    return 1;
                }
                else if (selectedOption == 1)
                {
                    return 2;
                }
                else
                {
                    return 3;
                }
            }
        }
    }
}

void printHeader()
{
    setColor(4);
    int x = 49, y = 10;
    gotoxy(x, y);
    cout << " ███████████ ██████████ █████   ████ █████   ████ ██████████ ██████   █████";
    gotoxy(x, y + 1);
    cout << "░█░░░███░░░█░░███░░░░░█░░███   ███░ ░░███   ███░ ░░███░░░░░█░░██████ ░░███ ";
    gotoxy(x, y + 2);
    cout << "░   ░███  ░  ░███  █ ░  ░███  ███    ░███  ███    ░███  █ ░  ░███░███ ░███ ";
    gotoxy(x, y + 3);
    cout << "    ░███     ░██████    ░███████     ░███████     ░██████    ░███░░███░███ ";
    gotoxy(x, y + 4);
    cout << "    ░███     ░███░░█    ░███░░███    ░███░░███    ░███░░█    ░███ ░░██████ ";
    gotoxy(x, y + 5);
    cout << "    ░███     ░███ ░   █ ░███ ░░███   ░███ ░░███   ░███ ░   █ ░███  ░░█████ ";
    gotoxy(x, y + 6);
    cout << "    █████    ██████████ █████ ░░████ █████ ░░████ ██████████ █████  ░░█████";
    gotoxy(x, y + 7);
    cout << "   ░░░░░    ░░░░░░░░░░ ░░░░░   ░░░░ ░░░░░   ░░░░ ░░░░░░░░░░ ░░░░░    ░░░░░ ";
    setColor(7);
}

void getCharacterName(int charIndex, string &charName)
{
    if (charIndex == 0)
    {
        charName = "JIN";
    }
    else if (charIndex == 1)
    {
        charName = "YOSHI";
    }
    else
    {
        charName = "PAUL";
    }
}

void showCharacterSelect(int &p1Char, int &p2Char)
{
    system("cls");

    string jinModel[17];
    string jinPunch1[17];
    string jinPunch2[17];
    string jinKick[17];
    string jinHurt[17];
    string yoshiModel[17];
    string yoshiPunch1[17];
    string yoshiPunch2[17];
    string yoshiKick[17];
    string yoshiHurt[17];
    string paulModel[17];
    string paulPunch1[17];
    string paulPunch2[17];
    string paulKick[17];
    string paulHurt[17];

    initializeJinMoves(jinModel, jinPunch1, jinPunch2, jinKick, jinHurt);
    initializeYoshimitsuMoves(yoshiModel, yoshiPunch1, yoshiPunch2, yoshiKick, yoshiHurt);
    initializePaulMoves(paulModel, paulPunch1, paulPunch2, paulKick, paulHurt);

    p1Char = 0;
    p2Char = 0;
    bool p1Selected = false;
    bool p2Selected = false;
    int totalCharacters = 3;

    while (p1Selected == false || p2Selected == false)
    {
        system("cls");

        setColor(11);
        gotoxy(20, 7);
        cout << "PLAYER 1 ";
        if (p1Selected)
        {
            setColor(160);
            cout << "[READY]";
        }
        else
        {
            setColor(8);
            cout << " (W/S to select, E to confirm)";
        }

        setColor(4);
        gotoxy(120, 7);
        cout << "PLAYER 2 ";
        if (p2Selected)
        {
            setColor(160);
            cout << "[READY]";
        }
        else
        {
            setColor(8);
            cout << " (UP/DOWN to select, NUMPAD7 to confirm)";
        }

        printCharacterOption(20, 10, "    JIN     ", p1Char == 0, 176);
        printCharacterOption(20, 12, " YOSHIMITSU ", p1Char == 1, 176);
        printCharacterOption(20, 14, "    PAUL    ", p1Char == 2, 176);

        printCharacterOption(120, 10, "    JIN     ", p2Char == 0, 64);
        printCharacterOption(120, 12, " YOSHIMITSU ", p2Char == 1, 64);
        printCharacterOption(120, 14, "    PAUL    ", p2Char == 2, 64);

        setColor(11);
        if (p1Char == 0)
        {
            printSprite(jinModel, 15, 18, false);
        }
        else if (p1Char == 1)
        {
            printSprite(yoshiModel, 15, 18, false);
        }
        else
        {
            printSprite(paulModel, 15, 18, false);
        }

        setColor(4);
        if (p2Char == 0)
        {
            printSprite(jinModel, 130, 18, true);
        }
        else if (p2Char == 1)
        {
            printSprite(yoshiModel, 130, 18, true);
        }
        else
        {
            printSprite(paulModel, 130, 18, true);
        }

        setColor(6);
        int x = 85 - 12, y = 25 - 12;
        gotoxy(x, y);
        cout << " █████   █████  █████████ ";
        gotoxy(x, y + 1);
        cout << "░░███   ░░███  ███░░░░░███";
        gotoxy(x, y + 2);
        cout << " ░███    ░███ ░███    ░░░ ";
        gotoxy(x, y + 3);
        cout << " ░███    ░███ ░░█████████ ";
        gotoxy(x, y + 4);
        cout << " ░░███   ███   ░░░░░░░░███";
        gotoxy(x, y + 5);
        cout << "  ░░░█████░    ███    ░███";
        gotoxy(x, y + 6);
        cout << "    ░░███     ░░█████████ ";
        gotoxy(x, y + 7);
        cout << "     ░░░       ░░░░░░░░░  ";

        bool inputReceived = false;
        while (inputReceived == false)
        {
            if (p1Selected == false)
            {
                if (GetAsyncKeyState('W') & 0x8000)
                {
                    p1Char = p1Char - 1;
                    if (p1Char < 0)
                    {
                        p1Char = totalCharacters - 1;
                    }
                    inputReceived = true;
                    playMenuMoveSound();
                    while (GetAsyncKeyState('W') & 0x8000)
                    {
                    }
                }
                if (GetAsyncKeyState('S') & 0x8000)
                {
                    p1Char = p1Char + 1;
                    if (p1Char >= totalCharacters)
                    {
                        p1Char = 0;
                    }
                    inputReceived = true;
                    playMenuMoveSound();
                    while (GetAsyncKeyState('S') & 0x8000)
                    {
                    }
                }
                if (GetAsyncKeyState('E') & 0x8000)
                {
                    p1Selected = true;
                    inputReceived = true;
                    playMenuEnterSound();
                    while (GetAsyncKeyState('E') & 0x8000)
                    {
                    }
                }
            }

            if (p2Selected == false)
            {
                if (GetAsyncKeyState(VK_UP) & 0x8000)
                {
                    p2Char = p2Char - 1;
                    if (p2Char < 0)
                    {
                        p2Char = totalCharacters - 1;
                    }
                    inputReceived = true;
                    playMenuMoveSound();
                    while (GetAsyncKeyState(VK_UP) & 0x8000)
                    {
                    }
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                    p2Char = p2Char + 1;
                    if (p2Char >= totalCharacters)
                    {
                        p2Char = 0;
                    }
                    inputReceived = true;
                    playMenuMoveSound();
                    while (GetAsyncKeyState(VK_DOWN) & 0x8000)
                    {
                    }
                }
                if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
                {
                    p2Selected = true;
                    inputReceived = true;
                    playMenuEnterSound();
                    while (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
                    {
                    }
                }
            }

            if (p1Selected && p2Selected)
            {
                inputReceived = true;
            }
        }
    }

    system("cls");
    setColor(96);
    gotoxy(81, 18);
    cout << " GET READY FOR BATTLE! ";

    string p1CharName;
    string p2CharName;

    getCharacterName(p1Char, p1CharName);
    getCharacterName(p2Char, p2CharName);

    setColor(11);
    gotoxy(70, 21);
    cout << p1CharName;

    setColor(7);
    gotoxy(90, 21);
    cout << "VS";

    setColor(4);
    gotoxy(110, 21);
    cout << p2CharName;

    time_t waitStart = time(NULL);
    while (time(NULL) - waitStart < 2)
    {
    }
}

int showMainMenu()
{
    system("cls");
    hideCursor();

    printMenuDecorations();

    int selectedOption = 0;
    int totalOptions = 3;

    while (true)
    {
        printHeader();

        printMenuOption(72, 18 + 5, "        New Game         ", selectedOption == 0);
        printMenuOption(72, 20 + 5, "     Load Saved Game     ", selectedOption == 1);
        printMenuOption(72, 22 + 5, "        Exit Game        ", selectedOption == 2);

        bool keyPressed = false;
        while (keyPressed == false)
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                selectedOption = selectedOption - 1;
                if (selectedOption < 0)
                {
                    selectedOption = totalOptions - 1;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_UP) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                selectedOption = selectedOption + 1;
                if (selectedOption >= totalOptions)
                {
                    selectedOption = 0;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                playMenuEnterSound();
                while (GetAsyncKeyState(VK_RETURN) & 0x8000)
                {
                }
                if (selectedOption == 0)
                {
                    return 1;
                }
                else if (selectedOption == 1)
                {
                    return 2;
                }
                else
                {
                    return 3;
                }
            }
        }
    }
}

void showCountdown(int &arenaLeft, int &arenaRight, int &arenaTop, int &arenaBottom)
{
    system("cls");

    setColor(4);
    displayTimerDigit(3, 81, 15);

    time_t startTime = time(NULL);
    while (time(NULL) - startTime < 1)
    {
    }

    for (int i = 0; i < 8; i++)
    {
        gotoxy(69, 15 + i);
        cout << "                              ";
    }

    setColor(4);
    displayTimerDigit(2, 81, 15);

    startTime = time(NULL);
    while (time(NULL) - startTime < 1)
    {
    }

    for (int i = 0; i < 8; i++)
    {
        gotoxy(69, 15 + i);
        cout << "                              ";
    }

    setColor(4);
    displayTimerDigit(1, 81, 15);

    startTime = time(NULL);
    while (time(NULL) - startTime < 1)
    {
    }

    for (int i = 0; i < 8; i++)
    {
        gotoxy(69, 15 + i);
        cout << "                              ";
    }
    playFightSound();

    setColor(4);
    gotoxy(59, 16);
    cout << " ███████████ █████   █████████  █████   █████ ███████████";
    gotoxy(59, 17);
    cout << "░░███░░░░░░█░░███   ███░░░░░███░░███   ░░███ ░█░░░███░░░█";
    gotoxy(59, 18);
    cout << " ░███   █ ░  ░███  ███     ░░░  ░███    ░███ ░   ░███  ░ ";
    gotoxy(59, 19);
    cout << " ░███████    ░███ ░███          ░███████████     ░███    ";
    gotoxy(59, 20);
    cout << " ░███░░░█    ░███ ░███    █████ ░███░░░░░███     ░███    ";
    gotoxy(59, 21);
    cout << " ░███  ░     ░███ ░░███  ░░███  ░███    ░███     ░███    ";
    gotoxy(59, 22);
    cout << " █████       █████ ░░█████████  █████   █████    █████   ";
    gotoxy(59, 23);
    cout << "░░░░░       ░░░░░   ░░░░░░░░░  ░░░░░   ░░░░░    ░░░░░    ";

    startTime = time(NULL);
    while (time(NULL) - startTime < 1)
    {
    }
    printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
}

void showRoundResult(int winner, int &p1Rounds, int &p2Rounds, int currentRound,
                     int &arenaLeft, int &arenaRight, int &arenaTop, int &arenaBottom,
                     string &p1Name, string &p2Name)
{
    system("cls");
    printMenuDecorations();
    setColor(96);
    gotoxy(68, 11);
    cout << "           ROUND " << currentRound << " COMPLETE!          ";

    gotoxy(68, 15);
    if (winner == 1)
    {
        setColor(11);
        cout << "        PLAYER 1 WINS THIS ROUND!      ";
        gotoxy(68, 17);
        setColor(96);
        cout << "              " << p1Name << " WINS!              ";
    }
    else if (winner == 2)
    {
        setColor(4);
        cout << "        PLAYER 2 WINS THIS ROUND!      ";
        gotoxy(68, 17);
        setColor(96);
        cout << "              " << p2Name << " WINS!              ";
    }
    else
    {
        setColor(8);
        cout << "            ROUND IS A print!           ";
        gotoxy(68, 17);
        setColor(96);
        cout << "           NO WINNER THIS ROUND        ";
    }

    gotoxy(72, 20);
    setColor(11);
    cout << "Player 1 (" << p1Name << ") Rounds Won: " << p1Rounds;
    gotoxy(72, 21);
    setColor(4);
    cout << "Player 2 (" << p2Name << ") Rounds Won: " << p2Rounds;
    Sleep(2000);
}

int showMatchEndMenu(int &p1Rounds, int &p2Rounds, string &p1Name, string &p2Name)
{
    system("cls");

    int selectedOption = 0;
    int totalOptions = 2;

    while (true)
    {
        setColor(6);
        int x = 47, y = 2;
        gotoxy(x, y);
        cout << " ███████████ █████ ██████   █████ █████  █████████  █████   █████ ██████████ ██████████  ";
        gotoxy(x, y + 1);
        cout << "░░███░░░░░░█░░███ ░░██████ ░░███ ░░███  ███░░░░░███░░███   ░░███ ░░███░░░░░█░░███░░░░███ ";
        gotoxy(x, y + 2);
        cout << " ░███   █ ░  ░███  ░███░███ ░███  ░███ ░███    ░░░  ░███    ░███  ░███  █ ░  ░███   ░░███";
        gotoxy(x, y + 3);
        cout << " ░███████    ░███  ░███░░███░███  ░███ ░░█████████  ░███████████  ░██████    ░███    ░███";
        gotoxy(x, y + 4);
        cout << " ░███░░░█    ░███  ░███ ░░██████  ░███  ░░░░░░░░███ ░███░░░░░███  ░███░░█    ░███    ░███";
        gotoxy(x, y + 5);
        cout << " ░███  ░     ░███  ░███  ░░█████  ░███  ███    ░███ ░███    ░███  ░███ ░   █ ░███    ███ ";
        gotoxy(x, y + 6);
        cout << " █████       █████ █████  ░░█████ █████░░█████████  █████   █████ ██████████ ██████████  ";
        gotoxy(x, y + 7);
        cout << "░░░░░       ░░░░░ ░░░░░    ░░░░░ ░░░░░  ░░░░░░░░░  ░░░░░   ░░░░░ ░░░░░░░░░░ ░░░░░░░░░░   ";

        gotoxy(70, 11);
        if (p1Rounds > p2Rounds)
        {
            setColor(11);
            cout << "     PLAYER 1 (" << p1Name << ") IS THE CHAMPION!     ";
        }
        else if (p2Rounds > p1Rounds)
        {
            setColor(4);
            cout << "     PLAYER 2 (" << p2Name << ") IS THE CHAMPION!     ";
        }
        else
        {
            setColor(8);
            cout << "        THE MATCH IS A print!       ";
        }

        gotoxy(78, 14);
        setColor(96);
        cout << "       Final Score      ";
        gotoxy(78, 15);
        setColor(11);
        cout << "Player 1 (" << p1Name << "): " << p1Rounds << " rounds";
        gotoxy(78, 16);
        setColor(4);
        cout << "Player 2 (" << p2Name << "): " << p2Rounds << " rounds";

        printMenuOption(77, 20, "      Rematch       ", selectedOption == 0);
        printMenuOption(77, 22, "   Return to Menu   ", selectedOption == 1);

        bool keyPressed = false;
        while (keyPressed == false)
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                selectedOption = selectedOption - 1;
                if (selectedOption < 0)
                {
                    selectedOption = totalOptions - 1;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_UP) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                selectedOption = selectedOption + 1;
                if (selectedOption >= totalOptions)
                {
                    selectedOption = 0;
                }
                keyPressed = true;
                playMenuMoveSound();
                while (GetAsyncKeyState(VK_DOWN) & 0x8000)
                {
                }
            }
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                playMenuEnterSound();
                while (GetAsyncKeyState(VK_RETURN) & 0x8000)
                {
                }
                if (selectedOption == 0)
                {
                    return 1;
                }
                else
                {
                    return 2;
                }
            }
        }
    }
}

void assignCharacterMoves(int charIndex, string Model[], string punch1[], string punch2[], string kick[], string hurt[],
                          string jinModel[], string jinPunch1[], string jinPunch2[], string jinKick[], string jinHurt[],
                          string yoshiModel[], string yoshiPunch1[], string yoshiPunch2[], string yoshiKick[], string yoshiHurt[],
                          string paulModel[], string paulPunch1[], string paulPunch2[], string paulKick[], string paulHurt[])
{
    if (charIndex == 0)
    {
        for (int i = 0; i < 17; i++)
        {
            Model[i] = jinModel[i];
            punch1[i] = jinPunch1[i];
            punch2[i] = jinPunch2[i];
            kick[i] = jinKick[i];
            hurt[i] = jinHurt[i];
        }
    }
    else if (charIndex == 1)
    {
        for (int i = 0; i < 17; i++)
        {
            Model[i] = yoshiModel[i];
            punch1[i] = yoshiPunch1[i];
            punch2[i] = yoshiPunch2[i];
            kick[i] = yoshiKick[i];
            hurt[i] = yoshiHurt[i];
        }
    }
    else
    {
        for (int i = 0; i < 17; i++)
        {
            Model[i] = paulModel[i];
            punch1[i] = paulPunch1[i];
            punch2[i] = paulPunch2[i];
            kick[i] = paulKick[i];
            hurt[i] = paulHurt[i];
        }
    }
}

void playRound(int &p1X, int &p1Y, int &p2X, int &p2Y, int &p1Health, int &p2Health,
               int &p1Rounds, int &p2Rounds, int &currentRound, int &timeRemaining,
               bool &returnToMenu, bool &gameSaved,
               string p1Model[], string p1Punch1[], string p1Punch2[], string p1Kick[], string p1Hurt[],
               string p2Model[], string p2Punch1[], string p2Punch2[], string p2Kick[], string p2Hurt[],
               int &arenaLeft, int &arenaRight, int &arenaTop, int &arenaBottom,
               int &p1Char, int &p2Char, string &p1Name, string &p2Name)
{
    time_t startTime = time(NULL);
    time_t currentTime;
    int elapsedSeconds;

    system("cls");
    printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
    updateHealthUI(p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Name, p2Name);
    refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);

    while (p1Health > 0 && p2Health > 0 && timeRemaining > 0)
    {
        currentTime = time(NULL);
        elapsedSeconds = (int)(currentTime - startTime);
        int newTimeRemaining = 30 - elapsedSeconds;
        if (newTimeRemaining < 0)
        {
            newTimeRemaining = 0;
        }

        if (newTimeRemaining != timeRemaining)
        {
            timeRemaining = newTimeRemaining;
            updateHealthUI(p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Name, p2Name);
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
            }
            int pauseChoice = showPauseMenu();

            if (pauseChoice == 1)
            {
                startTime = time(NULL) - (30 - timeRemaining);
                system("cls");
                printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
                updateHealthUI(p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Name, p2Name);
                refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            }
            else if (pauseChoice == 2)
            {
                saveGame(p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Char, p2Char);
                gameSaved = true;
                startTime = time(NULL) - (30 - timeRemaining);
                system("cls");
                printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
                updateHealthUI(p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Name, p2Name);
                refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
                setColor(10);
                gotoxy(78, 24);
                cout << "Game saved successfully!";
                Sleep(1500);
                gotoxy(78, 24);
                cout << "                        ";
            }
            else if (pauseChoice == 3)
            {
                returnToMenu = true;
                return;
            }
        }

        bool actionOccurred = false;

        if (GetAsyncKeyState('A') & 0x8000)
        {
            if (p1X > arenaLeft + 3)
            {
                erasePlayer(p1X, p1Y);
                p1X = p1X - 4;
                actionOccurred = true;
            }
        }
        if (GetAsyncKeyState('D') & 0x8000)
        {
            if (p1X + 22 < p2X)
            {
                erasePlayer(p1X, p1Y);
                p1X = p1X + 4;
                actionOccurred = true;
            }
        }
        if (GetAsyncKeyState('E') & 0x8000)
        {
            executeAttack(1, 1, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
        if (GetAsyncKeyState('Q') & 0x8000)
        {
            executeAttack(1, 2, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
        if (GetAsyncKeyState('Z') & 0x8000)
        {
            executeAttack(1, 3, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            if (p2X > p1X + 22)
            {
                erasePlayer(p2X, p2Y);
                p2X = p2X - 4;
                actionOccurred = true;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            if (p2X < arenaRight - 25)
            {
                erasePlayer(p2X, p2Y);
                p2X = p2X + 4;
                actionOccurred = true;
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
        {
            executeAttack(2, 1, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
        if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
        {
            executeAttack(2, 2, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
        {
            executeAttack(2, 3, p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining,
                          p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt, p1Name, p2Name, p1Char, p2Char);
            erasePlayer(p1X, p1Y);
            erasePlayer(p2X, p2Y);
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }

        if (actionOccurred)
        {
            refreshCharacters(p1X, p1Y, p2X, p2Y, p1Model, p2Model);
            printArena(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
    }

    if (p1Health > p2Health)
    {
        p1Rounds = p1Rounds + 1;
        showRoundResult(1, p1Rounds, p2Rounds, currentRound, arenaLeft, arenaRight, arenaTop, arenaBottom, p1Name, p2Name);
    }
    else if (p2Health > p1Health)
    {
        p2Rounds = p2Rounds + 1;
        showRoundResult(2, p1Rounds, p2Rounds, currentRound, arenaLeft, arenaRight, arenaTop, arenaBottom, p1Name, p2Name);
    }
    else
    {
        showRoundResult(0, p1Rounds, p2Rounds, currentRound, arenaLeft, arenaRight, arenaTop, arenaBottom, p1Name, p2Name);
    }
}

int playGame(bool loadFromSave)
{
    string jinModel[17];
    string jinPunch1[17];
    string jinPunch2[17];
    string jinKick[17];
    string jinHurt[17];
    string yoshiModel[17];
    string yoshiPunch1[17];
    string yoshiPunch2[17];
    string yoshiKick[17];
    string yoshiHurt[17];
    string paulModel[17];
    string paulPunch1[17];
    string paulPunch2[17];
    string paulKick[17];
    string paulHurt[17];

    initializeJinMoves(jinModel, jinPunch1, jinPunch2, jinKick, jinHurt);
    initializeYoshimitsuMoves(yoshiModel, yoshiPunch1, yoshiPunch2, yoshiKick, yoshiHurt);
    initializePaulMoves(paulModel, paulPunch1, paulPunch2, paulKick, paulHurt);

    int arenaLeft = 3;
    int arenaRight = 173;
    int arenaTop = 6;
    int arenaBottom = 45;

    int p1X = 50;
    int p1Y = 27;
    int p2X = 110;
    int p2Y = 27;
    int p1Health = 100;
    int p2Health = 100;
    int p1Rounds = 0;
    int p2Rounds = 0;
    int currentRound = 1;
    int timeRemaining = 30;
    int p1Char = 0;
    int p2Char = 0;

    if (loadFromSave)
    {
        int loadResult = showLoadGameMenu(p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds, currentRound, timeRemaining, p1Char, p2Char);
        if (loadResult == 0)
        {
            return 2;
        }
    }
    else
    {
        showCharacterSelect(p1Char, p2Char);
    }

    string p1Model[17];
    string p1Punch1[17];
    string p1Punch2[17];
    string p1Kick[17];
    string p1Hurt[17];
    string p2Model[17];
    string p2Punch1[17];
    string p2Punch2[17];
    string p2Kick[17];
    string p2Hurt[17];
    string p1Name;
    string p2Name;

    assignCharacterMoves(p1Char, p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt,
                         jinModel, jinPunch1, jinPunch2, jinKick, jinHurt,
                         yoshiModel, yoshiPunch1, yoshiPunch2, yoshiKick, yoshiHurt,
                         paulModel, paulPunch1, paulPunch2, paulKick, paulHurt);

    assignCharacterMoves(p2Char, p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt,
                         jinModel, jinPunch1, jinPunch2, jinKick, jinHurt,
                         yoshiModel, yoshiPunch1, yoshiPunch2, yoshiKick, yoshiHurt,
                         paulModel, paulPunch1, paulPunch2, paulKick, paulHurt);

    getCharacterName(p1Char, p1Name);
    getCharacterName(p2Char, p2Name);

    showCountdown(arenaLeft, arenaRight, arenaTop, arenaBottom);

    while (p1Rounds < 2 && p2Rounds < 2)
    {
        bool returnToMenu = false;
        bool gameSaved = false;

        playRound(p1X, p1Y, p2X, p2Y, p1Health, p2Health, p1Rounds, p2Rounds,
                  currentRound, timeRemaining, returnToMenu, gameSaved,
                  p1Model, p1Punch1, p1Punch2, p1Kick, p1Hurt,
                  p2Model, p2Punch1, p2Punch2, p2Kick, p2Hurt,
                  arenaLeft, arenaRight, arenaTop, arenaBottom,
                  p1Char, p2Char, p1Name, p2Name);

        if (returnToMenu)
        {
            return 2;
        }

        if (p1Rounds < 2 && p2Rounds < 2)
        {
            currentRound = currentRound + 1;
            p1X = 50;
            p1Y = 27;
            p2X = 110;
            p2Y = 27;
            p1Health = 100;
            p2Health = 100;
            timeRemaining = 30;

            showCountdown(arenaLeft, arenaRight, arenaTop, arenaBottom);
        }
    }

    int endChoice = showMatchEndMenu(p1Rounds, p2Rounds, p1Name, p2Name);
    return endChoice;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setConsoleSize();
    hideCursor();

    bool gameRunning = true;

    while (gameRunning)
    {
        int menuChoice = showMainMenu();

        if (menuChoice == 1)
        {
            int result = playGame(false);
            while (result == 1)
            {
                result = playGame(false);
            }
        }
        else if (menuChoice == 2)
        {
            int result = playGame(true);
            while (result == 1)
            {
                result = playGame(false);
            }
        }
        else if (menuChoice == 3)
        {
            gameRunning = false;
            return 0;
        }
    }

    system("cls");

    return 0;
}