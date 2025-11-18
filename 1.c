//創建視窗
#include <SDL2/SDL.h>
#define W 600
#define H 400
#undef main
//創建窗口
int main() {
    // 1. 初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    // 2. 建立窗口
    //窗口名稱 窗口座標 (x,y) 窗口大小(w ,h) 窗口參數（可不可以變）...
    SDL_Window *win = SDL_CreateWindow
    (
        "Hello",//畫面標題
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W, H,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE //窗口可以做什麼
    );
    if(win == NULL)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return -1;
    }
    SDL_Delay(3000);//Xcode 預設不會顯示
    SDL_DestroyWindow(win);
    SDL_Quit();
}