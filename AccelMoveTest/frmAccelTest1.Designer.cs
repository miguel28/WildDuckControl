namespace AccelMoveTest
{
    partial class frmAccelTest1
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
            this.components = new System.ComponentModel.Container();
            SpPerfChart.ChartPen chartPen1 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen2 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen3 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen4 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen5 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen6 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen7 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen8 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen9 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen10 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen11 = new SpPerfChart.ChartPen();
            SpPerfChart.ChartPen chartPen12 = new SpPerfChart.ChartPen();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.perfChart1 = new SpPerfChart.PerfChart();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.perfChart2 = new SpPerfChart.PerfChart();
            this.perfChart3 = new SpPerfChart.PerfChart();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 20;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(3, 571);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            // 
            // perfChart1
            // 
            this.perfChart1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.perfChart1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.perfChart1.Location = new System.Drawing.Point(3, 16);
            this.perfChart1.Name = "perfChart1";
            this.perfChart1.PerfChartStyle.AntiAliasing = true;
            chartPen1.Color = System.Drawing.Color.Black;
            chartPen1.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen1.Width = 1F;
            this.perfChart1.PerfChartStyle.AvgLinePen = chartPen1;
            this.perfChart1.PerfChartStyle.BackgroundColorBottom = System.Drawing.Color.LightGreen;
            this.perfChart1.PerfChartStyle.BackgroundColorTop = System.Drawing.Color.DarkGreen;
            chartPen2.Color = System.Drawing.Color.White;
            chartPen2.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen2.Width = 2F;
            this.perfChart1.PerfChartStyle.ChartLinePen = chartPen2;
            chartPen3.Color = System.Drawing.Color.Black;
            chartPen3.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen3.Width = 1F;
            this.perfChart1.PerfChartStyle.HorizontalGridPen = chartPen3;
            this.perfChart1.PerfChartStyle.ShowAverageLine = true;
            this.perfChart1.PerfChartStyle.ShowHorizontalGridLines = true;
            this.perfChart1.PerfChartStyle.ShowVerticalGridLines = true;
            chartPen4.Color = System.Drawing.Color.Black;
            chartPen4.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen4.Width = 1F;
            this.perfChart1.PerfChartStyle.VerticalGridPen = chartPen4;
            this.perfChart1.ScaleMode = SpPerfChart.ScaleMode.Absolute;
            this.perfChart1.Size = new System.Drawing.Size(451, 257);
            this.perfChart1.TabIndex = 1;
            this.perfChart1.TimerInterval = 20;
            this.perfChart1.TimerMode = SpPerfChart.TimerMode.Disabled;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.groupBox2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.groupBox3, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.groupBox4, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(927, 565);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.perfChart1);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(457, 276);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Axis X";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.perfChart2);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(466, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(458, 276);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Axis Y";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.perfChart3);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(3, 285);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(457, 277);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Axis Z";
            // 
            // groupBox4
            // 
            this.groupBox4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox4.Location = new System.Drawing.Point(466, 285);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(458, 277);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "groupBox4";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Controls.Add(this.label1, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(933, 621);
            this.tableLayoutPanel2.TabIndex = 3;
            // 
            // perfChart2
            // 
            this.perfChart2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.perfChart2.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.perfChart2.Location = new System.Drawing.Point(3, 16);
            this.perfChart2.Name = "perfChart2";
            this.perfChart2.PerfChartStyle.AntiAliasing = true;
            chartPen5.Color = System.Drawing.Color.Black;
            chartPen5.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen5.Width = 1F;
            this.perfChart2.PerfChartStyle.AvgLinePen = chartPen5;
            this.perfChart2.PerfChartStyle.BackgroundColorBottom = System.Drawing.Color.Aquamarine;
            this.perfChart2.PerfChartStyle.BackgroundColorTop = System.Drawing.Color.DarkSlateGray;
            chartPen6.Color = System.Drawing.Color.White;
            chartPen6.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen6.Width = 2F;
            this.perfChart2.PerfChartStyle.ChartLinePen = chartPen6;
            chartPen7.Color = System.Drawing.Color.Black;
            chartPen7.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen7.Width = 1F;
            this.perfChart2.PerfChartStyle.HorizontalGridPen = chartPen7;
            this.perfChart2.PerfChartStyle.ShowAverageLine = true;
            this.perfChart2.PerfChartStyle.ShowHorizontalGridLines = true;
            this.perfChart2.PerfChartStyle.ShowVerticalGridLines = true;
            chartPen8.Color = System.Drawing.Color.Black;
            chartPen8.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen8.Width = 1F;
            this.perfChart2.PerfChartStyle.VerticalGridPen = chartPen8;
            this.perfChart2.ScaleMode = SpPerfChart.ScaleMode.Absolute;
            this.perfChart2.Size = new System.Drawing.Size(452, 257);
            this.perfChart2.TabIndex = 2;
            this.perfChart2.TimerInterval = 20;
            this.perfChart2.TimerMode = SpPerfChart.TimerMode.Disabled;
            // 
            // perfChart3
            // 
            this.perfChart3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.perfChart3.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.perfChart3.Location = new System.Drawing.Point(3, 16);
            this.perfChart3.Name = "perfChart3";
            this.perfChart3.PerfChartStyle.AntiAliasing = true;
            chartPen9.Color = System.Drawing.Color.Black;
            chartPen9.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen9.Width = 1F;
            this.perfChart3.PerfChartStyle.AvgLinePen = chartPen9;
            this.perfChart3.PerfChartStyle.BackgroundColorBottom = System.Drawing.Color.Pink;
            this.perfChart3.PerfChartStyle.BackgroundColorTop = System.Drawing.Color.Red;
            chartPen10.Color = System.Drawing.Color.White;
            chartPen10.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen10.Width = 2F;
            this.perfChart3.PerfChartStyle.ChartLinePen = chartPen10;
            chartPen11.Color = System.Drawing.Color.Black;
            chartPen11.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen11.Width = 1F;
            this.perfChart3.PerfChartStyle.HorizontalGridPen = chartPen11;
            this.perfChart3.PerfChartStyle.ShowAverageLine = true;
            this.perfChart3.PerfChartStyle.ShowHorizontalGridLines = true;
            this.perfChart3.PerfChartStyle.ShowVerticalGridLines = true;
            chartPen12.Color = System.Drawing.Color.Black;
            chartPen12.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
            chartPen12.Width = 1F;
            this.perfChart3.PerfChartStyle.VerticalGridPen = chartPen12;
            this.perfChart3.ScaleMode = SpPerfChart.ScaleMode.Absolute;
            this.perfChart3.Size = new System.Drawing.Size(451, 258);
            this.perfChart3.TabIndex = 2;
            this.perfChart3.TimerInterval = 20;
            this.perfChart3.TimerMode = SpPerfChart.TimerMode.Disabled;
            // 
            // frmAccelTest1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(933, 621);
            this.Controls.Add(this.tableLayoutPanel2);
            this.Name = "frmAccelTest1";
            this.Text = "Accelerometer Test";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label1;
        private SpPerfChart.PerfChart perfChart1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private SpPerfChart.PerfChart perfChart2;
        private System.Windows.Forms.GroupBox groupBox3;
        private SpPerfChart.PerfChart perfChart3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
    }
}

