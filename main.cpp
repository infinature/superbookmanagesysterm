#include <SDL2/SDL.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 你的代码，这里可以留空，因为SDL程序通常使用main作为入口点
    return main(__argc, __argv); // 如果需要，可以调用main函数
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Init Failed: %s", SDL_GetError());
        return -1;
    }//初始化视频
    SDL_Window *win = SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1200, 800, 0); //创建主窗口win
    SDL_Event event;//定义事件
    SDL_Surface *surf=SDL_GetWindowSurface(win);//创建图形surf
    SDL_Surface *surf2=SDL_GetWindowSurface(win);//创建图形surf
    SDL_Surface *bmp_surf=SDL_LoadBMP("山大校徽.bmp");//导入图片
    SDL_Surface *bmp_surf2=SDL_LoadBMP("1.bmp");//导入图片
    SDL_Surface *bmp_surf3=SDL_LoadBMP("2.bmp");//导入图片
    SDL_Rect rect={0,400,300,0};//定义矩形
    SDL_Rect rect3={0,0,1200,300};//定义矩形
    SDL_Rect rect2={0,0,1200,900};//定义矩形
    SDL_FillRect(surf2,&rect2,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_FillRect(surf,&rect,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_FillRect(surf,&rect3,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_BlitSurface(bmp_surf2,NULL,surf2,&rect2);//显示绘图
    SDL_BlitSurface(bmp_surf3,NULL,surf,&rect3);//显示绘图
    SDL_BlitSurface(bmp_surf,NULL,surf2,&rect);//显示绘图
    SDL_UpdateWindowSurface(win);//更新图形



    while(true)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                break;//直到用户关闭再关闭
            }
            // 在这里添加登录按钮的点击事件处理代码，用于验证用户名和密码
        }

    }
    SDL_FreeSurface(bmp_surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(surf2);
    SDL_FreeSurface(bmp_surf2);
    SDL_FreeSurface(bmp_surf3);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
