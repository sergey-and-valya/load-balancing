using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl2D
{
    /// <summary>
    /// Допустимое решение двумерной задачи, как объединение двух одномерных решений
    /// </summary>
    /// <remarks>Хранит ссылки на одномерные решения, что позволяет менять решение, изменяя одномерные решения</remarks>
    public class ComposeSolution: ISolution
    {
        /// <summary>
        /// Допустимое решение двумерной задачи, как объединение двух одномерных решений
        /// </summary>
        /// <param name="x">Разбиение по первому направлению</param>
        /// <param name="y">Разбиение по второму направлению</param>
        public ComposeSolution(ISolution x, ISolution y)
        {
            this.X = x;
            this.Y = y;
        }

        /// <summary>
        /// Разбиение по первому направлению
        /// </summary>
        public ISolution X { get; protected set; }

        /// <summary>
        /// Разбиение по второму направлению
        /// </summary>
        public ISolution Y { get; protected set; }

        public int Dimensions
        {
            get { return 2; }
        }

        public int Size(int dimension)
        {
            switch (dimension)
            {
                case 0:
                    return X.Size(0);
                case 1:
                    return Y.Size(0);
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
                        return X[0];
                    case 1:
                        return Y[0];
                }
                throw new Exception("У разбиения только 2 размерности");
            }
        }
    }
}
