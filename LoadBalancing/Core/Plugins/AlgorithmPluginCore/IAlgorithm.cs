using Core;

namespace AlgorithmPluginCore
{
    /// <summary>
    /// Алгоритм для решения задачи разбиения матрицы
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IAlgorithm<T>
    {
        /// <summary>
        /// Запустить алгоритм для решения задачи разбиения матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Решение, полученное алгоритмом</returns>
        ISolution Run(IMatrix<T> matrix);
    }
}
