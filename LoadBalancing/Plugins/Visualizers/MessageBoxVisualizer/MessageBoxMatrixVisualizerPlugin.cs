using System.ComponentModel.Composition;
using System.Text;
using System.Windows.Forms;
using Core;
using CoreImpl2D;
using VisualizerPluginCore;

namespace MessageBoxVisualizer
{
    [Export(typeof(IMatrixVisualizerPlugin<int>))]
    public class MessageBoxMatrixVisualizerPlugin : IMatrixVisualizerPlugin<int>
    {
        public string Name
        {
            get { return "Простой визуализатор векторов и матриц"; }
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

        private class Visualizer : IMatrixVisualizer<int>
        {
            public void VisualizeMatrix(IMatrix<int> matrix)
            {
                StringBuilder text = new StringBuilder();
                var index = new Index2D();
                for (index.I = 0; index.I < matrix.Size(0); index.I++)
                {
                    index.J = 0;
                    text.Append(matrix[index]);

                    for (index.J = 1; index.J < matrix.Size(1); index.J++)
                    {
                        text.AppendFormat(" {0,3}", matrix[index]);
                    }

                    text.AppendLine();
                }
                MessageBox.Show(text.ToString());
            }
        }
    }
}