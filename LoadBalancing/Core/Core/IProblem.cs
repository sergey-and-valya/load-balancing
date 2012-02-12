namespace Core
{
    /// <summary>
    /// Задача
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public interface IProblem<T>
    {
        /// <summary>
        /// Матрица
        /// </summary>
        IMatrix<T> Matrix { get; }

        /// <summary>
        /// Критерий задачи
        /// </summary>
        ICriterium<T> Criterium { get; }
    }
}
