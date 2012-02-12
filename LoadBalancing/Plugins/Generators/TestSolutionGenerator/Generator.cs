using System;
using System.Collections.Generic;
using Core;
using CoreImpl2D;
using GeneratorPluginCore;
using LoadBalancing;
using MatrixStorage;
using System.Windows.Forms;

namespace TestSolutionGenerator
{
    internal class Generator : IGenerator<int, Tuple<PartitioningParameters, ISolution, double>>
    {
        private int count;
        private int M1;
        private int M2;
        private int m;
        private int n;
        private int Min;
        private int Max;

        public Generator(int count, int M1, int M2, int m, int n, int Min, int Max)
        {
            this.count = count;
            this.M1 = M1;
            this.M2 = M2;
            this.m = m;
            this.n = n;
            this.Min = Min;
            this.Max = Max;
        }

        public void GenerateMatrixes(IMatrixWriteStorage<int, Tuple<PartitioningParameters, ISolution, double>> matrixStorage)
        {
            for (int currentMatrix = 0; currentMatrix < count; currentMatrix++)
            {
                DenseMatrix<int> matrix = new DenseMatrix<int>(n, m);
                Random rnd = new Random();

                #region // формируем массив номеров строк, по которым идёт разбиение
                List<int> num_row = new List<int>(M1 + 2);

                int r = -1;
                int r_previous = 0;
                num_row.Add(-1);
                for (int i = 0; i < M1; i++)
                {

                    r = rnd.Next(r_previous, (i + 1) * ((n - 1) / M1));
                    r_previous = (i + 1) * ((n - 1) / M1) + 1;

                    num_row.Add(r);
                }
                num_row.Add(n - 1);

                #endregion

                #region   // формируем массив номеров столбцов, по которым идёт разбиение
                List<int> num_col = new List<int>(M2 + 2);

                r = -1;
                r_previous = 0;
                num_col.Add(-1);
                for (int i = 0; i < M2; i++)
                {
                    r = rnd.Next(r_previous, (i + 1) * ((m - 1) / M2));
                    r_previous = (i + 1) * ((m - 1) / M2) + 1;
                    num_col.Add(r);
                }
                num_col.Add(m - 1);

                #endregion

                #region  // поиск блока, содержащего наибольшее и наименьшее количество ячеек

                // поиск по первому измерению
                int max_size_row = num_row[1] - num_row[0];
                int min_size_row = num_row[1] - num_row[0];
                int tmp = 0;
                for (int i = 2; i < M1 + 2; i++)
                {
                    tmp = num_row[i] - num_row[i - 1];
                    if (tmp > max_size_row)
                    {
                        max_size_row = tmp;
                    }
                    if (tmp < min_size_row)
                    {
                        min_size_row = tmp;
                    }
                }

                // поиск по второму измерению
                int max_size_col = num_col[1] - num_col[0];
                int min_size_col = num_col[1] - num_col[0];
                tmp = 0;
                for (int i = 2; i < M2 + 2; i++)
                {
                    tmp = num_col[i] - num_col[i - 1];
                    if (tmp > max_size_col)
                    {
                        max_size_col = tmp;
                    }
                    if (tmp < min_size_col)
                    {
                        min_size_col = tmp;
                    }
                }

                int max_size = max_size_row * max_size_col;
                int min_size = min_size_row * min_size_col;
                if ((min_size <= 0) || (max_size <= 0))
                {
                    MessageBox.Show("Ошибка! Минимальный или максимальный блок имеет отрицательную размерность!");
                    return;
                }
                #endregion

                #region // поиск w - суммарной загрузки каждого блока и возможного отклонения epsilon от w

                int w, epsilon;                // искомые величины 

                // В блоке минимального размера суммарная загрузка изменяется на отрезке: 
                // [capacity_low_min_block, capacity_high_min_block]
                int capacity_low_min_block = min_size * this.Min;
                int capacity_high_min_block = min_size * this.Max;

                // В блоке максимального размера суммарная загрузка изменяется на отрезке: 
                // [capacity_low_max_block, capacity_high_max_block]
                int capacity_low_max_block = max_size * this.Min;
                int capacity_high_max_block = max_size * this.Max;

                if (capacity_low_max_block > capacity_high_min_block)
                {
                    // рассматриваемые отрезки не пересекаются
                    w = rnd.Next(capacity_low_max_block, capacity_low_max_block + (capacity_high_min_block - capacity_low_min_block) + 1);
                    epsilon = w - capacity_high_min_block;
                }
                else
                {
                    // рассматриваемые отрезки пересекаются, искомое w принадлежит пересечению отрезков
                    w = rnd.Next(Math.Max(capacity_low_min_block, capacity_low_max_block), Math.Min(capacity_high_min_block, capacity_high_max_block) + 1);
                    epsilon = w - capacity_low_min_block;
                }
                #endregion

                #region  // заполнение матрицы

                int size_row = 0;                           // размер блока по первому измерению
                int size_col = 0;                            // размер блока по второму измерению
                int size_block = 0;                        // размер блока (количество ячеек) 
                int w_block = 0;                           // суммарная загрузка блока
                int w_low = w - epsilon;              // загрузка блока изменяется на отрезке: [w_low, w_high]
                int w_high = w + epsilon;
                int w_low_block = 0;                    // для каждого блока загрузка изменяется на более узком отрезке, чем 
                int w_high_block = 0;                  // [w_low, w_high], а именно на отрезке [w_low_block, w_high_block]

                int sum, k_cur, l_cur;                   // вспомогательные переменные
                int sum_control;                           // переменная для контороля того, что в каждом блоке 
                int Max = 0;                                 // максимальная суммарная загрузка 
                // загрузка равна заданной загрузке w_block

                for (int i = 0; i < M1 + 1; i++)
                // суммарная загрузка каждого блока принимает значение в отрезке: [w - epsilon, w + epsilon], 
                // но в зависимости от размера каждого блока этот отрезок может стать меньше
                {
                    size_row = num_row[i + 1] - num_row[i];

                    for (int j = 0; j < M2 + 1; j++)
                    {
                        sum_control = 0;
                        size_col = num_col[j + 1] - num_col[j];

                        // размерность текущего блока (i, j)
                        size_block = size_row * size_col;


                        w_low_block = Math.Max(w_low, size_block * this.Min);
                        w_high_block = Math.Min(w_high, size_block * this.Max);

                        if (w_low_block > w_high_block)
                        {
                            MessageBox.Show("Ошибка! Получили блок с загрузкой на отрезке [w_low_block, w_high_block], где w_low_block > w_high_block");
                            return;
                        }

                        w_block = rnd.Next(w_low_block, w_high_block + 1);             // суммарная загрузка текущего блока

                        if (w_block > Max)
                        {
                            Max = w_block;
                        }

                        // заполнение ячеек текущего блока целочисленными значениями
                        sum = w_block;
                        for (int k = num_row[i] + 1; k <= num_row[i + 1]; k++)
                        {
                            for (int l = num_col[j] + 1; l <= num_col[j + 1]; l++)
                            {
                                size_block--;
                                matrix[k, l] = rnd.Next(this.Min, Math.Min(this.Max, sum - size_block * this.Min));
                                sum = sum - matrix[k, l];
                                sum_control += matrix[k, l];
                            }
                        }
                        while (sum != 0)
                        {
                            k_cur = rnd.Next(num_row[i] + 1, num_row[i + 1] + 1);
                            l_cur = rnd.Next(num_col[j] + 1, num_col[j + 1] + 1);
                            if (matrix[k_cur, l_cur] < this.Max)
                            {
                                matrix[k_cur, l_cur]++;
                                sum--;
                                sum_control++;
                            }
                        }
                        if (sum_control != w_block)
                        {
                            MessageBox.Show("Ошибка! Заданная загрузка для блока не равна полученной!");
                            return;
                        }
                    }
                }

                #endregion

                #region// полученное решение

                num_row.RemoveAt(M1 + 1);
                num_row.RemoveAt(0);

                num_col.RemoveAt(M2 + 1);
                num_col.RemoveAt(0);

                #endregion


                int[] x = num_row.ToArray();
                int[] y = num_col.ToArray();


                for (int i = 0; i < x.Length; i++)
                {
                    x[i]++;
                }

                for (int i = 0; i < y.Length; i++)
                {
                    y[i]++;
                }
                PartitioningParameters partitioning = new PartitioningParameters(M1 + 1, M2 + 1);
                ISolution solution = new Solution2D(x, y);

                matrixStorage.SaveMatrix("matrix with solution", matrix, new Tuple<PartitioningParameters, ISolution, double>(partitioning, solution, Max));
            }
        }


        // Функция генерации матрицы размера n на m (n строк, m - столбцов) с генерацией некоторого "решения". 
        // Под решением понимаются массивы (листы) num_row и num_col - номера строк и столбцов, по которым
        // производится декомпозиция матрицы. Количество разбиений по первому измерению - M1, по второму - M2.
        // В каждом полученном при декомпозиции блоке суммарная загрузка изменяется на отрезке: 
        // [w - epsilon, w + epsilon]. w и epsilon находятся в зависимости от min_value и max_value - диапазона значений
        // для ячейки матрицы. Здесь подразумевается, что min_value = 1.

        // Функция генерации матрицы возвращает true, если генерация прошла успешно и false в противном случае
    }
}
