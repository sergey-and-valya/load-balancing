using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using CoreImpl2D;
using GeneratorPluginCore;
using MatrixStorage;

namespace GaussGenerator
{
    [Export(typeof(IGeneratorPlugin<int, EmptyData>))]
    public class GaussGeneratorPlugin : IGeneratorPlugin<int, EmptyData>
    {
        public string Name
        {
            get { return "Генерация по Гауссу"; }
        }

        public bool HasGenerator(int dimensions)
        {
            if (dimensions != 2)
                return false;

            return true;
        }

        public IGenerator<int, EmptyData> CreateGenerator(int dimensions)
        {
            if (dimensions != 2)
                return null;

            var dialog = new ParametersDialog();

            if (dialog.ShowDialog() != DialogResult.OK)
                return null;

            return new Generator(dialog.Count, dialog.N, dialog.M, dialog.M1, dialog.M2, dialog.MinW, dialog.MaxW, dialog.MinH, dialog.MaxH);
        }

        private class Generator : IGenerator<int, EmptyData>
        {
            private readonly int count;
            private readonly int n;
            private readonly int m;
            private readonly int M1;
            private readonly int M2;
            private readonly int min_w;
            private readonly int max_w;
            private readonly double min_h;
            private readonly double max_h;

            public Generator(int count, int n, int m, int M1, int M2, int min_w, int max_w, double min_h, double max_h)
            {
                this.count = count;
                this.n = n;
                this.m = m;
                this.M1 = M1;
                this.M2 = M2;
                this.min_w = min_w;
                this.max_w = max_w;
                this.min_h = min_h;
                this.max_h = max_h;


                if (M1 >= n)
                {
                    Console.WriteLine("Заданы недопустимые параметры генерации! Уменьшите число разбиений по строкам.");
                    throw new Exception();
                }
                if (M2 >= m)
                {
                    Console.WriteLine("Заданы недопустимые параметры генерации! Уменьшите число разбиений по столбцам.");
                    throw new Exception();
                }

                if ((n <= 0) || (n <= 0) || (m <= 0) || (M1 <= 0) || (M2 <= 0) || (min_w <= 0) || (max_w <= 0) || (min_h <= 0) || (max_h <= 0))
                {
                    Console.WriteLine("Заданы недопустимые параметры генерации! Все параметры генерации должны быть положительны.");
                    throw new Exception();
                }

                int max_size_row;
                int max_size_col;
                int max_size;

                if (M1 == 1)
                {
                    max_size_row = (n - 1);
                }
                else
                {
                    max_size_row = 2 * (int)(Math.Ceiling((double)n / M1) - 1);
                }

                if (M2 == 1)
                {
                    max_size_col = m - 1;
                }
                else
                {
                    max_size_col = 2 * (int)(Math.Ceiling((double)m / M2) - 1);
                }

                max_size = max_size_row * max_size_col;
                if (max_w < max_size)
                {
                    Console.WriteLine("Заданы недопустимые параметры генерации! При заданных размерности матрицы, параметрах разбиения суммарная загрузка должна быть не меньше " + max_size);
                    throw new Exception();
                }

            }

