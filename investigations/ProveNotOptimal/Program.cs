using System;
using System.Diagnostics;

namespace ProveNotOptimal
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                const int n = 20;
                const int M = 4;
                const int A = 1; //v[i] = A..B
                const int B = 4; //v[i] = A..B

                Debug.Assert(M > 0);
                Debug.Assert(M <= n);

                int[] v = new int[n];
                int[] x = new int[M];
                int[] y = new int[M];

                int[] p = new int[n];
                int V = 0;
                double w = 0;
                int f = 0;
                int bestf = int.MaxValue;

                Random rnd = new Random();

                bool found = false;
                bool headerShown = false;

                x[M - 1] = n - 1;
                y[M - 1] = n - 1;

                while (!found)
                {
                    #region Генерация исходных данных

                    for (int j = 0; j < n; j++)
                    {
                        v[j] = rnd.Next(B - A + 1) + A;
                    }

                    #endregion

                    #region Нахождение решения предложенным алгоритмом

                    V = v[0];
                    p[0] = v[0];

                    for (int j = 1; j < n; j++)
                    {
                        p[j] = v[j] + p[j - 1];
                        V = Math.Max(V, v[j]);
                    }

                    w = (double) p[n - 1]/M;

                    for (int i = 0; i < M - 1; i++)
                    {
                        double point = w*(i + 1);

                        for (int j = 0; j < n; j++)
                        {
                            if (p[j] <= point && point < p[j + 1])
                            {
                                if (point - p[j] < p[j + 1] - point)
                                    x[i] = j;
                                else
                                    x[i] = j + 1;

                                break;
                            }
                        }
                    }

                    #endregion

                    #region Вычисление полученного значения критерия

                    f = 0;

                    int lastx = -1;
                    for (int i = 0; i < M; i++)
                    {
                        int s = 0;
                        for (int j = lastx + 1; j <= x[i]; j++)
                        {
                            s += v[j];
                        }
                        f = Math.Max(f, s);

                        lastx = x[i];
                    }

                    #endregion


                    #region Полный перебор всех допустимых разбиений

                    int current = 0;
                    y[0] = 0;

                    while (true)
                    {
                        if (y[current] > n + current - M)
                        {
                            current--;
                            if (current < 0)
                                break;
                            y[current]++;
                        }
                        else if (current < M - 2)
                        {
                            current++;
                            y[current] = y[current - 1] + 1;
                        }
                        else
                        {
                            #region Проверка допустимого решения

                            int newf = 0;

                            int lasty = -1;
                            for (int i = 0; i < M; i++)
                            {
                                int s = 0;
                                for (int j = lasty + 1; j <= y[i]; j++)
                                {
                                    s += v[j];
                                }
                                lasty = y[i];

                                newf = Math.Max(newf, s);
                            }

                            if (newf < f)
                            {
                                found = true;

                                if (!headerShown)
                                {
                                    #region Выводим первые строчки

                                    #region Выводим исходные данные

                                    Console.WriteLine("n = {0}", n);
                                    Console.WriteLine("M = {0}", M);

                                    Console.Write("v = [ ");
                                    for (int j = 0; j < n; j++)
                                    {
                                        if (j > 0)
                                            Console.Write(", ");
                                        Console.Write("{0}", v[j]);
                                    }
                                    Console.WriteLine(" ]");
                                    Console.WriteLine();

                                    Console.WriteLine("V = {0}", V);
                                    Console.WriteLine("w = {0}", w);

                                    #endregion

                                    Console.WriteLine();
                                    Console.WriteLine(new string('-', 70));
                                    Console.WriteLine();

                                    #region Выводим решение, полученное предложенным алгоритмом

                                    lastx = -1;
                                    for (int i = 0; i < M; i++)
                                    {
                                        Console.Write("[ ");
                                        for (int j = lastx + 1; j <= x[i]; j++)
                                        {
                                            if (j > lastx + 1)
                                                Console.Write(", ");
                                            Console.Write("{0}", v[j]);
                                        }
                                        Console.Write(" ]  ");
                                        lastx = x[i];
                                    }
                                    Console.WriteLine();

                                    Console.Write("[ ");
                                    lastx = -1;
                                    for (int i = 0; i < M; i++)
                                    {
                                        double s = 0;
                                        for (int j = lastx + 1; j <= x[i]; j++)
                                        {
                                            s += v[j];
                                        }
                                        if (i > 0)
                                            Console.Write(", ");
                                        Console.Write("{0}", s);
                                        lastx = x[i];
                                    }
                                    Console.WriteLine(" ]");

                                    #endregion

                                    Console.WriteLine("f' = {0}", f);

                                    Console.WriteLine();
                                    Console.WriteLine(new string('-', 70));
                                    Console.WriteLine();

                                    #endregion

                                    headerShown = true;
                                }


                                #region Выводим решение с меньшим критерием

                                lasty = -1;
                                for (int i = 0; i < M; i++)
                                {
                                    Console.Write("[ ");
                                    for (int j = lasty + 1; j <= y[i]; j++)
                                    {
                                        if (j > lasty + 1)
                                            Console.Write(", ");
                                        Console.Write("{0}", v[j]);
                                    }
                                    Console.Write(" ]  ");
                                    lasty = y[i];
                                }
                                Console.WriteLine();

                                Console.Write("[ ");
                                lasty = -1;
                                for (int i = 0; i < M; i++)
                                {
                                    double s = 0;
                                    for (int j = lasty + 1; j <= y[i]; j++)
                                    {
                                        s += v[j];
                                    }
                                    if (i > 0)
                                        Console.Write(", ");
                                    Console.Write("{0}", s);
                                    lasty = y[i];
                                }
                                Console.WriteLine(" ]");

                                Console.WriteLine("f = {0}", newf);
                                Console.WriteLine();
                                Console.WriteLine();

                                #endregion

                                bestf = Math.Min(bestf, newf);
                            }

                            y[current]++;

                            #endregion
                        }
                    }

                    #endregion
                }


                Console.WriteLine();
                Console.WriteLine(new string('-', 70));
                Console.WriteLine();

                Console.WriteLine("f' = {0}", f);
                Console.WriteLine("f* = {0}", bestf);

                Console.WriteLine(new string('=', 70));
                Console.ReadLine();
                Console.WriteLine();
                Console.WriteLine(new string('=', 70));
            }
        }
    }
}
