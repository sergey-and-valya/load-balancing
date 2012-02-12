using AlgorithmPluginCore;
using Core;
using CoreImpl2D;
using LoadBalancing;

namespace GreedyAlgorithm
{
    internal class StupidAlgorithm2D : IAlgorithm<int, LoadBalancingProblem>
    {
        public StupidAlgorithm2D(IAlgorithm<int, LoadBalancingProblem> auxilary)
        {
            this.auxilary = auxilary;
        }

        public ISolution Run(LoadBalancingProblem problem)
        {
            ISolution x = auxilary.Run(
                new LoadBalancingProblem(
                    new MatrixAsColumn(problem.Matrix),
                    new PartitioningParameters(problem.Parameters[0])));

            ISolution y = auxilary.Run(
                new LoadBalancingProblem(
                    new MatrixAsRow(problem.Matrix),
                    new PartitioningParameters(problem.Parameters[1])));

            return new ComposeSolution(x, y);
        }

        private IAlgorithm<int, LoadBalancingProblem> auxilary;
    }
}
