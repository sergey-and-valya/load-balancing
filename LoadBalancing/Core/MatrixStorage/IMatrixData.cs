using Core;

namespace MatrixStorage
{
    /// <summary>
    /// Данные, представляющие матрицу в хранилище матриц
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TData">Тип дополнительной информации, связанная с матрицей (например список хороших начальных решений)</typeparam>
    public interface IMatrixData<T, TData>
    {
        /// <summary>
        /// Название матрицы
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Матрица
        /// </summary>
        IMatrix<T> Matrix { get; }

        /// <summary>
        /// Информация, связанная с матрицей
        /// </summary>
        TData Data { get; }
    }
}
