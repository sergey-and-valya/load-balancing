using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Core;
using LoadBalancing;

namespace CoreParallel
{
    /// <summary>
    /// Фабрика планировщиков запросов на сборку информации с ячеек разбитой матрицы
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IPlannerFactory<T>
    {
        /// <summary>
        /// Создать планировщик запросов на сборку информации с ячеек разбитой матрицы для конкретной задачи
        /// </summary>
        /// <param name="parameters">Параметры разбиения</param>
        /// <param name="matrix">Матрица</param>
        /// <returns>Планировщик запросов на сборку информации с ячеек разбитой матрицы для данной задачи</returns>
        IPlanner<T> CreatePlanner(PartitioningParameters parameters, IMatrix<T> matrix);
    }
}