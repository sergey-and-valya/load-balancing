namespace GaussGenerator
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
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.lblCount = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.lblMax = new System.Windows.Forms.Label();
            this.lblMin = new System.Windows.Forms.Label();
            this.numCount = new System.Windows.Forms.NumericUpDown();
            this.numMaxW = new System.Windows.Forms.NumericUpDown();
            this.numMinW = new System.Windows.Forms.NumericUpDown();
            this.numM1 = new System.Windows.Forms.NumericUpDown();
            this.numM2 = new System.Windows.Forms.NumericUpDown();
            this.label12 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.txtMinH = new System.Windows.Forms.TextBox();
            this.txtMaxH = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMaxW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMinW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM2)).BeginInit();
            this.SuspendLayout();
            // 
            // numCountColumns
            // 
            this.numCountColumns.Location = new System.Drawing.Point(175, 60);
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
            this.numCountRows.Location = new System.Drawing.Point(175, 34);
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
            this.label10.Location = new System.Drawing.Point(12, 259);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(48, 13);
            this.label10.TabIndex = 31;
            this.label10.Text = "Высота:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 109);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(102, 13);
            this.label4.TabIndex = 33;
            this.label4.Text = "Средняя загрузка:";
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
            this.btnCancel.Location = new System.Drawing.Point(144, 349);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 27;
            this.btnCancel.Text = "Отмена";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(227, 349);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 26;
            this.btnOK.Text = "Ок";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 309);
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
            this.label8.Location = new System.Drawing.Point(12, 284);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(20, 13);
            this.label8.TabIndex = 18;
            this.label8.Text = "От";
            // 
            // lblMax
            // 
            this.lblMax.AutoSize = true;
            this.lblMax.Location = new System.Drawing.Point(12, 159);
            this.lblMax.Name = "lblMax";
            this.lblMax.Size = new System.Drawing.Size(22, 13);
            this.lblMax.TabIndex = 16;
            this.lblMax.Text = "До";
            // 
            // lblMin
            // 
            this.lblMin.AutoSize = true;
            this.lblMin.Location = new System.Drawing.Point(12, 134);
            this.lblMin.Name = "lblMin";
            this.lblMin.Size = new System.Drawing.Size(20, 13);
            this.lblMin.TabIndex = 21;
            this.lblMin.Text = "От";
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
            // numMaxW
            // 
            this.numMaxW.Location = new System.Drawing.Point(175, 157);
            this.numMaxW.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMaxW.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMaxW.Name = "numMaxW";
            this.numMaxW.Size = new System.Drawing.Size(120, 20);
            this.numMaxW.TabIndex = 20;
            this.numMaxW.Value = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            // 
            // numMinW
            // 
            this.numMinW.Location = new System.Drawing.Point(175, 132);
            this.numMinW.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numMinW.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMinW.Name = "numMinW";
            this.numMinW.Size = new System.Drawing.Size(120, 20);
            this.numMinW.TabIndex = 14;
            this.numMinW.Value = new decimal(new int[] {
            8000,
            0,
            0,
            0});
            // 
            // numM1
            // 
            this.numM1.Location = new System.Drawing.Point(175, 207);
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
            this.numM1.TabIndex = 13;
            this.numM1.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            // 
            // numM2
            // 
            this.numM2.Location = new System.Drawing.Point(175, 232);
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
            this.numM2.TabIndex = 22;
            this.numM2.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 209);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(22, 13);
            this.label12.TabIndex = 18;
            this.label12.Text = "M1";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(12, 234);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(22, 13);
            this.label14.TabIndex = 24;
            this.label14.Text = "M2";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(12, 184);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(65, 13);
            this.label16.TabIndex = 31;
            this.label16.Text = "Разбиение:";
            // 
            // txtMinH
            // 
            this.txtMinH.Location = new System.Drawing.Point(175, 281);
            this.txtMinH.Name = "txtMinH";
            this.txtMinH.Size = new System.Drawing.Size(120, 20);
            this.txtMinH.TabIndex = 36;
            this.txtMinH.Text = "0,0001";
            // 
            // txtMaxH
            // 
            this.txtMaxH.Location = new System.Drawing.Point(175, 306);
            this.txtMaxH.Name = "txtMaxH";
            this.txtMaxH.Size = new System.Drawing.Size(120, 20);
            this.txtMaxH.TabIndex = 36;
            this.txtMaxH.Text = "1";
            // 
            // ParametersDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(307, 378);
            this.Controls.Add(this.txtMaxH);
            this.Controls.Add(this.txtMinH);
            this.Controls.Add(this.numCountColumns);
            this.Controls.Add(this.numCountRows);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.lblCount);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.lblMax);
            this.Controls.Add(this.lblMin);
            this.Controls.Add(this.numM2);
            this.Controls.Add(this.numCount);
            this.Controls.Add(this.numM1);
            this.Controls.Add(this.numMaxW);
            this.Controls.Add(this.numMinW);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ParametersDialog";
            this.Text = "Параметры генератора";
            ((System.ComponentModel.ISupportInitialize)(this.numCountColumns)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCountRows)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMaxW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMinW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numM2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion Windows Form Designer generated code

        private System.Windows.Forms.NumericUpDown numCountColumns;
        private System.Windows.Forms.NumericUpDown numCountRows;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblCount;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lblMax;
        private System.Windows.Forms.Label lblMin;
        private System.Windows.Forms.NumericUpDown numCount;
        private System.Windows.Forms.NumericUpDown numMaxW;
        private System.Windows.Forms.NumericUpDown numMinW;
        private System.Windows.Forms.NumericUpDown numM1;
        private System.Windows.Forms.NumericUpDown numM2;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox txtMinH;
        private System.Windows.Forms.TextBox txtMaxH;

    }
}