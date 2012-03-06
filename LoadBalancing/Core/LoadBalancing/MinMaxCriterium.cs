using Core;

namespace LoadBalancing
{
    /// <summary>
    /// Минимаксный критерий для загрузки
    /// </summary>
    public static class MinMaxCriterium
    {
        public static double Calculate(IMatrix<int> matrix, ISolution solution)
        {
            return CoreUtilities.Utilities.Max(new SplittedMatrix(matrix, solution));
        }
    }
}