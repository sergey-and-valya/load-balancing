using System.ComponentModel.Composition;
using GeneratorPluginCore;
using MatrixStorage;
using Core;
using System;
using LoadBalancing;
using System.Windows.Forms;

namespace TestSolutionGenerator
{
    [Export(typeof(IGeneratorPlugin<int, Tuple<PartitioningParameters, ISolution, double>>))]
    public class TestSolutionGeneratorPlugin : IGeneratorPlugin<int, Tuple<PartitioningParameters, ISolution, double>>
    {
        public string Name
        {
            get { return "Генератор с решением"; }
        }

        public bool HasGenerator(int dimensions)
        {
            if (dimensions != 2)
                return false;

            return true;
        }

        public IGenerator<int, Tuple<PartitioningParameters, ISolution, double>> CreateGenerator(int dimensions)
        {
            if (dimensions != 2)
                return null;
            
            ParametersDialog dialog = new ParametersDialog();

            if (dialog.ShowDialog() != DialogResult.OK)
                return null;

            if (dialog.M1 >= dialog.CountRows)
            {
                MessageBox.Show("Заданы недопустимые параметры генерации!");
                return null;
            }

            if (dialog.M2 >= dialog.CountColumns)
            {
                MessageBox.Show("Заданы недопустимые параметры генерации!");
                return null;
            }

            return new Generator(dialog.Count, dialog.M1, dialog.M2, dialog.CountColumns, dialog.CountRows, dialog.Min, dialog.Max);
        }
    }
}
