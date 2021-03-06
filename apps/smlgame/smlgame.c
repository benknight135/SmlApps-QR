 /**
 * @file smlgame.c
 * @authors Ben Knight (bknight135@gmail.com)
 * @brief 
 * @version 0.0.2
 * @date 2020-08-09
 * 
 * @copyright Copyright (c) Benjamin Knight, 2020
 * 
 */

#include <windows.h>
#include <stdio.h>

#define IDT_TIMER_GAME_FRAME 1001

enum moveDirection {
    MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitFrame(HWND);
void DrawFrame(HWND);
void UpdatePlayer();
void Update(HWND);
long long milliseconds_now();

HPEN player_hpen;
HBRUSH player_hbrush;

const int window_width = 300;
const int window_height = 300;
const long long update_time = 1000;

const int player_size = 10;
const int player_x_max = 288;
const int player_x_min = 11;
const int player_y_max = 265;
const int player_y_min = 11;

long long last_update_time_ms = 0;
int player_x = 150;
int player_y = 150;
enum moveDirection player_direction = MOVE_UP;
int player_speed = 1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    MSG  msg;
    WNDCLASSW wc ={ 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"sml";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"sml",
        WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
        100, 100, window_width, window_height, NULL, NULL, hInstance, NULL);

    player_hbrush = CreateSolidBrush(RGB(0, 0, 0));
    player_hpen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    case WM_CREATE:
        InitFrame(hwnd);
        break;

    case WM_PAINT:
        DrawFrame(hwnd);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:

            // Process the LEFT ARROW key. 
            player_direction = MOVE_LEFT;
            break;

        case VK_RIGHT:

            // Process the RIGHT ARROW key. 
            player_direction = MOVE_RIGHT;
            break;

        case VK_UP:

            // Process the UP ARROW key. 
            player_direction = MOVE_UP;
            break;

        case VK_DOWN:

            // Process the DOWN ARROW key. 
            player_direction = MOVE_DOWN;
            break;

        default:
            break;
        }
        break;

    case WM_KEYUP:
        switch (wParam)
        {
        case VK_LEFT:

            // Process the LEFT ARROW key. 

            break;

        case VK_RIGHT:

            // Process the RIGHT ARROW key. 

            break;

        case VK_UP:

            // Process the UP ARROW key. 

            break;

        case VK_DOWN:

            // Process the DOWN ARROW key. 

            break;

        default:
            break;
        }
        break;

    case WM_TIMER: 
        switch (wParam) 
        { 
            case IDT_TIMER_GAME_FRAME: 
                // process the game timer 
                Update(hwnd);
                return 0; 
        } 
        break;

    case WM_DESTROY:
        KillTimer(hwnd, IDT_TIMER_GAME_FRAME);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void InitFrame(HWND hwnd) {
    SetTimer(hwnd, IDT_TIMER_GAME_FRAME, 16, (TIMERPROC)NULL);
}

void Update(HWND hwnd){
    UpdatePlayer(hwnd);
    InvalidateRect(hwnd, NULL, TRUE);
}

void UpdatePlayer() {
    switch (player_direction)
    {
    case MOVE_UP:
        player_y-= player_speed;
        break;
    case MOVE_DOWN:
        player_y+= player_speed;
        break;
    case MOVE_RIGHT:
        player_x+= player_speed;
        break;
    case MOVE_LEFT:
        player_x-= player_speed;
        break;
    }
    // Check player is at windows edges
    if (player_x >= player_x_max){
        player_x = player_x_max;
    }
    if (player_x <= player_x_min){
        player_x = player_x_min;
    }
    if (player_y >= player_y_max){
        player_y = player_y_max;
    }
    if (player_y <= player_y_min){
        player_y = player_y_min;
    }
}

void DrawFrame(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // draw player
    HPEN holdPen = SelectObject(hdc, player_hpen);
    HBRUSH holdBrush = SelectObject(hdc, player_hbrush);
    Rectangle(hdc, player_x-player_size, player_y-player_size, player_x+player_size, player_y+player_size);
    SelectObject(hdc, holdPen);
    SelectObject(hdc, holdBrush);

    EndPaint(hwnd, &ps);
}