#include "admin.h"

// 管理员登录
void adminLogin() {
    char pwd[50];
    InputBox(pwd, 50, "请输入管理员密码", "管理员登录");
    if (strcmp(pwd, ADMIN_PASSWORD) == 0) {
        currentPage = PAGE_ADMIN_MENU;
        drawAdminMenu();
    }
    else {
        MessageBox(GetHWnd(), "密码错误", "提示", MB_OK);
    }
}

// 注册就餐卡
void cardRegister() {
    char id[ID_LEN], name[NAME_LEN];
    InputBox(id, ID_LEN, "输入卡号", "注册");
    InputBox(name, NAME_LEN, "输入姓名", "注册");
    if (findCard(id) != -1 || id[0] == '\0') {
        MessageBox(GetHWnd(), "卡号已存在或为空", "错误", MB_OK);
    }
    else if (name[0] == '\0') {
        MessageBox(GetHWnd(), "名字不能为空", "错误", MB_OK);
    }
    else {
        strcpy(cards[cardCount].cardId, id);
        strcpy(cards[cardCount].name, name);
        cards[cardCount].balance = 0;
        cards[cardCount].status = ACTIVE;
        cardCount++;
        MessageBox(GetHWnd(), "注册成功", "提示", MB_OK);
    }
}

// 就餐卡操作
void cardOperate() {
    char id[ID_LEN];
    InputBox(id, ID_LEN, "请输入要操作的就餐卡号", "就餐卡操作");
    int idx = findCard(id);
    if (idx == -1) {
        MessageBox(GetHWnd(), "卡号不存在", "错误", MB_OK);
    }
    else {
        currentCard = idx; // 需要定义 currentCard 全局变量
        currentPage = PAGE_CARD_OPERATION;
        drawCardOperationPage(idx);
    }
}

// 菜品管理
void dishManage() {
    currentPage = PAGE_DISH_MANAGEMENT;
    drawDishManagementPage();
}

// 充值
void chargeMoney() {
    char money[20];
    InputBox(money, 20, "请输入充值金额（金额必须大于0）", "充值");
    double amount = atof(money);
    if (amount <= 0) {
        MessageBox(GetHWnd(), "请输入有效的充值金额", "错误", MB_OK);
    }
    else {
        cards[currentCard].balance += amount;
        MessageBox(GetHWnd(), "充值成功", "提示", MB_OK);
        drawCardOperationPage(currentCard);
    }
}

// 挂失
void reportLoss() {
    if (cards[currentCard].status == LOST) {
        MessageBox(GetHWnd(), "该卡已挂失", "提示", MB_OK);
    }
    else {
        cards[currentCard].status = LOST;
        MessageBox(GetHWnd(), "挂失成功", "提示", MB_OK);
        drawCardOperationPage(currentCard);
    }
}

// 取消挂失
void undoLoss() {
    if (cards[currentCard].status == ACTIVE) {
        MessageBox(GetHWnd(), "该卡状态正常", "提示", MB_OK);
    }
    else {
        cards[currentCard].status = ACTIVE;
        MessageBox(GetHWnd(), "取消挂失成功", "提示", MB_OK);
        drawCardOperationPage(currentCard);
    }
}

// 查看消费记录
void recordSearch() {
    char buf[2000] = "消费记录：\n";
    int found = 0;
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].cardId, cards[currentCard].cardId) == 0) {
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

// 添加菜品
void addDish() {
    char id[ID_LEN], name[NAME_LEN], price[20];
    InputBox(id, ID_LEN, "菜品编号（如 D001）", "添加菜品");
    if (findDish(id) != -1 || id[0] == '\0') {
        MessageBox(GetHWnd(), "菜品编号已存在或为空", "错误", MB_OK);
    }
    else {
        InputBox(name, NAME_LEN, "菜品名称", "添加菜品");
        InputBox(price, 20, "价格（元）", "添加菜品");

        if (name[0] == '\0' || price[0] == '\0') {
            MessageBox(GetHWnd(), "菜品名称或价格不能为空", "错误", MB_OK);
            return;
        }

        strcpy(dishes[dishCount].dishId, id);
        strcpy(dishes[dishCount].name, name);
        dishes[dishCount].price = atof(price);
        dishes[dishCount].sales = 0;
        dishCount++;
        MessageBox(GetHWnd(), "菜品添加成功", "提示", MB_OK);
    }
}

// 删除菜品
void deleteDish() {
    char id[ID_LEN];
    InputBox(id, ID_LEN, "请输入要删除的菜品编号", "删除菜品");
    int idx = findDish(id);
    if (idx == -1) {
        MessageBox(GetHWnd(), "菜品编号不存在", "错误", MB_OK);
    }
    else {
        // 确认是否删除
        char msg[100];
        sprintf(msg, "确认删除菜品： %s ？", dishes[idx].name);
        if (MessageBox(GetHWnd(), msg, "提示", MB_YESNO) == IDNO) { return; }

        for (int i = idx; i < dishCount - 1; i++) {
            dishes[i] = dishes[i + 1];
        }
        dishCount--;
        MessageBox(GetHWnd(), "菜品删除成功", "提示", MB_OK);
    }
}

// 修改价格
void editPrice() {
    char id[ID_LEN], price[20];
    InputBox(id, ID_LEN, "请输入菜品编号", "修改价格");
    int idx = findDish(id);
    if (idx == -1) {
        MessageBox(GetHWnd(), "菜品编号不存在", "错误", MB_OK);
    }
    else {
        char currPrice[50];
        sprintf(currPrice, "当前菜品: %s \n当前价格: %.2f 元\n\n请输入新价格:", dishes[idx].name, dishes[idx].price);
        InputBox(price, 20, currPrice, "修改价格");
        dishes[idx].price = atof(price);
        MessageBox(GetHWnd(), "价格修改成功", "提示", MB_OK);
    }
}