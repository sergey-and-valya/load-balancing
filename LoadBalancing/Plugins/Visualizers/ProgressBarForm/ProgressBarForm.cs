using System.Windows.Forms;

namespace ProgressBarForm
{
    public partial class ProgressBarForm : Form
    {
        public ProgressBarForm()
        {
            InitializeComponent();
        }

        public void SetLoadProgressBarStepValue(int maxValue)
        {
            LoadProgressBar.Maximum = maxValue;
        }

        public void IncrementLoadValue()
        {
            LoadProgressBar.PerformStep();
        }
    }
}