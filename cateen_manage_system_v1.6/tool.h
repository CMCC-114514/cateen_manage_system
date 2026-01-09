#ifndef TOOL_H
#define TOOL_H

#define _CRT_SECURE_NO_WARNINGS // 忽略 VS2022 对 scanf 等函数的安全警告
#include <string.h>
#include <stdio.h>
#include <time.h>

char* getCurrentTimeStr();
int findCard(const char* cardId);
int findDish(const char* dishId);

#endif // !TOOL_H

