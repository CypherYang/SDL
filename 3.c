//導入圖片
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

    // 1. 獲取與窗口關聯的 surface 用來在窗口顯示東西

    SDL_Surface *surf = SDL_GetWindowSurface(win);
    if(!surf)
    {
        SDL_Log("Get surface failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }
    // 2.導入BMP圖片(SDL kernel僅支援 BMP格式的圖片ㄋ)

    SDL_Surface *bmp_surf = SDL_LoadBMP("try.bmp");
    if(bmp_surf == NULL)
    {
        SDL_Log("Load BMP failed :%s",SDL_GetError());
        return -1;
    }

    // 3. 把圖片複製到窗口Surface上
    SDL_BlitSurface(bmp_surf , NULL ,surf ,NULL);
    //目標位置 複製區域 目標surface 窗口對應的surface
    SDL_UpdateWindowSurface(win);
    
    // 事件循環
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
    // 4. 釋放Surface
    SDL_FreeSurface(bmp_surf);
    SDL_FreeSurface(surf);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
