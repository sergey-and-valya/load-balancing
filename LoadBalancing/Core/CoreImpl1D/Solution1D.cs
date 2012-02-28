using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl1D
{
    /// <summary>
    /// Допустимое решение одномерной задачи
    /// </summary>
    public class Solution1D : ISolution
    {
        /// <summary>
        /// Допустимое решение одномерной задачи
        /// </summary>
        /// <param name="x">Разбиение</param>
        public Solution1D(IEnumerable<int> x)
        {
            this.x = new List<int>(x).ToArray();
        }

        /// <summary>
        /// Допустимое решение одномерной задачи
        /// </summary>
        /// <param name="x">Разбиение</param>
        public Solution1D(params int[] x) :
            this(x as IEnumerable<int>)
        {
        }

        /// <summary>
        /// Точка разбиения
        /// </summary>
        /// <param name="i">Номер точки разбиения от 0 до Size - 1</param>
        /// <returns>i-ая точка разбиения</returns>
        public int this[int i]
        {
            get { return x[i]; }
            set { x[i] = value; }
        }

        /// <summary>
        /// Количество точек разбиения решения
        /// </summary>
        /// <returns>Число точек разбиения</returns>
        public int Size
        {
            get { return x.Length; }
        }



        int ISolution.Dimensions
        {
            get { return 1; }
        }

        int ISolution.Size(int dimension)
        {
            if (dimension != 0)
                throw new Exception("У разбиения только 1 размерность");
            return x.Length;
        }

        IEnumerable<int> ISolution.this[int dimension]
        {
            get
            {
                if (dimension != 0)
                    throw new Exception("У разбиения только 1 размерность");
                return x;
            }
        }

        private readonly int[] x;
    }
}
