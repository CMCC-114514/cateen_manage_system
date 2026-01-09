#ifndef INTERFACE_H
#define INTERFACE_H

#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib,"EasyXa.lib")
#pragma comment(lib,"EasyXw.lib")

// 页面状态
typedef enum {
    PAGE_MAIN,
    PAGE_ADMIN_MENU,
    PAGE_STUDENT_MENU,
    PAGE_CARD_OPERATION,  // 新增：就餐卡操作页面
    PAGE_DISH_MANAGEMENT, // 新增：菜品管理页面
    PAGE_ALL_DISHES,      // 新增：查看所有菜品页面
    PAGE_SALES_RANKING,   // 新增：销售排行榜页面
    PAGE_STUDENT_BUY      // 新增：学生购买菜品页面
} Page;

extern int currentStudent;
extern Page currentPage;

void drawButton(int x1, int y1, int x2, int y2, const char* text);
int inRect(int x, int y, int x1, int y1, int x2, int y2);
void drawMainPage();
void drawAdminMenu();
void drawStudentMenu();
void drawCardOperationPage(int cardIdx);
void drawDishManagementPage();
void drawAllDishesPage();
void drawSalesRankingPage();
void drawStudentBuyPage();

#endif // !INTERFACE_H
