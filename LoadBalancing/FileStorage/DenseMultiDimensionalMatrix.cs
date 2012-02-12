using System;
using Core;

namespace FileStorage
{
    /// <summary>
    /// n-мерная сплошная матрица
    /// </summary>
    /// <typeparam name="T">Тип хранимых в матрице данных</typeparam>
    public class DenseMultiDimensionalMatrix<T> : IMatrix<T>
    {
        /// <summary>
        /// n-мерная сплошная матрица
        /// </summary>
        /// <param name="size">Размеры матрицы в каждом измерении</param>
        public DenseMultiDimensionalMatrix(int[] size)
        {
            this.size = size;

            matrix = Array.CreateInstance(typeof(T), size);
        }

        #region IMatrix<T> Members

        public int Dimensions
        {
            get { return size.Length; }
        }

        public int Size(int dimension)
        {
            return size[dimension];
        }

        public T this[IIndex index]
        {
            get
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                var ind = new int[index.Dimensions];
                for (int i = 0; i < index.Dimensions; i++)
                    ind[i] = index[i];
                return (T)matrix.GetValue(ind);
            }
            set
            {
                if (index.Dimensions != Dimensions)
                    throw new Exception("Неверная размерность индекса");
                var ind = new int[index.Dimensions];
                for (int i = 0; i < index.Dimensions; i++)
                    ind[i] = index[i];
                matrix.SetValue(value, ind);
            }
        }

        #endregion IMatrix<T> Members

        int[] size;

        Array matrix;
    }
}