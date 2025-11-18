# 編譯器
CC = gcc

# 目標執行檔
TARGET = 10

# 原始碼
SRC = 10.c

# SDL2 include & lib 路徑 (Homebrew)
INCLUDES = -I/opt/homebrew/opt/sdl2/include
LIBS = -L/opt/homebrew/opt/sdl2/lib -lSDL2

# 編譯參數
CFLAGS = -Wall -g $(INCLUDES)

# ========================
#       Build rules
# ========================
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean


