using System.ComponentModel.Composition;
using AlgorithmPluginCore;
using LoadBalancing;

namespace GreedyAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, PartitioningParameters>))]
    public class GreedyAlgorithmPlugin : IAlgorithmPlugin<int, PartitioningParameters>
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

        public IAlgorithm<int> CreateAlgorithm(int dimensions, PartitioningParameters parameters)
        {
            if (dimensions == 2)
            {
                return new GreedyAlgorithm2D(new StupidAlgorithm2D(new StupidAlgorithm1D(parameters[0]), new StupidAlgorithm1D(parameters[1])));
            }

            return null;
        }
    }
}
