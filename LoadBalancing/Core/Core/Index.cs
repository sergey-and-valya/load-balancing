using System;
using System.Collections.Generic;

namespace Core
{
    /// <summary>
    /// n-мерный индекс
    /// </summary>
    public class Index : IIndex
    {
        /// <summary>
        /// n-мерный индекс
        /// </summary>
        /// <param name="components">Компоненты индекса</param>
        public Index(IEnumerable<int> components)
        {
            this.components = new List<int>(components).ToArray();
        }

        /// <summary>
        /// n-мерный индекс
        /// </summary>
        /// <param name="components">Компоненты индекса</param>
        public Index(params int[] components) :
            this(components as IEnumerable<int>)
        {
        }


        public int Dimensions
        {
            get { return components.Length; }
        }

        public int this[int dimension]
        {
            get
            {
                if (dimension >= components.Length)
                    throw new Exception("Неверный номер измерения");
                return components[dimension];
            }
        }

        private int[] components;
    }
}
