#include <D:\github's hub\superbookmanagesysterm\include\head.h>





// 假设有一个全局变量或者在合适的地方定义的成员变量来控制渐变进度
float gradientProgress = 0.0f; // 渐变进度从0到1

// 渐变动画函数
void gradientAnimation(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color startColor, SDL_Color endColor, int duration) {
    int steps = 100; // 渐变步数
    int delay = duration / (steps * 6); // 每步的延迟时间

    for (int i = 0; i < steps; ++i) {
        float t = static_cast<float>(i) / (steps - 1);
        Uint8 r = startColor.r + t * (endColor.r - startColor.r);
        Uint8 g = startColor.g + t * (endColor.g - startColor.g);
        Uint8 b = startColor.b + t * (endColor.b - startColor.b);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
}

// 创建一个函数来渲染文本到按钮上
void RenderButtonText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Rect buttonRect = {350, 550, 200, 80}; // 调整按钮位置和大小
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            SDL_Rect textRect = {x + (buttonRect.w - textSurface->w) / 2, y + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}
// 绘制按钮的函数
void DrawButton(SDL_Renderer* renderer, SDL_Rect button, bool isPressed, const char* buttonText, TTF_Font* font, SDL_Color textColor) {
    // 根据是否按下改变按钮背景色
    SDL_Color buttonBackgroundColor;
    if (isPressed) {
        buttonBackgroundColor = {128, 128, 128}; // 按下时颜色变深
    } else {
        buttonBackgroundColor = {200, 200, 200}; // 未按下时使用浅灰色
    }

    // 绘制按钮背景
    SDL_SetRenderDrawColor(renderer, buttonBackgroundColor.r, buttonBackgroundColor.g, buttonBackgroundColor.b, 255);
    SDL_RenderFillRect(renderer, &button);

    // 根据背景色选择对比度高的文本颜色
    if (isPressed) {
        textColor = {255, 255, 255}; // 背景色深时使用白色文本
    } else {
        textColor = {0, 0, 0}; // 背景色浅时使用黑色文本
    }

    // 创建文本表面并转换为纹理
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {button.x + (button.w - textSurface->w) / 2, button.y + (button.h - textSurface->h) / 2, textSurface->w, textSurface->h};

    // 渲染文本
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // 清理
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}
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
    BuildIndex();
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
        User loggedInUser= logIn();
            SDL_Window* userWin = CreateUserWindow(loggedInUser); // 根据User对象创建窗口


if (userWin) {
    // 获取窗口的宽度和高度
int windowWidth, windowHeight;
SDL_GetWindowSize(userWin, &windowWidth, &windowHeight);

// 计算左侧和右侧区域的宽度
int leftWidth = windowWidth / 4;
int rightWidth = windowWidth - leftWidth;
// 右侧五个矩形的宽度和高度
int rectWidth = (rightWidth - 3*10) / 5; // 减去一些边距
int rectHeight = windowHeight - 4*10; // 设置矩形高度为窗口高度减去上下边距


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

    // 美化左侧上半部分区域
    SDL_Rect leftUpperRect = {0, 0, leftWidth, windowHeight};
    SDL_SetRenderDrawColor(userRenderer, 14, 47, 41, 255); // 设置背景颜色
    SDL_RenderFillRect(userRenderer, &leftUpperRect);

    // 美化用户名和用户类型文本渲染
    const int textPadding = 10; // 文字边距
    SDL_Color textColor = {255, 255, 255}; // 白色文字
    string usernameText = loggedInUser.name; // 获取用户名
    string userTypeText; // 用户类型文本，根据用户类型设置文本
switch (loggedInUser.type) {
    case 0:
        userTypeText = "Administrator";
        // 可以为管理员选择一个特定的颜色，例如深蓝色
        textColor = {221, 0, 139};
        break;
    case 1:
        userTypeText = "Teacher";
        // 为教师选择一个特定的颜色，例如绿色
        textColor = {23, 0, 233};
        break;
    case 2:
        userTypeText = "Student";
        // 为学生选择一个特定的颜色，例如橙色
        textColor = {255, 69, 0};
        break;
    default:
        userTypeText = "Unknown";
        // 未知用户类型使用默认颜色
        textColor = textColor;
        break;
}

  // 创建用户名和用户类型文本的表面，并美化
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, usernameText.c_str(), textColor);
    SDL_Surface* userTypeSurface = TTF_RenderText_Solid(font, userTypeText.c_str(), textColor);
    if (textSurface && userTypeSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(userRenderer, textSurface);
        SDL_Texture* userTypeTexture = SDL_CreateTextureFromSurface(userRenderer, userTypeSurface);
        if (textTexture && userTypeTexture) {
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
            case 0: color = {255, 235, 205}; buttonText = "UserADMIN"; break; // 浅粉色
            case 1: color = {224, 255, 255}; buttonText = "BookADMIN"; break; // 浅蓝色
            case 2: color = {173, 216, 230}; buttonText = "HaveBorrowed"; break; // 浅紫色
            case 3: color = {190, 190, 190}; buttonText = "SumStar"; break; // 灰色
            case 4: color = {112, 239, 213}; buttonText = "Myself"; break; // 浅珊瑚色
        }
        break;
    case 1: // 教师
    case 2: // 学生
        switch (i) {
            case 0: color = {255, 193, 193}; buttonText = "BorrowBook"; break; // 浅红色
            case 1: color = {210, 255, 185}; buttonText = "ReturnBook"; break; // 浅绿色
            case 2: color = {218, 188, 255}; buttonText = "HaveBorrowed"; break; // 浅紫色
            case 3: color = {190, 190, 190}; buttonText = "SumStar"; break; // 灰色
            case 4: color = {112, 228, 225}; buttonText = "Myself"; break; // 浅珊瑚色
        }
        break;
    default:
        color = {0, 0, 0}; buttonText = "未知"; break;
}
    // 使用渐变色填充矩形
    SDL_Color startColor = {
    (color.r ) ,  
    (color.g ) ,
    (color.b ) 
};
SDL_Color endColor = {
    color.r / 2,  // 直接对Uint8类型进行除以2操作
    color.g / 2,  // 同上
    color.b / 2   // 同上
};
    gradientAnimation(userRenderer, rect, startColor, endColor, 1000); // 调用渐变动画函数
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

        TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\Candara.ttf", 54); // 加载字体
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

if (newWindowTitle == "BorrowBook") {
 // 创建按钮
SDL_Rect borrowButton = {0, 0, windowWidth, rectHeight};
SDL_Rect returnButton = {0, rectHeight, windowWidth, rectHeight};
// 定义按钮状态变量
bool isBorrowButtonPressed = false;
bool isReturnButtonPressed = false;
bool bquit = false;
SDL_Event e;
std::string outputText = "";
while (!bquit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            bquit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            // 检测点击了Borrow按钮
            if (x >= borrowButton.x && x <= borrowButton.x + borrowButton.w && y >= borrowButton.y && y <= borrowButton.y + borrowButton.h) {
                isBorrowButtonPressed = true;
            } else if (x >= returnButton.x && x <= returnButton.x + returnButton.w && y >= returnButton.y && y <= returnButton.y + returnButton.h) {
                isReturnButtonPressed = true;
            }
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            if (isBorrowButtonPressed) {
                // Borrow按钮被点击
                string consoleTitle = "Console for " + string(newWindowTitle) + " " + "BorrowBook";
                CreateConsoleWindow(consoleTitle);
                BorrowBook(loggedInUser,getCurrentDateTime());
                isBorrowButtonPressed = false;
                SDL_Delay(100); // 延时100毫秒
                SDL_DestroyWindow(newWindow); 
                SDL_DestroyRenderer(renderer);// 关闭窗口
                bquit=true;
                break;
            } else if (isReturnButtonPressed) {
                // Return按钮被点击
                SDL_Delay(100); // 延时100毫秒
                SDL_DestroyWindow(newWindow);
                SDL_DestroyRenderer(renderer);
                bquit=true;
               break;
            }
            isReturnButtonPressed = false;
        }
    }

    // 绘制按钮
    DrawButton(renderer, borrowButton, isBorrowButtonPressed, "Borrow", font, textColor);
    DrawButton(renderer, returnButton, isReturnButtonPressed, "Back", font, textColor);
    SDL_RenderPresent(renderer);
}


}
if (newWindowTitle == "ReturnBook") {
 // 创建按钮
SDL_Rect borrowButton = {0, 0, windowWidth, rectHeight};
SDL_Rect returnButton = {0, rectHeight, windowWidth, rectHeight};
// 定义按钮状态变量
bool isBorrowButtonPressed = false;
bool isReturnButtonPressed = false;
bool bquit = false;
SDL_Event e;
std::string outputText = "";
while (!bquit) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            bquit = true;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            // 检测点击了Borrow按钮
            if (x >= borrowButton.x && x <= borrowButton.x + borrowButton.w && y >= borrowButton.y && y <= borrowButton.y + borrowButton.h) {
                isBorrowButtonPressed = true;
            } else if (x >= returnButton.x && x <= returnButton.x + returnButton.w && y >= returnButton.y && y <= returnButton.y + returnButton.h) {
                isReturnButtonPressed = true;
            }
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            if (isBorrowButtonPressed) {
                // Borrow按钮被点击
                string consoleTitle = "Console for " + string(newWindowTitle) + " " + "ReturnBook";
                CreateConsoleWindow(consoleTitle);
                returnBook(loggedInUser);
                isBorrowButtonPressed = false;
                    SDL_Delay(100); // 延时100毫秒
    SDL_DestroyWindow(newWindow); // 关闭窗口
    SDL_DestroyRenderer(renderer);
                bquit=true;
                break;
            } else if (isReturnButtonPressed) {
                // back按钮被点击
                SDL_Delay(100); // 延时100毫秒
                SDL_DestroyWindow(newWindow);
                SDL_DestroyRenderer(renderer);
                bquit=true;
               break;
            }
            isReturnButtonPressed = false;
        }
    }

    // 绘制按钮
    DrawButton(renderer, borrowButton, isBorrowButtonPressed, "returnbook", font, textColor);
    DrawButton(renderer, returnButton, isReturnButtonPressed, "back", font, textColor);
    SDL_RenderPresent(renderer);
}

}
if (newWindowTitle == "HaveBorrowed" && (loggedInUser.type == 0 )) {





    list<string> borrowedBookList = lookBorrowbook_man(loggedInUser);

    // 遍历字符串列表，将非空子串输出到窗口中，每输出一个子串就会自动换行
    int y = 10; // 起始y坐标，根据需要调整
    for (const auto& bookStr : borrowedBookList) {
        if (!bookStr.empty()) {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, bookStr.c_str(), textColor);
            if (textSurface) {
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_Rect textRect = {10, y, textSurface->w, textSurface->h}; // x坐标为10，根据需要调整
                    y += textSurface->h;
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
    }

    // 在窗口底部添加一个按钮用来退出窗口
    SDL_Rect buttonRect = {350, 550, 200, 80}; // 调整按钮位置和大小
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(renderer, &buttonRect);
    // 在绘制按钮之后，调用这个函数来渲染"back"文本
RenderButtonText(renderer, font, "back", textColor, buttonRect.x, buttonRect.y);
    SDL_RenderPresent(renderer);

    // 事件循环
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    SDL_Delay(100); // 延时100毫秒
                    SDL_DestroyWindow(newWindow);
                    SDL_DestroyRenderer(renderer);
                    quit = true;
                    break;
                }
            }
        }
    }
}

