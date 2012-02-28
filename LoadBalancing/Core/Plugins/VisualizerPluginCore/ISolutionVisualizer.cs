using System.Collections.Generic;
using Core;

namespace VisualizerPluginCore
{
    /// <summary>
    /// Визуализатор решений
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TProblem">Тип исходной задачи</typeparam>
    public interface ISolutionVisualizer<T, in TProblem>
        where TProblem : IProblem<T>
    {
        /// <summary>
        /// Отображает решение задачи
        /// </summary>
        /// <param name="problem">Исходная задача</param>
        /// <param name="solution">Решение задачи</param>
        void VisualizeSolution(TProblem problem, ISolution solution);
    }
}
