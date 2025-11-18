//顯示視窗
//繪製視窗
//讓視窗看起來有在動
#include <SDL2/SDL.h>
#define W 1200
#define H 800
#undef main
int main() {
    // 初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0){
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    // 建立窗口
    SDL_Window *win = SDL_CreateWindow(
        "Hello",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W,H,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if(!win)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 1. 獲取與窗口關聯的 surface 用來在窗口顯示東西
    SDL_Surface *surf = SDL_GetWindowSurface(win);
    if(NULL==surf)
    {
        SDL_Log("Get surface failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    // 2. 定義一個區域
    SDL_Rect rect = {100, 100, 100, 100};//位置(x ,y) 區域 (x ,y)

    // 3. surface 上進行繪製
    //SDL_FillRect(surf , &rect ,0x0000ff);//等價寫法
    SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format ,0 , 0, 255));
    //surfac指針 rect指針 顏色值
     
    // 4. 更新到畫面上
    SDL_UpdateWindowSurface(win);

    // 5. 事件循環
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
        SDL_UpdateWindowSurface(win);//更新到屏幕上
        SDL_Delay(20); //等20ms
    }

    // 6. 清理資源
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
