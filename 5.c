//SDL渲染器 （比Surface高級一點的）
#include <SDL2/SDL.h>
#define W 600
#define H 400
#undef main
//創建窗口
int main() {
    //  初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    //  建立窗口
    //窗口名稱 窗口座標 (x,y) 窗口大小(w ,h) 窗口參數（可不可以變）...
    SDL_Window *win = SDL_CreateWindow
    (
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W, H,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if(win == NULL)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return -1;
    }
    //渲染器

    //1. 創建窗口關聯的Renderer(渲染器)
    SDL_Renderer *rdr = SDL_CreateRenderer(win ,-1 ,0);//目標窗口 驅動索引（-1）默認屬性（0）
    if (NULL == rdr)
    {
        SDL_Log("failed %s" , SDL_GetError());
        return -1;
    }

    //2. 設置渲染顏色(背景)
    SDL_SetRenderDrawColor(rdr , 0 , 255 , 0 , 255);

    //3.清除屏幕
    SDL_RenderClear(rdr);

    //4.渲染呈現
    SDL_RenderPresent(rdr);

    //程式卡在這，直到事件發生
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


    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}