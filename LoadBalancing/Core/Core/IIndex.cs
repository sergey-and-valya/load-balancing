namespace Core
{
    /// <summary>
    /// Индекс в матрице.
    /// Для вектора размерность индекса равна 1 и описывает номер элемента в векторе.
    /// Для матрицы размерность индекса равна 2 и описывает номер строки и номер столбца в матрице.
    /// </summary>
    public interface IIndex
    {
        /// <summary>
        /// Размерность индекса (число компонент)
        /// </summary>
        int Dimensions { get; }

        /// <summary>
        /// Компонента индекса в размерности dimension
        /// </summary>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Компонента индекса</returns>
        int this[int dimension] { get; }
    }
}
