using System;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using CoreImpl2D;
using GeneratorPluginCore;
using MatrixStorage;

namespace ExponentGenerator
{
    [Export(typeof(IGeneratorPlugin<int, EmptyData>))]
    public class ExponentGeneratorPlugin : IGeneratorPlugin<int, EmptyData>
    {
        public string Name
        {
            get { return "Экспоненциальная генерация"; }
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

            return new Generator(dialog.Count, dialog.N, dialog.M, dialog.MinW, dialog.MaxW, dialog.MinH, dialog.MaxH, dialog.MountainsMin, dialog.MountainsMax);
        }

        private class Generator : IGenerator<int, EmptyData>
        {
            private readonly int count;
            private readonly int n;
            private readonly int m;
            private readonly double min_w;
            private readonly double max_w;
            private readonly double min_h;
            private readonly double max_h;
            private readonly int mountainsMin;
            private readonly int mountainsMax;

            public Generator(int count, int n, int m, double min_w, double max_w, double min_h, double max_h, int mountainsMin, int mountainsMax)
            {
                this.count = count;
                this.n = n;
                this.m = m;
                this.min_w = min_w;
                this.max_w = max_w;
                this.min_h = min_h;
                this.max_h = max_h;
                this.mountainsMax = mountainsMax;
                this.mountainsMin = mountainsMin;
            }

            public void GenerateMatrixes(IMatrixWriteStorage<int, EmptyData> matrixStorage)
            {
                Random rnd = new Random();

                for (int matrindex = 0; matrindex < count; matrindex++)
                {
                    DenseMatrix<int> matrix = new DenseMatrix<int>(m, n);
                    int mountainsCount = mountainsMin + rnd.Next(mountainsMax - mountainsMin);
                    
                    for (int mountain = 0; mountain < mountainsCount; mountain++)
                    {
                        double x = rnd.NextDouble() * m;
                        double y = rnd.NextDouble() * n;

                        double a = min_h + rnd.NextDouble() * (max_h - min_h);
                        double b = 1 / (min_w + rnd.NextDouble() * (max_w - min_w));

                        foreach (var index in MatrixEnumerator.Indexes(matrix))
                        {
                            double rx = index[0] - x;
                            double ry = index[1] - y;
                            double r = b * Math.Sqrt(rx * rx + ry * ry);
                            matrix[index] += (int)(a * Math.Exp(-r*r));
                        }

                    }

                    foreach (var index in MatrixEnumerator.Indexes(matrix))
                    {
                        matrix[index] += 1;
                    }

                    matrixStorage.SaveMatrix("Exponent", matrix, null);
                }
            }
        }
    }
}