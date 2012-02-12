using Core;

namespace AlgorithmPluginCore
{
    /// <summary>
    /// Алгоритм
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TProblem">Тип исходной задачи</typeparam>
    public interface IAlgorithm<T, TProblem>
        where TProblem : IProblem<T>
    {
        /// <summary>
        /// Запустить алгоритм
        /// </summary>
        /// <param name="problem">Исходная задача</param>
        /// <returns>Решение, полученное алгоритмом</returns>
        ISolution Run(TProblem problem);
    }
}
