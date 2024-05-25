#include<SDL2/SDL.h>
#include<head.h>
#include<iostream>
using namespace std;
int main()
{
    SDL_Init(SDL_INIT_VIDEO);//初始化窗口
    SDL_Window *mainwin=SDL_CreateWindow("SuperBookManageSysterm",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,900,600,0);//创建主窗口
    SDL_DestroyWindow(mainwin);//删除主窗口
    SDL_Quit();//推出sdl
    return 0;

}
