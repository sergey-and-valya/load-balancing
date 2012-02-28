using Core;

namespace CoreImpl1D
{
    /// <summary>
    /// Оболочка вокруг вектора, позволяющая работать по-номральному с вектором
    /// </summary>
    /// <typeparam name="T">Тип хранимых в векторе данных</typeparam>
    public class VectorWrapper<T> : IMatrix<T>
    {
        public VectorWrapper(IMatrix<T> matrix)
        {
            this.matrix = matrix;
        }

        public T this[int i]
        {
            get
            {
                return this[new Index1D(i)];
            }
            set
            {
                this[new Index1D(i)] = value;
            }
        }

        public int N
        {
            get { return Size(0); }
        }

        public int Dimensions
        {
            get { return matrix.Dimensions; }
        }

        public int Size(int dimension)
        {
            return matrix.Size(dimension);
        }

        public T this[IIndex index]
        {
            get
            {
                return matrix[index];
            }
            set
            {
                matrix[index] = value;
            }
        }

        private readonly IMatrix<T> matrix;
    }
}
