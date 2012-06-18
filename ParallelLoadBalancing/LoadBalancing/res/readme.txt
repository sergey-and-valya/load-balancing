count_row count_columns 
num_processor_row num_processor_col
array_partitions_rows[count_row + 1]
array_partitions_columns[count_columns + 1]
matrix[count_row][count_columns]

Подробнее
Структура файла, в котором хранится матрица следующая:
count_row  - количество строк (int)
count_columns - количество столбцов (int)
num_processor_row - количество процессоров по строкам (int)
num_processor_col - количество процессоров по столбцам (int)
array_partitions_rows - массив номеров разбиений по строкам, содержит num_processor_row + 1 элементов (первый элемент - 0, последний - count_row - 1) (int)
array_partitions_columns - массив номеров разбиений по строкам, содержит num_processor_col + 1 элементов (первый элемент - 0, последний - count_columns - 1) (int)
matrix[count_row][count_columns] - исходная матрица значений: в файле .txt хранится по строкам (double)