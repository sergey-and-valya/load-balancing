using System.Collections.Generic;

namespace Core
{
    /// <summary>
    /// Индексатор матрицы любой размерности
    /// </summary>
    public static class MultiDimensionMatrixEnumerator
    {
        /// <summary>
        /// Все индексы матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Перечисление индексов матрицы</returns>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        public static IEnumerable<IIndex> Indexes<T>(IMatrix<T> matrix)
        {
            int dimensions = matrix.Dimensions;
            int[] low = new int[dimensions];
            int[] high = new int[dimensions];

            for (int i = 0; i < dimensions; i++)
            {
                low[i] = 0;
                high[i] = matrix.Size(i) - 1;
            }

            return RangeEnumerator.Indexes(low, high);
        }
    }
}
