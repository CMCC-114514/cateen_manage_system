#define _CRT_SECURE_NO_WARNINGS
#include "interface.h"
#include "global.h"

int currentStudent = -1;
Page currentPage = PAGE_MAIN;

// 绘制按钮
void drawButton(int x1, int y1, int x2, int y2, const char* text) {
    rectangle(x1, y1, x2, y2);              //绘制矩形
    outtextxy(x1 + 20, y1 + 15, text);      //绘制文字
}

// 坐标判断是否在某矩形内（按钮判定）
int inRect(int x, int y, int x1, int y1, int x2, int y2) {
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

// 绘制主页
void drawMainPage() {
    cleardevice();

    // 标题
    settextstyle(30, 0, "黑体");
    outtextxy(230, 80, "食堂自动化管理系统");

    // 各按钮
    settextstyle(20, 0, "黑体");
    drawButton(300, 200, 500, 250, "管理员登录");
    drawButton(300, 280, 500, 330, "学生登录");
    drawButton(300, 360, 500, 410, "退出系统");
}

// 绘制管理员菜单
void drawAdminMenu() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(300, 80, "管理员菜单");

    settextstyle(20, 0, "黑体");
    drawButton(280, 180, 520, 230, "注册就餐卡");
    drawButton(280, 250, 520, 300, "操作就餐卡");
    drawButton(280, 320, 520, 370, "菜品管理");
    drawButton(280, 390, 520, 440, "返回主菜单");
}

// 绘制学生菜单
void drawStudentMenu() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(300, 80, "学生菜单");

    char buf[100];
    sprintf(buf, "姓名：%s   余额：%.2f 元",
        cards[currentStudent].name,
        cards[currentStudent].balance);

    settextstyle(18, 0, "黑体");
    outtextxy(200, 130, buf);

    drawButton(280, 200, 520, 250, "查看今日菜品");
    drawButton(280, 270, 520, 320, "购买菜品");
    drawButton(280, 340, 520, 390, "查询消费记录");
    drawButton(280, 410, 520, 460, "查询余额");
    drawButton(280, 480, 520, 530, "退出登录");
}

// 绘制就餐卡操作页面
void drawCardOperationPage(int cardIdx) {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(250, 50, "就餐卡操作");

    settextstyle(18, 0, "黑体");
    char info[200];
    sprintf(info, "卡号: %s | 姓名: %s",
        cards[cardIdx].cardId,
        cards[cardIdx].name);
    outtextxy(150, 100, info);

    sprintf(info, "余额: %.2f 元 | 状态: %s",
        cards[cardIdx].balance,
        cards[cardIdx].status == ACTIVE ? "正常" : "已挂失");
    outtextxy(150, 130, info);

    settextstyle(20, 0, "黑体");
    drawButton(150, 180, 650, 230, "1. 充值");
    drawButton(150, 240, 650, 290, "2. 挂失");
    drawButton(150, 300, 650, 350, "3. 取消挂失");
    drawButton(150, 360, 650, 410, "4. 查看消费记录");
    drawButton(150, 420, 650, 470, "5. 返回管理员菜单");
}

// 绘制菜品管理页面
void drawDishManagementPage() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(280, 50, "菜品管理");

    settextstyle(20, 0, "黑体");
    drawButton(150, 120, 650, 170, "1. 添加菜品");
    drawButton(150, 180, 650, 230, "2. 删除菜品");
    drawButton(150, 240, 650, 290, "3. 修改菜品价格");
    drawButton(150, 300, 650, 350, "4. 查看所有菜品");
    drawButton(150, 360, 650, 410, "5. 查看销售情况");
    drawButton(150, 420, 650, 470, "6. 返回管理员菜单");
}

