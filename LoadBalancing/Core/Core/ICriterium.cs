namespace Core
{
    /// <summary>
    /// Критерий задачи
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface ICriterium<T>
    {
        /// <summary>
        /// Значение критерия
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <param name="solution">Допустимое решение</param>
        /// <returns>Значение критерия</returns>
        double Value(IMatrix<T> matrix, ISolution solution);
    }
}
