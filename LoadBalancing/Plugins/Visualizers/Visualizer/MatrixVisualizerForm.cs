using System.Drawing;
using Core;
using CoreImpl2D;

namespace Visualizer
{
    public partial class MatrixVisualizerForm : VisualizerForm
    {
        public MatrixVisualizerForm(IMatrix<int> matrix, int min, int max)
        {
            InitParameters(matrix);
            SetMinMax(min, max);
            settingsEvent();
        }

        private void InitParameters(IMatrix<int> matrix)
        {
            Name = "MatrixVisualizerForm";
            Text = "     Visualizer of matrix";
            this.matrix = matrix;
            coefficient = 255.0 / CoreUtilities.Utilities.Max(matrix);
            sizeOfMatrix = new Size(matrix.Size(1), matrix.Size(0));
            matrixBitmap = new Bitmap(sizeOfMatrix.Width, sizeOfMatrix.Height);
            modeOfDrawing = Mode.Matrix;

            settingsEvent = SetStep;
            settingsEvent += SetCriterionSettings;
            settingsEvent += SetZoom;
            settingsEvent += SetBitmap;
        }

        private void SetCriterionSettings()
        {
            CriterionLabel.Hide();
            CriterionValueLabel.Hide();
        }

        protected override void SetBitmap()
        {
            var index = new Index2D();
            for (index.J = 0; index.J < sizeOfMatrix.Width; index.J++)
                for (index.I = 0; index.I < sizeOfMatrix.Height; index.I++)
                {
                    int value =
                        matrix[index] > MinTrackBar.Maximum ?
                        (matrix[index] - (MaxTrackBar.Maximum - MaxTrackBar.Value)) :
                        (matrix[index] + (MinTrackBar.Value - MinTrackBar.Minimum));
                    matrixBitmap.SetPixel(
                        index.J, index.I,
                        Color.FromArgb(255, (int)(coefficient * value), trackBarColor.green, trackBarColor.blue));
                }
        }

        protected override void SetStep()
        {
            int maxValue = (sizeOfMatrix.Width * sizeOfMatrix.Height);
        }
    }
}