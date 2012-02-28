using System;
using Core;

namespace CoreImpl2D
{
    /// <summary>
    /// Двумерная сплошная матрица
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public class DenseMatrix<T> : IMatrix<T>
    {
        /// <summary>
        /// Двумерная сплошная матрица
        /// </summary>
        /// <param name="m">Число строк</param>
        /// <param name="n">Число столбцов</param>
        public DenseMatrix(int m, int n)
        {
            this.m = m;
            this.n = n;

            matrix = new T[m][];
            for (int i = 0; i < m; i++)
                matrix[i] = new T[n];
        }

        /// <summary>
        /// Двумерная сплошная матрица
        /// </summary>
        /// <param name="matrix">Копируемая матрица</param>
        public DenseMatrix(IMatrix<T> matrix)
            : this(matrix.Size(0), matrix.Size(1))
        {
            var index = new Index2D();
            for (index.I = 0; index.I < m; index.I++)
            {
                for (index.J = 0; index.J < n; index.J++)
                {
                    this[index.I, index.J] = matrix[index];
                }
            }
        }

        /// <summary>
        /// Элемент матрицы
        /// </summary>
        /// <param name="i">Номер строки</param>
        /// <param name="j">Номер столбца</param>
        public T this[int i, int j]
        {
            get
            {
                return matrix[i][j];
            }
            set
            {
                matrix[i][j] = value;
            }
        }

        /// <summary>
        /// Число строк матрицы
        /// </summary>
        public int M
        {
            get { return m; }
        }

        /// <summary>
        /// Число столбцов матрицы
        /// </summary>
        public int N
        {
            get { return n; }
        }

        #region IMatrix<T> Members

        public int Dimensions
        {
            get { return 2; }
        }

        public int Size(int dimension)
        {
            switch (dimension)
            {
                case 0:
                    return m;
                case 1:
                    return n;
            }
            throw new Exception("У матрицы только 2 размерности");
        }

        public T this[IIndex index]
        {
            get
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                return matrix[index[0]][index[1]];
            }
            set
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                matrix[index[0]][index[1]] = value;
            }
        }

        #endregion IMatrix<T> Members

        private readonly int m;
        private readonly int n;

        private readonly T[][] matrix;
    }
}