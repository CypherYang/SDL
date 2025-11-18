//讓視窗看起來有在動
#include <SDL2/SDL.h>
#undef main
int main() {
    // 1. 初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0){
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    // 2. 建立窗口
    SDL_Window *win = SDL_CreateWindow(
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

    // 3. 獲取窗口 surface
    SDL_Surface *surf = SDL_GetWindowSurface(win);
    if(!surf){
        SDL_Log("Get surface failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    // 4. 繪製矩形

    SDL_Rect rect = {100, 100, 100, 100};//定義矩形區域 位置(x ,y) 區域 (x ,y)

    //SDL_FillRect(surf , &rect ,0x0000ff);//等價寫法
    SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format ,0 , 0, 255)); // 定義矩形顏色RGB
    
    // 5. 更新到畫面上
    SDL_UpdateWindowSurface(win);

    // 6. 事件循環
    SDL_Event event;
    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;
        }
        //看起來圖形會動起來
        SDL_FillRect(surf ,NULL ,0x000000);//原區域塗黑
        rect.x ++;//新座標
        SDL_FillRect(surf ,&rect ,0x0000ff);//新區域塗藍
        SDL_UpdateWindowSurface(win);
        SDL_Delay(20); //等20ms
    }

    // 6. 清理資源
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
