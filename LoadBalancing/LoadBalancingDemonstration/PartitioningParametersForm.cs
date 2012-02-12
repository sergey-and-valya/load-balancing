using System.Windows.Forms;

namespace LoadBalancingDemonstration
{
    public partial class PartitioningParametersForm : Form
    {
        public PartitioningParametersForm()
        {
            InitializeComponent();
        }

        public int M1
        {
            get { return (int)numM1.Value; }
        }

        public int M2
        {
            get { return (int)numM2.Value; }
        }
    }
}
