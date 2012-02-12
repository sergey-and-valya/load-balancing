using System.Windows.Forms;

namespace UniformGenerator
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