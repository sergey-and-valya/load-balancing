using System;
using Core;

namespace CoreUtilities
{
    /// <summary>
    /// Вспомогательные функции
    /// </summary>
    public static class Utilities
    {
        /// <summary>
        /// Максимальное значение в матрице
        /// </summary>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        /// <param name="matrix">Матрица</param>
        /// <returns>Максимальное значение в матрице</returns>
        public static T Max<T>(IMatrix<T> matrix)
            where T : IComparable<T>
        {
            T max = default(T);

            var enumerator = MultiDimensionMatrixEnumerator.Indexes(matrix).GetEnumerator();

            if (enumerator.MoveNext())
            {
                max = matrix[enumerator.Current];

                while (enumerator.MoveNext())
                {
                    if (max.CompareTo(matrix[enumerator.Current]) < 0)
                        max = matrix[enumerator.Current];
                }
            }

            return max;
        }

        /// <summary>
        /// Минимальное значение в матрице
        /// </summary>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        /// <param name="matrix">Матрица</param>
        /// <returns>Минимальное значение в матрице</returns>
        public static T Min<T>(IMatrix<T> matrix)
            where T : IComparable<T>
        {
            T min = default(T);

            var enumerator = MultiDimensionMatrixEnumerator.Indexes(matrix).GetEnumerator();

            if (enumerator.MoveNext())
            {
                min = matrix[enumerator.Current];

                while (enumerator.MoveNext())
                {
                    if (min.CompareTo(matrix[enumerator.Current]) > 0)
                        min = matrix[enumerator.Current];
                }
            }

            return min;
        }
    }
}