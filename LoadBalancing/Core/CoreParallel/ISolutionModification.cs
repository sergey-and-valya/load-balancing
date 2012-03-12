using Core;

namespace CoreParallel
{
    /// <summary>
    /// Преобразование решения, произведённое локальным решателем
    /// </summary>
    public interface ISolutionModification
    {
        /// <summary>
        /// Получить для указанного решения новое решение,
        /// путём применения данного преобразования
        /// </summary>
        /// <param name="solution">Исходное решение</param>
        /// <returns>Преобразованное решение</returns>
        ISolution ApplyTo(ISolution solution);
    }
}