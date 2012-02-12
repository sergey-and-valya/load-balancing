namespace LoadBalancingDemonstration
{
    partial class Test_result
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            this.panel1 = new System.Windows.Forms.Panel();
            this.UserResults = new System.Windows.Forms.DataGridView();
            this.matr_name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Matr_height = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Matr_width = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.M1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.M2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.criter = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Low_bound_disp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Good_solution_disp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.time = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GroupedResults = new System.Windows.Forms.DataGridView();
            this.count = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn6 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn7 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn9 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.btnGrouped = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UserResults)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroupedResults)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.UserResults);
            this.panel1.Controls.Add(this.GroupedResults);
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(856, 495);
            this.panel1.TabIndex = 0;
            // 
            // UserResults
            // 
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.UserResults.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.UserResults.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.UserResults.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.matr_name,
            this.Matr_height,
            this.Matr_width,
            this.M1,
            this.M2,
            this.criter,
            this.Low_bound_disp,
            this.Good_solution_disp,
            this.time});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.UserResults.DefaultCellStyle = dataGridViewCellStyle2;
            this.UserResults.Location = new System.Drawing.Point(0, 0);
            this.UserResults.Name = "UserResults";
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.UserResults.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.UserResults.Size = new System.Drawing.Size(853, 495);
            this.UserResults.TabIndex = 2;
            this.UserResults.Visible = false;
            // 
            // matr_name
            // 
            this.matr_name.HeaderText = "Имя матрицы";
            this.matr_name.Name = "matr_name";
            this.matr_name.ReadOnly = true;
            this.matr_name.Width = 200;
            // 
            // Matr_height
            // 
            this.Matr_height.HeaderText = "Высота матрицы";
            this.Matr_height.Name = "Matr_height";
            this.Matr_height.ReadOnly = true;
            this.Matr_height.Width = 60;
            // 
            // Matr_width
            // 
            this.Matr_width.HeaderText = "Длина матрицы";
            this.Matr_width.Name = "Matr_width";
            this.Matr_width.ReadOnly = true;
            this.Matr_width.Width = 60;
            // 
            // M1
            // 
            this.M1.HeaderText = "M1";
            this.M1.Name = "M1";
            this.M1.ReadOnly = true;
            this.M1.Width = 60;
            // 
            // M2
            // 
            this.M2.HeaderText = "M2";
            this.M2.Name = "M2";
            this.M2.ReadOnly = true;
            this.M2.Width = 60;
            // 
            // criter
            // 
            this.criter.HeaderText = "Критерий";
            this.criter.Name = "criter";
            this.criter.ReadOnly = true;
            this.criter.Width = 70;
            // 
            // Low_bound_disp
            // 
            this.Low_bound_disp.HeaderText = "Отклонение от нижней оценки";
            this.Low_bound_disp.Name = "Low_bound_disp";
            this.Low_bound_disp.ReadOnly = true;
            // 
            // Good_solution_disp
            // 
            this.Good_solution_disp.HeaderText = "Отклонение от \"хорошего\" решения";
            this.Good_solution_disp.Name = "Good_solution_disp";
            this.Good_solution_disp.ReadOnly = true;
            // 
            // time
            // 
            this.time.HeaderText = "time";
            this.time.Name = "time";
            this.time.ReadOnly = true;
            // 
            // GroupedResults
            // 
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.GroupedResults.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
            this.GroupedResults.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GroupedResults.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.count,
            this.dataGridViewTextBoxColumn4,
            this.dataGridViewTextBoxColumn5,
            this.dataGridViewTextBoxColumn6,
            this.dataGridViewTextBoxColumn7,
            this.dataGridViewTextBoxColumn9});
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle5.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.GroupedResults.DefaultCellStyle = dataGridViewCellStyle5;
            this.GroupedResults.Location = new System.Drawing.Point(0, 0);
            this.GroupedResults.Name = "GroupedResults";
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.GroupedResults.RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
            this.GroupedResults.Size = new System.Drawing.Size(853, 495);
            this.GroupedResults.TabIndex = 3;
            this.GroupedResults.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.CellDoubleClick);
            // 
            // count
            // 
            this.count.HeaderText = "Количество";
            this.count.Name = "count";
            this.count.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn4
            // 
            this.dataGridViewTextBoxColumn4.HeaderText = "M1";
            this.dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
            this.dataGridViewTextBoxColumn4.ReadOnly = true;
            this.dataGridViewTextBoxColumn4.Width = 60;
            // 
            // dataGridViewTextBoxColumn5
            // 
            this.dataGridViewTextBoxColumn5.HeaderText = "M2";
            this.dataGridViewTextBoxColumn5.Name = "dataGridViewTextBoxColumn5";
            this.dataGridViewTextBoxColumn5.ReadOnly = true;
            this.dataGridViewTextBoxColumn5.Width = 60;
            // 
            // dataGridViewTextBoxColumn6
            // 
            this.dataGridViewTextBoxColumn6.HeaderText = "Критерий";
            this.dataGridViewTextBoxColumn6.Name = "dataGridViewTextBoxColumn6";
            this.dataGridViewTextBoxColumn6.ReadOnly = true;
            this.dataGridViewTextBoxColumn6.Width = 70;
            // 
            // dataGridViewTextBoxColumn7
            // 
            this.dataGridViewTextBoxColumn7.HeaderText = "Отклонение от нижней оценки";
            this.dataGridViewTextBoxColumn7.Name = "dataGridViewTextBoxColumn7";
            this.dataGridViewTextBoxColumn7.ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn9
            // 
            this.dataGridViewTextBoxColumn9.HeaderText = "time";
            this.dataGridViewTextBoxColumn9.Name = "dataGridViewTextBoxColumn9";
            this.dataGridViewTextBoxColumn9.ReadOnly = true;
            // 
            // btnGrouped
            // 
            this.btnGrouped.Enabled = false;
            this.btnGrouped.Location = new System.Drawing.Point(871, 12);
            this.btnGrouped.Name = "btnGrouped";
            this.btnGrouped.Size = new System.Drawing.Size(108, 65);
            this.btnGrouped.TabIndex = 1;
            this.btnGrouped.Text = "Вернуться к сгруппированным результатам";
            this.btnGrouped.UseVisualStyleBackColor = true;
            this.btnGrouped.Click += new System.EventHandler(this.btnGrouped_Click);
            // 
            // Test_result
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(982, 519);
            this.Controls.Add(this.btnGrouped);
            this.Controls.Add(this.panel1);
            this.Name = "Test_result";
            this.Text = "Тестовая система";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.UserResults)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GroupedResults)).EndInit();
            this.ResumeLayout(false);

        }
        private System.Windows.Forms.Button btnGrouped;

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView UserResults;
        private System.Windows.Forms.DataGridView GroupedResults;
        private System.Windows.Forms.DataGridViewTextBoxColumn matr_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn Matr_height;
        private System.Windows.Forms.DataGridViewTextBoxColumn Matr_width;
        private System.Windows.Forms.DataGridViewTextBoxColumn M1;
        private System.Windows.Forms.DataGridViewTextBoxColumn M2;
        private System.Windows.Forms.DataGridViewTextBoxColumn criter;
        private System.Windows.Forms.DataGridViewTextBoxColumn Low_bound_disp;
        private System.Windows.Forms.DataGridViewTextBoxColumn Good_solution_disp;
        private System.Windows.Forms.DataGridViewTextBoxColumn time;
        private System.Windows.Forms.DataGridViewTextBoxColumn count;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn5;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn6;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn7;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn9;
    }
}