using System.ComponentModel.Composition;
using Core;
using LoadBalancing;
using Visualizer;
using VisualizerPluginCore;

namespace ColorVisualizer
{
    [Export(typeof(ISolutionVisualizerPlugin<int, LoadBalancingProblem>))]
    public class ColorSolutionVisualizerPlugin : ISolutionVisualizerPlugin<int, LoadBalancingProblem>
    {
        #region ISolutionVisualizerPlugin<int, LoadBalancingProblem> Members

        public string Name
        {
            get { return "Визуализатор решений в цвете"; }
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

        #endregion ISolutionVisualizerPlugin<int, LoadBalancingProblem> Members

        private class Visualizer : ISolutionVisualizer<int, LoadBalancingProblem>
        {
            public void VisualizeSolution(LoadBalancingProblem problem, ISolution solution)
            {
                var max = CoreUtilities.Utilities.Max(problem.Matrix);
                var min = CoreUtilities.Utilities.Min(problem.Matrix);
                var criterion = problem.Criterium.Value(problem.Matrix, solution);

                var splitted = new SplittedMatrix(problem.Matrix, solution);
                var solutionVisualizer =
                    new SolutionVisualizerForm(splitted, problem.Matrix,
                        solution, min, max, criterion);

                solutionVisualizer.Draw();
                solutionVisualizer.Show();
            }
        }
    }
}