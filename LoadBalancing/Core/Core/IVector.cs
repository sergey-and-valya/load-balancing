namespace Core
{
    public interface IVector<T>
    {
        T this[int i]
        {
            get;
            set;
        }

        int Size
        {
            get;
        }
    }
}
