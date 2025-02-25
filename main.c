#include <stdio.h>
#include <stdlib.h>
#include "datatime.h"

int main() {
    //Конструкторы
    datatime *dt1 = construct(25, 12, 2023, 15, 30);
    datatime *dt2 = construct(26, 12, 2023, 16, 45);
    
    //Сравнения
    printf("dt1 > dt2 %d\n", greater(*dt1, *dt2));
    printf("dt1 < dt2 %d\n", less(*dt1, *dt2));
    printf("dt1 == dt2 %d\n", equals(*dt1, *dt2));

    //Сеттеры
    set_day(dt1, 31);
    set_month(dt1, 1);
    set_year(dt1, 2024);
    set_hour(dt1, 12);
    set_minute(dt1, 0);

    //Форматированный вывод
    fprint_date(*dt1);

    datatime *dt3 = construct(1, 1, 2020, 0, 0);
    datatime *dt4 = construct(1, 1, 2024, 0, 0);
    
    fenter_date(dt4); // Форматированный ввод
    
    //Интервал
    int years = get_time_difference_years(*dt3, *dt4);
    int months = get_time_difference_months(*dt3, *dt4);
    int days = get_time_difference_days(*dt3, *dt4);
    int hours = get_time_difference_hours(*dt3, *dt4);
    int minutes = get_time_difference_minutes(*dt3, *dt4);

    printf("Разница: %d лет, %d месяцев, %d дней, %d часов, %d минут\n", years, months, days, hours, minutes);

    //Таймстамп
    printf("Timestamp: %ld сек.\n", get_timestamp(*dt4));
    
    //Деструкторы
    destroy(dt1);
    destroy(dt2);
    destroy(dt3);
    destroy(dt4);

    return 0;
}
