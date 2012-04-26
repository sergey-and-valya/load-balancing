using AlgorithmPluginCore;
using Core;
using CoreParallel;
using LoadBalancing;

namespace ParallelAlgorithm
{
    public class ParallelAlgorithm<T> : IAlgorithm<T>
    {
        public ParallelAlgorithm(PartitioningParameters parameters, IPlannerFactory<T> plannerFactory, IOptimizerPlanner<T> щзешьшяук)
        {
            
        }

        public ISolution Run(IMatrix<T> matrix)
        {
            runner.Run(planner);
        }
    }
}
