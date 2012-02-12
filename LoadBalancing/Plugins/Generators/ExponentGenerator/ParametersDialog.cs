using System.Windows.Forms;

namespace ExponentGenerator
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

        public double MaxW
        {
            get { return double.Parse(txtMaxW.Text); }
        }

        public double MinW
        {
            get { return double.Parse(txtMinW.Text); }
        }

        public double MaxH
        {
            get { return double.Parse(txtMaxH.Text); }
        }

        public double MinH
        {
            get { return double.Parse(txtMinH.Text); }
        }

        public int MountainsMin
        {
            get { return (int)numMountainsMin.Value; }
        }

        public int MountainsMax
        {
            get { return (int)numMountainsMax.Value; }
        }
    }
}