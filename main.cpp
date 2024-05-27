#include <SDL2/SDL.h> // 包含SDL2库的头文件，用于创建窗口和处理事件等
#include <SDL2/SDL_ttf.h> // 包含SDL_ttf库的头文件，用于处理字体
#include <windows.h> // 包含Windows API的头文件，用于创建控制台窗口
#include <iostream> // 包含输入输出流的头文件
#include <stdexcept> // 包含标准异常类的头文件
#include <chrono> // 包含时间日期相关的头文件
#include <thread> // 包含线程的头文件
#include <vector> // 包含动态数组的头文件
#include <string> // 包含字符串类的头文件
#include <D:\github's hub\superbookmanagesysterm\head.h>

using namespace std; // 使用标准命名空间


const string correctName = "admin"; // 正确的用户名
const string correctKey = "12345"; // 正确的登录密钥

// 创建新窗口的函数
SDL_Window* CreateNewWindow(const string& title) {
    // 设置窗口的宽度和高度
    int width = 800;
    int height = 600;
    // 创建窗口，位置居中，显示状态为 SDL_WINDOW_SHOWN
    SDL_Window* newWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    return newWindow;
}
// 创建新的控制台窗口函数
void CreateConsoleWindow(const string& title) {
    FreeConsole(); // 释放控制台
    AllocConsole(); // 分配新的控制台
    freopen("CONOUT$", "wt", stdout); // 重定向标准输出到控制台
    freopen("CONIN$", "rt", stdin);  // 重定向标准输入到控制台
    SetConsoleTitle(title.c_str());   // 设置控制台窗口标题
    cout << "New console window created with title: " << title << endl; // 输出新窗口的标题
}

// 根据用户类型创建新窗口的函数
SDL_Window* CreateUserWindow(const User& user) {
    string windowTitle;
    int width = 800;
    int height = 600;
    switch (user.type) {
        case 0:  // 管理员
            windowTitle = "Administrator Window"; // 设置窗口标题
            break;
        case 1://老师
            windowTitle = "Teacher Window"; // 设置窗口标题
            break;   
        case 2://学生
            windowTitle = "Student Window"; // 设置窗口标题
            break;        
        default:
            return nullptr; // 如果用户类型不是上述类型，则返回空指针
    }
    return SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN); // 创建窗口
}

// 处理矩形点击事件的函数
void HandleRectangleClick(SDL_Renderer* renderer, const User& user, int mouseX, int mouseY) {
    const int rectWidth = 200;
    const int rectHeight = 50;
    const int startX = 300;
    const int startY = 100;
    
    for (int i = 0; i < 6; ++i) {
        int x = startX + (i % 2) * rectWidth;
        int y = startY + (i / 2) * rectHeight;
        SDL_Rect rect = { x, y, rectWidth, rectHeight };
        if (mouseX >= rect.x && mouseX < rect.x + rect.w && mouseY >= rect.y && mouseY < rect.y + rect.h) {
            string consoleTitle = "Clicked " + user.name + "'s rect " + to_string(i + 1);
            CreateConsoleWindow(consoleTitle); // 创建新的控制台窗口
            break;
        }
    }
}

// WinMain是Windows程序的主入口点
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // SDL的WinMain入口将控制权转交给main函数
    return main(__argc, __argv);
}