// 绘制所有菜品列表页面
void drawAllDishesPage() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(300, 20, "所有菜品列表");

    settextstyle(14, 0, "宋体");
    int y = 70;
    char line[100];

    // 表头
    outtextxy(50, y, "编号");
    outtextxy(150, y, "菜品名称");
    outtextxy(350, y, "价格(元)");
    outtextxy(450, y, "销量");
    y += 40;

    // 菜品列表
    for (int i = 0; i < dishCount; i++) {
        sprintf(line, "%s", dishes[i].dishId);
        outtextxy(50, y, line);

        sprintf(line, "%s", dishes[i].name);
        outtextxy(150, y, line);

        sprintf(line, "%.2f", dishes[i].price);
        outtextxy(350, y, line);

        sprintf(line, "%d", dishes[i].sales);
        outtextxy(450, y, line);

        y += 30;
        if (y > 550) {
            y = 70; // 重新开始位置
        }
    }

    // 返回按钮
    settextstyle(20, 0, "黑体");
    drawButton(300, 500, 500, 550, "返回");
}

// 绘制销售排行榜页面
void drawSalesRankingPage() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(250, 20, "菜品销售排行榜");

    // 排序处理
    int indices[MAX_DISHES];
    for (int i = 0; i < dishCount; i++) {
        indices[i] = i;
    }

    // 冒泡排序
    for (int i = 0; i < dishCount - 1; i++) {
        for (int j = 0; j < dishCount - 1 - i; j++) {
            if (dishes[indices[j]].sales < dishes[indices[j + 1]].sales) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    settextstyle(14, 0, "宋体");
    int y = 70;
    char line[100];

    // 表头
    outtextxy(50, y, "排名");
    outtextxy(100, y, "编号");
    outtextxy(200, y, "菜品名称");
    outtextxy(400, y, "价格(元)");
    outtextxy(500, y, "销量");
    y += 40;

    // 排行榜列表
    for (int rank = 0; rank < dishCount; rank++) {
        Dish* d = &dishes[indices[rank]];

        sprintf(line, "%d", rank + 1);
        outtextxy(50, y, line);

        sprintf(line, "%s", d->dishId);
        outtextxy(100, y, line);

        sprintf(line, "%s", d->name);
        outtextxy(200, y, line);

        sprintf(line, "%.2f", d->price);
        outtextxy(400, y, line);

        sprintf(line, "%d", d->sales);
        outtextxy(500, y, line);

        y += 30;
        if (y > 550) {
            y = 70; // 重新开始的位置
        }
    }

    // 返回按钮
    settextstyle(20, 0, "黑体");
    drawButton(300, 500, 500, 550, "返回");
}

// 绘制学生购买菜品页面
void drawStudentBuyPage() {
    cleardevice();
    settextstyle(25, 0, "黑体");
    outtextxy(250, 20, "购买菜品");

    settextstyle(14, 0, "宋体");
    int y = 70;
    char line[100];

    // 显示学生余额
    sprintf(line, "当前余额: %.2f 元", cards[currentStudent].balance);
    outtextxy(50, 50, line);

    // 表头
    outtextxy(50, y, "编号");
    outtextxy(150, y, "菜品名称");
    outtextxy(350, y, "价格(元)");
    outtextxy(450, y, "购买");
    y += 40;

    // 菜品列表，每个菜品带购买按钮
    for (int i = 0; i < dishCount; i++) {
        sprintf(line, "%s", dishes[i].dishId);
        outtextxy(50, y, line);

        sprintf(line, "%s", dishes[i].name);
        outtextxy(150, y, line);

        sprintf(line, "%.2f", dishes[i].price);
        outtextxy(350, y, line);

        // 购买按钮
        char btnText[20];
        sprintf(btnText, "购买%d", i);
        settextstyle(14, 0, "黑体");
        rectangle(450, y - 10, 520, y + 20);
        outtextxy(460, y, "购买");

        y += 40;
        if (y > 500) {
            y = 70; // 重新开始位置
        }
    }

    // 返回按钮
    settextstyle(20, 0, "黑体");
    drawButton(300, 520, 500, 570, "返回");
}