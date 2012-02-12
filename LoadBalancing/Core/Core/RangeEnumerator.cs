using System;
using System.Collections.Generic;

namespace Core
{
    public static class RangeEnumerator
    {
        /// <summary>
        /// n - мерные индексы в пределах заданных границ
        /// </summary>
        /// <param name="low">Нижние границы для индексов</param>
        /// <param name="high">Верхние границы для индексов</param>
        /// <returns>Перечисление индексов</returns>
        public static IEnumerable<IIndex> Indexes(int[] low, int[] high)
        {
            if (low.Length != high.Length)
                throw new Exception("Размеры массивов должны совпадать");

            int dimensions = low.Length;
            int[] index = new int[dimensions];

            for (int i = 0; i < dimensions; i++)
            {
                if (high[i] < low[i])
                    yield break;

                index[i] = low[i];
            }

            int currentDimension = dimensions - 1;

            while (true)
            {
                yield return new Index(index);

                while (currentDimension >= 0 && (index[currentDimension] == high[currentDimension]))
                {
                    currentDimension--;
                }

                if (currentDimension == -1)
                    break;

                index[currentDimension]++;
                currentDimension++;

                while (currentDimension < dimensions)
                {
                    index[currentDimension] = low[currentDimension];
                    currentDimension++;
                }
                currentDimension--;
            }
        }
    }
}