if (newWindowTitle == "HaveBorrowed" && (loggedInUser.type == 1 || loggedInUser.type == 2)) {





    list<string> borrowedBookList = lookBorrowbook_stu(loggedInUser);

    // 遍历字符串列表，将非空子串输出到窗口中，每输出一个子串就会自动换行
    int y = 10; // 起始y坐标，根据需要调整
    for (const auto& bookStr : borrowedBookList) {
        if (!bookStr.empty()) {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, bookStr.c_str(), textColor);
            if (textSurface) {
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_Rect textRect = {10, y, textSurface->w, textSurface->h}; // x坐标为10，根据需要调整
                    y += textSurface->h;
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
    }

    // 在窗口底部添加一个按钮用来退出窗口
    SDL_Rect buttonRect = {350, 550, 200, 80}; // 调整按钮位置和大小
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(renderer, &buttonRect);
    // 在绘制按钮之后，调用这个函数来渲染"back"文本
RenderButtonText(renderer, font, "back", textColor, buttonRect.x, buttonRect.y);
    SDL_RenderPresent(renderer);


    // 事件循环
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    SDL_Delay(100); // 延时100毫秒
                    SDL_DestroyWindow(newWindow);
                    SDL_DestroyRenderer(renderer);
                    quit = true;
                    break;
                }
            }
        }
    }
}



