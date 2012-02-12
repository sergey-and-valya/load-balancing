using System;
using System.Drawing;
using System.Windows.Forms;
using Core;

namespace Visualizer
{
    public partial class VisualizerForm : Form
    {
        protected struct color
        {
            public int green;
            public int blue;
        }

        protected struct zoom
        {
            public double width;
            public double height;
        }

        protected zoom zoomOfSize;
        protected IMatrix<int> matrix;
        protected color trackBarColor;

        protected enum Mode
        {
            SumInBlocks,
            Matrix
        }

        protected Bitmap matrixBitmap;
        protected Bitmap sumInBlocksBitmap;
        protected Mode modeOfDrawing;

        protected Bitmap currentBitmap
        {
            get { return (modeOfDrawing == Mode.Matrix) ? matrixBitmap : sumInBlocksBitmap; }
        }

        protected int shift;
        protected Size screenSize = new Size(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
        protected double coefficient;
        protected Size sizeOfMatrix;

        protected delegate void SetSettingsEvent();
        protected SetSettingsEvent settingsEvent;

        protected struct Bound
        {
            public int max;
            public int min;

            public Bound(int min, int max)
            {
                this.min = min;
                this.max = max;
            }
        }
        protected Bound boundOfValuesOfMatrix;
        protected Bound boundOfValuesOfBlocks;

        protected VisualizerForm()
        {
            InitializeComponent();
            InitParameters();
        }

        private void InitParameters()
        {
            shift = 20;
            trackBarColor = new color();
            boundOfValuesOfMatrix = new Bound();
            boundOfValuesOfBlocks = new Bound();
        }

        public void Draw()
        {
            SetSettings();
            settingsEvent();
            SetDrawingBoxBackgroundImage(matrixBitmap);
        }

        protected virtual void SetSettings()
        {
            settingsEvent = new SetSettingsEvent(SetSize);
            settingsEvent += new SetSettingsEvent(SetElementsLocation);
            settingsEvent += new SetSettingsEvent(SetLabelsLocation);
        }

        private void SetSize()
        {
            DrawingBox.Size = new Size((int)(zoomOfSize.width * sizeOfMatrix.Width), (int)(zoomOfSize.height * sizeOfMatrix.Height));
            this.ClientSize = new Size(DrawingBox.Size.Width + 7 * shift, DrawingBox.Size.Height + shift);
        }

        private void SetElementsLocation()
        {
            MinTrackBar.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + shift,
                    MinTrackBar.Location.Y);
            MaxTrackBar.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + shift,
                    MaxTrackBar.Location.Y);
            GreenTrackBar.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + shift,
                    GreenTrackBar.Location.Y);
            BlueTrackBar.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + shift,
                    BlueTrackBar.Location.Y);

            BlocksColorGroupBox.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + shift,
                    MinTrackBar.Location.Y);
        }

        private void SetLabelsLocation()
        {
            MinLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 3 * shift,
                    MinTrackBar.Location.Y - shift / 2);

            ValueMinLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 9 * shift / 2,
                    MinTrackBar.Location.Y - shift / 2);

            MaxLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 3 * shift,
                    MaxTrackBar.Location.Y - shift / 2);

            ValueMaxLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 9 * shift / 2,
                    MaxTrackBar.Location.Y - shift / 2);

            GreenLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 3 * shift,
                    GreenTrackBar.Location.Y - shift / 2);

            BlueLabel.Location =
                new Point(
                    DrawingBox.Location.X + DrawingBox.Size.Width + 3 * shift,
                    BlueTrackBar.Location.Y - shift / 2);
        }

        protected void SetDrawingBoxBackgroundImage(Bitmap bitmap)
        {
            DrawingBox.BackgroundImage = new Bitmap(bitmap);
        }

        protected void SetMinMax(int min, int max)
        {
            MinTrackBar.Minimum = min;
            MinTrackBar.Maximum = min + (max - min) / 2;

            MaxTrackBar.Minimum = min + (max - min) / 2 + 1;
            MaxTrackBar.Maximum = max;

            MinTrackBar.Value = min;
            MaxTrackBar.Value = max;

            ValueMinLabel.Text = min.ToString();
            ValueMaxLabel.Text = max.ToString();
        }

        protected void MinTrackBar_Scroll(object sender, EventArgs e)
        {
            this.ChangeBitmap();
            this.SetDrawingBoxBackgroundImage(currentBitmap);
            ValueMinLabel.Text = MinTrackBar.Value.ToString();
        }

        protected void MaxTrackBar_Scroll(object sender, EventArgs e)
        {
            this.ChangeBitmap();
            this.SetDrawingBoxBackgroundImage(currentBitmap);
            ValueMaxLabel.Text = MaxTrackBar.Value.ToString();
        }

        protected void GreenTrackBar_Scroll(object sender, EventArgs e)
        {
            trackBarColor.green = GreenTrackBar.Value;
            this.ChangeBitmap();
            this.SetDrawingBoxBackgroundImage(currentBitmap);
        }

        protected void BlueTrackBar_Scroll(object sender, EventArgs e)
        {
            trackBarColor.blue = BlueTrackBar.Value;
            this.ChangeBitmap();
            this.SetDrawingBoxBackgroundImage(currentBitmap);
        }

        protected virtual void ChangeBitmap()
        {
            this.SetBitmap();
        }

        protected void SetZoom()
        {
            var shift = 100.0;

            if (sizeOfMatrix.Width != sizeOfMatrix.Height)
            {
                if (sizeOfMatrix.Width > screenSize.Width - shift)
                    zoomOfSize.width = (double)(screenSize.Width) / (double)(sizeOfMatrix.Width) - 0.2;
                else
                    zoomOfSize.width = (double)screenSize.Width / (2 * (double)sizeOfMatrix.Width);

                if (sizeOfMatrix.Height > screenSize.Height - shift)
                    zoomOfSize.height = (double)(screenSize.Height) / (double)(sizeOfMatrix.Height) - 0.2;
                else
                    zoomOfSize.height = (double)screenSize.Height / (2 * (double)sizeOfMatrix.Height);
            }
            else
                zoomOfSize.height = zoomOfSize.width = (double)screenSize.Height / (double)sizeOfMatrix.Height - 0.2;
        }

        protected virtual void SetBitmap() { }

        protected virtual void ModeChangeButton_Click(object sender, System.EventArgs e)
        {
            bool modeIsMatrix = modeOfDrawing == Mode.Matrix;
            modeOfDrawing = modeIsMatrix ? Mode.SumInBlocks : Mode.Matrix;
            SetDrawingBoxBackgroundImage(currentBitmap);
            Bound tempBound = !modeIsMatrix ? boundOfValuesOfMatrix : boundOfValuesOfBlocks;
            SetTrackBarVisible();
            ModeChangeButton.Image = new Bitmap(
                !modeIsMatrix ? Visualizer.Properties.Resources.switchOff : Visualizer.Properties.Resources.switchOn);
        }

        private void SetTrackBarVisible()
        {
            bool isVisible = modeOfDrawing == Mode.Matrix;
            BlueTrackBar.Visible = isVisible;
            GreenTrackBar.Visible = isVisible;
            GreenLabel.Visible = isVisible;
            BlueLabel.Visible = isVisible;
            MaxTrackBar.Visible = isVisible;
            MaxLabel.Visible = isVisible;
            MinTrackBar.Visible = isVisible;
            MinLabel.Visible = isVisible;
            ValueMaxLabel.Visible = isVisible;
            ValueMinLabel.Visible = isVisible;
            BlocksColorGroupBox.Visible = !isVisible;
        }

        protected virtual void SetStep() { }
    }
}