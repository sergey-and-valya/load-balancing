namespace Visualizer
{
    partial class VisualizerForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        protected void InitializeComponent()
        {
            this.CriterionValueLabel = new System.Windows.Forms.Label();
            this.CriterionLabel = new System.Windows.Forms.Label();
            this.GreenTrackBar = new System.Windows.Forms.TrackBar();
            this.BlueTrackBar = new System.Windows.Forms.TrackBar();
            this.MaxTrackBar = new System.Windows.Forms.TrackBar();
            this.MinTrackBar = new System.Windows.Forms.TrackBar();
            this.MinLabel = new System.Windows.Forms.Label();
            this.MaxLabel = new System.Windows.Forms.Label();
            this.BlueLabel = new System.Windows.Forms.Label();
            this.GreenLabel = new System.Windows.Forms.Label();
            this.ModeChangeButton = new System.Windows.Forms.Button();
            this.DrawingBox = new System.Windows.Forms.PictureBox();
            this.ValueMinLabel = new System.Windows.Forms.Label();
            this.ValueMaxLabel = new System.Windows.Forms.Label();
            this.BlocksColorGroupBox = new System.Windows.Forms.GroupBox();
            this.BlocksMinLabel = new System.Windows.Forms.Label();
            this.BlocksMaxLabel = new System.Windows.Forms.Label();
            this.GreenBlockPanel = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.BlockMidLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.GreenTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BlueTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MaxTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MinTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DrawingBox)).BeginInit();
            this.BlocksColorGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // CriterionValueLabel
            // 
            this.CriterionValueLabel.AutoSize = true;
            this.CriterionValueLabel.Location = new System.Drawing.Point(194, 133);
            this.CriterionValueLabel.Name = "CriterionValueLabel";
            this.CriterionValueLabel.Size = new System.Drawing.Size(35, 13);
            this.CriterionValueLabel.TabIndex = 27;
            this.CriterionValueLabel.Text = "label1";
            // 
            // CriterionLabel
            // 
            this.CriterionLabel.AutoSize = true;
            this.CriterionLabel.Location = new System.Drawing.Point(194, 120);
            this.CriterionLabel.Name = "CriterionLabel";
            this.CriterionLabel.Size = new System.Drawing.Size(58, 13);
            this.CriterionLabel.TabIndex = 26;
            this.CriterionLabel.Text = "Критерий:";
            // 
            // GreenTrackBar
            // 
            this.GreenTrackBar.Location = new System.Drawing.Point(290, 118);
            this.GreenTrackBar.Maximum = 255;
            this.GreenTrackBar.Name = "GreenTrackBar";
            this.GreenTrackBar.Size = new System.Drawing.Size(104, 45);
            this.GreenTrackBar.TabIndex = 15;
            this.GreenTrackBar.Scroll += new System.EventHandler(this.GreenTrackBar_Scroll);
            // 
            // BlueTrackBar
            // 
            this.BlueTrackBar.Location = new System.Drawing.Point(290, 169);
            this.BlueTrackBar.Maximum = 255;
            this.BlueTrackBar.Name = "BlueTrackBar";
            this.BlueTrackBar.Size = new System.Drawing.Size(104, 45);
            this.BlueTrackBar.TabIndex = 16;
            this.BlueTrackBar.Scroll += new System.EventHandler(this.BlueTrackBar_Scroll);
            // 
            // MaxTrackBar
            // 
            this.MaxTrackBar.Location = new System.Drawing.Point(290, 68);
            this.MaxTrackBar.Maximum = 255;
            this.MaxTrackBar.Minimum = 155;
            this.MaxTrackBar.Name = "MaxTrackBar";
            this.MaxTrackBar.Size = new System.Drawing.Size(104, 45);
            this.MaxTrackBar.TabIndex = 17;
            this.MaxTrackBar.Value = 255;
            this.MaxTrackBar.Scroll += new System.EventHandler(this.MaxTrackBar_Scroll);
            // 
            // MinTrackBar
            // 
            this.MinTrackBar.Location = new System.Drawing.Point(290, 17);
            this.MinTrackBar.Maximum = 255;
            this.MinTrackBar.Minimum = 155;
            this.MinTrackBar.Name = "MinTrackBar";
            this.MinTrackBar.Size = new System.Drawing.Size(104, 45);
            this.MinTrackBar.TabIndex = 18;
            this.MinTrackBar.Value = 155;
            this.MinTrackBar.Scroll += new System.EventHandler(this.MinTrackBar_Scroll);
            // 
            // MinLabel
            // 
            this.MinLabel.AutoSize = true;
            this.MinLabel.BackColor = System.Drawing.Color.Transparent;
            this.MinLabel.Location = new System.Drawing.Point(319, 9);
            this.MinLabel.Name = "MinLabel";
            this.MinLabel.Size = new System.Drawing.Size(27, 13);
            this.MinLabel.TabIndex = 19;
            this.MinLabel.Text = "Min:";
            // 
            // MaxLabel
            // 
            this.MaxLabel.AutoSize = true;
            this.MaxLabel.BackColor = System.Drawing.Color.Transparent;
            this.MaxLabel.Location = new System.Drawing.Point(316, 52);
            this.MaxLabel.Name = "MaxLabel";
            this.MaxLabel.Size = new System.Drawing.Size(30, 13);
            this.MaxLabel.TabIndex = 20;
            this.MaxLabel.Text = "Max:";
            // 
            // BlueLabel
            // 
            this.BlueLabel.AutoSize = true;
            this.BlueLabel.BackColor = System.Drawing.Color.Transparent;
            this.BlueLabel.Location = new System.Drawing.Point(315, 153);
            this.BlueLabel.Name = "BlueLabel";
            this.BlueLabel.Size = new System.Drawing.Size(31, 13);
            this.BlueLabel.TabIndex = 22;
            this.BlueLabel.Text = "Blue:";
            // 
            // GreenLabel
            // 
            this.GreenLabel.AutoSize = true;
            this.GreenLabel.BackColor = System.Drawing.Color.Transparent;
            this.GreenLabel.Location = new System.Drawing.Point(316, 102);
            this.GreenLabel.Name = "GreenLabel";
            this.GreenLabel.Size = new System.Drawing.Size(39, 13);
            this.GreenLabel.TabIndex = 23;
            this.GreenLabel.Text = "Green:";
            // 
            // ModeChangeButton
            // 
            this.ModeChangeButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ModeChangeButton.Image = global::Visualizer.Properties.Resources.switchOff;
            this.ModeChangeButton.Location = new System.Drawing.Point(226, 181);
            this.ModeChangeButton.Name = "ModeChangeButton";
            this.ModeChangeButton.Size = new System.Drawing.Size(32, 32);
            this.ModeChangeButton.TabIndex = 30;
            this.ModeChangeButton.UseVisualStyleBackColor = true;
            this.ModeChangeButton.Visible = false;
            this.ModeChangeButton.Click += new System.EventHandler(this.ModeChangeButton_Click);
            // 
            // DrawingBox
            // 
            this.DrawingBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.DrawingBox.Location = new System.Drawing.Point(12, 12);
            this.DrawingBox.Name = "DrawingBox";
            this.DrawingBox.Size = new System.Drawing.Size(260, 238);
            this.DrawingBox.TabIndex = 13;
            this.DrawingBox.TabStop = false;
            // 
            // ValueMinLabel
            // 
            this.ValueMinLabel.AutoSize = true;
            this.ValueMinLabel.BackColor = System.Drawing.Color.Transparent;
            this.ValueMinLabel.Location = new System.Drawing.Point(342, 9);
            this.ValueMinLabel.Name = "ValueMinLabel";
            this.ValueMinLabel.Size = new System.Drawing.Size(0, 13);
            this.ValueMinLabel.TabIndex = 31;
            // 
            // ValueMaxLabel
            // 
            this.ValueMaxLabel.AutoSize = true;
            this.ValueMaxLabel.BackColor = System.Drawing.Color.Transparent;
            this.ValueMaxLabel.Location = new System.Drawing.Point(346, 52);
            this.ValueMaxLabel.Name = "ValueMaxLabel";
            this.ValueMaxLabel.Size = new System.Drawing.Size(0, 13);
            this.ValueMaxLabel.TabIndex = 32;
            // 
            // BlocksColorGroupBox
            // 
            this.BlocksColorGroupBox.Controls.Add(this.panel1);
            this.BlocksColorGroupBox.Controls.Add(this.BlockMidLabel);
            this.BlocksColorGroupBox.Controls.Add(this.panel2);
            this.BlocksColorGroupBox.Controls.Add(this.GreenBlockPanel);
            this.BlocksColorGroupBox.Controls.Add(this.BlocksMaxLabel);
            this.BlocksColorGroupBox.Controls.Add(this.BlocksMinLabel);
            this.BlocksColorGroupBox.Location = new System.Drawing.Point(301, 208);
            this.BlocksColorGroupBox.Name = "BlocksColorGroupBox";
            this.BlocksColorGroupBox.Size = new System.Drawing.Size(71, 94);
            this.BlocksColorGroupBox.TabIndex = 33;
            this.BlocksColorGroupBox.TabStop = false;
            this.BlocksColorGroupBox.Text = "Blocks";
            this.BlocksColorGroupBox.Visible = false;
            // 
            // BlocksMinLabel
            // 
            this.BlocksMinLabel.AutoSize = true;
            this.BlocksMinLabel.Location = new System.Drawing.Point(34, 23);
            this.BlocksMinLabel.Name = "BlocksMinLabel";
            this.BlocksMinLabel.Size = new System.Drawing.Size(24, 13);
            this.BlocksMinLabel.TabIndex = 0;
            this.BlocksMinLabel.Text = "Min";
            // 
            // BlocksMaxLabel
            // 
            this.BlocksMaxLabel.AutoSize = true;
            this.BlocksMaxLabel.Location = new System.Drawing.Point(34, 45);
            this.BlocksMaxLabel.Name = "BlocksMaxLabel";
            this.BlocksMaxLabel.Size = new System.Drawing.Size(27, 13);
            this.BlocksMaxLabel.TabIndex = 1;
            this.BlocksMaxLabel.Text = "Max";
            // 
            // GreenBlockPanel
            // 
            this.GreenBlockPanel.BackColor = System.Drawing.Color.Lime;
            this.GreenBlockPanel.Location = new System.Drawing.Point(8, 19);
            this.GreenBlockPanel.Name = "GreenBlockPanel";
            this.GreenBlockPanel.Size = new System.Drawing.Size(20, 20);
            this.GreenBlockPanel.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Red;
            this.panel2.Location = new System.Drawing.Point(8, 41);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(20, 20);
            this.panel2.TabIndex = 3;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Blue;
            this.panel1.Location = new System.Drawing.Point(8, 63);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(20, 20);
            this.panel1.TabIndex = 5;
            // 
            // BlockMidLabel
            // 
            this.BlockMidLabel.AutoSize = true;
            this.BlockMidLabel.Location = new System.Drawing.Point(34, 67);
            this.BlockMidLabel.Name = "BlockMidLabel";
            this.BlockMidLabel.Size = new System.Drawing.Size(24, 13);
            this.BlockMidLabel.TabIndex = 4;
            this.BlockMidLabel.Text = "Mid";
            // 
            // VisualizerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(483, 346);
            this.Controls.Add(this.BlocksColorGroupBox);
            this.Controls.Add(this.ValueMaxLabel);
            this.Controls.Add(this.ValueMinLabel);
            this.Controls.Add(this.ModeChangeButton);
            this.Controls.Add(this.CriterionValueLabel);
            this.Controls.Add(this.CriterionLabel);
            this.Controls.Add(this.GreenLabel);
            this.Controls.Add(this.BlueLabel);
            this.Controls.Add(this.MaxLabel);
            this.Controls.Add(this.MinLabel);
            this.Controls.Add(this.MinTrackBar);
            this.Controls.Add(this.MaxTrackBar);
            this.Controls.Add(this.BlueTrackBar);
            this.Controls.Add(this.GreenTrackBar);
            this.Controls.Add(this.DrawingBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "VisualizerForm";
            this.Text = "VisualizerForm";
            ((System.ComponentModel.ISupportInitialize)(this.GreenTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BlueTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MaxTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MinTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DrawingBox)).EndInit();
            this.BlocksColorGroupBox.ResumeLayout(false);
            this.BlocksColorGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion Windows Form Designer generated code

        protected System.Windows.Forms.PictureBox DrawingBox;
        protected System.Windows.Forms.Label CriterionValueLabel;
        protected System.Windows.Forms.Label CriterionLabel;
        protected System.Windows.Forms.Button ModeChangeButton;
        protected System.Windows.Forms.TrackBar GreenTrackBar;
        protected System.Windows.Forms.TrackBar BlueTrackBar;
        protected System.Windows.Forms.TrackBar MaxTrackBar;
        protected System.Windows.Forms.TrackBar MinTrackBar;
        protected System.Windows.Forms.Label MinLabel;
        protected System.Windows.Forms.Label MaxLabel;
        protected System.Windows.Forms.Label BlueLabel;
        protected System.Windows.Forms.Label GreenLabel;
        private System.Windows.Forms.Label ValueMinLabel;
        private System.Windows.Forms.Label ValueMaxLabel;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel GreenBlockPanel;
        private System.Windows.Forms.Label BlocksMaxLabel;
        private System.Windows.Forms.Label BlocksMinLabel;
        protected System.Windows.Forms.GroupBox BlocksColorGroupBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label BlockMidLabel;
    }
}