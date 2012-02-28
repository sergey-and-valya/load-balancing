using System;
using Core;
using CoreImpl2D;

namespace GreedyAlgorithm
{
    /// <summary>
    /// Вектор из ячеек, полученных разбиением исходной матрицы вертикальными линиями
    /// </summary>
    public class MatrixAsRow : IMatrix<int>
    {
        /// <summary>
        /// Вектор из ячеек, полученных разбиением исходной матрицы вертикальными линиями
        /// </summary>
        /// <param name="matrix">Исходная матрица</param>
        public MatrixAsRow(IMatrix<int> matrix)
        {
            this.matrix = matrix;
        }

        public int Dimensions
        {
            get
            {
                return 1;
            }
        }

        public int Size(int dimension)
        {
            if (dimension != 0)
                throw new Exception("У разбитой матрицы только 1 размерность");
            return matrix.Size(1);
        }

        public int this[IIndex index]
        {
            get
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");

                var ind = new Index2D(-1, index[0]);
                int sum = 0;
                for (ind.I = 0; ind.I < matrix.Size(0); ind.I++)
                {
                    sum += matrix[ind];
                }

                return sum;
            }
            set
            {
                throw new NotSupportedException();
            }
        }

        private readonly IMatrix<int> matrix;
    }
}