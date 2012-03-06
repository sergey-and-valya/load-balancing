using System.ComponentModel.Composition;
using AlgorithmPluginCore;
using LoadBalancing;

namespace GreedyAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, PartitioningParameters>))]
    public class StupidAlgorithmPlugin : IAlgorithmPlugin<int, PartitioningParameters>
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

        public IAlgorithm<int> CreateAlgorithm(int dimensions, PartitioningParameters parameters)
        {
            if (parameters.Dimensions != dimensions)
                return null;

            switch (dimensions)
            {
                case 1:
                    return new StupidAlgorithm1D(parameters[0]);
                case 2:
                    return new StupidAlgorithm2D(new StupidAlgorithm1D(parameters[0]), new StupidAlgorithm1D(parameters[1]));
            }
            return null;
        }
    }
}
