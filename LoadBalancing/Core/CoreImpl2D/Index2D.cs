using System;
using Core;

namespace CoreImpl2D
{
    /// <summary>
    /// Двумерный индекс
    /// </summary>
    public class Index2D : IIndex
    {
        /// <summary>
        /// Двумерный индекс
        /// </summary>
        /// <param name="i">Первая компонента индекса</param>
        /// <param name="j">Вторая компонента индекса</param>
        public Index2D(int i, int j)
        {
            this.i = i;
            this.j = j;
        }

        /// <summary>
        /// Двумерный индекс
        /// </summary>
        public Index2D() :
            this(-1, -1)
        {
        }

        /// <summary>
        /// Первая компонента индекса
        /// </summary>
        public int I
        {
            get { return i; }
            set { i = value; }
        }

        /// <summary>
        /// Вторая компонента индекса
        /// </summary>
        public int J
        {
            get { return j; }
            set { j = value; }
        }

        public int Dimensions
        {
            get { return 2; }
        }

        public int this[int dimension]
        {
            get
            {
                switch (dimension)
                {
                    case 0:
                        return i;
                    case 1:
                        return j;
                }
                throw new Exception("У индекса только 2 компоненты");
            }
            set
            {
                switch (dimension)
                {
                    case 0:
                        i = value;
                        break;
                    case 1:
                        j = value;
                        break;
                    default:
                        throw new Exception("У индекса только 2 компоненты");
                }
            }
        }

        private int i;
        private int j;
    }
}
