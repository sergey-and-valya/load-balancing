using System;
using System.Collections.Generic;

namespace Core
{
    /// <summary>
    /// Допустимое решение n-мерной задачи
    /// </summary>
    public class Solution : ISolution
    {
        /// <summary>
        /// Допустимое решение n-мерной задачи
        /// </summary>
        /// <param name="x">Разбиения</param>
        public Solution(IEnumerable<int[]> x)
        {
            this.x = new List<int[]>(x).ToArray();
        }

        /// <summary>
        /// Допустимое решение n-мерной задачи
        /// </summary>
        /// <param name="x">Разбиения</param>
        public Solution(params int[][] x) :
            this(x as IEnumerable<int[]>)
        {
        }


        public int Dimensions
        {
            get { return x.Length; }
        }

        public int Size(int dimension)
        {
            if (dimension >= x.Length)
                throw new Exception("Неверный номер измерения");
            return x[dimension].Length;
        }

        public IEnumerable<int> this[int dimension]
        {
            get
            {
                if (dimension >= x.Length)
                    throw new Exception("Неверный номер измерения");
                return x[dimension];
            }
        }

        int[][] x;
    }
}
