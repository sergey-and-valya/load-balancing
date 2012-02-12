using System.Xml;
using System.Xml.Serialization;
using MatrixStorage;
using Core;
using System.Collections.Generic;
using System.IO;
using System;
using LoadBalancing;

namespace FileStorage
{
    using SolutionData = Tuple<PartitioningParameters, ISolution, double>;

    public class Storage :
        IMatrixReadStorage<int, EmptyData>, IMatrixWriteStorage<int, EmptyData>,
        IMatrixReadStorage<int, SolutionData>, IMatrixWriteStorage<int, SolutionData>
    {
        [Serializable]
        public class FileMatrixData
        {
            private class EmptyDataRecord : IMatrixData<int, EmptyData>
            {
                private FileMatrixData parent;

                public EmptyDataRecord(FileMatrixData parent)
                {
                    this.parent = parent;
                }

                public string Name
                {
                    get { return parent.Name; }
                }

                public IMatrix<int> Matrix
                {
                    get { return parent.Matrix; }
                }

                public EmptyData Data
                {
                    get { return null; }
                }
            }

            private class SolutionDataRecord : IMatrixData<int, SolutionData>
            {
                private FileMatrixData parent;

                public SolutionDataRecord(FileMatrixData parent)
                {
                    this.parent = parent;
                }

                public string Name
                {
                    get { return parent.Name; }
                }

                public IMatrix<int> Matrix
                {
                    get { return parent.Matrix; }
                }

                public SolutionData Data
                {
                    get { return parent.Solution; }
                }
            }

            public FileMatrixData()
            {
            }

            public FileMatrixData(string basePath, string name, string filename, int[] sizes, string solutionFilename = null)
            {
                this.BasePath = basePath;
                this.Name = name;
                this.Filename = filename;
                this.Sizes = sizes;
                this.SolutionFilename = solutionFilename;
            }

            [XmlIgnore]
            public string BasePath { get; set; }

            public IMatrixData<int, EmptyData> AsMatrixData()
            {
                if (SolutionFilename == null)
                    return new EmptyDataRecord(this);

                return null;
            }

            public IMatrixData<int, SolutionData> AsSolutionData()
            {
                if (SolutionFilename != null)
                    return new SolutionDataRecord(this);

                return null;
            }

            [XmlIgnore]
            private IMatrix<int> Matrix
            {
                get
                {
                    var m = matrix.Target as IMatrix<int>;
                    if (m == null)
                    {
                        m = new DenseMultiDimensionalMatrix<int>(Sizes);
                        matrix.Target = m;

                        using (var stream = File.OpenRead(BasePath + Filename))
                        using (var reader = new BinaryReader(stream))
                        {
                            foreach (var index in MultiDimensionMatrixEnumerator.Indexes(m))
                            {
                                m[index] = reader.ReadInt32();
                            }
                        }
                    }
                    return m;
                }
            }

            [XmlIgnore]
            private SolutionData Solution
            {
                get
                {
                    if (SolutionFilename == null)
                    {
                        return null;
                    }

                    var solutionData = solution.Target as SolutionData;
                    if (solutionData == null)
                    {
                        using (var stream = File.OpenRead(BasePath + SolutionFilename))
                        using (var reader = new BinaryReader(stream))
                        {
                            var counts = new int[Sizes.Length];
                            for (int i = 0; i < Sizes.Length; i++)
                            {
                                counts[i] = reader.ReadInt32();
                            }
                            var p = new PartitioningParameters(counts);

                            int[][] _s = new int[Sizes.Length][];
                            for (int i = 0; i < Sizes.Length; i++)
                            {
                                var _si = new int[counts[i] - 1];
                                for (int j = 0; j < counts[i] - 1; j++)
                                {
                                    _si[j] = reader.ReadInt32();
                                }
                                _s[i] = _si;
                            }

                            var f = reader.ReadDouble();

                            var s = new Solution(_s);
                            solutionData = new SolutionData(p, s, f);
                            solution.Target = solutionData;
                        }
                    }
                    return solutionData;
                }
            }

            public string Name;

            public string Filename;

            [XmlElement(IsNullable = true)]
            public string SolutionFilename;

            public int[] Sizes;

            [XmlIgnore]
            private WeakReference matrix = new WeakReference(null);

            [XmlIgnore]
            private WeakReference solution = new WeakReference(null);
        }

        public Storage(string path = "")
        {
            Path = path;
        }

        private string _path;
        public string Path
        {
            set
            {
                if (Directory.Exists(value))
                {
                    _path = value;
                }
                else
                {
                    _path = Directory.GetCurrentDirectory();
                }
                if (!_path.EndsWith(@"\"))
                {
                    _path += @"\";
                }
            }
            get { return _path; }
        }

        IEnumerable<IMatrixData<int, EmptyData>> IMatrixReadStorage<int, EmptyData>.ReadMatrixes()
        {
            Directory.CreateDirectory(Path + @"data\");
            foreach (var filename in Directory.EnumerateFiles(Path + "data", "*.xml"))
            {
                using (var stream = File.OpenRead(filename))
                using (var textreader = new StreamReader(stream))
                using (var xml = new XmlTextReader(textreader))
                {
                    var serializer = new XmlSerializer(typeof(FileMatrixData));
                    var matrixData = serializer.Deserialize(xml) as FileMatrixData;

                    matrixData.BasePath = Path;

                    if (matrixData != null)
                    {
                        if (matrixData.SolutionFilename == null)
                        {
                            yield return matrixData.AsMatrixData();
                        }
                    }
                }
            }
        }

        IMatrixData<int, EmptyData> IMatrixWriteStorage<int, EmptyData>.SaveMatrix(string name, IMatrix<int> matrix, EmptyData data)
        {
            Directory.CreateDirectory(Path + @"data\matrixes\");
            string filename = "1";
            int currentFilename = 1;

            while (File.Exists(Path + @"data\" + filename + ".xml"))
            {
                currentFilename++;
                filename = currentFilename.ToString();
            }

            var sizes = new int[matrix.Dimensions];

            for (int i = 0; i < matrix.Dimensions; i++)
            {
                sizes[i] = matrix.Size(i);
            }

            var matrixData = new FileMatrixData(Path, name, @"data\matrixes\" + filename, sizes);


            using (var stream = File.OpenWrite(Path + @"data\" + filename + ".xml"))
            using (var textwriter = new StreamWriter(stream))
            using (var xml = new XmlTextWriter(textwriter))
            {
                var serializer = new XmlSerializer(typeof(FileMatrixData));
                serializer.Serialize(xml, matrixData);
            }

            using (var stream = File.OpenWrite(Path + @"data\matrixes\" + filename))
            using (var writer = new BinaryWriter(stream))
            {
                foreach (var index in MultiDimensionMatrixEnumerator.Indexes(matrix))
                {
                    writer.Write(matrix[index]);
                }
            }

            return matrixData.AsMatrixData();
        }

        IEnumerable<IMatrixData<int, SolutionData>> IMatrixReadStorage<int, SolutionData>.ReadMatrixes()
        {
            Directory.CreateDirectory(Path + @"data\");
            foreach (var filename in Directory.EnumerateFiles(Path + "data", "*.xml"))
            {
                using (var stream = File.OpenRead(filename))
                using (var textreader = new StreamReader(stream))
                using (var xml = new XmlTextReader(textreader))
                {
                    var serializer = new XmlSerializer(typeof(FileMatrixData));
                    var matrixData = serializer.Deserialize(xml) as FileMatrixData;

                    matrixData.BasePath = Path;

                    if (matrixData != null)
                    {
                        if (matrixData.SolutionFilename != null)
                        {
                            yield return matrixData.AsSolutionData();
                        }
                    }
                }
            }
        }

        IMatrixData<int, SolutionData> IMatrixWriteStorage<int, SolutionData>.SaveMatrix(string name, IMatrix<int> matrix, SolutionData data)
        {
            Directory.CreateDirectory(Path + @"data\matrixes\");
            Directory.CreateDirectory(Path + @"data\solutions\");
            string filename = "1";
            int currentFilename = 1;

            while (File.Exists(Path + @"data\" + filename + ".xml"))
            {
                currentFilename++;
                filename = currentFilename.ToString();
            }

            var sizes = new int[matrix.Dimensions];

            for (int i = 0; i < matrix.Dimensions; i++)
            {
                sizes[i] = matrix.Size(i);
            }

            var matrixData = new FileMatrixData(Path, name, @"data\matrixes\" + filename, sizes, @"data\solutions\" + filename);

            using (var stream = File.OpenWrite(Path + @"data\" + filename + ".xml"))
            using (var textwriter = new StreamWriter(stream))
            using (var xml = new XmlTextWriter(textwriter))
            {
                var serializer = new XmlSerializer(typeof(FileMatrixData));
                serializer.Serialize(xml, matrixData);
            }

            using (var stream = File.OpenWrite(Path + @"data\matrixes\" + filename))
            using (var writer = new BinaryWriter(stream))
            {
                foreach (var index in MultiDimensionMatrixEnumerator.Indexes(matrix))
                {
                    writer.Write(matrix[index]);
                }
            }

            using (var stream = File.OpenWrite(Path + @"data\solutions\" + filename))
            using (var writer = new BinaryWriter(stream))
            {
                for (int i = 0; i < data.Item1.Dimensions; i++)
                {
                    writer.Write(data.Item1[i]);
                }

                for (int i = 0; i < data.Item1.Dimensions; i++)
                {
                    foreach (int j in data.Item2[i])
                    {
                        writer.Write(j);
                    }
                }

                writer.Write(data.Item3);
            }

            return matrixData.AsSolutionData();
        }
    }
}