else if (newWindowTitle == "SumStar") {
    // 调用 Rank 函数获取排名信息
    list<string> p = Rank();
    
    // 确保字体已加载
    if (!font) {
        SDL_Log("字体加载失败");
        return -1; // 字体加载失败，返回错误代码
    }

    // 绘制一个矩形区域并填充文本内容
    SDL_Color color = {128, 128, 128}; // 灰色
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, NULL); // 使用 NULL 来填充整个渲染目标

    // 获取窗口宽度和高度
    int windowWidth = 800; // 假设窗口宽度为800
    int windowHeight = 600; // 假设窗口高度为600

    // 渲染窗口标题 "SumStar:"
    string titleText = "SumStar:";
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, titleText.c_str(), textColor);
    if (!titleSurface) {
        SDL_Log("渲染标题失败");
        return -1;
    }
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    if (!titleTexture) {
        SDL_Log("创建标题纹理失败");
        SDL_FreeSurface(titleSurface);
        return -1;
    }
    SDL_QueryTexture(titleTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_Rect titleRect = {0, 0, rect.w, rect.h};
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);
SDL_Rect textRect = {0, 0, 0, 0}; // 初始化文本渲染区域
SDL_Rect lineRect = {0, 0, 0, 0}; // 初始化行号渲染区域
    // 初始化y坐标，以便排名信息从标题下方开始渲染
    int y = rect.h; // 标题的高度

    // 遍历排名信息并渲染每个文本项及其行号
    int line_number = 1; // 行号起始值
    for (const string& textLine : p) {
        // 创建文本表面和纹理
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, textLine.c_str(), textColor);
        if (!textSurface) {
            SDL_Log("创建文本表面失败");
            continue;
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            SDL_Log("创建文本纹理失败");
            SDL_FreeSurface(textSurface);
            continue;
        }
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

        // 设置文本渲染区域
        textRect.x = 10; // 左边距
        textRect.y = y;

        // 渲染文本
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // 计算行号字符串宽度
        char line_number_str[10];
        sprintf(line_number_str, "%d", line_number);
        SDL_Surface* lineSurface = TTF_RenderText_Solid(font, line_number_str, textColor);
        if (lineSurface) {
            SDL_Texture* lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);
            if (lineTexture) {
                SDL_QueryTexture(lineTexture, NULL, NULL, &lineRect.w, &lineRect.h);

                // 设置行号渲染区域，位于窗口的最右端，与文本行垂直居中对齐
                lineRect.x = windowWidth - lineRect.w - 10; // 右边距
                lineRect.y = y + (textRect.h - lineRect.h) / 2;

                // 渲染行号
                SDL_RenderCopy(renderer, lineTexture, NULL, &lineRect);
                SDL_DestroyTexture(lineTexture);

            }
            SDL_FreeSurface(lineSurface);
        }

        // 更新y坐标以便于下一个文本项的渲染
        y += textRect.h;
        line_number++;

        // 清理纹理
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }

        // 在窗口底部添加一个按钮用来退出窗口
    SDL_Rect buttonRect = {350, 550, 200, 80}; // 调整按钮位置和大小
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(renderer, &buttonRect);
    // 在绘制按钮之后，调用这个函数来渲染"back"文本
