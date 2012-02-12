using Core;

namespace MatrixStorage
{
    /// <summary>
    /// Хранилище матриц для записи
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TData">Тип дополнительной информации, связанная с матрицей (например список хороших начальных решений)</typeparam>
    public interface IMatrixWriteStorage<T, TData>
    {
        /// <summary>
        /// Сохраняет матрицу в хранилище
        /// </summary>
        /// <param name="name">Имя матрицы</param>
        /// <param name="matrix">Матрица</param>
        /// <param name="data">Дополнительная информация, связанные с матрицей  (например список хороших начальных решений)</param>
        /// <returns>Запись в хранилище, соответсвующая матрице</returns>
        IMatrixData<T, TData> SaveMatrix(string name, IMatrix<T> matrix, TData data);
    }
}
