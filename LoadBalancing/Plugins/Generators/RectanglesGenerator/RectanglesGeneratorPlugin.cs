using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Windows.Forms;
using Core;
using CoreImpl2D;
using GeneratorPluginCore;
using MatrixStorage;

namespace RectanglesGenerator
{
    [Export(typeof(IGeneratorPlugin<int, EmptyData>))]
    public class RectanglesGeneratorPlugin : IGeneratorPlugin<int, EmptyData>
    {
        public string Name
        {
            get { return "Случайные прямоугольники"; }
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

            return new Generator(dialog.Count, dialog.N, dialog.M, dialog.MinH, dialog.MaxH, dialog.RectsMin, dialog.RectsMax);
        }

        private class Generator : IGenerator<int, EmptyData>
        {
            private int count;
            private int n;
            private int m;
            private int min_h;
            private int max_h;
            private int rectsMin;
            private int rectsMax;

            public Generator(int count, int n, int m, int min_h, int max_h, int rectsMin, int rectsMax)
            {
                this.count = count;
                this.n = n;
                this.m = m;
                this.min_h = min_h;
                this.max_h = max_h;
                this.rectsMax = rectsMax;
                this.rectsMin = rectsMin;
            }

            public void GenerateMatrixes(IMatrixWriteStorage<int, EmptyData> matrixStorage)
            {
                Random rnd = new Random();

                var indexIJ = new Index2D();

                for (int matrindex = 0; matrindex < count; matrindex++)
                {
                    DenseMatrix<int> matrix = new DenseMatrix<int>(m, n);
                    int rectsCount = rectsMin + rnd.Next(rectsMax - rectsMin);

                    for (int rect = 0; rect < rectsCount; rect++)
                    {
                        int x1 = rnd.Next(m);
                        int y1 = rnd.Next(n);

                        int x2 = x1 + rnd.Next(m - x1);
                        int y2 = y1 + rnd.Next(n - y1);

                        int A = min_h + rnd.Next(max_h - min_h);

                        for (indexIJ.I = x1; indexIJ.I <= x2; indexIJ.I++)
                            for (indexIJ.J = y1; indexIJ.J <= y2; indexIJ.J++)
                            {
                                matrix[indexIJ] += A;
                            }

                    }

                    foreach (var index in MatrixEnumerator.Indexes(matrix))
                    {
                        matrix[index] += 1;
                    }

                    matrixStorage.SaveMatrix("Rectangles", matrix, null);
                }
            }
        }
    }
}