using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.Linq;
using System.Windows.Forms;
using AlgorithmPluginCore;
using Core;
using GeneratorPluginCore;
using LoadBalancing;
using MatrixStorage;
using VisualizerPluginCore;
using FileStorage;

namespace LoadBalancingDemonstration
{
    using SolutionData = Tuple<PartitioningParameters, ISolution, double>;

    public partial class MainForm : Form,
        IMatrixWriteStorage<int, EmptyData>,
        IMatrixWriteStorage<int, SolutionData>
    {
        [ImportMany(typeof(IGeneratorPlugin<int, EmptyData>))]
        private IEnumerable<IGeneratorPlugin<int, EmptyData>> Generators;

        [ImportMany(typeof(IGeneratorPlugin<int, Tuple<PartitioningParameters, ISolution, double>>))]
        private IEnumerable<IGeneratorPlugin<int, Tuple<PartitioningParameters, ISolution, double>>> SolutionGenerators;

        [ImportMany(typeof(IMatrixVisualizerPlugin<int>))]
        private IEnumerable<IMatrixVisualizerPlugin<int>> MatrixVisualizers;

        [ImportMany(typeof(ISolutionVisualizerPlugin<int, LoadBalancingProblem>))]
        private IEnumerable<ISolutionVisualizerPlugin<int, LoadBalancingProblem>> SolutionVisualizers;

        [ImportMany(typeof(IAlgorithmPlugin<int, LoadBalancingProblem>))]
        private IEnumerable<IAlgorithmPlugin<int, LoadBalancingProblem>> Algorithms;

        readonly IList<IMatrixData<int, EmptyData>> matrixes;
        readonly IList<IMatrixData<int, SolutionData>> solutionMatrixes;

        readonly Storage fileStorage;

        public MainForm()
        {
            InitializeComponent();

            AggregateCatalog catalog = new AggregateCatalog(
                new DirectoryCatalog("Plugins/Generators"),
                new DirectoryCatalog("Plugins/Visualizers"),
                new DirectoryCatalog("Plugins/Algorithms")
                );

            CompositionContainer container = new CompositionContainer(catalog);

            container.ComposeParts(this);

            foreach (var generator in Generators)
            {
                lstGenerators.Items.Add(generator.Name);
            }

            foreach (var generator in SolutionGenerators)
            {
                lstGenerators.Items.Add(generator.Name);
            }

            foreach (var matrixVisualizer in MatrixVisualizers)
            {
                lstMatrixVisualizers.Items.Add(matrixVisualizer.Name);
            }

            foreach (var solutionVisualizer in SolutionVisualizers)
            {
                lstSolutionVisualizers.Items.Add(solutionVisualizer.Name);
            }

            foreach (var algorithm in Algorithms)
            {
                lstAlgorithms.Items.Add(algorithm.Name);
            }

            matrixes = new List<IMatrixData<int, EmptyData>>();
            solutionMatrixes = new List<IMatrixData<int, SolutionData>>();
            fileStorage = new Storage();
            lstMatrixes.DisplayMember = "Name";

            UpdateStorage();

            if (lstGenerators.Items.Count > 0) lstGenerators.SelectedIndex = 0;
            if (lstMatrixes.Items.Count > 0) lstMatrixes.SelectedIndex = 0;
            if (lstMatrixVisualizers.Items.Count > 0) lstMatrixVisualizers.SelectedIndex = 0;
            if (lstSolutionVisualizers.Items.Count > 0) lstSolutionVisualizers.SelectedIndex = 0;
            if (lstAlgorithms.Items.Count > 0)
            {
                if (lstAlgorithms.Items.IndexOf("Полный перебор") == 0)
                    lstAlgorithms.SelectedIndex = 1;
                else
                    lstAlgorithms.SelectedIndex = 0;
            }
        }

        private void UpdateStorage()
        {
            lblPath.Text = fileStorage.Path;

            lstMatrixes.ClearSelected();
            lstMatrixes.Items.Clear();

            foreach (var pair in (fileStorage as IMatrixReadStorage<int, EmptyData>).ReadMatrixes())
            {
                lstMatrixes.Items.Add(pair);
                matrixes.Add(pair);
            }

            foreach (var pair in (fileStorage as IMatrixReadStorage<int, SolutionData>).ReadMatrixes())
            {
                lstMatrixes.Items.Add(pair);
                solutionMatrixes.Add(pair);
            }
        }

        #region SelectedIndexChanged functios

        private void lstGenerators_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckBtnGeneratorEnabled();
        }

