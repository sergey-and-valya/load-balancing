using Core;

namespace LoadBalancing
{
    /// <summary>
    /// Минимаксный критерий для загрузки
    /// </summary>
    public sealed class MinMaxCriterium : ICriterium<int>
    {
        private MinMaxCriterium() { }

        private static MinMaxCriterium instance;

        public static MinMaxCriterium Instance
        {
            get
            {
                return instance ?? (instance = new MinMaxCriterium());
            }
        }

        public double Value(IMatrix<int> matrix, ISolution solution)
        {
            SplittedMatrix m = new SplittedMatrix(matrix, solution);
            return CoreUtilities.Utilities.Max(m);
        }
    }
}