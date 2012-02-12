using System;
using Core;

namespace CoreUtilities
{
    public static class Utilities
    {
        public static T Max<T>(IMatrix<T> matrix, T max)
            where T : IComparable<T>
        {
            foreach (IIndex index in MultiDimensionMatrixEnumerator.Indexes(matrix))
                if (max.CompareTo(matrix[index]) < 0)
                    max = matrix[index];
            return max;
        }

        public static T Min<T>(IMatrix<T> matrix, T min)
            where T : IComparable<T>
        {
            foreach (IIndex index in MultiDimensionMatrixEnumerator.Indexes(matrix))
                if (min.CompareTo(matrix[index]) > 0)
                    min = matrix[index];
            return min;
        }
    }
}