RenderButtonText(renderer, font, "back", textColor, buttonRect.x, buttonRect.y);
    SDL_RenderPresent(renderer);


    // 事件循环
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    SDL_Delay(100); // 延时100毫秒
                    SDL_DestroyWindow(newWindow);
                    quit = true;
                    break;
                }
            }
        }
    }


}


else if (newWindowTitle == "Myself") {
    // 定义矩形区域的颜色
    SDL_Color colors[] = {
        {128, 128, 128}, // 灰色
        {0, 0, 0},       // 黑色
        {66, 66, 255}      // 蓝色
    };
    // 定义每个矩形区域的文本内容
    string texts[] = {
        loggedInUser.name,   // 用户名
        (loggedInUser.type == 0 ? "Administrator" : loggedInUser.type == 1 ? "Teacher" : loggedInUser.type == 2 ? "Student" : "Unknown"), // 用户类型
        loggedInUser.key     // 用户密钥
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
        // 在窗口底部添加一个按钮用来退出窗口
    SDL_Rect buttonRect = {350, 550, 200, 80}; // 调整按钮位置和大小
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(renderer, &buttonRect);
    // 在绘制按钮之后，调用这个函数来渲染"back"文本
RenderButtonText(renderer, font, "back", textColor, buttonRect.x, buttonRect.y);
    SDL_RenderPresent(renderer);


    // 事件循环
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    SDL_Delay(100); // 延时100毫秒
                    SDL_DestroyWindow(newWindow);
                    SDL_DestroyRenderer(renderer);
                    quit = true;
                    break;
                }
            }
        }
    }
    

}








