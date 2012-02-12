using System.ComponentModel.Composition;
using AlgorithmPluginCore;
using LoadBalancing;

namespace GreedyAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, LoadBalancingProblem>))]
    public class GreedyAlgorithmPlugin : IAlgorithmPlugin<int, LoadBalancingProblem>
    {
        public string Name
        {
            get { return "Декомпозиционный алгоритм с локальной оптимизацией"; }
        }

        public bool HasAlgorithm(int dimensions)
        {
            if (dimensions != 2)
                return false;

            return true;
        }

        public IAlgorithm<int, LoadBalancingProblem> CreateAlgorithm(int dimensions)
        {
            if (dimensions == 2)
            {
                return new GreedyAlgorithm2D(new StupidAlgorithm2D(new StupidAlgorithm1D()));
            }

            return null;
        }
    }
}
