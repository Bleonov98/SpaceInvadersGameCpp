#include "stdfix.h"
#include "GameObject.h"

class World
{

private:

    char coord[50];

    vector<vector <char>> videoMemory;

    HINSTANCE hInstance;

    class VirtualTerminal {
    public:
        HWND hWindowConsole = GetForegroundWindow();

        bool Terminal() {

            // Set output mode to handle virtual terminal sequences
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut == INVALID_HANDLE_VALUE)
            {
                return false;
            }
            HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
            if (hIn == INVALID_HANDLE_VALUE)
            {
                return false;
            }

            DWORD dwOriginalOutMode = 0;
            DWORD dwOriginalInMode = 0;
            if (!GetConsoleMode(hOut, &dwOriginalOutMode))
            {
                return false;
            }
            if (!GetConsoleMode(hIn, &dwOriginalInMode))
            {
                return false;
            }

            DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
            DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

            DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
            if (!SetConsoleMode(hOut, dwOutMode))
            {
                // we failed to set both modes, try to step down mode gracefully.
                dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
                if (!SetConsoleMode(hOut, dwOutMode))
                {
                    // Failed to set any VT mode, can't do anything here.
                    return -1;
                }
            }

            DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;
            if (!SetConsoleMode(hIn, dwInMode))
            {
                // Failed to set VT input mode, can't do anything here.
                return -1;
            }

            return 0;
        }

        void SetScreenSize() {
            int Width = 150, Height = 56, err = 40;

            HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);

            COORD monitorSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
            COORD bufferSize = { Width, Height };

            _SMALL_RECT Rect;
            Rect.Top = 0;
            Rect.Left = 0;
            Rect.Bottom = Height - 1;
            Rect.Right = Width - 1;

            SetConsoleScreenBufferSize(hWnd, bufferSize);

            SetWindowPos(hWindowConsole, HWND_NOTOPMOST, 
                (monitorSize.X / 2 - Width * 4 - err), (monitorSize.Y / 2 - Height * 8 - err), 0, 0, 
                SWP_NOZORDER | SWP_NOREPOSITION | SWP_NOREDRAW);

            SetConsoleWindowInfo(hWnd, TRUE, &Rect);

            SetWindowLong(hWindowConsole, GWL_STYLE, GetWindowLong(hWindowConsole, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
        }
    };

    VirtualTerminal term;

public:

    World() {};

    World(int winWidth, int winHeight) {
        videoMemory.resize(winHeight);

        for (int i = 0; i < winHeight; i++)
        {
            videoMemory[i].resize(winWidth);
        }

        SetPos(0, 0);

        for (int i = 0; i < winHeight; i++)
        {
            for (int j = 0; j < winWidth; j++)
            {
                videoMemory[i][j] = '#';
            }
            cout << endl;
        }
    };

    void SetPos(int x, int y);

    void CreateWorld();

    void DrawArea();

    // void DrawTitle();

    // void Comunication();

    void RunWorld();
};

