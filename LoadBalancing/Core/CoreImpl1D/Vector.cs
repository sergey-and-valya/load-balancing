using System;
using System.Collections.Generic;
using Core;

namespace CoreImpl1D
{
    /// <summary>
    /// Вектор
    /// </summary>
    /// <typeparam name="T">Тип хранимых в векторе данных</typeparam>
    public class Vector<T> : IMatrix<T>
    {
        /// <summary>
        /// Вектор
        /// </summary>
        /// <param name="n">Число элементов вектора</param>
        public Vector(int n)
        {
            vector = new T[n];
        }
        
        /// <summary>
        /// Вектор
        /// </summary>
        /// <param name="vector">Компоненты вектора</param>
        public Vector(IEnumerable<T> vector)
        {
            this.vector = new List<T>(vector).ToArray();
        }

        /// <summary>
        /// Целочисленный вектор
        /// </summary>
        /// <param name="vector">Компоненты вектора</param>
        public Vector(params T[] vector) :
            this(vector as IEnumerable<T>)
        {
        }

        /// <summary>
        /// Число элементов вектора
        /// </summary>
        public int N
        {
            get { return vector.Length; }
        }

        public T this[int i]
        {
            get
            {
                return vector[i];
            }
            set
            {
                vector[i] = value;
            }
        }


        public int Dimensions
        {
            get { return 1; }
        }

        public int Size(int dimension)
        {
            if (dimension != 0)
                throw new Exception("У вектора только 1 размерность");
            return vector.Length;
        }

        public T this[IIndex index]
        {
            get
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                return vector[index[0]];
            }
            set
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                vector[index[0]] = value;
            }
        }

        private readonly T[] vector;
    }
}
