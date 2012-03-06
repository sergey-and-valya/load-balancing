namespace AlgorithmPluginCore
{
    /// <summary>Плагин алгоритм</summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TProblemParameters">Тип параметров исходной задачи</typeparam>
    public interface IAlgorithmPlugin<T, in TProblemParameters>
    {
        /// <summary>
        /// Название плагина
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Имеется ли в плагине алгоритм решения задачи балансировки нагрузки для матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>
        /// true, если вызов CreateAlgorithm(dimensions, parameters) может вернуть
        /// алгоритм решения задачи для матриц размерности dimensions.
        /// false, если CreateAlgorithm(dimensions, parameters) точно вернёт null
        /// </returns>
        bool HasAlgorithm(int dimensions);

        /// <summary>
        /// Создаёт алгоритм решения задачи балансировки нагрузки для матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <param name="parameters">Описание параметров исходной задачи</param>
        /// <returns>
        /// Алгоритм решения задачи или null, если плагин не может быть правильно
        /// сконфигурирован, например, если пользователь не ввёл дополнительные данные
        /// </returns>
        IAlgorithm<T> CreateAlgorithm(int dimensions, TProblemParameters parameters);
    }
}
