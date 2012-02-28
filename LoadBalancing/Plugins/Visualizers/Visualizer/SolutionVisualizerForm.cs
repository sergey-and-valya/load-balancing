using System.Drawing;
using Core;
using CoreImpl2D;
using LoadBalancing;

namespace Visualizer
{
    public partial class SolutionVisualizerForm : VisualizerForm
    {
        private SplittedMatrix splittedMatrix;
        private ISolution solution;
        private int zoomShift;

        private int solutionSizeRow;
        private int solutionSizeColumn;

        private int[][] sumOfSplittedElements;

        private Bound almostBound;

        public SolutionVisualizerForm(SplittedMatrix splittedMatrix, IMatrix<int> matrix, ISolution solution, int min, int max, double criterion)
        {
            InitParameters(splittedMatrix, matrix, solution);
            SetSizeOfBitmap();
            SetMinMax(min, max);
            SetBoundOfValuesOfMatrix(min, max);
            SetCriterion(criterion);
            settingsEvent();
        }

        private void InitParameters(SplittedMatrix splittedMatrix, IMatrix<int> matrix, ISolution solution)
        {
            Name = "SolutionVisualizerForm";
            Text = "     Visualizer of solution";
            this.splittedMatrix = splittedMatrix;
            this.matrix = matrix;
            this.solution = solution;
            int rows = matrix.Size(1);
            int columns = matrix.Size(0);
            int minSize = rows < columns ? rows : columns;
            zoomShift = 1 + minSize / 400;
            coefficient = 255.0 / CoreUtilities.Utilities.Max(matrix);
            modeOfDrawing = Mode.Matrix;
            ModeChangeButton.Visible = true;
            settingsEvent = SetZoom;
            settingsEvent += SetSolutionSize;
            settingsEvent += SetStep;
            settingsEvent += SetBitmap;
            settingsEvent += InitSumInBlocks;
            settingsEvent += SetBoundOfValuesOfBlocks;
            settingsEvent += SetSumInBlocks;
        }

        private void SetSizeOfBitmap()
        {
            sizeOfMatrix = new Size(matrix.Size(1) + solution.Size(1) * zoomShift, matrix.Size(0) + solution.Size(0) * zoomShift);
            matrixBitmap = new Bitmap(sizeOfMatrix.Width, sizeOfMatrix.Height);
            sumInBlocksBitmap = new Bitmap(sizeOfMatrix.Width, sizeOfMatrix.Height);
        }

        private void SetBoundOfValuesOfMatrix(int min, int max)
        {
            boundOfValuesOfMatrix.max = max;
            boundOfValuesOfMatrix.min = min;
        }

        private void SetCriterion(double criterion)
        {
            CriterionValueLabel.Text = criterion.ToString();
        }

        private int GetMaxOfSumOfSplittedElements()
        {
            int max = 0;

            for (int i = 0; i < solutionSizeColumn; i++)
                for (int j = 0; j < solutionSizeRow; j++)
                {
                    int value = sumOfSplittedElements[i][j];
                    if (max < value)
                        max = value;
                }

            return max;
        }

        private int GetMinOfSumOfSplittedElements()
        {
            int min = boundOfValuesOfBlocks.max;

            for (int i = 0; i < solutionSizeColumn; i++)
                for (int j = 0; j < solutionSizeRow; j++)
                {
                    int value = sumOfSplittedElements[i][j];
                    if (min > value)
                        min = value;
                }

            return min;
        }

        private void SetAlmostMaxOfSumOfSplittedElements()
        {
            int max = 0;

            for (int i = 0; i < solutionSizeColumn; i++)
                for (int j = 0; j < solutionSizeRow; j++)
                {
                    int value = sumOfSplittedElements[i][j];
                    if (max < value && value != boundOfValuesOfBlocks.max)
                        max = value;
                }

            almostBound.max = max;
        }

        private void SetAlmostMinOfSumOfSplittedElements()
        {
            int min = boundOfValuesOfBlocks.max;

            for (int i = 0; i < solutionSizeColumn; i++)
                for (int j = 0; j < solutionSizeRow; j++)
                {
                    int value = sumOfSplittedElements[i][j];
                    if (min > value && value != boundOfValuesOfBlocks.min)
                        min = value;
                }

            almostBound.min = min;
        }

        private void SetChangeModeButtonLocation()
        {
            ModeChangeButton.Location = new Point(
                DrawingBox.Location.X + DrawingBox.Size.Width + 4 * shift,
                DrawingBox.Location.Y + DrawingBox.Height - 3 * shift);
        }

        private void SetCriterionLocation()
        {
            CriterionLabel.Location =
                   new Point(
                       DrawingBox.Location.X + DrawingBox.Size.Width + shift / 2,
                       DrawingBox.Location.Y + DrawingBox.Height - (int)(1.5 * shift));
            CriterionValueLabel.Location =
                   new Point(
                       DrawingBox.Location.X + DrawingBox.Size.Width + shift / 2,
                       DrawingBox.Location.Y + DrawingBox.Height - shift / 2);
        }

        private void SetSolutionSize()
        {
            solutionSizeRow = splittedMatrix.Size(1);
            solutionSizeColumn = splittedMatrix.Size(0);
        }

