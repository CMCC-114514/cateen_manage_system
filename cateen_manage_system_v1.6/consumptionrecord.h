#ifndef CONSUMPTIONRECORD_H
#define CONSUMPTIONRECORD_H

#include "studentcard.h"
#include "dish.h"

// 消费记录结构体
typedef struct {
    char cardId[ID_LEN];         // 消费的卡号
    char dishId[DISHID_LEN];     // 购买的菜品编号
    double amount;           // 消费金额
    char timeStr[30];        // 消费时间，格式："YYYY-MM-DD HH:MM:SS"
} ConsumptionRecord;

#endif // !ADMINISTRATOR_H
