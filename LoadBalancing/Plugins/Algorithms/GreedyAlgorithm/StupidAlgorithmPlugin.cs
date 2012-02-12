using System.ComponentModel.Composition;
using AlgorithmPluginCore;
using LoadBalancing;

namespace GreedyAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, LoadBalancingProblem>))]
    public class StupidAlgorithmPlugin : IAlgorithmPlugin<int, LoadBalancingProblem>
    {
        public string Name
        {
            get { return "Декомпозиционный алгоритм"; }
        }

        public bool HasAlgorithm(int dimensions)
        {
            if (dimensions > 2)
                return false;

            return true;
        }

        public IAlgorithm<int, LoadBalancingProblem> CreateAlgorithm(int dimensions)
        {
            switch (dimensions)
            {
                case 1:
                    return new StupidAlgorithm1D();
                case 2:
                    return new StupidAlgorithm2D(new StupidAlgorithm1D());
            }
            return null;
        }
    }
}
