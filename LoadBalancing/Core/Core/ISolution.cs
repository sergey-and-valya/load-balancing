using System.Collections.Generic;

namespace Core
{
    /// <summary>
    /// Допустимое решение n-мерной задачи
    /// </summary>
    /// <remarks>
    /// При разбиении вектора на M частей, размер разбиения (Size(0)) равен M - 1
    /// Граничные точки не учитываются в разбиении
    /// </remarks>
    /// <example>
    /// При разбиении вектора из 9 элементов на 3 равных части по 3 элемента в каждой
    /// решение будет представляться точками 3 и 6
    /// </example>
    public interface ISolution
    {
        /// <summary>
        /// Размерность решения
        /// </summary>
        int Dimensions
        {
            get;
        }

        /// <summary>
        /// Количество точек разбиения решения в выбранной размерности
        /// </summary>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Число точек разбиения</returns>
        int Size(int dimension);

        /// <summary>
        /// Разбиение
        /// </summary>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Массив размера Size(dimension)</returns>
        IEnumerable<int> this[int dimension]
        {
            get;
        }
    }
}
