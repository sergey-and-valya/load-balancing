using System;
using System.Collections.Generic;
using Core;

namespace CoreParallel
{
    /// <summary>
    /// ѕреобразование решени€, смещающее одну из точек разбиени€ на новую позицию
    /// </summary>
    public class MovePartitionPoint : ISolutionModification
    {
        /// <summary>
        /// –ешение, полученное после применени€ решени€
        /// </summary>
        protected class ModifiedSolution : ISolution
        {
            public ModifiedSolution(ISolution baseSolution, int dimension, int i, int newPosition)
            {
                this.dimension = dimension;
                this.i = i;
                this.newPosition = newPosition;
        
                BaseSolution = baseSolution;
            }

            public int Dimensions
            {
                get { return BaseSolution.Dimensions; }
            }

            public int Size(int dimension)
            {
                return BaseSolution.Dimensions;
            }

            private IEnumerable<int> MovePosition(IEnumerable<int> enumerable)
            {

            }

            public IEnumerable<int> this[int dimension]
            {
                get
                {
                    if (dimension != this.dimension)
                    {
                        return BaseSolution[dimension];
                    }

                    return BaseSolution[dimension]
                }
            }

            private readonly int dimension;
            private readonly int i;
            private readonly int newPosition;
            protected readonly ISolution BaseSolution;
        }

        /// <summary>
        /// ѕреобразование решени€, смещающее одну из точек разбиени€ на новую позицию
        /// </summary>
        /// <param name="dimension">Ќомер разбиени€</param>
        /// <param name="i">Ќомер точки разбиени€</param>
        /// <param name="newPosition">Ќовое положение точки разбиени€</param>
        public MovePartitionPoint(int dimension, int i, int newPosition)
        {
            this.dimension = dimension;
            this.i = i;
            this.newPosition = newPosition;
        }

        public ISolution ApplyTo(ISolution solution)
        {
            return new ModifiedSolution(solution, dimension, i, newPosition);
        }

        private readonly int dimension;
        private readonly int i;
        private readonly int newPosition;
    }
}