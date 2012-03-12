using Core;

namespace CoreParallel
{
    /// <summary>
    /// Сборщик информации о матрице на узле
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    /// <typeparam name="TCollectedData">Тип собираемых данных</typeparam>
    public interface ICollector<T, out TCollectedData>
    {
        /// <summary>
        /// Собрать информацию о матрице
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Собранная информация</returns>
        TCollectedData CollectData(IMatrix<T> matrix);
    }
}
