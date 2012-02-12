using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl1D
{
    /// <summary>
    /// Индексатор вектора
    /// </summary>
    public static class VectorEnumerator
    {
        /// <summary>
        /// Все индексы вектора
        /// </summary>
        /// <param name="vector">Вектор</param>
        /// <returns>Перечисление индексов вектора</returns>
        /// <typeparam name="T">Тип хранимых в векторе данных</typeparam>
        public static IEnumerable<IIndex> Indexes<T>(IMatrix<T> vector)
        {
            if (vector.Dimensions != 1)
                throw new Exception("Размерность вектора должна быть равна 1");

            int n = vector.Size(0);
            var index = new Index1D();
            for (index.I = 0; index.I < n; index.I++)
                yield return index;
        }
    }
}
