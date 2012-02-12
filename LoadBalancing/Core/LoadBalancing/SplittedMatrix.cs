using System;
using System.Collections.Generic;
using System.Linq;
using Core;

namespace LoadBalancing
{
    /// <summary>
    /// Матрица ячеек, полученных с помощью данного разбиения
    /// </summary>
    public class SplittedMatrix : IMatrix<int>
    {
        /// <summary>
        /// Матрица ячеек, полученных с помощью данного разбиения
        /// </summary>
        /// <param name="matrix">Исходная матрицы</param>
        /// <param name="solution">Допустимое решение</param>
        public SplittedMatrix(IMatrix<int> matrix, ISolution solution)
        {
            if (matrix.Dimensions != solution.Dimensions)
                throw new Exception("Размерности матрицы и решения должны совпадать");

            this.matrix = matrix;
            this.solution = solution;
        }

        /// <summary>
        /// Индексы элементов исходной матрицы, которые принадлежат ячейке разбитой матрицы с индексом index
        /// </summary>
        /// <param name="index">Индекс ячейки разбитой матрицы</param>
        /// <returns>Перечисление элементов исходной матрицы, которые принадлежат ячейке разбитой матрицы с индексом index</returns>
        public IEnumerable<IIndex> CellElements(IIndex index)
        {
            int[] low = new int[index.Dimensions];
            int[] high = new int[index.Dimensions];

            for (int i = 0; i < index.Dimensions; i++)
            {
                low[i] = CellLow(index[i], i);
                high[i] = CellHigh(index[i], i);
            }

            return RangeEnumerator.Indexes(low, high);
        }

        /// <summary>
        /// Индекс первой строки исходной матрицы, принадлежащей заданной ячейки разбитой матрицы в заданном направлении
        /// </summary>
        /// <param name="index">Индекс ячейки разбитой матрицы в заданной размерности</param>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Индекс первой строки исходной матрицы, принадлежащей заданной ячейки разбитой матрицы в заданном направлении</returns>
        public int CellLow(int index, int dimension)
        {
            if (index == 0)
                return 0;
            else
                return solution[dimension].ElementAt(index - 1);
        }

        /// <summary>
        /// Индекс последней строки исходной матрицы, принадлежащей заданной ячейки разбитой матрицы в заданном направлении
        /// </summary>
        /// <param name="index">Индекс ячейки разбитой матрицы в заданной размерности</param>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Индекс последней строки исходной матрицы, принадлежащей заданной ячейки разбитой матрицы в заданном направлении</returns>
        public int CellHigh(int index, int dimension)
        {
            if (index == solution.Size(dimension))
                return matrix.Size(dimension) - 1;
            else
                return solution[dimension].ElementAt(index) - 1;
        }

        public int Dimensions
        {
            get { return matrix.Dimensions; }
        }

        public int Size(int dimension)
        {
            return solution.Size(dimension) + 1;
        }

        public int this[IIndex index]
        {
            get
            {
                int sum = 0;
                foreach (IIndex ind in CellElements(index))
                {
                    sum += matrix[ind];
                }

                return sum;
            }
            set
            {
                throw new InvalidOperationException();
            }
        }

        private IMatrix<int> matrix;
        private ISolution solution;
    }
}