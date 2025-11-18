//單獨修改pixel
#include <SDL2/SDL.h>
#undef main
int main() {
    // 初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    // 建立窗口
    SDL_Window *win = SDL_CreateWindow
    (
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 400,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if(!win)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 1.獲取窗口 surface
    SDL_Surface *surf = SDL_GetWindowSurface(win);
    if(!surf)
    {
        SDL_Log("Get surface failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    //2. 修改像素點顏色值=>修改內存值
    Uint32 *px = (Uint32 *)surf->pixels;
    px[20000] =0xffffffff;
    for(int i = 20000 ;i<20100 ;i++)
    {
        px[i] = 0xffffffff;
    }

    // 3.更新到畫面上
    SDL_UpdateWindowSurface(win);

    // 4.事件循環

    SDL_Event event;
    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;
        }
        
    }

    // 6. 清理資源
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}