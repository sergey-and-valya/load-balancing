using AlgorithmPluginCore;
using Core;
using CoreImpl2D;
using LoadBalancing;

namespace FullSearchAlgorithm
{
    internal class FullSearchAlgorithm2D : IAlgorithm<int, LoadBalancingProblem>
    {
        public ISolution Run(LoadBalancingProblem problem)
        {
            var criterium = problem.Criterium;
            var matrix = problem.Matrix;

            double best_f = double.MaxValue;
            int[] best_x = null;
            int[] best_y = null;
            bool best_x_changed = false;

            int m = problem.Matrix.Size(0);
            int n = problem.Matrix.Size(1);

            int M = problem.Parameters[0];
            int N = problem.Parameters[1];
            
            int[] x = new int[M - 1];
            int[] y = new int[N - 1];

            var solution = new ArraySolution(x, y);

            if (M == 1)
            {
                best_x = x;

                if (N == 1)
                {
                    best_y = y;
                }
                else
                {
                    int currentY = 0;
                    y[0] = 1;

                    while (true)
                    {
                        if (y[currentY] > n + currentY - N)
                        {
                            currentY--;
                            if (currentY < 0)
                                break;
                            y[currentY]++;
                        }
                        else if (currentY < N - 2)
                        {
                            currentY++;
                            y[currentY] = y[currentY - 1] + 1;
                        }
                        else
                        {
                            double f = criterium.Value(matrix, solution);

                            if (f < best_f)
                            {
                                best_f = f;

                                best_y = (int[]) y.Clone();
                            }

                            y[currentY]++;
                        }
                    }
                }
            }
            else
            {
                int currentX = 0;
                x[0] = 1;

                while (true)
                {
                    if (x[currentX] > m + currentX - M)
                    {
                        currentX--;
                        if (currentX < 0)
                            break;
                        x[currentX]++;
                    }
                    else if (currentX < M - 2)
                    {
                        currentX++;
                        x[currentX] = x[currentX - 1] + 1;
                    }
                    else
                    {


                        int currentY = 0;
                        y[0] = 1;

                        while (true)
                        {
                            if (y[currentY] > n + currentY - N)
                            {
                                currentY--;
                                if (currentY < 0)
                                    break;
                                y[currentY]++;
                            }
                            else if (currentY < N - 2)
                            {
                                currentY++;
                                y[currentY] = y[currentY - 1] + 1;
                            }
                            else
                            {
                                double f = criterium.Value(matrix, solution);

                                if (f < best_f)
                                {
                                    best_f = f;

                                    best_y = (int[]) y.Clone();
                                    best_x_changed = true;
                                }

                                y[currentY]++;
                            }
                        }

                        if (best_x_changed)
                        {
                            best_x = (int[]) x.Clone();
                            best_x_changed = false;
                        }

                        x[currentX]++;
                    }
                }
            }
            return new ArraySolution(best_x, best_y);
        }
    }
}