// main函数是程序的入口点
int main(int argc, char *argv[]) {
    // 初始化SDL视频和TTF库
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError()); // 记录错误信息
        return -1; // 初始化失败，返回错误代码
    }
    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError()); // 记录错误信息
        SDL_Quit(); // 退出SDL
        return -1; // 初始化失败，返回错误代码
    }

    // 创建SDL窗口和渲染器
    SDL_Window* win = SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 900, SDL_WINDOW_SHOWN); // 创建窗口
    if (!win) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError()); // 记录错误信息
        TTF_Quit(); // 退出TTF库
        SDL_Quit(); // 退出SDL
        return -1; // 创建窗口失败，返回错误代码
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); // 创建渲染器
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError()); // 记录错误信息
        SDL_DestroyWindow(win); // 销毁窗口
        TTF_Quit(); // 退出TTF库
        SDL_Quit(); // 退出SDL
        return -1; // 创建渲染器失败，返回错误代码
    }

    // 加载位图和字体
    SDL_Surface* bmp_surf = SDL_LoadBMP("山大校徽.bmp"); // 加载位图
    SDL_Surface* bmp_surf2 = SDL_LoadBMP("1.bmp"); // 加载位图
    SDL_Surface* bmp_surf3 = SDL_LoadBMP("2.bmp"); // 加载位图
    SDL_Surface* bmp_surf4 = SDL_LoadBMP("登录.bmp"); // 加载位图
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Candara.ttf", 72); // 加载字体
    if (!bmp_surf || !bmp_surf2 || !bmp_surf3 || !bmp_surf4 || !font) {
        SDL_Log("Failed to load resources: %s", SDL_GetError()); // 记录错误信息
        // 清理资源
        SDL_FreeSurface(bmp_surf); // 释放位图资源
        SDL_FreeSurface(bmp_surf2); // 释放位图资源
        SDL_FreeSurface(bmp_surf3); // 释放位图资源
        SDL_FreeSurface(bmp_surf4); // 释放位图资源
        TTF_CloseFont(font); // 释放字体资源
        SDL_DestroyRenderer(renderer); // 销毁渲染器
        SDL_DestroyWindow(win); // 销毁窗口
        TTF_Quit(); // 退出TTF库
        SDL_Quit(); // 退出SDL
        return -1; // 加载资源失败，返回错误代码
    }

    // 定义目标区域
    SDL_Rect rect = {0, 400, 300, 0}; // 定义一个目标区域
    SDL_Rect rect3 = {0, 0, 1200, 300}; // 定义一个目标区域
    SDL_Rect rect2 = {0, 0, 1200, 900}; // 定义一个目标区域
    SDL_Rect rect4 = {400, 300, 400, 150}; // 定义一个目标区域

    // 将位图转换为纹理
    SDL_Texture* tex_surf = SDL_CreateTextureFromSurface(renderer, bmp_surf); // 从位图创建纹理
    SDL_Texture* tex_surf2 = SDL_CreateTextureFromSurface(renderer, bmp_surf2); // 从位图创建纹理
    SDL_Texture* tex_surf3 = SDL_CreateTextureFromSurface(renderer, bmp_surf3); // 从位图创建纹理
    SDL_Texture* tex_surf4 = SDL_CreateTextureFromSurface(renderer, bmp_surf4); // 从位图创建纹理
    if (!tex_surf || !tex_surf2 || !tex_surf3 || !tex_surf4) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError()); // 记录错误信息
        // 清理资源
        SDL_FreeSurface(bmp_surf); // 释放位图资源
        SDL_FreeSurface(bmp_surf2); // 释放位图资源
        SDL_FreeSurface(bmp_surf3); // 释放位图资源
        SDL_FreeSurface(bmp_surf4); // 释放位图资源
        TTF_CloseFont(font); // 释放字体资源
        SDL_DestroyTexture(tex_surf); // 销毁纹理
        SDL_DestroyTexture(tex_surf2); // 销毁纹理
        SDL_DestroyTexture(tex_surf3); // 销毁纹理
        SDL_DestroyTexture(tex_surf4); // 销毁纹理
        SDL_DestroyRenderer(renderer); // 销毁渲染器
        SDL_DestroyWindow(win); // 销毁窗口
        TTF_Quit(); // 退出TTF库
        SDL_Quit(); // 退出SDL
        return -1; // 创建纹理失败，返回错误代码
    }

    // 渲染循环
    bool running = true; // 渲染循环的控制变量
    while (running) {
        SDL_Event event; // SDL事件结构体
        while (SDL_PollEvent(&event)) { // 检查事件队列中是否有事件
            if (event.type == SDL_QUIT) { // 如果事件类型是退出事件
                running = false; // 设置渲染循环结束
            } else if (event.type == SDL_MOUSEBUTTONDOWN) { // 如果事件类型是鼠标按下
                int x = event.button.x; // 获取鼠标点击的x坐标
                int y = event.button.y; // 获取鼠标点击的y坐标
                if (x >= rect4.x && x <= rect4.x + rect4.w && y >= rect4.y && y <= rect4.y + rect4.h) { // 检查鼠标点击是否在rect4区域内
                    running = false; // 设置渲染循环结束
                }
            }
        }

        // 渲染逻辑
        SDL_RenderClear(renderer); // 清空渲染器，准备渲染下一帧
        SDL_RenderCopy(renderer, tex_surf2, NULL, &rect2); // 将tex_surf2纹理绘制到rect2区域
        SDL_RenderCopy(renderer, tex_surf3, NULL, &rect3); // 将tex_surf3纹理绘制到rect3区域
        SDL_RenderCopy(renderer, tex_surf, NULL, &rect); // 将tex_surf3纹理绘制到rect区域
        SDL_RenderCopy(renderer, tex_surf4, NULL, &rect4); // 将tex_surf4纹理绘制到rect4区域


        // 展示渲染结果
        SDL_RenderPresent(renderer); // 将渲染的内容展示到屏幕上
    }



    // 创建控制台窗口以输入用户名和密码
    CreateConsoleWindow("Login"); // 创建标题为"Login"的控制台窗口

    // 输入用户名和密码
    string inputName, inputKey; // 定义用户名和密码变量
    bool validInput = false; // 定义有效输入的标志变量
    while (!validInput) { // 如果输入无效，则循环
        cout << "Enter username: "; // 提示输入用户名
        getline(cin, inputName); // 读取一行输入作为用户名
        cout << "Enter key: "; // 提示输入密钥
        getline(cin, inputKey); // 读取一行输入作为密钥

        if (inputName == correctName && inputKey == correctKey) 
        { // 如果用户名和密钥正确
            validInput = true; // 设置有效输入标志为真
            // 登录成功后的代码可以在这里添加
                // 登录成功后，可以创建用户窗口
            User loggedInUser; // 创建一个User对象
            loggedInUser.name = inputName; // 设置User对象的用户名
            loggedInUser.key = inputKey; // 设置User对象的密钥
            loggedInUser.type = 0; // 设置User对象的用户类型为管理员
            SDL_Window* userWin = CreateUserWindow(loggedInUser); // 根据User对象创建窗口


if (userWin) {
    // 获取窗口的宽度和高度
    int windowWidth, windowHeight;
    SDL_GetWindowSize(userWin, &windowWidth, &windowHeight);

    // 计算左侧和右侧区域的宽度
    int leftWidth = windowWidth / 4;
    int rightWidth = windowWidth - leftWidth;
    // 右侧五个矩形的宽度和高度
    int rectWidth = (rightWidth - 4 * 10) / 5; // 减去一些边距
    int rectHeight = (windowHeight / 2 - 2 * 10) / 2; // 减去一些边距

    // 创建一个渲染器
    SDL_Renderer* userRenderer = SDL_CreateRenderer(userWin, -1, SDL_RENDERER_ACCELERATED);
    if (!userRenderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(userWin); // 销毁用户窗口
        return -1; // 渲染器创建失败，返回错误代码
    }

    // 加载字体
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Candara.ttf", 18);
    if (!font) {
        SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
        SDL_DestroyRenderer(userRenderer);
        SDL_DestroyWindow(userWin); // 销毁用户窗口
        return -1; // 字体加载失败，返回错误代码
    }

    // 渲染循环
    bool userRunning = true;
    while (userRunning) {
        SDL_Event event;
        // 处理所有事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                userRunning = false; // 用户请求关闭窗口
            }
           
        }

        // 渲染逻辑
        SDL_RenderClear(userRenderer); // 清空渲染器
SDL_Rect leftUpperRect = {0, 0, leftWidth, windowHeight / 2};
        SDL_SetRenderDrawColor(userRenderer, 14, 47, 41, 0); // 透明背景或设置为其他颜色
        SDL_RenderFillRect(userRenderer, &leftUpperRect);

        // 显示左侧上半部分区域的用户名和用户类型
        const int textPadding = 10; // 文字边距
        SDL_Color textColor = {255, 255, 255}; // 白色文字
        string usernameText = loggedInUser.name; // 获取用户名
        string userTypeText; // 用户类型文本，根据用户类型设置文本
        switch (loggedInUser.type) {
            case 0:
                userTypeText = "Administrator";
                break;
            case 1:
                userTypeText = "Teacher";
                break;
            case 2:
                userTypeText = "Student";
                break;
            default:
                userTypeText = "Unknown";
                break;
        }

        // 创建用户名和用户类型文本的表面
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, usernameText.c_str(), textColor);
        SDL_Surface* userTypeSurface = TTF_RenderText_Solid(font, userTypeText.c_str(), textColor);
        if (textSurface && userTypeSurface) {
            // 将文本表面转换为纹理
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(userRenderer, textSurface);
            SDL_Texture* userTypeTexture = SDL_CreateTextureFromSurface(userRenderer, userTypeSurface);
            if (textTexture && userTypeTexture) {
                // 计算文本渲染位置
                SDL_Rect textRect = {leftUpperRect.x + textPadding, leftUpperRect.y + textPadding, textSurface->w, textSurface->h};
                SDL_Rect userTypeRect = {leftUpperRect.x + textPadding, leftUpperRect.y + textSurface->h + 2 * textPadding, userTypeSurface->w, userTypeSurface->h};

                // 渲染文本
                SDL_RenderCopy(userRenderer, textTexture, NULL, &textRect);
                SDL_RenderCopy(userRenderer, userTypeTexture, NULL, &userTypeRect);
            }
            // 清理
            SDL_FreeSurface(textSurface);
            SDL_FreeSurface(userTypeSurface);
            SDL_DestroyTexture(textTexture);
            SDL_DestroyTexture(userTypeTexture);
        } else {
            SDL_Log("TTF_RenderText_Solid failed: %s", SDL_GetError());
        }

        // 填充左侧区域和右侧五个矩形
        for (int i = 0; i < 5; ++i) {
            int x = leftWidth + 10 + i * (rectWidth + 10); // 加边距
            int y = 10; // 顶部边距
            SDL_Rect rect = { x, y, rectWidth, rectHeight };
            
            // 根据 user.type 设置颜色和文本
            SDL_Color color;
            string buttonText;
            switch (loggedInUser.type) {
                case 0: // 管理员
                    switch (i) {
                        case 0: color = {255, 0, 0}; buttonText = "UserADMIN"; break;
                        case 1: color = {0, 255, 0}; buttonText = "BookADMIN"; break;
                        case 2: color = {128, 0, 128}; buttonText = "HaveBorrowed"; break;
                        case 3: color = {100, 100, 100}; buttonText = "SumStar"; break;
                        case 4: color = {255, 105, 180}; buttonText = "Myself"; break;
                    }
                    break;
                case 1: // 教师
                case 2: // 学生
                    switch (i) {
                        case 0: color = {255, 0, 0}; buttonText = "BorrowBook"; break;
                        case 1: color = {0, 255, 0}; buttonText = "ReturnBook"; break;
                        case 2: color = {128, 0, 128}; buttonText = "HaveBorrowed"; break;
                        case 3: color = {100, 100, 100}; buttonText = "SumStar"; break;
                        case 4: color = {255, 105, 180}; buttonText = "Myself"; break;
                    }
                    break;
                default:
                    color = {0, 0, 0}; buttonText = "未知"; break;
            }

            // 填充矩形颜色
            SDL_SetRenderDrawColor(userRenderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(userRenderer, &rect);

            // 渲染文本到矩形中心
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), {255, 255, 255});
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(userRenderer, textSurface);
                if (textTexture) {
                    // 计算文本渲染的中心位置
                    int textX = x + (rectWidth - textSurface->w) / 2;
                    int textY = y + (rectHeight - textSurface->h) / 2;
                    SDL_Rect textRect = { textX, textY, textSurface->w, textSurface->h };
                    SDL_RenderCopy(userRenderer, textTexture, NULL, &textRect);
                }
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }

        // 展示渲染结果
        SDL_RenderPresent(userRenderer);
        bool userRunning = true;
    while (userRunning) {
        SDL_Event event;
        string newWindowTitle; // 用于存储新窗口的标题

        // 处理所有事件
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                userRunning = false; // 用户请求关闭窗口
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // 检测点击区域并设置新窗口标题
                for (int i = 0; i < 5; ++i) 
                {
                int rectX = leftWidth + 10 + i * (rectWidth + 10);
                int rectY = 10;
                SDL_Rect rect = { rectX, rectY, rectWidth, rectHeight };
                if (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h) {
                 // 根据用户类型设置窗口标题
                    switch (loggedInUser.type) {
                        case 0: // 管理员
                            switch (i) {
                                case 0: newWindowTitle = "UserADMIN"; break;
                                case 1: newWindowTitle = "BookADMIN"; break;
                                case 2: newWindowTitle = "HaveBorrowed"; break;
                                case 3: newWindowTitle = "SumStar"; break;
                                case 4: newWindowTitle = "Myself"; break;
                            }
                            break;
                        case 1: // 教师
                        case 2: // 学生
                            switch (i) {
                                case 0: newWindowTitle = "BorrowBook"; break;
                                case 1: newWindowTitle = "ReturnBook"; break;
                                case 2: newWindowTitle = "HaveBorrowed"; break;
                                case 3: newWindowTitle = "SumStar"; break;
                                case 4: newWindowTitle = "Myself"; break;
                            }
                            break;
                        default:
                            // 如果用户类型未知，不设置窗口标题
                            break;
                    }
                    break; // 退出循环，因为我们只处理第一个点击的矩形
                }
            }

                // 如果设置了新窗口标题，则创建新窗口
if (!newWindowTitle.empty()) {
    SDL_Window* newWindow = CreateNewWindow(newWindowTitle);
    if (newWindow) {
        SDL_Renderer* renderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
            SDL_DestroyWindow(newWindow);
            return -1;
        }

        TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Candara.ttf", 18); // 加载字体
        if (!font) {
            SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(newWindow);
            return -1;
        }

        SDL_Color textColor = {255, 255, 255}; // 白色文字

        // 根据窗口标题绘制不同的内容
        int windowWidth, windowHeight;
        SDL_GetWindowSize(newWindow, &windowWidth, &windowHeight);
        int rectHeight = windowHeight / 3;

if (newWindowTitle == "HaveBorrowed") {
    // 定义每个矩形区域的颜色
    SDL_Color colors[] = {
        {128, 128, 128}, // 灰色
        {0, 0, 0},       // 黑色
        {0, 0, 255}      // 蓝色
    };
    // 定义每个矩形中的文本
    string texts[] = {
        "bookname", 
        "borrow'date", 
        "borrow'user"
    };

    // 获取窗口尺寸
    int windowWidth, windowHeight;
    SDL_GetWindowSize(newWindow, &windowWidth, &windowHeight);

    // 计算每个矩形的高度，这里假设窗口高度可以被3整除
    int rectHeight = windowHeight / 3;

    // 绘制三个矩形区域并填充文本内容
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect = {0, i * rectHeight, windowWidth, rectHeight};
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 渲染文本到矩形中心
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, texts[i].c_str(), textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                // 计算文本渲染的中心位置
                int textX = windowWidth / 2; // 水平居中
                int textY = rect.y + (rectHeight - textSurface->h) / 2; // 垂直居中
                SDL_Rect textRect = {textX - textSurface->w / 2, textY, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
} 
else if (newWindowTitle == "SumStar") {
            // 绘制一个矩形区域并填充文本内容
            SDL_Color color = {128, 128, 128}; // 灰色
            string text = "bookname and star";
            SDL_Rect rect = {0, 0, windowWidth, windowHeight};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &rect);
            // 渲染文本
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
                    SDL_Rect textRect = {(rect.w - textSurface->w) / 2, (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                }
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        } 
        else if (newWindowTitle == "Myself") {
            // 绘制三个矩形区域（灰色，黑色，蓝色）
    // 依次为生成窗口区域的1/3并从上到下纵向排列
    int rectHeight = windowHeight / 3; // 每个矩形的高度
    string texts[] = {"user'name", "user'type", "user'key"};
    SDL_Color colors[] = {
        {128, 128, 128}, // 灰色
        {0, 0, 0},       // 黑色
        {0, 0, 255}      // 蓝色
    };

    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect = {0, i * rectHeight, windowWidth, rectHeight};
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 渲染文本到矩形中心
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, texts[i].c_str(), textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                int textX = windowWidth / 2; // 假设文本水平居中
                int textY = rect.y + (rectHeight - textSurface->h) / 2; // 垂直居中
                SDL_Rect textRect = {textX - textSurface->w / 2, textY, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
        } 
else if (newWindowTitle == "UserADMIN" || newWindowTitle == "BookADMIN") {
    // 定义矩形区域的颜色
    SDL_Color colors[] = {
        {255, 0, 0},   // 红色
        {0, 255, 0},   // 绿色
        {0, 0, 255}    // 蓝色
    };
    // 定义按钮文本
    const char* buttonTexts[] = {"add", "delete", "look"}; // 使用字符指针数组

    // 获取窗口尺寸
    int windowWidth, windowHeight;
    SDL_GetWindowSize(newWindow, &windowWidth, &windowHeight);

    // 计算每个矩形的高度，这里假设窗口高度可以被3整除
    int rectHeight = windowHeight / 3;

    // 绘制三个矩形区域并填充文本内容
    for (int i = 0; i < 3; ++i) {
        SDL_Rect rect = {0, rectHeight * i, windowWidth, rectHeight};
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 渲染文本到矩形中心
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonTexts[i], textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                // 计算文本渲染的中心位置
                int textX = windowWidth / 2 - textSurface->w / 2; // 水平居中
                int textY = rect.y + (rectHeight - textSurface->h) / 2; // 垂直居中
                SDL_Rect textRect = {textX, textY, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
}
else if (newWindowTitle == "BorrowBook" || newWindowTitle == "ReturnBook") {
            // 绘制一个矩形区域并填充文本内容
            string text = "book'name";
            SDL_Color color = {128, 128, 128}; // 灰色
            SDL_Rect rect = {0, 0, windowWidth, windowHeight};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &rect);
            // 渲染文本
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
                    SDL_Rect textRect = {(rect.w - textSurface->w) / 2, (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                }
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }   
        
            // 展示渲染结果
        SDL_RenderPresent(renderer);

        // 清理资源
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
    } 

    
    newWindowTitle.clear(); // 清空标题，以便下次点击使用
}
            }
        }

    }
            // 清理资源
    TTF_CloseFont(font); // 关闭字体
    SDL_DestroyRenderer(userRenderer); // 销毁渲染器
    SDL_DestroyWindow(userWin); // 销毁用户窗口


    }

}


}
    // 清理资源
    SDL_FreeSurface(bmp_surf); // 释放bmp_surf位图资源
    SDL_FreeSurface(bmp_surf2); // 释放bmp_surf2位图资源
    SDL_FreeSurface(bmp_surf3); // 释放bmp_surf3位图资源
    SDL_FreeSurface(bmp_surf4); // 释放bmp_surf4位图资源
    TTF_CloseFont(font); // 释放加载的字体资源
    SDL_DestroyTexture(tex_surf); // 销毁纹理资源
    SDL_DestroyTexture(tex_surf2); // 销毁纹理资源
    SDL_DestroyTexture(tex_surf3); // 销毁纹理资源
    SDL_DestroyTexture(tex_surf4); // 销毁纹理资源
    SDL_DestroyRenderer(renderer); // 销毁渲染器资源
    SDL_DestroyWindow(win); // 销毁窗口资源
    TTF_Quit(); // 退出TTF库
    SDL_Quit(); // 退出SDL库
    return 0; // 正常退出程序，返回0
}
}


