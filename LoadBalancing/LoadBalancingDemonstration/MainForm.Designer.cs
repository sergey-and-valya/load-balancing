namespace LoadBalancingDemonstration
{
    partial class MainForm
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
            System.Windows.Forms.Label label3;
            System.Windows.Forms.Label label4;
            System.Windows.Forms.Label label2;
            System.Windows.Forms.Label label5;
            System.Windows.Forms.Label label1;
            this.lblPath = new System.Windows.Forms.Label();
            this.btnTest = new System.Windows.Forms.Button();
            this.lstMatrixes = new System.Windows.Forms.ListBox();
            this.btnGenerator = new System.Windows.Forms.Button();
            this.btnMatrixVisualizer = new System.Windows.Forms.Button();
            this.btnAlgorithm = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.lstGenerators = new System.Windows.Forms.ComboBox();
            this.lstMatrixVisualizers = new System.Windows.Forms.ComboBox();
            this.lstAlgorithms = new System.Windows.Forms.ComboBox();
            this.lstSolutionVisualizers = new System.Windows.Forms.ComboBox();
            this.btnPath = new System.Windows.Forms.Button();
            this.dlgMatrixPath = new System.Windows.Forms.FolderBrowserDialog();
            label3 = new System.Windows.Forms.Label();
            label4 = new System.Windows.Forms.Label();
            label2 = new System.Windows.Forms.Label();
            label5 = new System.Windows.Forms.Label();
            label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new System.Drawing.Point(12, 166);
            label3.Name = "label3";
            label3.Size = new System.Drawing.Size(53, 13);
            label3.TabIndex = 5;
            label3.Text = "Матрицы";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new System.Drawing.Point(12, 15);
            label4.Name = "label4";
            label4.Size = new System.Drawing.Size(68, 13);
            label4.TabIndex = 5;
            label4.Text = "Генераторы";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new System.Drawing.Point(12, 42);
            label2.Name = "label2";
            label2.Size = new System.Drawing.Size(126, 13);
            label2.TabIndex = 5;
            label2.Text = "Визуализаторы матриц";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new System.Drawing.Point(12, 69);
            label5.Name = "label5";
            label5.Size = new System.Drawing.Size(64, 13);
            label5.TabIndex = 5;
            label5.Text = "Алгоритмы";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(12, 366);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(101, 13);
            label1.TabIndex = 5;
            label1.Text = "Путь к хранилищу:";
            // 
            // lblPath
            // 
            this.lblPath.AutoEllipsis = true;
            this.lblPath.Location = new System.Drawing.Point(119, 366);
            this.lblPath.Name = "lblPath";
            this.lblPath.Size = new System.Drawing.Size(308, 13);
            this.lblPath.TabIndex = 5;
            this.lblPath.Text = "...";
            // 
            // btnTest
            // 
            this.btnTest.Enabled = false;
            this.btnTest.Location = new System.Drawing.Point(15, 309);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(446, 46);
            this.btnTest.TabIndex = 1;
            this.btnTest.Text = "Тестовая среда";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // lstMatrixes
            // 
            this.lstMatrixes.FormattingEnabled = true;
            this.lstMatrixes.Location = new System.Drawing.Point(15, 182);
            this.lstMatrixes.Name = "lstMatrixes";
            this.lstMatrixes.Size = new System.Drawing.Size(447, 121);
            this.lstMatrixes.TabIndex = 3;
            this.lstMatrixes.SelectedIndexChanged += new System.EventHandler(this.lstMatrixes_SelectedIndexChanged);
            // 
            // btnGenerator
            // 
            this.btnGenerator.Enabled = false;
            this.btnGenerator.Location = new System.Drawing.Point(15, 121);
            this.btnGenerator.Name = "btnGenerator";
            this.btnGenerator.Size = new System.Drawing.Size(146, 33);
            this.btnGenerator.TabIndex = 4;
            this.btnGenerator.Text = "Генерация";
            this.btnGenerator.UseVisualStyleBackColor = true;
            this.btnGenerator.Click += new System.EventHandler(this.btnGenerator_Click);
            // 
            // btnMatrixVisualizer
            // 
            this.btnMatrixVisualizer.Enabled = false;
            this.btnMatrixVisualizer.Location = new System.Drawing.Point(167, 121);
            this.btnMatrixVisualizer.Name = "btnMatrixVisualizer";
            this.btnMatrixVisualizer.Size = new System.Drawing.Size(146, 33);
            this.btnMatrixVisualizer.TabIndex = 6;
            this.btnMatrixVisualizer.Text = "Просмотр матрицы";
            this.btnMatrixVisualizer.UseVisualStyleBackColor = true;
            this.btnMatrixVisualizer.Click += new System.EventHandler(this.btnMatrixVisualizer_Click);
            // 
            // btnAlgorithm
            // 
            this.btnAlgorithm.Enabled = false;
            this.btnAlgorithm.Location = new System.Drawing.Point(319, 121);
            this.btnAlgorithm.Name = "btnAlgorithm";
            this.btnAlgorithm.Size = new System.Drawing.Size(142, 33);
            this.btnAlgorithm.TabIndex = 6;
            this.btnAlgorithm.Text = "Запустить алгоритм";
            this.btnAlgorithm.UseVisualStyleBackColor = true;
            this.btnAlgorithm.Click += new System.EventHandler(this.btnAlgorithm_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 97);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(133, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Визуализаторы решений";
            // 
            // lstGenerators
            // 
            this.lstGenerators.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.lstGenerators.FormattingEnabled = true;
            this.lstGenerators.Location = new System.Drawing.Point(86, 12);
            this.lstGenerators.Name = "lstGenerators";
            this.lstGenerators.Size = new System.Drawing.Size(375, 21);
            this.lstGenerators.TabIndex = 7;
            this.lstGenerators.SelectedIndexChanged += new System.EventHandler(this.lstGenerators_SelectedIndexChanged);
            // 
            // lstMatrixVisualizers
            // 
            this.lstMatrixVisualizers.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.lstMatrixVisualizers.FormattingEnabled = true;
            this.lstMatrixVisualizers.Location = new System.Drawing.Point(144, 39);
            this.lstMatrixVisualizers.Name = "lstMatrixVisualizers";
            this.lstMatrixVisualizers.Size = new System.Drawing.Size(317, 21);
            this.lstMatrixVisualizers.TabIndex = 8;
            this.lstMatrixVisualizers.SelectedIndexChanged += new System.EventHandler(this.lstMatricesVisualizers_SelectedIndexChanged);
            // 
            // lstAlgorithms
            // 
            this.lstAlgorithms.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.lstAlgorithms.FormattingEnabled = true;
            this.lstAlgorithms.Location = new System.Drawing.Point(82, 66);
            this.lstAlgorithms.Name = "lstAlgorithms";
            this.lstAlgorithms.Size = new System.Drawing.Size(379, 21);
            this.lstAlgorithms.TabIndex = 9;
            this.lstAlgorithms.SelectedIndexChanged += new System.EventHandler(this.lstAlgorithms_SelectedIndexChanged);
            // 
            // lstSolutionVisualizers
            // 
            this.lstSolutionVisualizers.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.lstSolutionVisualizers.FormattingEnabled = true;
            this.lstSolutionVisualizers.Location = new System.Drawing.Point(151, 94);
            this.lstSolutionVisualizers.Name = "lstSolutionVisualizers";
            this.lstSolutionVisualizers.Size = new System.Drawing.Size(310, 21);
            this.lstSolutionVisualizers.TabIndex = 10;
            this.lstSolutionVisualizers.SelectedIndexChanged += new System.EventHandler(this.lstSolutionVisualizers_SelectedIndexChanged);
            // 
            // btnPath
            // 
            this.btnPath.Location = new System.Drawing.Point(433, 361);
            this.btnPath.Name = "btnPath";
            this.btnPath.Size = new System.Drawing.Size(28, 23);
            this.btnPath.TabIndex = 11;
            this.btnPath.Text = "...";
            this.btnPath.UseVisualStyleBackColor = true;
            this.btnPath.Click += new System.EventHandler(this.btnPath_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 394);
            this.Controls.Add(this.btnPath);
            this.Controls.Add(this.lstSolutionVisualizers);
            this.Controls.Add(this.lstAlgorithms);
            this.Controls.Add(this.lstMatrixVisualizers);
            this.Controls.Add(this.lstGenerators);
            this.Controls.Add(this.btnAlgorithm);
            this.Controls.Add(this.btnMatrixVisualizer);
            this.Controls.Add(label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(label2);
            this.Controls.Add(this.lblPath);
            this.Controls.Add(label1);
            this.Controls.Add(label3);
            this.Controls.Add(label4);
            this.Controls.Add(this.btnGenerator);
            this.Controls.Add(this.lstMatrixes);
            this.Controls.Add(this.btnTest);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "Балансировка нагрузки";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.ListBox lstMatrixes;
        private System.Windows.Forms.Button btnGenerator;
        private System.Windows.Forms.Button btnMatrixVisualizer;
        private System.Windows.Forms.Button btnAlgorithm;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox lstGenerators;
        private System.Windows.Forms.ComboBox lstMatrixVisualizers;
        private System.Windows.Forms.ComboBox lstAlgorithms;
        private System.Windows.Forms.ComboBox lstSolutionVisualizers;
        private System.Windows.Forms.Button btnPath;
        private System.Windows.Forms.FolderBrowserDialog dlgMatrixPath;
        private System.Windows.Forms.Label lblPath;

    }
}