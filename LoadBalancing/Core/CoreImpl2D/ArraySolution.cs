using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl2D
{
    /// <summary>
    /// Допустимое решение двумерной задачи
    /// </summary>
    /// <remarks>Хранит ссылки на массивы, что позволяет менять решение, изменяя массивы</remarks>
    public class ArraySolution: ISolution
    {
        /// <summary>
        /// Допустимое решение двумерной задачи
        /// </summary>
        /// <param name="x">Разбиение по первому направлению</param>
        /// <param name="y">Разбиение по второму направлению</param>
        public ArraySolution(int[] x, int[] y)
        {
            this.X = x;
            this.Y = y;
        }

        /// <summary>
        /// Разбиение по первому направлению
        /// </summary>
        public int[] X { get; protected set; }

        /// <summary>
        /// Разбиение по второму направлению
        /// </summary>
        public int[] Y { get; protected set; }

        public int Dimensions
        {
            get { return 2; }
        }

        public int Size(int dimension)
        {
            switch (dimension)
            {
                case 0:
                    return X.Length;
                case 1:
                    return Y.Length;
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
                        return X;
                    case 1:
                        return Y;
                }
                throw new Exception("У разбиения только 2 размерности");
            }
        }
    }
}
