using System.Windows.Forms;

namespace TestSolutionGenerator
{
    public partial class ParametersDialog : Form
    {
        public ParametersDialog()
        {
            InitializeComponent();
        }

        public int Count
        {
            get { return (int)numCount.Value; }
        }

        public int Min
        {
            get { return (int)numMin.Value; }
        }

        public int Max
        {
            get { return (int)numMax.Value; }
        }

        public int M1
        {
            get { return (int)numM1.Value; }
        }

        public int M2
        {
            get { return (int)numM2.Value; }
        }

        public int CountRows
        {
            get { return (int)numCountRows.Value; }
        }

        public int CountColumns
        {
            get { return (int)numCountColumns.Value; }
        }
    }
}