using System.Collections.Generic;
using Core;

namespace CoreParallel
{
    /// <summary>
    /// Локальный оптимизатор решения
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface ILocalOptimizer<T>
    {
        /// <summary>
        /// Список индексов ячеек разбитой матрицы, в пределах которых локальный оптимизатор
        /// проводит оптимизацию
        /// </summary>
        /// <returns>Перечисление индексов разбитой матрицы</returns>
        /// <remarks>
        /// Одновременно могут быть запущены только те локальные оптимизаторы,
        /// для которых эти списки не пересекаются
        /// </remarks>
        IEnumerable<IIndex> Workers();
        
        /// <summary>
        /// Запустить процедуру локальной оптимизации
        /// </summary>
        /// <param name="planner">Планировщик запросов на сборку информации с ячеек разбитой матрицы</param>
        /// <returns>Преобразование текущего решения, выполненное локальным оптимизатором</returns>
        ISolutionModification Run(IPlanner<T> planner);
    }
}
