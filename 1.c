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
    SDL_Window *win = SDL_CreateWindow
    (
        "Hello",//畫面標題
        SDL_WINDOWPOS_CENTERED,//視窗左上x座標
        SDL_WINDOWPOS_CENTERED,//視窗左上y座標
        W, H,//視窗大小
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE //flags — 視窗行為/能力設定
    );
    if(win == NULL)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return -1;
    }
    SDL_Delay(3000);//Xcode 預設不會顯示(if Windows就會顯示)
    SDL_DestroyWindow(win);
    SDL_Quit();
}
