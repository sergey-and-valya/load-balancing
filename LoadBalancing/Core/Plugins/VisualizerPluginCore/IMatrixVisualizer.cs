using Core;

namespace VisualizerPluginCore
{
    /// <summary>
    /// Визуализатор матриц
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IMatrixVisualizer<T>
    {
        /// <summary>
        /// Отображает матрицу
        /// </summary>
        /// <param name="matrix">Матрица</param>
        void VisualizeMatrix(IMatrix<T> matrix);
    }
}
