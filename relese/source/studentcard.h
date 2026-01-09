#ifndef STUDENTCARD_H
#define STUDENTCARD_H

#define ID_LEN       20     // 卡号编号最大长度（含 '\0'）
#define NAME_LEN     50     // 姓名最大长度（含 '\0'）

#define _CRT_SECURE_NO_WARNINGS // 忽略 VS2022 对 scanf 等函数的安全警告
#include <stdio.h>
#include <string.h>
#include "tool.h"

// 学生就餐卡信息结构体
typedef struct {
    char cardId[ID_LEN];     // 卡号，如 "B27081012"
    char name[NAME_LEN];     // 学生姓名
    double balance;          // 当前余额（单位：元）
    int status;              // 卡状态：0=正常(ACTIVE)，1=挂失(LOST)
} StudentCard;

void studentLogin();
void showAllDishes();
void showRecord();
void balanceResearch();
void dishBuy(int i);

#endif // !STUDENTCARD_H