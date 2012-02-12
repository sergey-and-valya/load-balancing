using System.Windows.Forms;

namespace RectanglesGenerator
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
        
        public int N
        {
            get { return (int)numCountColumns.Value; }
        }

        public int M
        {
            get { return (int)numCountRows.Value; }
        }

        public int MaxH
        {
            get { return (int)numMaxH.Value; }
        }

        public int MinH
        {
            get { return (int)numMinH.Value; }
        }

        public int RectsMin
        {
            get { return (int)numRectsMin.Value; }
        }

        public int RectsMax
        {
            get { return (int)numRectsMax.Value; }
        }
    }
}