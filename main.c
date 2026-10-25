#include <stdio.h>
int max(int a, int b) // ФУНКЦИЯ MAX(1)
{
    if (a > b)
    {
        return a;
    }
    
    return b;
    
}

int min(int a, int b) // ФУНКЦИЯ MIN(2)
{
    if (a < b)
    {
        return a;
    }
    
    
    return b;
    
}

int is_input_valid(int stock, int daily_demand, int lead_days, int safety_days, int max_order, double reliability) // ФУНКЦИЯ ПРОВЕРКИ ОБЛАСТИ ОПРЕДЕЛЕНИЯ ВВОДА И ЕГО ПРАВИЛЬНОСТИ(3)
{
    if ((stock < 0) || (daily_demand < 0) || (lead_days < 0) || (safety_days < 0) || (max_order < 0))
    {
        return 0;
    }
    if ((reliability < 0) || (reliability > 100))
    {
        return 0;
    }
    return 1;
}
int calculating_days_left(int daily_demand) // ФУНКЦИЯ проверки деления на 0 в формуле(4)
{
    if (daily_demand == 0)
    {
        return 0;
    }
    return 1;
}

int get_status_code(int stock, int expected_during_lead, int reorder_point, double reliability) // ФУНКЦИЯ ОПРЕДЕЛЕНИЯ СТАТУСА ТЕКУЩИХ СКЛАДСКИХ ЗАПАСОВ(5)
{
    if ((stock < expected_during_lead) || (reliability < 70))
    {
        return 1;
    }
    else if (stock <= reorder_point)
    {
        return 2;
    }
    else if (reliability < 85)
    {
        return 3;
    }
    return 4;
}

int main(void)
{

    int stock, daily_demand, lead_days, safety_days, max_order;
    double reliability; // ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ ДЛЯ ВВОДА

    printf("Current Stock:"); // текущий остаток на складе, шт.
    scanf("%d", &stock);
    printf("Daily Demand:"); // сколько товара продаётся в день, шт.
    scanf("%d", &daily_demand);
    printf("Lead Time:"); // за сколько дней поставщик привозит заказ
    scanf("%d", &lead_days);
    printf("Safety Stock Days:"); //	на сколько дней держим запас «на всякий случай»
    scanf("%d", &safety_days);
    printf("Maximum Order Quantity:"); // максимум, который можно заказать за раз, шт.
    scanf("%d", &max_order);
    printf("Supplier Reliability:"); // надёжность поставщика, %
    scanf("%lf", &reliability);

    int reorder_point;        // точка заказа: если остаток упал до неё, пора заказывать
    int expected_during_lead; // сколько продадим, пока ждём доставку
    int target_stock;         // до какого уровня хотим пополнить склад
    int recommended_order;    // сколько заказать: не меньше 0 и не больше лимита
    int days_left;            // осталось дней

    printf("\n---OUTPUT---\n\n");

    if (is_input_valid(stock, daily_demand, lead_days, safety_days, max_order, reliability) == 0) //(3)
    {
        printf("INVALID INPUT. TRY AGAIN WITH CORRECT DATA");
        return 1;
    }

    if (calculating_days_left(daily_demand) == 0) //(4)
    {
        printf("UNPROFITABLE BUSINESS");
        return 1;
    }

    reorder_point = daily_demand * (lead_days + safety_days);
    printf("reorder_point: %d\n", reorder_point);

    expected_during_lead = daily_demand * lead_days;
    printf("expected_during_lead: %d\n", expected_during_lead);

    target_stock = reorder_point + daily_demand * safety_days;
    printf("target_stock: %d\n", target_stock);

    recommended_order = min(max_order, max(0, target_stock - stock)); // (1,2)
    printf("recommended order: %d\n", recommended_order);

    days_left = stock / daily_demand;
    printf("days_left: %d\n", days_left);
    printf("CONCLUSION: ");
    if (get_status_code(stock, expected_during_lead, reorder_point, reliability) == 1) // (5)
    {
        printf("CRITICAL");
    }
    else if (get_status_code(stock, expected_during_lead, reorder_point, reliability) == 2)
    {
        printf("ORDER_NOW");
    }
    else if (get_status_code(stock, expected_during_lead, reorder_point, reliability) == 3)
    {
        printf("SUPPLIER_WARNING");
    }
    else if (get_status_code(stock, expected_during_lead, reorder_point, reliability) == 4)
    {
        printf("ENOUGH");
    }
    return 0;
}
