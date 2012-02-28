using Core;

namespace LoadBalancing
{
    /// <summary>
    /// Вспомогательные функции
    /// </summary>
    public static class Utilities
    {
        /// <summary>
        /// Сумма элементов матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <returns>Сумма элементов</returns>
        public static long Sum(IMatrix<int> matrix)
        {
            long sum = 0;
            foreach (IIndex index in MultiDimensionMatrixEnumerator.Indexes(matrix))
                sum += matrix[index];
            return sum;
        }

        /// <summary>
        /// Средняя нагрузка при заданных параметрах разбиения матрицы
        /// </summary>
        /// <param name="matrix">Матрица</param>
        /// <param name="partitioning">Параметры разбиения матрицы</param>
        /// <returns>Сумма элементов</returns>
        public static double W(IMatrix<int> matrix, PartitioningParameters partitioning)
        {
            int N = 1;
            for (int i = 0; i < partitioning.Dimensions; i++)
                N *= partitioning[i];

            return Sum(matrix) / (double)N;
        }
    }
}
