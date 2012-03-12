using System.Threading;
using Core;

namespace CoreParallel
{
    /// <summary>
    /// Дополнения для IPlanner
    /// </summary>
    public static class PlannerExtensions
    {
        /// <summary>
        /// Выполнить синхронный сбор информации с процессора
        /// </summary>
        /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
        /// <typeparam name="TCollectedData">Тип собираемых данных</typeparam>
        /// <param name="planner">Планировщик запросов</param>
        /// <param name="index">Индекс ячейки разбитой матрицы</param>
        /// <param name="collector">Сборщик информации</param>
        /// <returns>Собранная информация</returns>
        public static TCollectedData RunCollector<T, TCollectedData>(this IPlanner<T> planner, IIndex index, ICollector<T, TCollectedData> collector)
        {
            var e = new ManualResetEvent(false);
            TCollectedData result = default(TCollectedData);
            planner.RunCollectorAsync(index, collector, (data) =>
                {
                    result = data;
                    e.Set();
                });
            e.WaitOne();

            return result;
        }
    }
}