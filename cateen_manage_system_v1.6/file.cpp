#include "file.h"
#include "global.h"
#include "graphics.h"

void loadData() {
    FILE* fp;

    // 加载学生卡
    fp = fopen("data/cards.txt", "r");
    if (fp != NULL) {
        cardCount = 0;
        while (fscanf(fp, "%19[^|]|%49[^|]|%lf|%d\n",
            cards[cardCount].cardId,
            cards[cardCount].name,
            &cards[cardCount].balance,
            &cards[cardCount].status) == 4) {
            cardCount++;
            if (cardCount >= MAX_CARDS) break;
        }
        fclose(fp);
    }

    // 加载菜品
    fp = fopen("data/dishes.txt", "r");
    if (fp != NULL) {
        dishCount = 0;
        while (fscanf(fp, "%19[^|]|%49[^|]|%lf|%d\n",
            dishes[dishCount].dishId,
            dishes[dishCount].name,
            &dishes[dishCount].price,
            &dishes[dishCount].sales) == 4) {
            dishCount++;
            if (dishCount >= MAX_DISHES) break;
        }
        fclose(fp);
    }

    // 加载消费记录
    fp = fopen("data/records.txt", "r");
    if (fp != NULL) {
        recordCount = 0;
        while (fscanf(fp, "%19[^|]|%19[^|]|%lf|%29[^\n]\n",
            records[recordCount].cardId,
            records[recordCount].dishId,
            &records[recordCount].amount,
            records[recordCount].timeStr) == 4) {
            recordCount++;
            if (recordCount >= MAX_RECORDS) break;
        }
        fclose(fp);
    }
    MessageBox(GetHWnd(), "加载数据完成", "提示", MB_OK);
}

void saveData() {
    FILE* fp;

    // 保存学生卡
    fp = fopen("data/cards.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < cardCount; i++) {
            fprintf(fp, "%s|%s|%.2f|%d\n",
                cards[i].cardId,
                cards[i].name,
                cards[i].balance,
                cards[i].status);
        }
        fclose(fp);
    }

    // 保存菜品
    fp = fopen("data/dishes.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < dishCount; i++) {
            fprintf(fp, "%s|%s|%.2f|%d\n",
                dishes[i].dishId,
                dishes[i].name,
                dishes[i].price,
                dishes[i].sales);
        }
        fclose(fp);
    }

    // 保存消费记录
    fp = fopen("data/records.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < recordCount; i++) {
            fprintf(fp, "%s|%s|%.2f|%s\n",
                records[i].cardId,
                records[i].dishId,
                records[i].amount,
                records[i].timeStr);
        }
        fclose(fp);
    }
    //MessageBox(GetHWnd(), "保存数据成功", "提示", MB_OK);
}