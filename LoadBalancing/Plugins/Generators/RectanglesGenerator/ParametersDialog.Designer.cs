namespace RectanglesGenerator
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
            this.numCountColumns = new System.Windows.Forms.NumericUpDown();
            this.numCountRows = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.lblCount = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.numCount = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.numRectsMax = new System.Windows.Forms.NumericUpDown();
            this.numRectsMin = new System.Windows.Forms.NumericUpDown();
            this.numMaxH = new System.Windows.Forms.NumericUpDown();
            this.numMinH = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRectsMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRectsMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMaxH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMinH)).BeginInit();
            this.SuspendLayout();
            // 
            // numCountColumns
            // 
            this.numCountColumns.Location = new System.Drawing.Point(175, 83);
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
            this.numCountColumns.TabIndex = 35;
            this.numCountColumns.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // numCountRows
            // 
            this.numCountRows.Location = new System.Drawing.Point(175, 57);
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
            this.numCountRows.TabIndex = 34;
            this.numCountRows.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 112);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(48, 13);
            this.label10.TabIndex = 31;
            this.label10.Text = "Высота:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 84);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(116, 13);
            this.label3.TabIndex = 32;
            this.label3.Text = "Количество столбцов";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(98, 13);
            this.label2.TabIndex = 29;
            this.label2.Text = "Количество строк";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(126, 13);
            this.label1.TabIndex = 28;
            this.label1.Text = "Размерность матрицы:";
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(144, 277);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 27;
            this.btnCancel.Text = "Отмена";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(227, 277);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 26;
            this.btnOK.Text = "Ок";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 162);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(22, 13);
            this.label9.TabIndex = 24;
            this.label9.Text = "До";
            // 
            // lblCount
            // 
            this.lblCount.AutoSize = true;
            this.lblCount.Location = new System.Drawing.Point(12, 9);
            this.lblCount.Name = "lblCount";
            this.lblCount.Size = new System.Drawing.Size(79, 13);
            this.lblCount.TabIndex = 23;
            this.lblCount.Text = "Число матриц";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 137);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(20, 13);
            this.label8.TabIndex = 18;
            this.label8.Text = "От";
            // 
            // numCount
            // 
            this.numCount.Location = new System.Drawing.Point(175, 7);
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
            this.numCount.TabIndex = 25;
            this.numCount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 210);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(20, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "От";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 235);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(22, 13);
            this.label6.TabIndex = 24;
            this.label6.Text = "До";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 185);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(135, 13);
            this.label7.TabIndex = 31;
            this.label7.Text = "Число прямоугольников:";
            // 
            // numRectsMax
            // 
            this.numRectsMax.Location = new System.Drawing.Point(175, 234);
            this.numRectsMax.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numRectsMax.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numRectsMax.Name = "numRectsMax";
            this.numRectsMax.Size = new System.Drawing.Size(120, 20);
            this.numRectsMax.TabIndex = 38;
            this.numRectsMax.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // numRectsMin
            // 
            this.numRectsMin.Location = new System.Drawing.Point(175, 208);
            this.numRectsMin.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numRectsMin.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numRectsMin.Name = "numRectsMin";
            this.numRectsMin.Size = new System.Drawing.Size(120, 20);
            this.numRectsMin.TabIndex = 37;
            this.numRectsMin.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // numMaxH
            // 
            this.numMaxH.Location = new System.Drawing.Point(175, 160);
            this.numMaxH.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMaxH.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMaxH.Name = "numMaxH";
            this.numMaxH.Size = new System.Drawing.Size(120, 20);
            this.numMaxH.TabIndex = 40;
            this.numMaxH.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // numMinH
            // 
            this.numMinH.Location = new System.Drawing.Point(175, 134);
            this.numMinH.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMinH.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMinH.Name = "numMinH";
            this.numMinH.Size = new System.Drawing.Size(120, 20);
            this.numMinH.TabIndex = 39;
            this.numMinH.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // ParametersDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(307, 308);
            this.Controls.Add(this.numMaxH);
            this.Controls.Add(this.numMinH);
            this.Controls.Add(this.numRectsMax);
            this.Controls.Add(this.numRectsMin);
            this.Controls.Add(this.numCountColumns);
            this.Controls.Add(this.numCountRows);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lblCount);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.numCount);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ParametersDialog";
            this.Text = "Параметры генератора";
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRectsMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRectsMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMaxH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMinH)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion Windows Form Designer generated code

        private System.Windows.Forms.NumericUpDown numCountColumns;
        private System.Windows.Forms.NumericUpDown numCountRows;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblCount;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown numCount;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown numRectsMax;
        private System.Windows.Forms.NumericUpDown numRectsMin;
        private System.Windows.Forms.NumericUpDown numMaxH;
        private System.Windows.Forms.NumericUpDown numMinH;

    }
}