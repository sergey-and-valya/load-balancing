namespace UniformGenerator
{
    partial class ParametersDialog
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
            this.numMin = new System.Windows.Forms.NumericUpDown();
            this.lblMin = new System.Windows.Forms.Label();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.numCount = new System.Windows.Forms.NumericUpDown();
            this.lblCount = new System.Windows.Forms.Label();
            this.numMax = new System.Windows.Forms.NumericUpDown();
            this.lblMax = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.numCountRows = new System.Windows.Forms.NumericUpDown();
            this.numCountColumns = new System.Windows.Forms.NumericUpDown();
            this.DrawingBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.numMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DrawingBox)).BeginInit();
            this.SuspendLayout();
            // 
            // numMin
            // 
            this.numMin.Location = new System.Drawing.Point(180, 7);
            this.numMin.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMin.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMin.Name = "numMin";
            this.numMin.Size = new System.Drawing.Size(120, 20);
            this.numMin.TabIndex = 0;
            this.numMin.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblMin
            // 
            this.lblMin.AutoSize = true;
            this.lblMin.Location = new System.Drawing.Point(3, 9);
            this.lblMin.Name = "lblMin";
            this.lblMin.Size = new System.Drawing.Size(20, 13);
            this.lblMin.TabIndex = 1;
            this.lblMin.Text = "От";
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(225, 165);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 3;
            this.btnOK.Text = "Ок";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(142, 165);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 4;
            this.btnCancel.Text = "Отмена";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // numCount
            // 
            this.numCount.Location = new System.Drawing.Point(180, 61);
            this.numCount.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numCount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numCount.Name = "numCount";
            this.numCount.Size = new System.Drawing.Size(120, 20);
            this.numCount.TabIndex = 2;
            this.numCount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblCount
            // 
            this.lblCount.AutoSize = true;
            this.lblCount.Location = new System.Drawing.Point(3, 61);
            this.lblCount.Name = "lblCount";
            this.lblCount.Size = new System.Drawing.Size(79, 13);
            this.lblCount.TabIndex = 1;
            this.lblCount.Text = "Число матриц";
            // 
            // numMax
            // 
            this.numMax.Location = new System.Drawing.Point(180, 33);
            this.numMax.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMax.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMax.Name = "numMax";
            this.numMax.Size = new System.Drawing.Size(120, 20);
            this.numMax.TabIndex = 1;
            this.numMax.Value = new decimal(new int[] {
            9,
            0,
            0,
            0});
            // 
            // lblMax
            // 
            this.lblMax.AutoSize = true;
            this.lblMax.Location = new System.Drawing.Point(3, 35);
            this.lblMax.Name = "lblMax";
            this.lblMax.Size = new System.Drawing.Size(22, 13);
            this.lblMax.TabIndex = 1;
            this.lblMax.Text = "До";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 89);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(126, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Размерность матрицы:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 112);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(98, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Количество строк";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 136);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(116, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Количество столбцов";
            // 
            // numCountRows
            // 
            this.numCountRows.Location = new System.Drawing.Point(180, 105);
            this.numCountRows.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numCountRows.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numCountRows.Name = "numCountRows";
            this.numCountRows.Size = new System.Drawing.Size(120, 20);
            this.numCountRows.TabIndex = 10;
            this.numCountRows.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // numCountColumns
            // 
            this.numCountColumns.Location = new System.Drawing.Point(180, 131);
            this.numCountColumns.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numCountColumns.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numCountColumns.Name = "numCountColumns";
            this.numCountColumns.Size = new System.Drawing.Size(120, 20);
            this.numCountColumns.TabIndex = 11;
            this.numCountColumns.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // DrawingBox
            // 
            this.DrawingBox.Location = new System.Drawing.Point(319, 12);
            this.DrawingBox.Name = "DrawingBox";
            this.DrawingBox.Size = new System.Drawing.Size(459, 399);
            this.DrawingBox.TabIndex = 6;
            this.DrawingBox.TabStop = false;
            // 
            // ParametersDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(304, 191);
            this.Controls.Add(this.numCountColumns);
            this.Controls.Add(this.numCountRows);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DrawingBox);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.lblCount);
            this.Controls.Add(this.lblMax);
            this.Controls.Add(this.lblMin);
            this.Controls.Add(this.numCount);
            this.Controls.Add(this.numMax);
            this.Controls.Add(this.numMin);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ParametersDialog";
            this.Text = "Параметры генератора";
            ((System.ComponentModel.ISupportInitialize)(this.numMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DrawingBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion Windows Form Designer generated code

        private System.Windows.Forms.NumericUpDown numMin;
        private System.Windows.Forms.Label lblMin;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.NumericUpDown numCount;
        private System.Windows.Forms.Label lblCount;
        private System.Windows.Forms.NumericUpDown numMax;
        private System.Windows.Forms.Label lblMax;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numCountRows;
        private System.Windows.Forms.NumericUpDown numCountColumns;
        private System.Windows.Forms.PictureBox DrawingBox;
    }
}