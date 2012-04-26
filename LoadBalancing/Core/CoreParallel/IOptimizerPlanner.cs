using Core;
using LoadBalancing;

namespace CoreParallel
{
    /// <summary>
    /// Планировщик запусков локальных оптимизаторов
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IOptimizerPlanner<T>
    {
        /// <summary>
        /// Запустить планировщик для заданной задачи, используя указанный планировщик запросов на сборку информации
        /// </summary>
        /// <param name="parameters">Параметры разбиения</param>
        /// <param name="matrix">Исходная матрица</param>
        /// <param name="runner">Планировщик запросов на сборку информации с ячеек разбитой матрицы</param>
        /// <returns>Решение</returns>
        ISolution Run(PartitioningParameters parameters, IMatrix<T> matrix, IPlanner<T> runner);
    }
}
