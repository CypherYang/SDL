//炫染線與點
//渲染方塊
//使方塊有在動
#include <SDL2/SDL.h>
#define W 1200
#define H 800
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
    SDL_Renderer *rdr = SDL_CreateRenderer(win ,-1 ,0);
    if (NULL == rdr)
    {
        SDL_Log("failed %s" , SDL_GetError());
        return -1;
    }
    //2. 設置渲染顏色
    SDL_SetRenderDrawColor(rdr , 0, 255, 0, 255);
    SDL_RenderClear(rdr);//3.清除屏幕
    SDL_SetRenderDrawBlendMode(rdr ,SDL_BLENDMODE_BLEND);//使透明通道有用

    //渲染點與線
    SDL_SetRenderDrawColor(rdr , 0 ,0 ,0 ,255);//設置渲染顏色
    SDL_RenderDrawPoint(rdr , 200 ,300);//渲染點 渲染器 點座標

    /*for (int i =200; i< 300 ; i+=5)//渲染多個點
    {
        SDL_RenderDrawPoint(rdr , i ,300);
    }*/

    SDL_RenderDrawLine(rdr , 0 ,0 , 200 ,250 );//渲染一條線
    //渲染多條線
    SDL_Point pt[5]={{0 ,0},{100 ,100},{100 ,300},{200 ,300},{180 ,190}};
    SDL_RenderDrawLines(rdr,pt ,5);//渲染器 點座標 要連接幾個點

    //目前不會顯示，因為while裡面會刷新

    //設置渲染顏色(方塊)
    SDL_SetRenderDrawColor(rdr ,0 ,0 ,0 ,50);// R G B 透明通道(255 不透明)
    SDL_Rect rect ={200 , 200, 100, 100};//起始座標(x ,y) 與 大小(h ,w)
    //SDL_RenderDrawRect(rdr ,&rect);//繪製方形
    SDL_RenderFillRect(rdr ,&rect);//繪製方塊

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
        //使方塊動起來

        //先把方塊清掉，重設座標，再畫方塊

        SDL_SetRenderDrawColor(rdr , 0 ,255 ,0 ,255);//設定顏色
        SDL_RenderClear(rdr);//用設定顏色清除屏幕
        SDL_SetRenderDrawColor(rdr ,0 ,0 ,0 ,50);//設置顏色
        rect.x ++;//座標變動
        SDL_RenderFillRect(rdr ,&rect);//繪製方塊
        SDL_RenderPresent(rdr);//渲染呈現
        SDL_Delay(10);
        
    }
    SDL_DestroyRenderer(rdr);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
