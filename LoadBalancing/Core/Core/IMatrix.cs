namespace Core
{
    /// <summary>
    /// Матрица некоторой размерности
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IMatrix<T>
    {
        /// <summary>
        /// Размерность матрицы (1 - вектор, 2 - матрица, 3 - трёхмерный массив и т.д.)
        /// </summary>
        int Dimensions
        {
            get;
        }

        /// <summary>
        /// Размер матрицы в соответствующем направлении (например, Size(0) = m, Size(1) = n в двумерном случае)
        /// </summary>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Размер матрицы в выбранном направлении</returns>
        int Size(int dimension);

        /// <summary>
        /// Элемент матрицы по индексу
        /// </summary>
        /// <param name="index">Индекс</param>
        /// <returns>Элемент матрицы</returns>
        T this[IIndex index]
        {
            get;
            set;
        }
    }
}