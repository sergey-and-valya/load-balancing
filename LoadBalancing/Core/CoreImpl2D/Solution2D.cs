using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl2D
{
    /// <summary>
    /// Допустимое решение двумерной задачи
    /// </summary>
    public class Solution2D : ISolution
    {
        /// <summary>
        /// Допустимое решение двумерной задачи
        /// </summary>
        /// <param name="x">Разбиение по первому направлению</param>
        /// <param name="y">Разбиение по второму направлению</param>
        public Solution2D(IEnumerable<int> x, IEnumerable<int> y)
        {
            this.x = new List<int>(x).ToArray();
            this.y = new List<int>(y).ToArray();
        }

        /// <summary>
        /// Допустимое решение двумерной задачи
        /// </summary>
        /// <param name="x">Разбиение по первому направлению</param>
        /// <param name="y">Разбиение по второму направлению</param>
        public Solution2D(int[] x, int[] y) :
            this(x as IEnumerable<int>, y as IEnumerable<int>)
        {
        }


        public int Dimensions
        {
            get { return 2; }
        }

        public int Size(int dimension)
        {
            switch (dimension)
            {
                case 0:
                    return x.Length;
                case 1:
                    return y.Length;
            }
            throw new Exception("У разбиения только 2 размерности");
        }

        public IEnumerable<int> this[int dimension]
        {
            get
            {
                switch (dimension)
                {
                    case 0:
                        return x;
                    case 1:
                        return y;
                }
                throw new Exception("У разбиения только 2 размерности");
            }
        }

        private readonly int[] x;
        private readonly int[] y;
    }
}
