using System.ComponentModel.Composition;
using Core;
using LoadBalancing;
using Visualizer;
using VisualizerPluginCore;

namespace ColorVisualizer
{
    [Export(typeof(ISolutionVisualizerPlugin<int>))]
    public class ColorSolutionVisualizerPlugin : ISolutionVisualizerPlugin<int>
    {
        #region ISolutionVisualizerPlugin<int> Members

        public string Name
        {
            get { return "Визуализатор решений в цвете"; }
        }

        public bool HasSolutionVisualizer(int dimensions)
        {
            return dimensions <= 2;
        }

        public ISolutionVisualizer<int> CreateSolutionVisualizer(int dimensions)
        {
            if (dimensions > 2)
                return null;

            return new Visualizer();
        }

        #endregion ISolutionVisualizerPlugin<int> Members

        private class Visualizer : ISolutionVisualizer<int>
        {
            public void VisualizeSolution(IMatrix<int> matrix, ISolution solution)
            {
                var max = CoreUtilities.Utilities.Max(matrix);
                var min = CoreUtilities.Utilities.Min(matrix);
                var criterion = MinMaxCriterium.Calculate(matrix, solution);

                var splitted = new SplittedMatrix(matrix, solution);
                var solutionVisualizer =
                    new SolutionVisualizerForm(splitted, matrix,
                        solution, min, max, criterion);

                solutionVisualizer.Draw();
                solutionVisualizer.Show();
            }
        }
    }
}