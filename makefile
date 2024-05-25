CXXFLAGS += -ID:C:\Users\Lenovo\Downloads\SDL2-devel-2.30.3-mingw\SDL2-2.30.3\x86_64-w64-mingw32\include #改成你电脑上的include路径
# CXXFLAGS += -fexec-charset=GBK -finput-charset=UTF-8
LDFLAGS +=  -LD:C:\Users\Lenovo\Downloads\SDL2-devel-2.30.3-mingw\SDL2-2.30.3\x86_64-w64-mingw32\lib  # 改成你电脑上的lib路径

CXXFLAGS += -std=c++23 
# 如果不用特别新的C++特性，上面这行不用写
LDLIBS += -lSDL2

LDLIBS += -mwindows # 用于去除运行时命令行窗口


main.exe: main.o
	$(CXX) $^ -o $(basename $@) $(LDFLAGS) $(LDLIBS)

.PHONY: run clean

run: main.exe
	$<

clean:
	$(RM) *.exe *.o