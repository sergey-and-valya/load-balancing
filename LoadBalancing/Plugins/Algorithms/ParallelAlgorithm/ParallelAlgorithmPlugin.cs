using System.ComponentModel.Composition;
using AlgorithmPluginCore;
using LoadBalancing;

namespace ParallelAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, PartitioningParameters>))]
    public class StupidAlgorithmPlugin : IAlgorithmPlugin<int, PartitioningParameters>
    {
        public string Name
        {
            get { return "Параллельный алгоритм"; }
        }

        public bool HasAlgorithm(int dimensions)
        {
            return true;
        }

        public IAlgorithm<int> CreateAlgorithm(int dimensions, PartitioningParameters parameters)
        {
            
            return null;
        }
    }
}
