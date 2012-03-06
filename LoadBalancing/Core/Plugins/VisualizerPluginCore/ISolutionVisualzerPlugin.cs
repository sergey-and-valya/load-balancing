namespace VisualizerPluginCore
{
    /// <summary>
    /// Плагин визуализатора решений задачи
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface ISolutionVisualizerPlugin<T>
    {
        /// <summary>
        /// Название плагина
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Имеется ли в плагине визуализатор решений задачи для заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность решений задачи</param>
        /// <returns>
        /// true, если вызов CreateSolutionVisualizer(dimensions) может вернуть
        /// визуализатор решений задачи размерности dimensions.
        /// false, если CreateSolutionVisualizer(dimensions) точно вернёт null
        /// </returns>
        bool HasSolutionVisualizer(int dimensions);

        /// <summary>
        /// Создаёт визуализатор решений задачи заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность решения задачи</param>
        /// <returns>
        /// Визуализатор решений задачи заданной размерности или null, если плагин не может
        /// быть правильно сконфигурирован, например, если пользователь не ввёл дополнительные данные
        /// </returns>
        ISolutionVisualizer<T> CreateSolutionVisualizer(int dimensions);
    }
}
