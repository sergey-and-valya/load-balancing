using Core;

namespace MatrixStorage
{
    public class MatrixData<T, TData> : IMatrixData<T, TData>
    {
        public MatrixData(string name, IMatrix<T> matrix, TData data)
        {
            Name = name;
            Matrix = matrix;
            Data = data;
        }

        public string Name { get; protected set; }
        public IMatrix<T> Matrix { get; protected set; }
        public TData Data { get; protected set; }

        public override string ToString()
        {
            return Name;
        }
    }
}