            public void GenerateMatrixes(IMatrixWriteStorage<int, EmptyData> matrixStorage)
            {
                Random rnd = new Random();

                for (int matrindex = 0; matrindex < count; matrindex++)
                {
                    #region // задаём разбиения по каждому измерению
                    // формируем массив номеров строк, по которым идёт разбиение
                    List<int> num_row = CreatePartition(M1, n);

                    // формируем массив номеров столбцов, по которым идёт разбиение
                    List<int> num_col = CreatePartition(M2, m);


                    #endregion

                    #region  // заполнение матрицы

                    int[,] matrix = new int[n, m];
                    int size_row, size_col, size_block;
                    int sum_control;                           // переменная для контороля того, что в каждом блоке // загрузка равна заданной загрузке w_block
                    int Max = 0;                                 // максимальная суммарная загрузка 

                    int w_block;
                    double h, f;
                    int expectation_1, expectation_2;
                    double D1, D2;

                    for (int i = 0; i < M1 + 1; i++)
                    // суммарная загрузка каждого блока принимает значение в отрезке: [w - epsilon, w + epsilon], 
                    // но в зависимости от размера каждого блока этот отрезок может стать меньше
                    {
                        size_row = num_row[i + 1] - num_row[i];
                        expectation_1 = num_row[i + 1] - (num_row[i + 1] - num_row[i]) / 2;
                        for (int j = 0; j < M2 + 1; j++)
                        {
                            size_col = num_col[j + 1] - num_col[j];

                            // размерность текущего блока (i, j)
                            size_block = size_row * size_col;
                            h = rnd.NextDouble() * (max_h - min_h) + min_h;
                            w_block = rnd.Next(Math.Max(size_block, min_w), max_w + 1);

                            if (w_block > Max)
                            {
                                Max = w_block;
                            }
                            // заполнение ячеек текущего блока целочисленными значениями по распределению Гаусса
                            sum_control = 0;
                            // генерируем центр распределения: это есть (M1, M2) - локальные координаты
                            expectation_2 = num_col[j + 1] - (num_col[j + 1] - num_col[j]) / 2;
                            // пусть D1 = D2
                            D1 = D2 = Math.Sqrt(1 / (2 * h * Math.PI));

                            for (int k = num_row[i] + 1; k <= num_row[i + 1]; k++)
                            {
                                for (int l = num_col[j] + 1; l <= num_col[j + 1]; l++)
                                {
                                    // нужно использовать локальные координаты
                                    f = w_block * (1.0 / (2.0 * Math.PI * D1 * D2)) * Math.Exp(-0.5 * ((((k - expectation_1) * (k - expectation_1)) / (D1 * D1)) + (((l - expectation_2) * (l - expectation_2)) / (D2 * D2))));
                                    matrix[k, l] = (int)Math.Ceiling(f);
                                    sum_control += matrix[k, l];
                                }
                            }
                            if (w_block < sum_control)
                            {
                                // перебор по суммарной загрузке блока
                                while ((w_block < sum_control) && (w_block >= sum_control - size_block))
                                {
                                    sum_control -= size_block;
                                    for (int k = num_row[i] + 1; k <= num_row[i + 1]; k++)
                                    {
                                        for (int l = num_col[j] + 1; l <= num_col[j + 1]; l++)
                                        {
                                            matrix[k, l] = Math.Max(1, matrix[k, l]--);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                // недобор по суммарной загрузке блока
                                while (w_block > sum_control)
                                {
                                    sum_control += size_block;
                                    for (int k = num_row[i] + 1; k <= num_row[i + 1]; k++)
                                    {
                                        for (int l = num_col[j] + 1; l <= num_col[j + 1]; l++)
                                        {
                                            matrix[k, l]++;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    #endregion

                    #region // полученное решение
                    // 1. матрица matrix
                    // 2. разбиение по осям
                    CreateSolution(num_row, num_col);
                    // максимальная загрузка при полученном разбиении
                    // 3. Max
                    #endregion

                    #region // вывод для проверки
                    for (int i = 0; i < n; i++)
                    {
                        Console.WriteLine();
                        for (int j = 0; j < m; j++)
                        {
                            int ost = matrix[i, j] / 10;
                            if (ost == 0)
                            {
                                Console.Write(" ");
                            }
                            Console.Write(matrix[i, j] + "   ");
                        }
                    }
                    #endregion

                    DenseMatrix<int> Matrix = new DenseMatrix<int>(n, m);

                    foreach (var index in MatrixEnumerator.Indexes(Matrix))
                    {
                        Matrix[index] = matrix[index[0], index[1]];
                    }

                    matrixStorage.SaveMatrix("Gauss", Matrix, null);
                }
            }
        }

        static List<int> CreatePartition(int count_partition, int size_partition)
        {
            Random rnd = new Random(DateTime.Now.Millisecond);
            List<int> partition = new List<int>(count_partition + 2);
            int r;
            partition.Add(-1);
            int size = size_partition / count_partition;
            for (int i = 0; i < count_partition - 1; i++)
            {
                r = rnd.Next(i * size, (i + 1) * size);
                partition.Add(r);
            }
            r = rnd.Next((count_partition - 1) * size, size_partition - 1);
            partition.Add(r);
            partition.Add(size_partition - 1);
            return partition;
        }

        static void CreateSolution(List<int> num_row, List<int> num_col)
        {
            num_row.RemoveAt(num_row.Count - 1);
            num_row.RemoveAt(0);

            num_col.RemoveAt(num_col.Count - 1);
            num_col.RemoveAt(0);

            for (int i = 0; i < num_row.Count; i++)
            {
                num_row[i]++;
            }
            for (int j = 0; j < num_col.Count; j++)
            {
                num_col[j]++;
            }
        }
    }
}