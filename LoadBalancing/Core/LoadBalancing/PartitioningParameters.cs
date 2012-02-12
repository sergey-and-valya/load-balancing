using System;
using System.Collections.Generic;

namespace LoadBalancing
{
    /// <summary>
    /// Параметры задачи балансировки - число разбиений по каждому направлению
    /// </summary>
    public class PartitioningParameters
    {
        /// <summary>
        /// Параметры задачи балансировки - число разбиений по каждому направлению
        /// </summary>
        /// <param name="counts">Число разбиений по каждому направлению</param>
        public PartitioningParameters(IEnumerable<int> counts)
        {
            this.counts = new List<int>(counts).ToArray();
        }

        /// <summary>
        /// Параметры задачи балансировки - число разбиений по каждому направлению
        /// </summary>
        /// <param name="counts">Число разбиений по каждому направлению</param>
        public PartitioningParameters(params int[] counts) :
            this(counts as IEnumerable<int>)
        {
        }

        /// <summary>
        /// Размерность разбиваемой матрицы
        /// </summary>
        public int Dimensions
        {
            get { return counts.Length; }
        }

        /// <summary>
        /// Число разбиений в направлении dimension
        /// </summary>
        /// <param name="dimension">Номер размерности (0 - i, 1 - j и т.д.) от 0 до Dimensions - 1</param>
        /// <returns>Число разбиений</returns>
        public int this[int dimension]
        {
            get
            {
                if (dimension >= counts.Length)
                    throw new Exception("Неверный номер измерения");
                return counts[dimension];
            }
        }

        private int[] counts;
    }
}
