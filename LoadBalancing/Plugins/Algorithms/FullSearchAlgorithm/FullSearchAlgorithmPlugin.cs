using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using AlgorithmPluginCore;
using LoadBalancing;

namespace FullSearchAlgorithm
{
    [Export(typeof(IAlgorithmPlugin<int, LoadBalancingProblem>))]
    public class FullSearchAlgorithmPlugin : IAlgorithmPlugin<int, LoadBalancingProblem>
    {
        public string Name
        {
            get { return "Полный перебор"; }
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
                if ((MessageBox.Show("Вы уверены, что хотите запустить полный перебор?", "Важный вопрос", MessageBoxButtons.YesNo) == DialogResult.Yes))
                if ((MessageBox.Show("Точно-точно?", "Ещё один важный вопрос", MessageBoxButtons.YesNo) == DialogResult.Yes))
                {
                    return new FullSearchAlgorithm2D();
                }
                throw new Exception();
            }

            return null;
        }
    }
}
