//SDL 渲染單一圖片
//創建視窗
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
    //渲染圖片

    //創建窗口關聯的Renderer(渲染器)
    SDL_Renderer *rdr = SDL_CreateRenderer(win ,-1 ,0);
    if (NULL == rdr)
    {
        SDL_Log("failed %s" , SDL_GetError());
        return -1;
    }

    //1. 導入圖片
    SDL_Surface *img_surf = SDL_LoadBMP("try.bmp");
    if (NULL == img_surf)
    {
        SDL_Log("failed %s",SDL_GetError());
        return -1;
    }
    //補：動態設置窗口大小使窗口大小與圖片大小匹配
    SDL_SetWindowSize(win , img_surf->w ,img_surf->h);//窗口 重設寬與重設高


    //2. BMP只能導入surface 要創建texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rdr ,img_surf);
    if(NULL == texture)
    {
        SDL_Log("failed %s" ,SDL_GetError());
    }

    //SDL_Rect rect = {100 ,200 ,800 ,600};//用來複製的設定目標區域

    //3. 將texture複製到渲染器
    SDL_RenderCopy(rdr ,texture ,NULL ,NULL);//渲染器 Texture 複製來源區域 目標區域 (NULL為整個區域)

    //渲染呈現
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
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_FreeSurface(img_surf);
    SDL_Quit();
    return 0;
}