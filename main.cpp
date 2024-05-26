#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>
#include "head.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace std;
const string correctName = "admin";
const string correctKey = "12345";

// 函数声明
void CreateConsoleWindow(const string& title);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // SDL的WinMain入口将控制权转交给main函数
    return main(__argc, __argv);
}
int main(int argc, char *argv[]) {
    // 初始化SDL视频和TTF库
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 创建SDL窗口和渲染器
    SDL_Window* win = SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    if (!win) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }
    SDL_Surface *surf=SDL_GetWindowSurface(win);//创建图形surf
    SDL_Surface *surf2=SDL_GetWindowSurface(win);//创建图形surf2
    SDL_Surface *bmp_surf=SDL_LoadBMP("山大校徽.bmp");//导入图片
    SDL_Surface *bmp_surf2=SDL_LoadBMP("1.bmp");//导入图片
    SDL_Surface *bmp_surf3=SDL_LoadBMP("2.bmp");//导入图片
    SDL_Surface *bmp_surf4=SDL_LoadBMP("登录.bmp");//导入图片
    SDL_Rect rect={0,400,300,0};//定义矩形
    SDL_Rect rect3={0,0,1200,300};//定义矩形
    SDL_Rect rect2={0,0,1200,900};//定义矩形
    SDL_Rect rect4={400,300,400,150};//定义矩形
    SDL_FillRect(surf2,&rect2,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_FillRect(surf,&rect,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_FillRect(surf,&rect3,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_FillRect(surf,&rect4,SDL_MapRGB(surf->format,255,255,255));//创建矩形
    SDL_BlitSurface(bmp_surf2,NULL,surf2,&rect2);//显示绘图
    SDL_BlitSurface(bmp_surf3,NULL,surf,&rect3);//显示绘图
    SDL_BlitSurface(bmp_surf,NULL,surf2,&rect);//显示绘图
    SDL_BlitSurface(bmp_surf4,NULL,surf,&rect4);//显示绘图


    // 加载字体和颜色
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Candara.ttf", 72);
    SDL_Color textColor = {255, 0, 0};

    // 渲染循环
    bool running = true;
    SDL_Event event;

while (running) {
    SDL_RenderClear(renderer); // 添加这一行代码

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // 检测是否点击了rect4区域
            SDL_Rect rect4 = {400, 300, 400, 150};
            int x = event.button.x;
            int y = event.button.y;
            if (x >= rect4.x && x <= rect4.x + rect4.w && y >= rect4.y && y <= rect4.y + rect4.h) {
                // 关闭当前窗口
                running = false;
            }
        }
    }

    // 渲染逻辑
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(win);//更新图形
}


    // 关闭SDL资源
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    // 创建控制台窗口以输入用户名和密码
    CreateConsoleWindow("Login");


// 输入用户名和密码
string inputName, inputKey;
bool validInput = false;
while (!validInput) {
    cout << "Enter username: ";
    getline(cin, inputName);
    cout << "Enter key: ";
    getline(cin, inputKey);

    // 验证用户名和密码
    if (inputName == correctName && inputKey == correctKey) {
        validInput = true;
        // 打开一个新的空白窗口
        win = SDL_CreateWindow("Blank Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!win) {
            SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
            return -1;
        }
        // 新窗口的渲染循环可以放在这里
        // ...
    } else {
        // 输入错误，重新打开终端窗口
        CreateConsoleWindow("Login");
    }
}

    // 清理资源
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(bmp_surf);
    SDL_FreeSurface(surf);
    SDL_FreeSurface(surf2);
    SDL_FreeSurface(bmp_surf2);
    SDL_FreeSurface(bmp_surf3);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
// 创建新的控制台窗口
void CreateConsoleWindow(const string& title) {
    FreeConsole(); // 如果已经有一个控制台窗口，先关闭它
    AllocConsole(); // 为应用程序分配一个新的控制台窗口
    freopen("CONOUT$", "wt", stdout); // 重定向标准输出到控制台
    freopen("CONIN$", "rt", stdin);  // 重定向标准输入到控制台
    SetConsoleTitle(title.c_str());   // 设置控制台窗口的标题
}