        private void lstMatricesVisualizers_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckBtnMatrixVisualizerEnabled();
        }

        private void lstAlgorithms_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckBtnAlgorithmEnabled();
            CheckBtnTestEnabled();
        }

        private void lstMatrixes_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckBtnAlgorithmEnabled();
            CheckBtnMatrixVisualizerEnabled();
        }

        private void lstSolutionVisualizers_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckBtnAlgorithmEnabled();
        }

        #endregion SelectedIndexChanged functios

        #region CheckBtnEnabled functios

        private void CheckBtnGeneratorEnabled()
        {
            btnGenerator.Enabled = SelectedGeneratorPlugin != null || SelectedSolutionGeneratorPlugin != null;
        }

        private void CheckBtnMatrixVisualizerEnabled()
        {
            btnMatrixVisualizer.Enabled = SelectedMatrixVisualiserPlugin != null && (SelectedMatrixData != null || SelectedSolutionMatrixData != null);
        }

        private void CheckBtnAlgorithmEnabled()
        {
            btnAlgorithm.Enabled = SelectedAlgorithmPlugin != null && (SelectedMatrixData != null || SelectedSolutionMatrixData != null) && SelectedSolutionVisualiserPlugin != null;
        }

        private void CheckBtnTestEnabled()
        {
            btnTest.Enabled = SelectedAlgorithmPlugin != null && lstMatrixes.Items.Count > 0;
        }

        #endregion CheckBtnEnabled functios

        #region Private properties

        private IGeneratorPlugin<int, EmptyData> SelectedGeneratorPlugin
        {
            get
            {
                if (lstGenerators.SelectedIndex == -1)
                    return null;

                if (lstGenerators.SelectedIndex >= Generators.Count())
                    return null;

                return Generators.ElementAt(lstGenerators.SelectedIndex);
            }
        }

        private IGeneratorPlugin<int, SolutionData> SelectedSolutionGeneratorPlugin
        {
            get
            {
                if (lstGenerators.SelectedIndex == -1)
                    return null;

                if (lstGenerators.SelectedIndex < Generators.Count())
                    return null;

                return SolutionGenerators.ElementAt(lstGenerators.SelectedIndex - Generators.Count());
            }
        }

        private IAlgorithmPlugin<int, LoadBalancingProblem> SelectedAlgorithmPlugin
        {
            get
            {
                if (lstAlgorithms.SelectedIndex == -1)
                    return null;
                return Algorithms.ElementAt(lstAlgorithms.SelectedIndex);
            }
        }

        private IMatrixVisualizerPlugin<int> SelectedMatrixVisualiserPlugin
        {
            get
            {
                if (lstMatrixVisualizers.SelectedIndex == -1)
                    return null;
                return MatrixVisualizers.ElementAt(lstMatrixVisualizers.SelectedIndex);
            }
        }

        private ISolutionVisualizerPlugin<int, LoadBalancingProblem> SelectedSolutionVisualiserPlugin
        {
            get
            {
                if (lstSolutionVisualizers.SelectedIndex == -1)
                    return null;
                return SolutionVisualizers.ElementAt(lstSolutionVisualizers.SelectedIndex);
            }
        }

        private IMatrixData<int, EmptyData> SelectedMatrixData
        {
            get
            {
                if (lstMatrixes.SelectedIndex == -1)
                    return null;
                return lstMatrixes.SelectedItem as IMatrixData<int, EmptyData>;
            }
        }

        private IMatrixData<int, SolutionData> SelectedSolutionMatrixData
        {
            get
            {
                if (lstMatrixes.SelectedIndex == -1)
                    return null;
                return lstMatrixes.SelectedItem as IMatrixData<int, SolutionData>;
            }
        }

        private IMatrix<int> SelectedMatrix
        {
            get
            {
                if (SelectedMatrixData != null)
                    return SelectedMatrixData.Matrix;

                if (SelectedSolutionMatrixData != null)
                    return SelectedSolutionMatrixData.Matrix;

                return null;
            }
        }

        #endregion Private properties

        #region button_Click functions

        private void btnGenerator_Click(object sender, EventArgs e)
        {
            if (SelectedGeneratorPlugin != null)
            {
                var generatorPlugin = SelectedGeneratorPlugin;
                if (generatorPlugin.HasGenerator(2))
                {
                    var generator = generatorPlugin.CreateGenerator(2);
                    if (generator != null)
                    {
                        generator.GenerateMatrixes(this);
                        ListElementsSetSelected();
                    }
                }
            }
            else
                if (SelectedSolutionGeneratorPlugin != null)
                {
                    var generatorPlugin = SelectedSolutionGeneratorPlugin;
                    if (generatorPlugin.HasGenerator(2))
                    {
                        var generator = generatorPlugin.CreateGenerator(2);
                        if (generator != null)
                        {
                            generator.GenerateMatrixes(this);
                            ListElementsSetSelected();
                        }
                    }
                }
        }

        private void ListElementsSetSelected()
        {
            lstMatrixes.SetSelected(lstMatrixes.Items.Count - 1, true);
            lstAlgorithms.SelectedIndex = 0;
            lstSolutionVisualizers.SelectedIndex = 0;
            lstMatrixVisualizers.SelectedIndex = 0;
        }

        private void btnMatrixVisualizer_Click(object sender, EventArgs e)
        {
            var visualizerPlugin = SelectedMatrixVisualiserPlugin;
            if (visualizerPlugin.HasMatrixVisualizer(2))
            {
                var matrixVisualizer = visualizerPlugin.CreateMatrixVisualizer(2);
                matrixVisualizer.VisualizeMatrix(SelectedMatrix);
            }
        }

        private void btnAlgorithm_Click(object sender, EventArgs e)
        {
            try
            {
                var algorithmPlugin = SelectedAlgorithmPlugin;
                if (algorithmPlugin.HasAlgorithm(2))
                {
                    var algorithm = algorithmPlugin.CreateAlgorithm(2);
                    var solutionVisualiserPlugin = SelectedSolutionVisualiserPlugin;
                    LoadBalancingProblem problem = null;

                    if (SelectedSolutionMatrixData != null)
                        problem = new LoadBalancingProblem(SelectedMatrix, SelectedSolutionMatrixData.Data.Item1);
                    else if (SelectedMatrixData != null)
                    {
                        var f = new PartitioningParametersForm();
                        if (f.ShowDialog() != DialogResult.OK)
                            return;
                        problem = new LoadBalancingProblem(SelectedMatrix, new PartitioningParameters(f.M1, f.M2));
                    }
                    var solution = algorithm.Run(problem);

                    if (solutionVisualiserPlugin.HasSolutionVisualizer(2))
                    {
                        var solutionVisualiser = solutionVisualiserPlugin.CreateSolutionVisualizer(2);
                        solutionVisualiser.VisualizeSolution(problem, solution);
                    }
                }
            }
            catch { }
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            try
            {
                var algorithmPlugin = SelectedAlgorithmPlugin;
                if (algorithmPlugin.HasAlgorithm(2))
                {
                    var algorithm = algorithmPlugin.CreateAlgorithm(2);

                    var f = new PartitioningParametersForm();
                    if (f.ShowDialog() != DialogResult.OK)
                        return;
                    var partitioningParameters = new PartitioningParameters(f.M1, f.M2);
                    Test_result tr = new Test_result(fileStorage, fileStorage, algorithm, partitioningParameters);
                    tr.ShowDialog();
                }
            }
            catch { }
        }

        #endregion button_Click functions

        IMatrixData<int, EmptyData> IMatrixWriteStorage<int, EmptyData>.SaveMatrix(string name, IMatrix<int> matrix, EmptyData data)
        {
            var matrixData = (fileStorage as IMatrixWriteStorage<int, EmptyData>).SaveMatrix(name, matrix, data);
            lstMatrixes.Items.Add(matrixData);

            CheckBtnTestEnabled();

            return matrixData;
        }

        IMatrixData<int, SolutionData> IMatrixWriteStorage<int, SolutionData>.SaveMatrix(string name, IMatrix<int> matrix, SolutionData data)
        {
            var solutionMatrixData = (fileStorage as IMatrixWriteStorage<int, SolutionData>).SaveMatrix(name, matrix, data);
            lstMatrixes.Items.Add(solutionMatrixData);

            CheckBtnTestEnabled();

            return solutionMatrixData;
        }

        private void btnPath_Click(object sender, EventArgs e)
        {
            if (dlgMatrixPath.ShowDialog() == DialogResult.OK)
            {
                fileStorage.Path = dlgMatrixPath.SelectedPath;
                UpdateStorage();
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }
    }
}