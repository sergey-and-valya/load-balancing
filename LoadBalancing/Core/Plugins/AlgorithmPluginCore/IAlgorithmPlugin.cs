using Core;
namespace AlgorithmPluginCore
{
    /// <summary>Плагин алгоритм</summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TProblem">Тип исходной задачи</typeparam>
    public interface IAlgorithmPlugin<T, TProblem>
        where TProblem : IProblem<T>
    {
        /// <summary>
        /// Название плагина
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Имеется ли в плагине алгоритм решения задачи балансировки нагрузки для матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>true, если вызов CreateAlgorithm(dimensions) алгоритм решения задачи балансировки нагрузки для матриц размерности dimensions.
        /// false, если CreateAlgorithm(dimensions) вернёт null</returns>
        bool HasAlgorithm(int dimensions);

        /// <summary>
        /// Создаёт алгоритм решения задачи балансировки нагрузки для матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>Алгоритм решения задачи балансировки нагрузки или null,
        /// если плагин не может быть правильно сконфигурирован, например,
        /// если пользователь не ввёл дополнительные данные</returns>
        IAlgorithm<T, TProblem> CreateAlgorithm(int dimensions);
    }
}
