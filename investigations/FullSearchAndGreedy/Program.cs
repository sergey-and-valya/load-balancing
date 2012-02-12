#define USE_MIN_DISPERSE_CRITERION

using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace FullSearchAndGreedy
{
    internal class Program
    {
        delegate double CriterionDelegate(int M1, int M2, int[] x, int[] y, int[,] v);

        private static void Main(string[] args)
        {
            Console.CursorVisible = false;
            Console.WindowHeight = Console.LargestWindowHeight;
            Console.WindowWidth = Console.BufferWidth;

            const int n1 = 20;
            const int n2 = 20;
            const int M1 = 4;
            const int M2 = 4;

            //v[i, j] = A(i,j) .. (A(i,j) + B(i,j))
            Func<int, int, int> A = (i, j) => 1;
            Func<int, int, int> B = (i, j) => 8;

            Debug.Assert(M1 > 0);
            Debug.Assert(M2 > 0);
            int[,] v = new int[n1, n2];

            int V;
            int V1;
            int V2;
            double w;
            double w1;
            double w2;

            Random rnd = new Random();

            while (true)
            {
                int[] x = new int[M1];
                int[] y = new int[M2];

                int d = -1;

                var best_x_list = new List<int[]>();
                var best_y_list = new List<int[]>();
                double best_f = double.MaxValue;

                int cursorPosOnEnd;
                int cursorPos;

                x[M1 - 1] = n1 - 1;
                y[M2 - 1] = n2 - 1;

                #region Генерация исходных данных

                w = 0;
                V = 0;
                V1 = 0;
                V2 = 0;

                for (int i = 0; i < n1; i++)
                    for (int j = 0; j < n2; j++)
                    {
                        v[i, j] = rnd.Next(B(i, j) + 1) + A(i, j);
                        w += v[i, j];
                        V = Math.Max(V, v[i, j]);
                    }

                for (int i = 0; i < n1; i++)
                {
                    int s = 0;
                    for (int j = 0; j < n2; j++)
                    {
                        s += v[i, j];
                    }
                    V1 = Math.Max(V1, s);
                }

                for (int j = 0; j < n2; j++)
                {
                    int s = 0;
                    for (int i = 0; i < n1; i++)
                    {
                        s += v[i, j];
                    }
                    V2 = Math.Max(V2, s);
                }

                w1 = w / M1;
                w2 = w / M2;
                w = w / (M1 * M2);

                #endregion


                #region Вывод исходных данных

                Console.WriteLine("n1 = {0}", n1);
                Console.WriteLine("n2 = {0}", n2);
                Console.WriteLine("M1 = {0}", M1);
                Console.WriteLine("M2 = {0}", M2);
                Console.WriteLine();

                Console.WriteLine("V = {0}", V);
                Console.WriteLine("w = {0}", w);
                Console.WriteLine();
                Console.WriteLine("Vx = {0}", V1);
                Console.WriteLine("wx = {0}", w1);
                Console.WriteLine();
                Console.WriteLine("Vy = {0}", V2);
                Console.WriteLine("wy = {0}", w2);
                Console.WriteLine();
                cursorPosOnEnd = Console.CursorTop;
                Console.WriteLine("Stupid solution:");


                double best_f_1 = double.MaxValue;
                double best_f_2 = double.MaxValue;
                var best_x_list_1 = new List<int[]>();
                var best_y_list_1 = new List<int[]>();
                var best_x_list_2 = new List<int[]>();
                var best_y_list_2 = new List<int[]>();
                var x_1 = new int[M1];
                var y_1 = new int[1];
                var x_2 = new int[1];
                var y_2 = new int[M2];
                x_1[M1 - 1] = n1 - 1;
                y_1[0] = n2 - 1;
                x_2[0] = n1 - 1;
                y_2[M2 - 1] = n2 - 1;

#if USE_MIN_DISPERSE_CRITERION
                CriterionDelegate initialStrategy1 = DispersionCriterion(w1);
                CriterionDelegate initialStrategy2 = DispersionCriterion(w2);
#else
                CriterionDelegate initialStrategy1 = MainCriterion;
                CriterionDelegate initialStrategy2 = MainCriterion;
#endif

                FullSearch(-1, M1, 1, n1, n2, x_1, y_1, v, ref best_f_1, ref d, best_x_list_1, best_y_list_1, initialStrategy1);
                FullSearch(-1, 1, M2, n1, n2, x_2, y_2, v, ref best_f_2, ref d, best_x_list_2, best_y_list_2, initialStrategy2);

                double stupid_f = MainCriterion(M1, M2, best_x_list_1[0], best_y_list_2[0], v);
                DisplaySolution(M1, M2, n1, n2, stupid_f, w, w1, w2, -1, -1, v, best_x_list_1[0], best_y_list_2[0]);

                Console.WriteLine();
                Console.WriteLine("f~ = {0}", stupid_f);

                if (TryGreedy(M1, M2, n1, n2, stupid_f, w, w1, w2, v, best_x_list_1[0], best_y_list_2[0]))
                {
                    double greedy_f = MainCriterion(M1, M2, best_x_list_1[0], best_y_list_2[0], v);
                    Console.WriteLine();
                    Console.WriteLine("Greedy f~ = {0}", greedy_f);
                }

                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine(new string('-', 70));
                Console.ResetColor();

                #endregion

                cursorPos = Console.CursorTop;

                d = -1;
                FullSearch(cursorPos, M1, M2, n1, n2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, MainCriterion);


                Console.CursorTop = cursorPos;

                if (Console.BufferHeight <= (best_x_list.Count + 1) * (2 * M2 + n2 + 5) + 20)
                    Console.BufferHeight = (best_x_list.Count + 1) * (2 * M2 + n2 + 5) + 20;

                Console.WriteLine("Best solutions:");

                DisplaySolutions(M1, M2, n1, n2, best_f, w, w1, w2, v, best_x_list, best_y_list);

                Console.WriteLine();
                Console.WriteLine("f* = {0}", best_f);

                Console.CursorTop = cursorPosOnEnd;

                Console.ReadLine();

                Console.Clear();
            }
        }

        private static void FullSearch(int cursorPos, int M1, int M2, int n1, int n2, int[] x, int[] y, int[,] v, ref double best_f, ref int d, List<int[]> best_x_list, List<int[]> best_y_list, CriterionDelegate criterion)
        {
            #region Полный перебор решений

            if (M1 == 1)
            {
                if (M2 == 1)
                {
                    CheckSolution(cursorPos, M1, M2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, criterion);
                }
                else
                {
                    FullSearchY(cursorPos, M1, M2, n2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, criterion);
                }
            }
            else
            {
                #region Полный перебор всех допустимых разбиений по x

                int currentX = 0;
                x[0] = 0;

                while (true)
                {
                    if (x[currentX] > n1 + currentX - M1)
                    {
                        currentX--;
                        if (currentX < 0)
                            break;
                        x[currentX]++;
                    }
                    else if (currentX < M1 - 2)
                    {
                        currentX++;
                        x[currentX] = x[currentX - 1] + 1;
                    }
                    else
                    {
                        if (M2 == 1)
                        {
                            CheckSolution(cursorPos, M1, M2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, criterion);
                        }
                        else
                        {
                            FullSearchY(cursorPos, M1, M2, n2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, criterion);
                        }
                        x[currentX]++;
                    }
                }

                #endregion
            }

            #endregion
        }

        private static void FullSearchY(int cursorPos, int M1, int M2, int n2, int[] x, int[] y, int[,] v, ref double best_f, ref int d, List<int[]> best_x_list, List<int[]> best_y_list, CriterionDelegate criterion)
        {
            #region Полный перебор всех допустимых разбиений по y

            int currentY = 0;
            y[0] = 0;

            while (true)
            {
                if (y[currentY] > n2 + currentY - M2)
                {
                    currentY--;
                    if (currentY < 0)
                        break;
                    y[currentY]++;
                }
                else if (currentY < M2 - 2)
                {
                    currentY++;
                    y[currentY] = y[currentY - 1] + 1;
                }
                else
                {
                    CheckSolution(cursorPos, M1, M2, x, y, v, ref best_f, ref d, best_x_list, best_y_list, criterion);

                    y[currentY]++;
                }
            }

            #endregion
        }

#if USE_MIN_DISPERSE_CRITERION
        private static CriterionDelegate DispersionCriterion(double w)
        {
            return delegate(int M1, int M2, int[] x, int[] y, int[,] v)
            {
                double result = 0;

                int lastx = -1;
                for (int i = 0; i < M1; i++)
                {
                    int lasty = -1;
                    for (int j = 0; j < M2; j++)
                    {
                        int s = 0;

                        for (int k = lastx + 1; k <= x[i]; k++)
                            for (int p = lasty + 1; p <= y[j]; p++)
                            {
                                s += v[k, p];
                            }

                        result += (s - w) * (s - w);

                        lasty = y[j];
                    }

                    lastx = x[i];
                }

                return result;
            };
        }
#endif

        private static double MainCriterion(int M1, int M2, int[] x, int[] y, int[,] v)
        {
            int result = 0;

            int lastx = -1;
            for (int i = 0; i < M1; i++)
            {
                int lasty = -1;
                for (int j = 0; j < M2; j++)
                {
                    int s = 0;

                    for (int k = lastx + 1; k <= x[i]; k++)
                        for (int p = lasty + 1; p <= y[j]; p++)
                        {
                            s += v[k, p];
                        }

                    result = Math.Max(result, s);

                    lasty = y[j];
                }

                lastx = x[i];
            }

            return result;
        }

        private static void CheckSolution(int cursorPos, int M1, int M2, int[] x, int[] y, int[,] v, ref double best_f, ref int d, List<int[]> best_x_list, List<int[]> best_y_list, CriterionDelegate criterion)
        {
            #region Проверка допустимого решения

            double f = criterion(M1, M2, x, y, v);

            if (f < best_f)
            {
                if (d <= 0)
                    d = f.ToString().Length;

                if (cursorPos >= 0)
                {
                    Console.CursorTop = cursorPos;
                    Console.WriteLine("f' = {0,-" + d + "}", f);
                }

                best_f = f;

                best_x_list.Clear();
                best_y_list.Clear();

                best_x_list.Add((int[])x.Clone());
                best_y_list.Add((int[])y.Clone());
            }
            else if (f == best_f)
            {
                best_x_list.Add((int[])x.Clone());
                best_y_list.Add((int[])y.Clone());
            }

            #endregion
        }

        private static void DisplaySolutions(int M1, int M2, int n1, int n2, double best_f, double w, double w1, double w2, int[,] v, IList<int[]> x_list, IList<int[]> y_list)
        {
            #region Выводим разбиения

            for (int b = 0; b < x_list.Count; b++)
            {
                var x = x_list[b];
                var y = y_list[b];

                DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, -1, -1, v, x, y);
            }

            #endregion
        }

        private static void DisplaySolution(int M1, int M2, int n1, int n2, double best_f, double w, double w1, double w2, int highlightx, int highlighty, int[,] v, int[] x, int[] y)
        {
            int lastx;
            int lasty;
            int d;
            string format;

            int[,] sum = new int[M1, M2];
            int[] sum1 = new int[M1];
            int[] sum2 = new int[M2];

            #region Считаем загрузки просессоров

            lastx = -1;
            for (int i = 0; i < M1; i++)
            {
                lasty = -1;
                for (int j = 0; j < M2; j++)
                {
                    int s = 0;

                    for (int k = lastx + 1; k <= x[i]; k++)
                        for (int p = lasty + 1; p <= y[j]; p++)
                        {
                            s += v[k, p];
                        }

                    sum[i, j] = s;

                    lasty = y[j];
                }

                lastx = x[i];
            }

            for (int i = 0; i < M1; i++)
            {
                int s = 0;
                for (int j = 0; j < M2; j++)
                {
                    s += sum[i, j];
                }
                sum1[i] += s;
            }

            for (int j = 0; j < M2; j++)
            {
                int s = 0;
                for (int i = 0; i < M1; i++)
                {
                    s += sum[i, j];
                }
                sum2[j] += s;
            }

            #endregion

            Console.WriteLine(new string(' ', 15));

            #region Выводим разбиение

            #region Узнаём самую длинное число

            d = 0;

            for (int i = 0; i < n1; i++)
                for (int j = 0; j < n2; j++)
                    d = Math.Max(d, v[i, j].ToString().Length);

            #endregion

            #region Выводим красивую табличку

            format = "{0,-" + d + "} ";

            #region Выводим линию из звёздочек

            lastx = -1;

            Console.Write("* ");

            for (int i = 0; i < M1; i++)
            {
                for (int k = lastx + 1; k <= x[i]; k++)
                {
                    Console.Write("{0} ", new string('*', d));
                }

                if (i == highlightx)
                    Console.ForegroundColor = ConsoleColor.Blue;
                Console.Write("* ");
                if (i == highlightx)
                    Console.ResetColor();
                lastx = x[i];
            }

            Console.WriteLine();

            #endregion

            lasty = -1;
            for (int j = 0; j < M2; j++)
            {
                for (int p = lasty + 1; p <= y[j]; p++)
                {
                    lastx = -1;
                    Console.Write("* ");

                    for (int i = 0; i < M1; i++)
                    {
                        Console.ForegroundColor = (sum[i, j] <= w) ? ConsoleColor.Green : ((sum[i, j] == best_f) ? ConsoleColor.Red : ConsoleColor.Yellow);
                        for (int k = lastx + 1; k <= x[i]; k++)
                        {
                            Console.Write(format, v[k, p]);
                        }
                        Console.ResetColor();

                        if (i == highlightx)
                            Console.ForegroundColor = ConsoleColor.Blue;
                        Console.Write("* ");
                        if (i == highlightx)
                            Console.ResetColor();
                        lastx = x[i];
                    }
                    Console.WriteLine();
                }

                #region Выводим линию из звёздочек

                lastx = -1;

                if (j == highlighty)
                    Console.ForegroundColor = ConsoleColor.Blue;
                Console.Write("* ");
                if (j == highlighty)
                    Console.ResetColor();

                for (int i = 0; i < M1; i++)
                {
                    if (j == highlighty)
                        Console.ForegroundColor = ConsoleColor.Blue;
                    for (int k = lastx + 1; k <= x[i]; k++)
                    {
                        Console.Write("{0} ", new string('*', d));
                    }

                    if (j == highlighty || i == highlightx)
                        Console.ForegroundColor = ConsoleColor.Blue;
                    Console.Write("* ");
                    if (j == highlighty || i == highlightx)
                        Console.ResetColor();

                    lastx = x[i];
                }

                Console.WriteLine();

                #endregion

                lasty = y[j];
            }

            Console.WriteLine();

            #endregion

            #endregion

            #region Выводим загрузки процессоров

            #region Узнаём самую длинную сумму

            d = 0;
            for (int i = 0; i < M1; i++)
            {
                for (int j = 0; j < M2; j++)
                {
                    d = Math.Max(d, sum[i, j].ToString().Length);
                }

                d = Math.Max(d, sum1[i].ToString().Length);
            }

            for (int j = 0; j < M2; j++)
            {
                d = Math.Max(d, sum2[j].ToString().Length);
            }

            #endregion

            #region Выводим табличку

            format = "{0,-" + d + "} ";
            for (int j = 0; j < M2; j++)
            {
                for (int i = 0; i < M1; i++)
                {
                    Console.ForegroundColor = (sum[i, j] <= w) ? ConsoleColor.Green : ((sum[i, j] == best_f) ? ConsoleColor.Red : ConsoleColor.Yellow);
                    Console.Write(format, sum[i, j]);
                    Console.ResetColor();
                }

                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.Write(" |  ");
                Console.ResetColor();

                Console.ForegroundColor = (sum2[j] <= w2) ? ConsoleColor.Green : ConsoleColor.Yellow;
                Console.Write(format, sum2[j]);
                Console.ResetColor();

                Console.WriteLine();

            }

            Console.ForegroundColor = ConsoleColor.Cyan;
            for (int i = 0; i < M1; i++)
            {
                Console.Write(new string('-', d + 1));
            }
            Console.Write("-+");
            Console.ResetColor();

            Console.WriteLine();

            for (int i = 0; i < M1; i++)
            {
                Console.ForegroundColor = (sum1[i] <= w1) ? ConsoleColor.Green : ConsoleColor.Yellow;
                Console.Write(format, sum1[i]);
                Console.ResetColor();
            }

            Console.WriteLine();

            #endregion

            #endregion
        }

        private static bool TryGreedy(int M1, int M2, int n1, int n2, double best_f, double w, double w1, double w2, int[,] v, int[] x, int[] y)
        {
            bool doneSmth = false;
            int[,] sum = new int[M1, M2];
            int[] deltaX = new int[M1];
            int[] deltaY = new int[M2];

            int lastx;
            int lasty;

            #region Считаем загрузки просессоров

            lastx = -1;
            for (int i = 0; i < M1; i++)
            {
                lasty = -1;
                for (int j = 0; j < M2; j++)
                {
                    int s = 0;

                    for (int k = lastx + 1; k <= x[i]; k++)
                        for (int p = lasty + 1; p <= y[j]; p++)
                        {
                            s += v[k, p];
                        }

                    sum[i, j] = s;

                    lasty = y[j];
                }

                lastx = x[i];
            }
            #endregion


            #region Считаем максимальные загрузки по каждой из осей

            int[] max1 = new int[M1];
            int[] max2 = new int[M2];

            for (int i = 0; i < M1; i++)
            {
                int m = 0;
                for (int j = 0; j < M2; j++)
                {
                    m = Math.Max(m, sum[i, j]);
                }
                max1[i] = m;
            }
            for (int j = 0; j < M2; j++)
            {
                int m = 0;
                for (int i = 0; i < M1; i++)
                {
                    m = Math.Max(m, sum[i, j]);
                }
                max2[j] = m;
            }

            #endregion

            while (true)
            {
                int movedI = -1;
                int movedJ = -1;

            tryMoveHor:
                #region Двигаем только горизонтальную линию

                for (int j = 0; j < M2 - 1; j++)
                {
                    bool canMoveUp = (j == 0 && y[0] > 0) || (j > 0 && y[j] > y[j - 1] + 1);
                    bool canMoveDown = y[j] < y[j + 1] - 1;

                    int old_f_2 = Math.Max(max2[j], max2[j + 1]);

                    if (canMoveUp)
                    {
                        #region Двигаем горизонтальную линию вверх

                        int up_max = 0;
                        int bottom_max = 0;

                        lastx = -1;
                        for (int I = 0; I < M1; I++)
                        {
                            int s = 0;

                            for (int p = lastx + 1; p <= x[I]; p++)
                            {
                                s += v[p, y[j]];
                            }

                            deltaX[I] = s;

                            up_max = Math.Max(up_max, sum[I, j] - s);
                            bottom_max = Math.Max(bottom_max, sum[I, j + 1] + s);

                            lastx = x[I];
                        }

                        if (Math.Max(up_max, bottom_max) < old_f_2)
                        {
                            y[j]--;

                            for (int I = 0; I < M1; I++)
                            {
                                bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                sum[I, j] -= deltaX[I];
                                sum[I, j + 1] += deltaX[I];

                                if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                {
                                    max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                }
                                else if (b)
                                {
                                    int m = 0;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        m = Math.Max(m, sum[I, J]);
                                    }
                                    max1[I] = m;
                                }
                            }

                            max2[j] = up_max;
                            max2[j + 1] = bottom_max;

                            if (old_f_2 == best_f)
                                best_f = MainCriterion(M1, M2, x, y, v);

                            movedJ = j;
                            if (movedI == -1)
                                goto tryMoveVert;
                            else
                                goto display;
                        }

                        #endregion
                    }

                    if (canMoveDown)
                    {
                        #region Двигаем горизонтальную линию вниз

                        int up_max = 0;
                        int bottom_max = 0;

                        lastx = -1;
                        for (int I = 0; I < M1; I++)
                        {
                            int s = 0;

                            for (int p = lastx + 1; p <= x[I]; p++)
                            {
                                s += v[p, y[j] + 1];
                            }

                            deltaX[I] = s;

                            up_max = Math.Max(up_max, sum[I, j] + s);
                            bottom_max = Math.Max(bottom_max, sum[I, j + 1] - s);

                            lastx = x[I];
                        }

                        if (Math.Max(up_max, bottom_max) < old_f_2)
                        {
                            y[j]++;

                            for (int I = 0; I < M1; I++)
                            {
                                bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                sum[I, j] += deltaX[I];
                                sum[I, j + 1] -= deltaX[I];

                                if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                {
                                    max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                }
                                else if (b)
                                {
                                    int m = 0;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        m = Math.Max(m, sum[I, J]);
                                    }
                                    max1[I] = m;
                                }
                            }

                            max2[j] = up_max;
                            max2[j + 1] = bottom_max;

                            if (old_f_2 == best_f)
                                best_f = MainCriterion(M1, M2, x, y, v);

                            movedJ = j;
                            if (movedI == -1)
                                goto tryMoveVert;
                            else
                                goto display;
                        }

                        #endregion
                    }
                }

                #endregion

            tryMoveVert:
                #region Двигаем только вертикальную линию

                for (int i = 0; i < M1 - 1; i++)
                {
                    bool canMoveLeft = (i == 0 && x[0] > 0) || (i > 0 && x[i] > x[i - 1] + 1);
                    bool canMoveRight = x[i] < x[i + 1] - 1;

                    int old_f_1 = Math.Max(max1[i], max1[i + 1]);

                    if (canMoveLeft)
                    {
                        #region Двигаем вертикальную линию влево

                        int left_max = 0;
                        int right_max = 0;

                        lasty = -1;
                        for (int J = 0; J < M2; J++)
                        {
                            int s = 0;

                            for (int p = lasty + 1; p <= y[J]; p++)
                            {
                                s += v[x[i], p];
                            }

                            deltaY[J] = s;

                            left_max = Math.Max(left_max, sum[i, J] - s);
                            right_max = Math.Max(right_max, sum[i + 1, J] + s);

                            lasty = y[J];
                        }

                        if (Math.Max(left_max, right_max) < old_f_1)
                        {
                            x[i]--;

                            for (int J = 0; J < M2; J++)
                            {
                                bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                sum[i, J] -= deltaY[J];
                                sum[i + 1, J] += deltaY[J];

                                if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                {
                                    max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                }
                                else if (b)
                                {
                                    int m = 0;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        m = Math.Max(m, sum[I, J]);
                                    }
                                    max2[J] = m;
                                }
                            }

                            max1[i] = left_max;
                            max1[i + 1] = right_max;

                            if (old_f_1 == best_f)
                                best_f = MainCriterion(M1, M2, x, y, v);

                            movedI = i;
                            if (movedJ == -1)
                                goto tryMoveHor;
                            else
                                goto display;
                        }

                        #endregion
                    }

                    if (canMoveRight)
                    {
                        #region Двигаем вертикальную линию вправо

                        int left_max = 0;
                        int right_max = 0;

                        lasty = -1;
                        for (int J = 0; J < M2; J++)
                        {
                            int s = 0;

                            for (int p = lasty + 1; p <= y[J]; p++)
                            {
                                s += v[x[i] + 1, p];
                            }

                            deltaY[J] = s;

                            left_max = Math.Max(left_max, sum[i, J] + s);
                            right_max = Math.Max(right_max, sum[i + 1, J] - s);

                            lasty = y[J];
                        }

                        if (Math.Max(left_max, right_max) < old_f_1)
                        {
                            x[i]++;

                            for (int J = 0; J < M2; J++)
                            {
                                bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                sum[i, J] += deltaY[J];
                                sum[i + 1, J] -= deltaY[J];

                                if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                {
                                    max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                }
                                else if (b)
                                {
                                    int m = 0;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        m = Math.Max(m, sum[I, J]);
                                    }
                                    max2[J] = m;
                                }
                            }

                            max1[i] = left_max;
                            max1[i + 1] = right_max;

                            if (old_f_1 == best_f)
                                best_f = MainCriterion(M1, M2, x, y, v);

                            movedI = i;
                            if (movedJ == -1)
                                goto tryMoveHor;
                            else
                                goto display;
                        }

                        #endregion
                    }

                }

                #endregion

                if (movedI > -1 || movedJ > -1)
                    goto display;

                for (int i = 0; i < M1 - 1; i++)
                {
                    bool canMoveLeft = (i == 0 && x[0] > 0) || (i > 0 && x[i] > x[i - 1] + 1);
                    bool canMoveRight = x[i] < x[i + 1] - 1;

                    int old_f_1 = Math.Max(max1[i], max1[i + 1]);

                    if (canMoveLeft || canMoveRight)
                    {
                        #region Двигаем точку по диагонали

                        for (int j = 0; j < M2 - 1; j++)
                        {
                            bool canMoveUp = (j == 0 && y[0] > 0) || (j > 0 && y[j] > y[j - 1] + 1);
                            bool canMoveDown = y[j] < y[j + 1] - 1;

                            int old_f_2 = Math.Max(max2[j], max2[j + 1]);
                            int old_f = Math.Max(old_f_1, old_f_2);

                            if (canMoveLeft)
                            {
                                if (canMoveUp)
                                {
                                    #region Двигаем точку влево вверх

                                    int left_max = 0;
                                    int right_max = 0;

                                    lasty = -1;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        if (J == j || J == j + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lasty + 1; p <= y[J]; p++)
                                        {
                                            s += v[x[i], p];
                                        }

                                        deltaY[J] = s;

                                        left_max = Math.Max(left_max, sum[i, J] - s);
                                        right_max = Math.Max(right_max, sum[i + 1, J] + s);

                                        lasty = y[J];
                                    }

                                    if (Math.Max(left_max, right_max) >= old_f)
                                        goto checkMoveLeftDown;

                                    int up_max = 0;
                                    int bottom_max = 0;

                                    lastx = -1;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        if (I == i || I == i + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lastx + 1; p <= x[I]; p++)
                                        {
                                            s += v[p, y[j]];
                                        }

                                        deltaX[I] = s;

                                        up_max = Math.Max(up_max, sum[I, j] - s);
                                        bottom_max = Math.Max(bottom_max, sum[I, j + 1] + s);

                                        lastx = x[I];
                                    }

                                    if (Math.Max(up_max, bottom_max) >= old_f)
                                        goto checkMoveLeftDown;

                                    int leftBound;
                                    int rightBound = x[i + 1];
                                    int upBound;
                                    int bottomBound = y[j + 1];

                                    if (i == 0)
                                        leftBound = 0;
                                    else
                                        leftBound = x[i - 1] + 1;

                                    if (j == 0)
                                        upBound = 0;
                                    else
                                        upBound = y[j - 1] + 1;

                                    int A = 0;
                                    int B = 0;
                                    int C = 0;
                                    int D = 0;

                                    for (int k = leftBound; k < x[i]; k++)
                                    {
                                        for (int p = upBound; p < y[j]; p++)
                                        {
                                            A += v[k, p];
                                        }
                                        for (int p = y[j]; p <= bottomBound; p++)
                                        {
                                            C += v[k, p];
                                        }
                                    }

                                    if (Math.Max(A, C) > old_f)
                                        goto checkMoveLeftDown;

                                    for (int k = x[i]; k <= rightBound; k++)
                                    {
                                        for (int p = upBound; p < y[j]; p++)
                                        {
                                            B += v[k, p];
                                        }
                                        for (int p = y[j]; p <= bottomBound; p++)
                                        {
                                            D += v[k, p];
                                        }
                                    }

                                    if (Math.Max(Math.Max(A, B), Math.Max(C, D)) < old_f)
                                    {
                                        x[i]--;
                                        y[j]--;

                                        for (int J = 0; J < M2; J++)
                                        {
                                            if (J == j || J == j + 1)
                                                continue;

                                            bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                            sum[i, J] -= deltaY[J];
                                            sum[i + 1, J] += deltaY[J];

                                            if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                            {
                                                max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int I = 0; I < M1; I++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max2[J] = m;
                                            }
                                        }

                                        for (int I = 0; I < M1; I++)
                                        {
                                            if (I == i || I == i + 1)
                                                continue;

                                            bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                            sum[I, j] -= deltaX[I];
                                            sum[I, j + 1] += deltaX[I];

                                            if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                            {
                                                max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int J = 0; J < M2; J++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max1[I] = m;
                                            }
                                        }

                                        max1[i] = Math.Max(Math.Max(A, C), left_max);
                                        max1[i + 1] = Math.Max(Math.Max(B, D), right_max);
                                        max2[j] = Math.Max(Math.Max(A, B), up_max);
                                        max2[j + 1] = Math.Max(Math.Max(C, D), bottom_max);

                                        sum[i, j] = A;
                                        sum[i + 1, j] = B;
                                        sum[i, j + 1] = C;
                                        sum[i + 1, j + 1] = D;

                                        if (old_f == best_f)
                                            best_f = MainCriterion(M1, M2, x, y, v);

                                        DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, i, j, v, x, y);
                                        goto next;
                                    }

                                    #endregion
                                }

                            checkMoveLeftDown:
                                if (canMoveDown)
                                {
                                    #region Двигаем точку влево вниз

                                    int left_max = 0;
                                    int right_max = 0;

                                    lasty = -1;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        if (J == j || J == j + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lasty + 1; p <= y[J]; p++)
                                        {
                                            s += v[x[i], p];
                                        }

                                        deltaY[J] = s;

                                        left_max = Math.Max(left_max, sum[i, J] - s);
                                        right_max = Math.Max(right_max, sum[i + 1, J] + s);

                                        lasty = y[J];
                                    }

                                    if (Math.Max(left_max, right_max) >= old_f)
                                        goto checkMoveRight;

                                    int up_max = 0;
                                    int bottom_max = 0;

                                    lastx = -1;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        if (I == i || I == i + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lastx + 1; p <= x[I]; p++)
                                        {
                                            s += v[p, y[j] + 1];
                                        }

                                        deltaX[I] = s;

                                        up_max = Math.Max(up_max, sum[I, j] + s);
                                        bottom_max = Math.Max(bottom_max, sum[I, j + 1] - s);

                                        lastx = x[I];
                                    }

                                    if (Math.Max(up_max, bottom_max) >= old_f)
                                        goto checkMoveRight;

                                    int leftBound;
                                    int rightBound = x[i + 1];
                                    int upBound;
                                    int bottomBound = y[j + 1];

                                    if (i == 0)
                                        leftBound = 0;
                                    else
                                        leftBound = x[i - 1] + 1;

                                    if (j == 0)
                                        upBound = 0;
                                    else
                                        upBound = y[j - 1] + 1;

                                    int A = 0;
                                    int B = 0;
                                    int C = 0;
                                    int D = 0;

                                    for (int k = leftBound; k < x[i]; k++)
                                    {
                                        for (int p = upBound; p < y[j] + 2; p++)
                                        {
                                            A += v[k, p];
                                        }
                                        for (int p = y[j] + 2; p <= bottomBound; p++)
                                        {
                                            C += v[k, p];
                                        }
                                    }

                                    if (Math.Max(A, C) > old_f)
                                        goto checkMoveRight;

                                    for (int k = x[i]; k <= rightBound; k++)
                                    {
                                        for (int p = upBound; p < y[j] + 2; p++)
                                        {
                                            B += v[k, p];
                                        }
                                        for (int p = y[j] + 2; p <= bottomBound; p++)
                                        {
                                            D += v[k, p];
                                        }
                                    }

                                    if (Math.Max(Math.Max(A, B), Math.Max(C, D)) < old_f)
                                    {
                                        x[i]--;
                                        y[j]++;

                                        for (int J = 0; J < M2; J++)
                                        {
                                            if (J == j || J == j + 1)
                                                continue;

                                            bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                            sum[i, J] -= deltaY[J];
                                            sum[i + 1, J] += deltaY[J];

                                            if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                            {
                                                max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int I = 0; I < M1; I++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max2[J] = m;
                                            }
                                        }

                                        for (int I = 0; I < M1; I++)
                                        {
                                            if (I == i || I == i + 1)
                                                continue;

                                            bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                            sum[I, j] += deltaX[I];
                                            sum[I, j + 1] -= deltaX[I];

                                            if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                            {
                                                max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int J = 0; J < M2; J++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max1[I] = m;
                                            }
                                        }

                                        sum[i, j] = A;
                                        sum[i + 1, j] = B;
                                        sum[i, j + 1] = C;
                                        sum[i + 1, j + 1] = D;

                                        max1[i] = Math.Max(Math.Max(A, C), left_max);
                                        max1[i + 1] = Math.Max(Math.Max(B, D), right_max);
                                        max2[j] = Math.Max(Math.Max(A, B), up_max);
                                        max2[j + 1] = Math.Max(Math.Max(C, D), bottom_max);

                                        if (old_f == best_f)
                                            best_f = MainCriterion(M1, M2, x, y, v);

                                        DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, i, j, v, x, y);
                                        goto next;
                                    }

                                    #endregion
                                }
                            }

                        checkMoveRight:
                            if (canMoveRight)
                            {
                                if (canMoveUp)
                                {
                                    #region Двигаем точку вправо вверх

                                    int left_max = 0;
                                    int right_max = 0;

                                    lasty = -1;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        if (J == j || J == j + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lasty + 1; p <= y[J]; p++)
                                        {
                                            s += v[x[i] + 1, p];
                                        }

                                        deltaY[J] = s;

                                        left_max = Math.Max(left_max, sum[i, J] + s);
                                        right_max = Math.Max(right_max, sum[i + 1, J] - s);

                                        lasty = y[J];
                                    }

                                    if (Math.Max(left_max, right_max) >= old_f)
                                        goto checkMoveRightDown;

                                    int up_max = 0;
                                    int bottom_max = 0;

                                    lastx = -1;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        if (I == i || I == i + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lastx + 1; p <= x[I]; p++)
                                        {
                                            s += v[p, y[j]];
                                        }

                                        deltaX[I] = s;

                                        up_max = Math.Max(up_max, sum[I, j] - s);
                                        bottom_max = Math.Max(bottom_max, sum[I, j + 1] + s);

                                        lastx = x[I];
                                    }

                                    if (Math.Max(up_max, bottom_max) >= old_f)
                                        goto checkMoveRightDown;

                                    int leftBound;
                                    int rightBound = x[i + 1];
                                    int upBound;
                                    int bottomBound = y[j + 1];

                                    if (i == 0)
                                        leftBound = 0;
                                    else
                                        leftBound = x[i - 1] + 1;

                                    if (j == 0)
                                        upBound = 0;
                                    else
                                        upBound = y[j - 1] + 1;

                                    int A = 0;
                                    int B = 0;
                                    int C = 0;
                                    int D = 0;

                                    for (int k = leftBound; k < x[i] + 2; k++)
                                    {
                                        for (int p = upBound; p < y[j]; p++)
                                        {
                                            A += v[k, p];
                                        }
                                        for (int p = y[j]; p <= bottomBound; p++)
                                        {
                                            C += v[k, p];
                                        }
                                    }

                                    if (Math.Max(A, C) > old_f)
                                        goto checkMoveRightDown;

                                    for (int k = x[i] + 2; k <= rightBound; k++)
                                    {
                                        for (int p = upBound; p < y[j]; p++)
                                        {
                                            B += v[k, p];
                                        }
                                        for (int p = y[j]; p <= bottomBound; p++)
                                        {
                                            D += v[k, p];
                                        }
                                    }

                                    if (Math.Max(Math.Max(A, B), Math.Max(C, D)) < old_f)
                                    {
                                        x[i]++;
                                        y[j]--;

                                        for (int J = 0; J < M2; J++)
                                        {
                                            if (J == j || J == j + 1)
                                                continue;

                                            bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                            sum[i, J] += deltaY[J];
                                            sum[i + 1, J] -= deltaY[J];

                                            if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                            {
                                                max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int I = 0; I < M1; I++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max2[J] = m;
                                            }
                                        }

                                        for (int I = 0; I < M1; I++)
                                        {
                                            if (I == i || I == i + 1)
                                                continue;

                                            bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                            sum[I, j] -= deltaX[I];
                                            sum[I, j + 1] += deltaX[I];

                                            if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                            {
                                                max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int J = 0; J < M2; J++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max1[I] = m;
                                            }
                                        }

                                        sum[i, j] = A;
                                        sum[i + 1, j] = B;
                                        sum[i, j + 1] = C;
                                        sum[i + 1, j + 1] = D;

                                        max1[i] = Math.Max(Math.Max(A, C), left_max);
                                        max1[i + 1] = Math.Max(Math.Max(B, D), right_max);
                                        max2[j] = Math.Max(Math.Max(A, B), up_max);
                                        max2[j + 1] = Math.Max(Math.Max(C, D), bottom_max);

                                        if (old_f == best_f)
                                            best_f = MainCriterion(M1, M2, x, y, v);

                                        DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, i, j, v, x, y);
                                        goto next;
                                    }

                                    #endregion
                                }

                            checkMoveRightDown:
                                if (canMoveDown)
                                {
                                    #region Двигаем точку вправо вниз

                                    int left_max = 0;
                                    int right_max = 0;

                                    lasty = -1;
                                    for (int J = 0; J < M2; J++)
                                    {
                                        if (J == j || J == j + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lasty + 1; p <= y[J]; p++)
                                        {
                                            s += v[x[i] + 1, p];
                                        }

                                        deltaY[J] = s;

                                        left_max = Math.Max(left_max, sum[i, J] + s);
                                        right_max = Math.Max(right_max, sum[i + 1, J] - s);

                                        lasty = y[J];
                                    }

                                    if (Math.Max(left_max, right_max) >= old_f)
                                        continue;

                                    int up_max = 0;
                                    int bottom_max = 0;

                                    lastx = -1;
                                    for (int I = 0; I < M1; I++)
                                    {
                                        if (I == i || I == i + 1)
                                            continue;

                                        int s = 0;

                                        for (int p = lastx + 1; p <= x[I]; p++)
                                        {
                                            s += v[p, y[j] + 1];
                                        }

                                        deltaX[I] = s;

                                        up_max = Math.Max(up_max, sum[I, j] + s);
                                        bottom_max = Math.Max(bottom_max, sum[I, j + 1] - s);

                                        lastx = x[I];
                                    }

                                    if (Math.Max(up_max, bottom_max) >= old_f)
                                        continue;

                                    int leftBound;
                                    int rightBound = x[i + 1];
                                    int upBound;
                                    int bottomBound = y[j + 1];

                                    if (i == 0)
                                        leftBound = 0;
                                    else
                                        leftBound = x[i - 1] + 1;

                                    if (j == 0)
                                        upBound = 0;
                                    else
                                        upBound = y[j - 1] + 1;

                                    int A = 0;
                                    int B = 0;
                                    int C = 0;
                                    int D = 0;

                                    for (int k = leftBound; k < x[i] + 2; k++)
                                    {
                                        for (int p = upBound; p < y[j] + 2; p++)
                                        {
                                            A += v[k, p];
                                        }
                                        for (int p = y[j] + 2; p <= bottomBound; p++)
                                        {
                                            C += v[k, p];
                                        }
                                    }

                                    if (Math.Max(A, C) > old_f)
                                        continue;

                                    for (int k = x[i] + 2; k <= rightBound; k++)
                                    {
                                        for (int p = upBound; p < y[j] + 2; p++)
                                        {
                                            B += v[k, p];
                                        }
                                        for (int p = y[j] + 2; p <= bottomBound; p++)
                                        {
                                            D += v[k, p];
                                        }
                                    }

                                    if (Math.Max(Math.Max(A, B), Math.Max(C, D)) < old_f)
                                    {
                                        x[i]++;
                                        y[j]++;

                                        for (int J = 0; J < M2; J++)
                                        {
                                            if (J == j || J == j + 1)
                                                continue;

                                            bool b = sum[i, J] == max2[J] || sum[i + 1, J] == max2[J];
                                            sum[i, J] += deltaY[J];
                                            sum[i + 1, J] -= deltaY[J];

                                            if (sum[i, J] > max2[J] || sum[i + 1, J] > max2[J])
                                            {
                                                max2[J] = Math.Max(sum[i, J], sum[i + 1, J]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int I = 0; I < M1; I++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max2[J] = m;
                                            }
                                        }

                                        for (int I = 0; I < M1; I++)
                                        {
                                            if (I == i || I == i + 1)
                                                continue;

                                            bool b = sum[I, j] == max1[I] || sum[I, j + 1] == max1[I];

                                            sum[I, j] += deltaX[I];
                                            sum[I, j + 1] -= deltaX[I];

                                            if (sum[I, j] > max1[I] || sum[I, j + 1] > max1[I])
                                            {
                                                max1[I] = Math.Max(sum[I, j], sum[I, j + 1]);
                                            }
                                            else if (b)
                                            {
                                                int m = 0;
                                                for (int J = 0; J < M2; J++)
                                                {
                                                    m = Math.Max(m, sum[I, J]);
                                                }
                                                max1[I] = m;
                                            }
                                        }

                                        sum[i, j] = A;
                                        sum[i + 1, j] = B;
                                        sum[i, j + 1] = C;
                                        sum[i + 1, j + 1] = D;

                                        max1[i] = Math.Max(Math.Max(A, C), left_max);
                                        max1[i + 1] = Math.Max(Math.Max(B, D), right_max);
                                        max2[j] = Math.Max(Math.Max(A, B), up_max);
                                        max2[j + 1] = Math.Max(Math.Max(C, D), bottom_max);

                                        if (old_f == best_f)
                                            best_f = MainCriterion(M1, M2, x, y, v);

                                        DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, i, j, v, x, y);
                                        goto next;
                                    }

                                    #endregion
                                }
                            }

                        }

                        #endregion
                    }
                }

                break;
            display:
                DisplaySolution(M1, M2, n1, n2, best_f, w, w1, w2, movedI, movedJ, v, x, y);
                goto next;
            next:
                doneSmth = true;
            }

            return doneSmth;
        }
    }
}


