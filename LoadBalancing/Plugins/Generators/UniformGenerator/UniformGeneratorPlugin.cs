using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using Core;
using CoreImpl2D;
using GeneratorPluginCore;
using MatrixStorage;

namespace UniformGenerator
{
    [Export(typeof(IGeneratorPlugin<int, EmptyData>))]
    public class UniformGeneratorPlugin : IGeneratorPlugin<int, EmptyData>
    {
        public string Name
        {
            get { return "Равномерная генерация значений"; }
        }

        public bool HasGenerator(int dimensions)
        {
            if (dimensions != 2)
                return false;

            return true;
        }

        public IGenerator<int, EmptyData> CreateGenerator(int dimensions)
        {
            if (dimensions != 2)
                return null;

            var dialog = new ParametersDialog();

            if (dialog.ShowDialog() != DialogResult.OK)
                return null;
            
            return new Generator(dimensions, dialog.Count, dialog.Min, dialog.Max, dialog.CountRows, dialog.CountColumns);
            
        }

        private class Generator : IGenerator<int, EmptyData>
        {
            private int dimensions;
            private int count;
            private int min;
            private int max;
            private int countRows;
            private int countColumns;

            public Generator(int dimensions, int count, int min, int max, int countRows, int countColumns)
            {
                this.dimensions = dimensions;
                this.count = count;
                this.min = min;
                this.max = max;
                this.countRows = countRows;
                this.countColumns = countColumns;
            }

            public void GenerateMatrixes(IMatrixWriteStorage<int, EmptyData> matrixStorage)
            {
                Random rnd = new Random();

                for (int i = 0; i < count; i++)
                {
                    DenseMatrix<int> matrix = new DenseMatrix<int>(countRows, countColumns);

                    foreach (IIndex index in MatrixEnumerator.Indexes(matrix))
                        matrix[index] = rnd.Next(max - min + 1) + min;

                    matrixStorage.SaveMatrix("uniform", matrix, null);
                }
            }
        }
    }
}