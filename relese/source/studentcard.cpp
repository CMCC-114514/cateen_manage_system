#include "studentcard.h"
#include "tool.h"
#include "interface.h"
#include "global.h"

// 学生登录
void studentLogin() {
    char id[ID_LEN];
    InputBox(id, ID_LEN, "请输入就餐卡号", "学生登录");
    int idx = findCard(id);
    if (idx == -1) {
        MessageBox(GetHWnd(), "卡号不存在", "错误", MB_OK);
    }
    else if (cards[idx].status == LOST) {
        MessageBox(GetHWnd(), "卡已挂失", "错误", MB_OK);
    }
    else {
        currentStudent = idx;
        currentPage = PAGE_STUDENT_MENU;
        drawStudentMenu();
    }
}

// 显示所有菜品
void showAllDishes() {
    char buf[2000] = "菜品列表：\n\n";
    for (int i = 0; i < dishCount; i++) {
        char line[100];
        sprintf(line, "%s. %s -- %.2f 元\n",
            dishes[i].dishId,
            dishes[i].name,
            dishes[i].price);
        strcat(buf, line);
    }
    MessageBox(GetHWnd(), buf, "今日菜单", MB_OK);
}

// 查看消费记录
void showRecord() {
    char buf[2000] = "您的消费记录：\n\n";
    int found = 0;
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].cardId, cards[currentStudent].cardId) == 0) {
            char dishName[NAME_LEN] = "未知菜品";
            int dIdx = findDish(records[i].dishId);
            if (dIdx != -1) {
                strcpy(dishName, dishes[dIdx].name);
            }
            char line[100];
            sprintf(line, "[%s] 购买 %s，消费 %.2f 元\n",
                records[i].timeStr,
                dishName,
                records[i].amount);
            strcat(buf, line);
            found = 1;
        }
    }
    if (!found) {
        strcat(buf, "暂无消费记录");
    }
    MessageBox(GetHWnd(), buf, "消费记录", MB_OK);
}

// 查询余额
void balanceResearch() {
    char buf[100];
    sprintf(buf, "当前余额: %.2f 元", cards[currentStudent].balance);
    MessageBox(GetHWnd(), buf, "余额查询", MB_OK);
}

//购买菜品
void dishBuy(int i) {
    // 输入购买数量
    char numOfDishes[2];                          
    InputBox(numOfDishes, 2, "请输入购买数量（必须大于0）", "提示");
    int n = atof(numOfDishes);      // 购买数量

    //输入检测
    if (n == 0)     // 数量为0，表明没有输入数字/输入了其他类型的数据/输入0
    {
        MessageBox(GetHWnd(), "请输入一个有效的数字", "错误", MB_OK);
        return;
    }

    // 余额是否足够
    if (cards[currentStudent].balance < dishes[i].price*n) {
        MessageBox(GetHWnd(), "余额不足", "错误", MB_OK);
        return;
    }

    // 确认购买
    char msg[100];
    sprintf(msg, "确认购买 %d 份 %s (%.2f 元)？", n, dishes[i].name, dishes[i].price*n);
    if (MessageBox(GetHWnd(), msg, "确认购买", MB_YESNO) == IDYES) {
        cards[currentStudent].balance -= dishes[i].price*n;
        dishes[i].sales++;

        // 添加消费记录
        if (recordCount < MAX_RECORDS) {
            strcpy(records[recordCount].cardId, cards[currentStudent].cardId);  //卡号
            strcpy(records[recordCount].dishId, dishes[i].dishId);              //菜品编号
            records[recordCount].amount = dishes[i].price*n;                    //消费金额
            strcpy(records[recordCount].timeStr, getCurrentTimeStr());          
            recordCount++;
        }

        MessageBox(GetHWnd(), "购买成功", "提示", MB_OK);
        currentPage = PAGE_STUDENT_MENU;
        drawStudentMenu();
    }
}