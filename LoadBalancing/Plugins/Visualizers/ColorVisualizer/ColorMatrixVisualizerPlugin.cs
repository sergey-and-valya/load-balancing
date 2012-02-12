using System.ComponentModel.Composition;
using Core;
using CoreUtilities;
using Visualizer;
using VisualizerPluginCore;

namespace ColorVisualizer
{
    [Export(typeof(IMatrixVisualizerPlugin<int>))]
    public class ColorMatrixVisualizerPlugin : IMatrixVisualizerPlugin<int>
    {
        #region IMatrixVisualizerPlugin<int> Members

        public string Name
        {
            get { return "Визуализатор матриц в цвете"; }
        }

        public bool HasMatrixVisualizer(int dimensions)
        {
            if (dimensions > 2)
                return false;

            return true;
        }

        public IMatrixVisualizer<int> CreateMatrixVisualizer(int dimensions)
        {
            if (dimensions > 2)
                return null;

            return new Visualizer();
        }

        #endregion IMatrixVisualizerPlugin<int> Members

        private class Visualizer : IMatrixVisualizer<int>
        {
            public void VisualizeMatrix(IMatrix<int> matrix)
            {
                var matrixVisualizer =
                    new MatrixVisualizerForm(matrix, Utilities.Min(matrix), Utilities.Max(matrix));
                matrixVisualizer.Draw();
                matrixVisualizer.Show();
            }
        }
    }
}