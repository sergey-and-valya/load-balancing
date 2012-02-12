using System;
using Core;
using CoreImpl2D;

namespace GreedyAlgorithm
{
    /// <summary>
    /// Вектор из ячеек, полученных разбиением исходной матрицы горизонтальными линиями
    /// </summary>
    public class MatrixAsColumn : IMatrix<int>
    {
        /// <summary>
        /// Вектор из ячеек, полученных разбиением исходной матрицы горизонтальными линиями
        /// </summary>
        /// <param name="matrix">Исходная матрица</param>
        public MatrixAsColumn(IMatrix<int> matrix)
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
            return matrix.Size(0);
        }

        public int this[IIndex index]
        {
            get
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");

                int sum = 0;

                var ind = new Index2D(index[0], -1);
                for (ind.J = 0; ind.J < matrix.Size(1); ind.J++)
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

        private IMatrix<int> matrix;
    }
}
