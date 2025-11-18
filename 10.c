//鼠標移動事件 鼠標按下事件 視窗大小改變
#include <SDL2/SDL.h>
#define W 720
#define H 640
#undef main

SDL_Window *win = NULL;
SDL_Renderer *rdr = NULL;

// 會跟著滑鼠移動的方形
SDL_Rect rect = {100, 100, 200, 100};
int green =200;
int init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        return -1;
    }

    win = SDL_CreateWindow("Follow Mouse",
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
            SDL_Point pt;
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

                case SDL_MOUSEMOTION://鼠標移動事件
                    SDL_Log("x = %d , y= %d" , event.motion.x , event.motion.y);
                    rect.x = event.motion.x - 100;//改變位置
                    rect.y = event.motion.y - 50;//重新繪製
                    draw();
                    break;

                case SDL_MOUSEBUTTONDOWN://鼠標按鍵按下事件
                    SDL_Log("鼠標被按下了 : x = %d y = %d button = %d clicks = %d", event.button.x, event.button.y, event.button.button, event.button.clicks);
                    //點擊位置(x) 點擊位置(y) 點擊左右間或中間 點擊次數
                    pt = (SDL_Point){event.button.x , event.button.y};//讓pt=鼠標的點擊位置
                    if(SDL_PointInRect(&pt ,&rect))//判斷點擊是否在繪製區域
                        {
                            green=255;
                            draw();
                        }
                    break;

                case SDL_MOUSEBUTTONUP://鼠標按鍵放開事件
                    SDL_Log("鼠標被放開了 : x = %d y = %d button = %d clicks = %d",event.button.x,event.button.y,event.button.button,event.button.clicks);
                    pt = (SDL_Point) {event.button.x , event.button.y};
                    if(SDL_PointInRect(&pt ,&rect))
                    {
                        green = 200;
                        draw();
                    }
                    break;
            }
        }
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
