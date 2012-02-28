using System.Collections.Generic;
using Core;

namespace MatrixStorage
{
    /// <summary>
    /// Хранилище матриц для чтения
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TData">Тип дополнительной информации, связанная с матрицей (например список хороших начальных решений)</typeparam>
    public interface IMatrixReadStorage<T, out TData>
    {
        /// <summary>
        /// Получает перечисление матриц в хранилище
        /// </summary>
        /// <returns>Перечисление матриц в хранилище</returns>
        IEnumerable<IMatrixData<T, TData>> ReadMatrixes();
    }
}
