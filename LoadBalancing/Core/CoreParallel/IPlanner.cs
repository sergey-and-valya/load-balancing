using Core;

namespace CoreParallel
{
    /// <summary>
    /// ѕланировщик запросов на сборку информации с €чеек разбитой матрицы
    /// </summary>
    /// <typeparam name="T">“ип хранимых в матрице данных</typeparam>
    public interface IPlanner<T>
    {
        /// <summary>
        /// —обрать информацию о матрице с €чейки разбитой матрицы
        /// </summary>
        /// <typeparam name="TCollectedData">“ип собираемых данных</typeparam>
        /// <param name="index">»ндекс €чейки разбитой матрицы</param>
        /// <param name="collector">—борщик информации</param>
        /// <returns>—обранна€ информаци€</returns>
        TCollectedData RunCollector<TCollectedData>(IIndex index, ICollector<T, TCollectedData> collector);
    }
}