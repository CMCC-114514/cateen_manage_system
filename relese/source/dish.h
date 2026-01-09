#ifndef DISH_H
#define DISH_H

#define DISHID_LEN       20     // 菜品编号最大长度（含 '\0'）
#define DISHNAME_LEN     50     // 菜名最大长度（含 '\0'）

// 菜品信息结构体
typedef struct {
    char dishId[DISHID_LEN];     // 菜品编号，如 "D001"
    char name[DISHNAME_LEN];     // 菜品名称
    double price;            // 单价（元）
    int sales;          // 销售次数
} Dish;

#endif // !DISH_H
