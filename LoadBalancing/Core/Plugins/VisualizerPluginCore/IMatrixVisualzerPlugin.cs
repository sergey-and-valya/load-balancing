namespace VisualizerPluginCore
{
    /// <summary>
    /// Плагин визуализатора матриц
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IMatrixVisualizerPlugin<T>
    {
        /// <summary>
        /// Название плагина
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Имеется ли в плагине визуализатор матриц для заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>true, если вызов CreateMatrixVisualizer(dimensions) вернёт визуализатор матриц размерности dimensions.
        /// false, если CreateMatrixVisualizer(dimensions) вернёт null</returns>
        bool HasMatrixVisualizer(int dimensions);

        /// <summary>
        /// Создаёт визуализатор матриц заданной размерности
        /// </summary>
        /// <param name="dimensions">Размерность матрицы</param>
        /// <returns>Визуализатор матриц заданной размерности или null,
        /// если плагин не может быть правильно сконфигурирован, например,
        /// если пользователь не ввёл дополнительные данные</returns>
        IMatrixVisualizer<T> CreateMatrixVisualizer(int dimensions);
    }
}