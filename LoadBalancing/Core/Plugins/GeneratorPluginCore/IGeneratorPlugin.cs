using System;
using MatrixStorage;

namespace GeneratorPluginCore
{
    /// <summary>
    /// Плагин генератора матриц
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TData">Тип дополнительной информации, связанная с матрицей (например список хороших начальных решений)</typeparam>
    public interface IGeneratorPlugin<T, TData>
    {
        /// <summary>
        /// Название плагина
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Имеется ли в плагине генератор матриц для заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>true, если вызов CreateGenerator(dimensions) вернёт генератор матриц размерности dimensions.
        /// false, если CreateGenerator(dimensions) вернёт null</returns>
        bool HasGenerator(int dimensions);

        /// <summary>
        /// Создаёт генератор матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>Генератор матриц заданной размерности или null,
        /// если плагин не может быть правильно сконфигурирован, например,
        /// если пользователь не ввёл дополнительные данные</returns>
        IGenerator<T, TData> CreateGenerator(int dimensions);
    }
}
