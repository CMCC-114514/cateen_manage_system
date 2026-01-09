  #define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>             // 标准库（malloc, exit 等，此处主要用于 exit）
#include <io.h>                 // Windows 特有：_setmode, _fileno
#include <fcntl.h>              // 文件控制：O_U16TEXT（本程序未用，保留兼容性）

#include "global.h"
#include "studentcard.h"
#include "tool.h"
#include "file.h"
#include "interface.h"
#include "admin.h"

// =================== 主函数 ===================
int main() {
    initgraph(800, 600);
    setbkcolor(CYAN);
    //setlinecolor(BLACK);
    //settextcolor(BLACK);
    cleardevice();

    // 初始化示例菜品
    loadData();

    drawMainPage();

    while (1) {
        MOUSEMSG m = GetMouseMsg();
        if (m.uMsg != WM_LBUTTONDOWN) continue;

        // ===== 主界面 =====
        if (currentPage == PAGE_MAIN) {
            if (inRect(m.x, m.y, 300, 200, 500, 250)) {
                // 管理员登录
                adminLogin();
            }
            else if (inRect(m.x, m.y, 300, 280, 500, 330)) {
                // 学生登录
                studentLogin();
            }
            else if (inRect(m.x, m.y, 300, 360, 500, 410)) {
                // 退出程序
                saveData();
                closegraph();
                return 0;
            }
        }

        // ===== 管理员菜单 =====
        else if (currentPage == PAGE_ADMIN_MENU) {
            if (inRect(m.x, m.y, 280, 180, 520, 230)) {
                // 注册学生卡
                cardRegister();
                saveData();
            }
            else if (inRect(m.x, m.y, 280, 250, 520, 300)) {
                // 就餐卡操作 - 进入新页面
                cardOperate();
            }
            else if (inRect(m.x, m.y, 280, 320, 520, 370)) {
                // 菜品管理 - 进入新页面
                dishManage();
            }
            else if (inRect(m.x, m.y, 280, 390, 520, 440)) {
                currentPage = PAGE_MAIN;
                drawMainPage();
            }
        }

        // ===== 就餐卡操作页面 =====
        else if (currentPage == PAGE_CARD_OPERATION) {
            if (inRect(m.x, m.y, 150, 180, 650, 230)) {
                // 充值
                chargeMoney();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 240, 650, 290)) {
                // 挂失
                reportLoss();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 300, 650, 350)) {
                // 取消挂失
                undoLoss();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 360, 650, 410)) {
                // 查看消费记录
                recordSearch();
            }
            else if (inRect(m.x, m.y, 150, 420, 650, 470)) {
                // 返回管理员菜单
                currentPage = PAGE_ADMIN_MENU;
                drawAdminMenu();
            }
        }

        // ===== 菜品管理页面 =====
        else if (currentPage == PAGE_DISH_MANAGEMENT) {
            if (inRect(m.x, m.y, 150, 120, 650, 170)) {
                // 添加菜品
                addDish();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 180, 650, 230)) {
                // 删除菜品
                deleteDish();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 240, 650, 290)) {
                // 修改价格
                editPrice();
                saveData();
            }
            else if (inRect(m.x, m.y, 150, 300, 650, 350)) {
                // 查看所有菜品
                currentPage = PAGE_ALL_DISHES;
                drawAllDishesPage();
            }
            else if (inRect(m.x, m.y, 150, 360, 650, 410)) {
                // 查看销售排行榜
                currentPage = PAGE_SALES_RANKING;
                drawSalesRankingPage();
            }
            else if (inRect(m.x, m.y, 150, 420, 650, 470)) {
                // 返回管理员菜单
                currentPage = PAGE_ADMIN_MENU;
                drawAdminMenu();
            }
        }

        // ===== 所有菜品页面 =====
        else if (currentPage == PAGE_ALL_DISHES) {
            if (inRect(m.x, m.y, 300, 500, 500, 550)) {
                // 返回菜品管理页面
                currentPage = PAGE_DISH_MANAGEMENT;
                drawDishManagementPage();
            }
        }

        // ===== 销售排行榜页面 =====
        else if (currentPage == PAGE_SALES_RANKING) {
            if (inRect(m.x, m.y, 300, 500, 500, 550)) {
                // 返回菜品管理页面
                currentPage = PAGE_DISH_MANAGEMENT;
                drawDishManagementPage();
            }
        }

        // ===== 学生菜单页面 =====
        else if (currentPage == PAGE_STUDENT_MENU) {
            if (inRect(m.x, m.y, 280, 200, 520, 250)) {
                // 查看菜品列表 - 显示所有菜品
                showAllDishes();
            }
            else if (inRect(m.x, m.y, 280, 270, 520, 320)) {
                // 购买菜品 - 进入购买页面
                currentPage = PAGE_STUDENT_BUY;
                drawStudentBuyPage();
            }
            else if (inRect(m.x, m.y, 280, 340, 520, 390)) {
                // 查看消费记录
                showRecord();
            }
            else if (inRect(m.x, m.y, 280, 410, 520, 460)) {
                // 查询余额
                balanceResearch();
            }
            else if (inRect(m.x, m.y, 280, 480, 520, 530)) {
                // 退出登录
                currentPage = PAGE_MAIN;
                currentStudent = -1;
                drawMainPage();
            }
        }

        // ===== 学生购买菜品页面 =====
        else if (currentPage == PAGE_STUDENT_BUY) {
            // 检查点击了哪个购买按钮
            int buttonHeight = 40;
            int startY = 70;
            for (int i = 0; i <= dishCount; i++) {
                int buttonY = startY + (i * buttonHeight);
                if (inRect(m.x, m.y, 450, buttonY - 10, 520, buttonY + 20)) {
                    dishBuy(i - 1);
                }
            }
            
            // 返回按钮
            if (inRect(m.x, m.y, 300, 520, 500, 570)) {
                currentPage = PAGE_STUDENT_MENU;
                drawStudentMenu();
            }
            saveData();
        }
    }
}
