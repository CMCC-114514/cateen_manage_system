#ifndef GLOBAL_H
#define GLOBAL_H

#include "consumptionrecord.h"

// =================== 宏定义 ===================
#define MAX_CARDS    1000   // 最多支持 1000 张学生卡
#define MAX_DISHES   200    // 最多支持 200 种菜品
#define MAX_RECORDS  5000   // 最多保存 5000 条消费记录
#define ACTIVE 0   // 正常状态，可消费
#define LOST   1   // 挂失状态，禁止使用

extern StudentCard cards[MAX_CARDS];
extern int cardCount;
extern Dish dishes[MAX_DISHES];
extern int dishCount;
extern ConsumptionRecord records[MAX_RECORDS];
extern int recordCount;
extern const char* ADMIN_PASSWORD;
extern int currentCard;

#endif // !GLOBAL_H

