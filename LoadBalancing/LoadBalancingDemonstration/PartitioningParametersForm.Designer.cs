namespace LoadBalancingDemonstration
{
    partial class PartitioningParametersForm
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
            System.Windows.Forms.Label lblM1;
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.lblM2 = new System.Windows.Forms.Label();
            this.numM2 = new System.Windows.Forms.NumericUpDown();
            this.numM1 = new System.Windows.Forms.NumericUpDown();
            lblM1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numM2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(94, 59);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 10;
            this.btnCancel.Text = "Отмена";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(177, 59);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 9;
            this.btnOK.Text = "Ок";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // lblM2
            // 
            this.lblM2.AutoSize = true;
            this.lblM2.Location = new System.Drawing.Point(12, 35);
            this.lblM2.Name = "lblM2";
            this.lblM2.Size = new System.Drawing.Size(22, 13);
            this.lblM2.TabIndex = 8;
            this.lblM2.Text = "M2";
            // 
            // lblM1
            // 
            lblM1.AutoSize = true;
            lblM1.Location = new System.Drawing.Point(12, 9);
            lblM1.Name = "lblM1";
            lblM1.Size = new System.Drawing.Size(22, 13);
            lblM1.TabIndex = 6;
            lblM1.Text = "M1";
            // 
            // numM2
            // 
            this.numM2.Location = new System.Drawing.Point(132, 33);
            this.numM2.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numM2.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numM2.Name = "numM2";
            this.numM2.Size = new System.Drawing.Size(120, 20);
            this.numM2.TabIndex = 7;
            this.numM2.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // numM1
            // 
            this.numM1.Location = new System.Drawing.Point(132, 7);
            this.numM1.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numM1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numM1.Name = "numM1";
            this.numM1.Size = new System.Drawing.Size(120, 20);
            this.numM1.TabIndex = 5;
            this.numM1.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            // 
            // PartitioningParametersForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(264, 94);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.lblM2);
            this.Controls.Add(lblM1);
            this.Controls.Add(this.numM2);
            this.Controls.Add(this.numM1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "PartitioningParametersForm";
            this.Text = "Параметры разбиения";
            ((System.ComponentModel.ISupportInitialize)(this.numM2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label lblM2;
        private System.Windows.Forms.NumericUpDown numM2;
        private System.Windows.Forms.NumericUpDown numM1;
    }
}