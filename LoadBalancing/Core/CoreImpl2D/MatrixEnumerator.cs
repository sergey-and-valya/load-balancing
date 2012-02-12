using System;
using System.Collections.Generic;
using Core;
using CoreImpl1D;

namespace CoreImpl2D
{
    /// <summary>
    /// Индексатор матрицы
    /// </summary>
    public static class MatrixEnumerator
    {
        /// <summary>
        /// Все индексы матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Перечисление индексов матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> Indexes<T>(IMatrix<T> matrix)
        {
            if (matrix.Dimensions != 2)
                throw new Exception("Размерность матрицы должна быть равна 2");

            int m = matrix.Size(0);
            int n = matrix.Size(1);
            var index = new Index2D();

            for (index.I = 0; index.I < m; index.I++)
            {
                for (index.J = 0; index.J < n; index.J++)
                {
                    yield return index;
                }
            }
        }

        /// <summary>
        /// Индексы указанной строки матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <param name="row">Номер строки</param>
        /// <returns>Перечисление индексов строки матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> RowIndexes<T>(IMatrix<T> matrix, int row)
        {
            if (matrix.Dimensions != 2)
                throw new Exception("Размерность матрицы должна быть равна 2");

            int n = matrix.Size(1);

            var index = new Index2D(row, -1);
            for (index.J = 0; index.J < n; index.J++)
            {
                yield return index;
            }
        }

        /// <summary>
        /// Индексы указанного столбца матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <param name="column">Номер столбца</param>
        /// <returns>Перечисление индексов столбца матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> ColumnIndexes<T>(IMatrix<T> matrix, int column)
        {
            if (matrix.Dimensions != 2)
                throw new Exception("Размерность матрицы должна быть равна 2");

            int m = matrix.Size(0);

            var index = new Index2D(-1, column);
            for (index.I = 0; index.I < m; index.I++)
            {
                yield return index;
            }
        }

        /// <summary>
        /// Индексы столбцов матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Перечисление индексов столбцов матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> Columns<T>(IMatrix<T> matrix)
        {
            if (matrix.Dimensions != 2)
                throw new Exception("Размерность матрицы должна быть равна 2");

            int n = matrix.Size(1);
            var index = new Index1D();
            for (index.I = 0; index.I < n; index.I++)
                yield return index;
        }


        /// <summary>
        /// Индексы строк матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Перечисление индексов строк матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> Rows<T>(IMatrix<T> matrix)
        {
            if (matrix.Dimensions != 2)
                throw new Exception("Размерность матрицы должна быть равна 2");

            int m = matrix.Size(0);
            var index = new Index1D();
            for (index.I = 0; index.I < m; index.I++)
                yield return index;
        }
    }
}
