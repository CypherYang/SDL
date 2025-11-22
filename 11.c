//鍵盤事件
#include <SDL2/SDL.h>
#define W 720
#define H 640
#undef main

SDL_Window *win = NULL;
SDL_Renderer *rdr = NULL;

// 會跟著滑鼠移動的方形
SDL_Rect rect = {100, 100, 200, 100};
int dx = 1;
int dy = 0;
int green =200;
int init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    win = SDL_CreateWindow("key event",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            W, H,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(!win) return -1;

    rdr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if(!rdr) return -1;

    return 0;
}

void dinit()
{
    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void draw()
{
    SDL_SetRenderDrawColor(rdr, 100, 100, 100, 255);//設置顏色(gray)
    SDL_RenderClear(rdr);//用設置的顏色清除平目

    SDL_SetRenderDrawColor(rdr, 0, green, 0, 255);//設置顏色(white)
    SDL_RenderFillRect(rdr, &rect);//用設置的顏色畫出方塊

    SDL_RenderPresent(rdr);//呈現
}

void event_loop()
{
    SDL_Event event;
    int running = 1;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_WINDOWEVENT://窗口事件，窗口事件有很多事件
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)//如果窗口事件是大小改變事件
                    {
                        draw();//如果窗口大小改變，就重新畫一個
                    } 
                    break;

                case SDL_KEYDOWN://鍵盤事件 任意鍵盤按下
                    SDL_Log("DOWN sym = %d ,scancode = %d" , event.key.keysym.sym ,event.key.keysym.scancode);

                    //event.key.keysym.sym 是 按下個ASCII code

                    if (event.key.keysym.sym == SDLK_UP)//鍵盤按上
                    {
                        SDL_Log("UP");
                        dy = -1;
                        dx = 0;
                    }
                    
                    if (event.key.keysym.sym == SDLK_DOWN)//鍵盤按下
                    {
                        SDL_Log("DOWN");
                        dy = 1;
                        dx = 0;
                    }
                    if (event.key.keysym.sym == SDLK_LEFT)//鍵盤按左
                    {
                        SDL_Log("left");
                        dx =-1;
                        dy =0;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT)//鍵盤按右
                    {
                        SDL_Log("RIGHT");
                        dx = 1;
                        dy = 0;
                    }
                    break;

                case SDL_KEYUP://鍵盤事件 任意鍵盤鬆開
                    //SDL_Log("UP sym = %d ,scancode = %d" , event.key.keysym.sym ,event.key.keysym.scancode);
                    break;

                //不好說明直接運行看效果

                case SDL_TEXTEDITING:
                    SDL_Log("Edit %s",event.edit.text);
                    break;
                case SDL_TEXTINPUT:
                    SDL_Log("Input %s" ,event.text.text);
                    break;
                default:
                    break;
            }
        }
        rect.x += dx;
        rect.y += dy;
        draw();
        SDL_Delay(16); // 60 FPS
    }
}

int main()
{
    if(init() < 0)
        return -1;
    draw();
    event_loop();
    dinit();
    return 0;
}