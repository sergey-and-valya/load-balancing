using AlgorithmPluginCore;
using Core;
using CoreImpl1D;
using LoadBalancing;

namespace GreedyAlgorithm
{
    internal class StupidAlgorithm1D : IAlgorithm<int, LoadBalancingProblem>
    {
        public ISolution Run(LoadBalancingProblem problem)
        {
            int M = problem.Parameters[0];
            int[] x = new int[M - 1];
            VectorWrapper<int> v = new VectorWrapper<int>(problem.Matrix);
            int n = v.N;

            double w = LoadBalancing.Utilities.W(v, problem.Parameters);

            int[] p = new int[n];
            p[0] = v[0];

            for (int i = 1; i < n; i++)
            {
                p[i] = p[i - 1] + v[i];
            }

            for (int i = 0; i < M - 1; i++)
            {
                double point = w * (i + 1);

                if (point < p[0])
                {
                    x[i] = 1;
                }

                if (p[n - 1] <= point)
                {
                    x[i] = n - 1;
                }

                for (int j = 0; j < n - 1; j++)
                {
                    if (p[j] <= point && point < p[j + 1])
                    {
                        if (point - p[j] < p[j + 1] - point)
                            x[i] = j + 1;
                        else
                            x[i] = j + 2;

                        break;
                    }
                }
            }
            
            return new Solution1D(x);
        }
    }
}