        protected override void SetBitmap()
        {
            for (int i = 0; i < solutionSizeColumn; i++) //строка разбитой матрицы
            {
                var lastOnI = splittedMatrix.CellHigh(i, 0);

                var index = new Index2D();
                //строка исходной матрицы, попавшая в строку разбитой матрицы
                for (index.I = splittedMatrix.CellLow(i, 0); index.I <= lastOnI; index.I++)
                    for (int j = 0; j < solutionSizeRow; j++) //столбец разбитой матрицы
                    {
                        var lastOnJ = splittedMatrix.CellHigh(j, 1);

                        //строка исходной матрицы, попавшая в столбец разбитой матрицы
                        for (index.J = splittedMatrix.CellLow(j, 1); index.J <= lastOnJ; index.J++)
                        {
                            SetPixelToBitmapOfMatrix(
                                (int)(coefficient * GetValueOfMatrixFrom(matrix[index])),
                                index.I + i * zoomShift,
                                index.J + j * zoomShift);
                        }
                    }
            }
        }

        private int GetValueOfMatrixFrom(int value)
        {
            return value > MinTrackBar.Maximum ?
                  (value - (MaxTrackBar.Maximum - MaxTrackBar.Value)) :
                  (value + (MinTrackBar.Value - MinTrackBar.Minimum));
        }

        private void SetPixelToBitmapOfMatrix(int value, int row, int column)
        {
            matrixBitmap.SetPixel(column, row, Color.FromArgb(255, value, trackBarColor.green, trackBarColor.blue));
        }

        private void InitSumInBlocks()
        {
            var index = new Index2D();
            sumOfSplittedElements = new int[solutionSizeColumn][];
            for (int i = 0; i < solutionSizeColumn; i++)
            {
                sumOfSplittedElements[i] = new int[solutionSizeRow];
                var lastOnI = splittedMatrix.CellHigh(i, 0);
                for (index.I= splittedMatrix.CellLow(i, 0); index.I <= lastOnI; index.I++)
                    for (int j = 0; j < solutionSizeRow; j++) //столбец разбитой матрицы
                    {
                        var lastOnJ = splittedMatrix.CellHigh(j, 1);
                        for (index.J = splittedMatrix.CellLow(j, 1); index.J <= lastOnJ; index.J++)
                            sumOfSplittedElements[i][j] += matrix[index];
                    }
            }
        }

        private void SetBoundOfValuesOfBlocks()
        {
            boundOfValuesOfBlocks.max = GetMaxOfSumOfSplittedElements();
            boundOfValuesOfBlocks.min = GetMinOfSumOfSplittedElements();
            SetAlmostMaxOfSumOfSplittedElements();
            SetAlmostMinOfSumOfSplittedElements();
        }

        private void SetSumInBlocks()
        {
            double coef1 = 255.0 / (almostBound.max - almostBound.min);
            double coef2 = -almostBound.min * coef1;

            for (int i = 0; i < solutionSizeColumn; i++) //строка разбитой матрицы
            {
                var lastOnI = splittedMatrix.CellHigh(i, 0);

                //строка исходной матрицы, попавшая в строку разбитой матрицы
                for (int ki = splittedMatrix.CellLow(i, 0); ki <= lastOnI; ki++)
                    for (int j = 0; j < solutionSizeRow; j++) //столбец разбитой матрицы
                    {
                        var lastOnJ = splittedMatrix.CellHigh(j, 1);
                        int tempValue = sumOfSplittedElements[i][j];
                        int valueRed = 0;
                        int valueGreen = 0;
                        int valueBlue = 0;
                        if (tempValue == boundOfValuesOfBlocks.max)
                            valueRed = GetValueOfMatrixFrom(255);
                        else
                            if (tempValue == boundOfValuesOfBlocks.min)
                                valueGreen = GetValueOfMatrixFrom(255);
                            else
                                valueBlue = (int)(coef2 + coef1 * GetValueOfMatrixFrom(sumOfSplittedElements[i][j]));

                        //строка исходной матрицы, попавшая в столбец разбитой матрицы
                        for (int kj = splittedMatrix.CellLow(j, 1); kj <= lastOnJ; kj++)
                        {
                            SetPixelToSumInBlocksBitmap(valueRed, valueGreen, valueBlue, ki + i * zoomShift, kj + j * zoomShift);
                        }
                    }
            }
        }

        private void SetPixelToSumInBlocksBitmap(int valueRed, int valueGreen, int valueBlue, int row, int column)
        {
            sumInBlocksBitmap.SetPixel(column, row, Color.FromArgb(255, valueRed, valueGreen, valueBlue));
        }

        protected override void SetSettings()
        {
            base.SetSettings();
            settingsEvent += SetChangeModeButtonLocation;
            settingsEvent += SetCriterionLocation;
        }

        protected override void ChangeBitmap()
        {
            if (modeOfDrawing == Mode.Matrix)
                SetBitmap();
            else
                SetSumInBlocks();
        }

        protected override void SetStep()
        {
            int maxValue = (matrix.Size(1) * matrix.Size(0) * 2);
        }
    }
}