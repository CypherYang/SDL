//整理代碼
//把 初始化 繪製 釋放 事件循環 寫成函式
#include <SDL2/SDL.h>
#define W 1200
#define H 800
#undef main
SDL_Window *win = NULL;
SDL_Renderer *rdr = NULL;
int init()
{
    //  初始化 SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    win = SDL_CreateWindow
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
    rdr = SDL_CreateRenderer(win ,-1 ,0);
    if (NULL == rdr)
    {
        SDL_Log("failed %s" , SDL_GetError());
        return -1;
    }
    return 0;
}

void dinit()
{
    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int draw()
{
    SDL_SetRenderDrawColor(rdr , 0 ,255, 0,255);//設置泫然顏色
    SDL_RenderClear(rdr);//用渲染顏色去清除屏目
    SDL_Surface *img_surf = SDL_LoadBMP("try.bmp");
    if (NULL == img_surf)
    {
        SDL_Log("failed %s",SDL_GetError());
        return -1;
    }

    //補：動態設置窗口大小使窗口大小與圖片大小匹配
    SDL_SetWindowSize(win , img_surf->w ,img_surf->h);//窗口 重設寬 與重設高

    
    //BMP只能導入surface 要創建texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rdr ,img_surf);
    if(NULL == texture)
    {
        SDL_Log("failed %s" ,SDL_GetError());
        return -1;
    }


    //將texture複製到渲染器
    SDL_RenderCopy(rdr ,texture ,NULL ,NULL);
    //渲染器 Texture 複製來源區域 目標區域 翻轉角度(逆時) 旋轉中心 旋轉快捷

    SDL_RenderPresent(rdr);//呈現
    return 0;
}

void event_loop()
{
    SDL_Event event;
    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return ;
            default:
                break;
            }
                
        }
    }
}

int main() 
{
    if(init() < 0)
    {
        return -1;
    }
    draw();
    event_loop();
    dinit();
    return 0;
}