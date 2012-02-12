using System.ComponentModel.Composition;
using System.Text;
using System.Windows.Forms;
using Core;
using CoreImpl2D;
using LoadBalancing;
using VisualizerPluginCore;

namespace MessageBoxVisualizer
{
    [Export(typeof(ISolutionVisualizerPlugin<int, LoadBalancingProblem>))]
    public class MessageBoxSolutionVisualizerPlugin : ISolutionVisualizerPlugin<int, LoadBalancingProblem>
    {
        #region ISolutionVisualizerPlugin<int,LoadBalancingProblem> Members

        public string Name
        {
            get { return "Простой визуализатор решений"; }
        }

        public bool HasSolutionVisualizer(int dimensions)
        {
            return true;
        }

        public ISolutionVisualizer<int, LoadBalancingProblem> CreateSolutionVisualizer(int dimensions)
        {
            if (dimensions > 2)
                return null;

            return new Visualizer();
        }

        #endregion ISolutionVisualizerPlugin<int,LoadBalancingProblem> Members

        private class Visualizer : ISolutionVisualizer<int, LoadBalancingProblem>
        {
            public void VisualizeSolution(LoadBalancingProblem problem, ISolution solution)
            {
                var text = new StringBuilder();
                var splitted = new SplittedMatrix(problem.Matrix, solution);
                var index = new Index2D();

                for (int i = 0; i < splitted.Size(0); i++) //строка разбитой матрицы
                {
                    if (i != 0)
                        text.AppendLine();
                    for (index.I = splitted.CellLow(i, 0); index.I <= splitted.CellHigh(i, 0); index.I++) //строка исходной матрицы, попавшая в строку разбитой матрицы
                    {
                        for (int j = 0; j < splitted.Size(1); j++) //столбец разбитой матрицы
                        {
                            if (j != 0)
                                text.AppendFormat("    ");

                            for (index.J = splitted.CellLow(j, 1); index.J <= splitted.CellHigh(j, 1); index.J++) //столбец исходной матрицы, попавший в столбец разбитой матрицы
                                text.AppendFormat("{0,3} ", problem.Matrix[index]);
                        }
                        text.AppendLine();
                    }
                }

                MessageBox.Show(text.ToString());
            }
        }
    }
}