using System;
using Core;

namespace CoreImpl1D
{
    /// <summary>
    /// Одномерный индекс
    /// </summary>
    public class Index1D : IIndex
    {
        /// <summary>
        /// Одномерный индекс
        /// </summary>
        /// <param name="i">Значение индекса</param>
        public Index1D(int i)
        {
            this.i = i;
        }

        /// <summary>
        /// Одномерный индекс
        /// </summary>
        /// <param name="i">Значение индекса</param>
        public Index1D() :
            this(-1)
        {
        }

        /// <summary>
        /// Значение индекса
        /// </summary>
        public int I
        {
            get { return i; }
            set { i = value; }
        }


        public int Dimensions
        {
            get { return 1; }
        }

        public int this[int dimension]
        {
            get
            {
                if (dimension != 0)
                    throw new Exception("У индекса только 1 компонента");
                return i;
            }
            set
            {
                if (dimension != 0)
                    throw new Exception("У индекса только 1 компонента");
                i = value;
            }
        }

        private int i;
    }
}
