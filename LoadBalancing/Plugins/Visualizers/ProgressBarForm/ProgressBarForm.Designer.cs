namespace ProgressBarForm
{
    partial class ProgressBarForm
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
        private void InitializeComponent()
        {
            this.LoadProgressBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            //
            // LoadProgressBar
            //
            this.LoadProgressBar.Location = new System.Drawing.Point(12, 12);
            this.LoadProgressBar.Name = "LoadProgressBar";
            this.LoadProgressBar.Size = new System.Drawing.Size(188, 23);
            this.LoadProgressBar.Step = 1;
            this.LoadProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.LoadProgressBar.TabIndex = 0;
            //
            // ProgressBarForm
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(212, 46);
            this.ControlBox = false;
            this.Controls.Add(this.LoadProgressBar);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ProgressBarForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "                          Progress";
            this.ResumeLayout(false);
        }

        #endregion Windows Form Designer generated code

        private System.Windows.Forms.ProgressBar LoadProgressBar;
    }
}