#include <stdio.h>
#include <stdlib.h>
#include "datatime.h"

int main() {
    //Конструкторы
    datatime *dt1 = construct(25, 12, 2023, 15, 30);
    datatime *dt2 = construct(26, 12, 2023, 16, 45);
    print_date(*dt1);
    print_date(*dt2);

    //Сравнения
    printf("dt1 > dt2 %d\n", greater(*dt1, *dt2));
    printf("dt1 < dt2 %d\n", less(*dt1, *dt2));
    printf("dt1 == dt2 %d\n", equals(*dt1, *dt2));

    //Сеттеры
    set_day(dt1, 31); 
    fprint_date(*dt1);
    increment_day(dt1, 1);// Пример переполнения дней в месяцах
    printf("Дата после применения сеттера с переполнением\n");
    fprint_date(*dt1);

    datatime *dt3 = construct(1, 1, 2020, 0, 0);
    datatime *dt4 = construct(1, 1, 2024, 0, 0);
    
    fenter_date(dt4); // Форматированный ввод
    
    datatime * diff = get_time_difference(*dt3, *dt4);
    printf("Разница: %d лет, %d месяцев, %d дней, %d часов, %d минут\n", diff->year, diff->month, diff->day, diff->hour, diff->minute);

    //Таймстамп
    printf("Timestamp: %ld сек.\n", get_timestamp(*dt4));
    
    //Деструкторы
    destroy(dt1);
    destroy(dt2);
    destroy(dt3);
    destroy(dt4);

    return 0;
}
