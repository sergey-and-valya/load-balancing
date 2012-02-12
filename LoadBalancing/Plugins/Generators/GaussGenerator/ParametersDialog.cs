using System.Windows.Forms;

namespace GaussGenerator
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
        
        public int M1
        {
            get { return (int)numM1.Value; }
        }

        public int M2
        {
            get { return (int)numM2.Value; }
        }

        public int MaxW
        {
            get { return (int)numMaxW.Value; }
        }

        public int MinW
        {
            get { return (int)numMinW.Value; }
        }

        public double MaxH
        {
            get { return double.Parse(txtMaxH.Text); }
        }

        public double MinH
        {
            get { return double.Parse(txtMinH.Text); }
        }
    }
}