## Force termination of a thread
Дочерняя нить должна распечатывать текст на экран. Через две секунды после создания дочерней нити, родительская нить должна прервать ее вызовом функции **pthread_cancel**.
## Thread creation
Напишите программу, которая создает нить. Используйте атрибуты по умолчанию. Родительская и вновь созданная нити должны распечатать десять строк текста. 
## Thread parameters
Напишите программу, которая создает четыре нити, исполняющие одну и ту же функцию. Эта функция должна распечатать последовательность текстовых строк, переданных как параметр. Каждая из созданных нитей должна распечатать различные последовательности строк.
## Waiting for a thread
Модифицируйте программу ***Thread creation*** так, чтобы вывод родительской нити производился после завершения дочерней. Используйте **pthread_join**.

