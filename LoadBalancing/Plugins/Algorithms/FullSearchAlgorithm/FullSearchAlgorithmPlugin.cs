using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using AlgorithmPluginCore;
using LoadBalancing;

namespace FullSearchAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, PartitioningParameters>))]
    public class FullSearchAlgorithmPlugin : IAlgorithmPlugin<int, PartitioningParameters>
    {
        public string Name
        {
            get { return "Полный перебор"; }
        }

        public bool HasAlgorithm(int dimensions)
        {
            return dimensions == 2;
        }

        public IAlgorithm<int> CreateAlgorithm(int dimensions, PartitioningParameters parameters)
        {
            if (dimensions == 2 && parameters.Dimensions == 2)
            {
                if ((MessageBox.Show("Вы уверены, что хотите запустить полный перебор?", "Важный вопрос", MessageBoxButtons.YesNo) == DialogResult.Yes))
                if ((MessageBox.Show("Точно-точно?", "Ещё один важный вопрос", MessageBoxButtons.YesNo) == DialogResult.Yes))
                {
                    return new FullSearchAlgorithm2D(parameters[0], parameters[1]);
                }
                throw new Exception();
            }

            return null;
        }
    }
}
