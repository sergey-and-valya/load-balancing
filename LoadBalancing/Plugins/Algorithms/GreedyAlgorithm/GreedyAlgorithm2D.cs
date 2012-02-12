using System.Linq;
using AlgorithmPluginCore;
using Core;
using CoreImpl2D;
using LoadBalancing;

namespace GreedyAlgorithm
{
    internal class GreedyAlgorithm2D : IAlgorithm<int, LoadBalancingProblem>
    {
        public GreedyAlgorithm2D(IAlgorithm<int, LoadBalancingProblem> auxilary)
        {
            this.auxilary = auxilary;
        }

        public ISolution Run(LoadBalancingProblem problem)
        {
            var startSolution = auxilary.Run(problem);

            int[] x = startSolution[0].ToArray();
            int[] y = startSolution[1].ToArray();

            var solution = new ArraySolution(x, y);
            var m = new SplittedMatrix(problem.Matrix, solution);

            while (true)
            {
                bool result = false;

                for (int I = 0; I < x.Length; I++)
                    for (int J = 0; J < y.Length; J++)
                    {
                        result |= LocalProcedure(x, y, m, I, J);
                    }

                if (!result)
                    break;
            }

            return solution;
        }

        private bool LocalProcedure(int[] x, int[] y, SplittedMatrix matrix, int I, int J)
        {
            int max;

            max = LocalMaximumHorizontal(matrix, I);

            if (TryToMoveHorizontal(max, 1, x, I, matrix))
                return true;

            if (TryToMoveHorizontal(max, -1, x, I, matrix))
                return true;

            max = LocalMaximumVertical(matrix, J);

            if (TryToMoveVertical(max, 1, y, J, matrix))
                return true;

            if (TryToMoveVertical(max, -1, y, J, matrix))
                return true;

            max = LocalMaximumDiag(matrix, I, J);

            if (TryToMoveDiag(max, -1, -1, x, y, I, J, matrix))
                return true;

            if (TryToMoveDiag(max, -1, 1, x, y, I, J, matrix))
                return true;

            if (TryToMoveDiag(max, 1, -1, x, y, I, J, matrix))
                return true;

            if (TryToMoveDiag(max, 1, 1, x, y, I, J, matrix))
                return true;

            return false;
        }

        private int LocalMaximumDiag(SplittedMatrix matrix, int I, int J)
        {
            int max = 0;

            var index = new Index2D();

            for (index.I = I; index.I <= I + 1; index.I++)
                for (index.J = 0; index.J < matrix.Size(1); index.J++)
                {
                    if (max < matrix[index])
                    {
                        max = matrix[index];
                    }
                }

            for (index.J = J; index.J <= J + 1; index.J++)
                for (index.I = 0; index.I < matrix.Size(0); index.I++)
                {
                    if (max < matrix[index])
                    {
                        max = matrix[index];
                    }
                }
            return max;
        }


        private int LocalMaximumHorizontal(SplittedMatrix matrix, int I)
        {
            int max = 0;

            var index = new Index2D();

            for (index.I = I; index.I <= I + 1; index.I++)
                for (index.J = 0; index.J < matrix.Size(1); index.J++)
                {
                    if (max < matrix[index])
                    {
                        max = matrix[index];
                    }
                }

            return max;
        }


        private int LocalMaximumVertical(SplittedMatrix matrix, int J)
        {
            int max = 0;

            var index = new Index2D();

            for (index.J = J; index.J <= J + 1; index.J++)
                for (index.I = 0; index.I < matrix.Size(0); index.I++)
                {
                    if (max < matrix[index])
                    {
                        max = matrix[index];
                    }
                }

            return max;
        }

        private bool TryToMoveDiag(int max, int deltai, int deltaj, int[] x, int[] y, int I, int J, SplittedMatrix matrix)
        {
            x[I] = x[I] + deltai;
            y[J] = y[J] + deltaj;

            if (LocalMaximumDiag(matrix, I, J) < max)
                return true;

            x[I] = x[I] - deltai;
            y[J] = y[J] - deltaj;

            return false;
        }

        private bool TryToMoveVertical(int max, int deltaj, int[] y, int J, SplittedMatrix matrix)
        {
            y[J] = y[J] + deltaj;

            if (LocalMaximumVertical(matrix, J) < max)
                return true;

            y[J] = y[J] - deltaj;

            return false;
        }

        private bool TryToMoveHorizontal(int max, int deltai, int[] x, int I, SplittedMatrix matrix)
        {
            x[I] = x[I] + deltai;

            if (LocalMaximumHorizontal(matrix, I) < max)
                return true;

            x[I] = x[I] - deltai;

            return false;
        }

        private IAlgorithm<int, LoadBalancingProblem> auxilary;
    }
}
