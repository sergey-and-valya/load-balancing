using Core;

namespace VisualizerPluginCore
{
    /// <summary>
    /// Визуализатор решений
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface ISolutionVisualizer<T>
    {
        /// <summary>
        /// Отображает решение задачи
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <param name="solution">Решение задачи</param>
        void VisualizeSolution(IMatrix<T> matrix, ISolution solution);
    }
}
