using System.Collections.Generic;
using Core;

namespace CoreParallel
{
    /// <summary>
    /// Локальный оптимизатор решения
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface ILocalSolver<T>
    {
        /// <summary>
        /// Список индексов ячеек разбитой матрицы, в пределах которых локальный оптимизатор
        /// проводит оптимизацию
        /// </summary>
        /// <param name="matrix">Исходная задача</param>
        /// <param name="solution">Текущее разбиение матрицы</param>
        /// <returns>Перечисление индексов разбитой матрицы</returns>
        /// <remarks>
        /// Одновременно могут быть запущены только те локальные оптимизаторы,
        /// для которых эти списки не пересекаются
        /// </remarks>
        IEnumerable<IIndex> Workers(IMatrix<T> matrix, ISolution solution);
        
        /// <summary>
        /// Запустить процедуру локальной оптимизации
        /// </summary>
        /// <param name="matrix">Исходная задача</param>
        /// <param name="solution">Текущее разбиение матрицы</param>
        /// <returns>Преобразование текущего решения, выполненное локальным оптимизатором</returns>
        ISolutionModification Run(IMatrix<T> matrix, ISolution solution);
    }
}
