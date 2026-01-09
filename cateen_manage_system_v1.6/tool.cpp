#include "tool.h"
#include "global.h"

// 返回当前时间
char* getCurrentTimeStr() {
    static char buffer[30];
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
    return buffer;
}

// 搜索餐卡
int findCard(const char* cardId) {
    for (int i = 0; i < cardCount; i++) {
        if (strcmp(cards[i].cardId, cardId) == 0) {
            return i;
        }
    }
    return -1;
}

// 搜索菜品
int findDish(const char* dishId) {
    for (int i = 0; i < dishCount; i++) {
        if (strcmp(dishes[i].dishId, dishId) == 0) {
            return i;
        }
    }
    return -1;
}