else if (newWindowTitle == "UserADMIN" || newWindowTitle == "BookADMIN") {
    // 定义矩形区域的颜色
    SDL_Color colors[] = {
        {0, 139, 139},   
        {0, 206, 209},   
        {212, 242, 231},  
        {211, 212, 204} 
    };
    // 定义按钮文本
    const char* buttonTexts[] = {"add", "delete", "look", "return"};

    // 获取窗口尺寸
    int windowWidth, windowHeight;
    SDL_GetWindowSize(newWindow, &windowWidth, &windowHeight);

    // 计算每个矩形的高度，这里假设窗口高度可以被4整除
    int rectHeight = windowHeight / 4;

    // 创建和显示四个矩形
    for (int i = 0; i < 4; ++i) {
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
SDL_RenderCopy(renderer, textTexture, NULL, &textRect);            }
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
    SDL_RenderPresent(renderer);

bool running = true;
while (running) {
    SDL_Event event;
    // 处理所有事件
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false; // 用户请求关闭窗口
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // 检查是否点击了按钮
for (int i = 0; i < 4; ++i) {
    SDL_Rect rect = {0, rectHeight * i, windowWidth, rectHeight};
    if (event.button.x >= rect.x && event.button.x < rect.x + rect.w &&
        event.button.y >= rect.y && event.button.y < rect.y + rect.h) {
        // 根据点击的按钮执行对应的操作
if (buttonTexts[i] == "return") {

    SDL_Delay(100); // 延时100毫秒
    SDL_DestroyWindow(newWindow); // 关闭窗口
    SDL_DestroyRenderer(renderer);
    running = false; // 设置running为false以退出循环
    break; // 跳出循环
} else {
            // 根据点击的按钮创建新的控制台窗口
        string consoleTitle = "Console for " + string(newWindowTitle) + " " + buttonTexts[i];
        CreateConsoleWindow(consoleTitle);

        // 根据点击的按钮执行对应的函数
if (newWindowTitle == "UserADMIN") {
    if (buttonTexts[i] == "add") {
        addUser();
    } else if (buttonTexts[i] == "delete") {
        deleteUser();
    } else if (buttonTexts[i] == "look") {
        lookUser();
    }
    SDL_Delay(100); // 延时100毫秒
    SDL_DestroyWindow(newWindow); // 关闭窗口
    SDL_DestroyRenderer(renderer);
    running = false; // 设置running为false以退出循环
    break; // 跳出循环
} else if (newWindowTitle == "BookADMIN") {
    if (buttonTexts[i] == "add") {
        addBook();
    } else if (buttonTexts[i] == "delete") {
        //deleteBook();  // For BookADMIN's delete logic
    } else if (buttonTexts[i] == "look") {
        lookBook();  // For BookADMIN's view logic
    }
    SDL_Delay(100); // 延时100毫秒
    SDL_DestroyWindow(newWindow); // 关闭窗口
    SDL_DestroyRenderer(renderer);
    running = false; // 设置running为false以退出循环
    break; // 跳出循环
}
        break; // 跳出循环
    }
}
                }
            }
        }
    }
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