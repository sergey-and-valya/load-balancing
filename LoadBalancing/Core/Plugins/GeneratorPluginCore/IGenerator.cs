using MatrixStorage;

namespace GeneratorPluginCore
{
    /// <summary>
    /// Генератор матриц с дополнительной информацией
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TData">Тип дополнительной информации, связанная с матрицей (например список хороших начальных решений)</typeparam>
    public interface IGenerator<T, TData>
    {
        /// <summary>
        /// Генерирует набор матриц, записывая каждую в хранилище
        /// </summary>
        /// <param name="matrixStorage">Хранилище матриц</param>
        void GenerateMatrixes(IMatrixWriteStorage<T, TData> matrixStorage);
    }
}
