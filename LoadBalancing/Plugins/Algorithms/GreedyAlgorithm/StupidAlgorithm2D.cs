using AlgorithmPluginCore;
using Core;
using CoreImpl2D;
using LoadBalancing;

namespace GreedyAlgorithm
{
    internal class StupidAlgorithm2D : IAlgorithm<int>
    {
        public StupidAlgorithm2D(IAlgorithm<int> auxilaryX, IAlgorithm<int> auxilaryY)
        {
            this.auxilaryX = auxilaryX;
            this.auxilaryY = auxilaryY;
        }

        public ISolution Run(IMatrix<int> matrix)
        {
            ISolution x = auxilaryX.Run(new MatrixAsColumn(matrix));

            ISolution y = auxilaryY.Run(new MatrixAsRow(matrix));

            return new ComposeSolution(x, y);
        }

        private readonly IAlgorithm<int> auxilaryX;
        private readonly IAlgorithm<int> auxilaryY;
    }
}
