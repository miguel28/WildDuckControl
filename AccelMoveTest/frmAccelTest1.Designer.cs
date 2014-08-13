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
            this.tmrReceive = new System.Windows.Forms.Timer(this.components);
            this.lblRawValues = new System.Windows.Forms.Label();
            this.perfChart1 = new SpPerfChart.PerfChart();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.grpAxisX = new System.Windows.Forms.GroupBox();
            this.grpAxisY = new System.Windows.Forms.GroupBox();
            this.perfChart2 = new SpPerfChart.PerfChart();
            this.grpAxisZ = new System.Windows.Forms.GroupBox();
            this.perfChart3 = new SpPerfChart.PerfChart();
            this.grpCommands = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btnCalibrate = new System.Windows.Forms.Button();
            this.lblXOffset = new System.Windows.Forms.Label();
            this.lblYOffset = new System.Windows.Forms.Label();
            this.lblZOffset = new System.Windows.Forms.Label();
            this.lblPosZ = new System.Windows.Forms.Label();
            this.lblPosY = new System.Windows.Forms.Label();
            this.lblPosX = new System.Windows.Forms.Label();
            this.btnStart = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            this.grpAxisX.SuspendLayout();
            this.grpAxisY.SuspendLayout();
            this.grpAxisZ.SuspendLayout();
            this.grpCommands.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tmrReceive
            // 
            this.tmrReceive.Interval = 20;
            this.tmrReceive.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lblRawValues
            // 
            this.lblRawValues.AutoSize = true;
            this.lblRawValues.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblRawValues.Location = new System.Drawing.Point(3, 571);
            this.lblRawValues.Name = "lblRawValues";
            this.lblRawValues.Size = new System.Drawing.Size(86, 31);
            this.lblRawValues.TabIndex = 0;
            this.lblRawValues.Text = "label1";
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
            this.tableLayoutPanel1.Controls.Add(this.grpAxisX, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.grpAxisY, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.grpAxisZ, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.grpCommands, 1, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(927, 565);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // grpAxisX
            // 
            this.grpAxisX.Controls.Add(this.perfChart1);
            this.grpAxisX.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpAxisX.Location = new System.Drawing.Point(3, 3);
            this.grpAxisX.Name = "grpAxisX";
            this.grpAxisX.Size = new System.Drawing.Size(457, 276);
            this.grpAxisX.TabIndex = 0;
            this.grpAxisX.TabStop = false;
            this.grpAxisX.Text = "Axis X";
            // 
            // grpAxisY
            // 
            this.grpAxisY.Controls.Add(this.perfChart2);
            this.grpAxisY.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpAxisY.Location = new System.Drawing.Point(466, 3);
            this.grpAxisY.Name = "grpAxisY";
            this.grpAxisY.Size = new System.Drawing.Size(458, 276);
            this.grpAxisY.TabIndex = 1;
            this.grpAxisY.TabStop = false;
            this.grpAxisY.Text = "Axis Y";
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
            // grpAxisZ
            // 
            this.grpAxisZ.Controls.Add(this.perfChart3);
            this.grpAxisZ.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpAxisZ.Location = new System.Drawing.Point(3, 285);
            this.grpAxisZ.Name = "grpAxisZ";
            this.grpAxisZ.Size = new System.Drawing.Size(457, 277);
            this.grpAxisZ.TabIndex = 2;
            this.grpAxisZ.TabStop = false;
            this.grpAxisZ.Text = "Axis Z";
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
            // grpCommands
            // 
            this.grpCommands.Controls.Add(this.btnStart);
            this.grpCommands.Controls.Add(this.lblPosZ);
            this.grpCommands.Controls.Add(this.lblPosY);
            this.grpCommands.Controls.Add(this.lblPosX);
            this.grpCommands.Controls.Add(this.lblZOffset);
            this.grpCommands.Controls.Add(this.lblYOffset);
            this.grpCommands.Controls.Add(this.lblXOffset);
            this.grpCommands.Controls.Add(this.btnCalibrate);
            this.grpCommands.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpCommands.Location = new System.Drawing.Point(466, 285);
            this.grpCommands.Name = "grpCommands";
            this.grpCommands.Size = new System.Drawing.Size(458, 277);
            this.grpCommands.TabIndex = 3;
            this.grpCommands.TabStop = false;
            this.grpCommands.Text = "Commands";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Controls.Add(this.lblRawValues, 0, 1);
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
            // btnCalibrate
            // 
            this.btnCalibrate.Location = new System.Drawing.Point(18, 19);
            this.btnCalibrate.Name = "btnCalibrate";
            this.btnCalibrate.Size = new System.Drawing.Size(80, 26);
            this.btnCalibrate.TabIndex = 0;
            this.btnCalibrate.Text = "Calibrate";
            this.btnCalibrate.UseVisualStyleBackColor = true;
            this.btnCalibrate.Click += new System.EventHandler(this.btnCalibrate_Click);
            // 
            // lblXOffset
            // 
            this.lblXOffset.AutoSize = true;
            this.lblXOffset.Location = new System.Drawing.Point(18, 66);
            this.lblXOffset.Name = "lblXOffset";
            this.lblXOffset.Size = new System.Drawing.Size(35, 13);
            this.lblXOffset.TabIndex = 1;
            this.lblXOffset.Text = "label1";
            // 
            // lblYOffset
            // 
            this.lblYOffset.AutoSize = true;
            this.lblYOffset.Location = new System.Drawing.Point(18, 95);
            this.lblYOffset.Name = "lblYOffset";
            this.lblYOffset.Size = new System.Drawing.Size(35, 13);
            this.lblYOffset.TabIndex = 2;
            this.lblYOffset.Text = "label2";
            // 
            // lblZOffset
            // 
            this.lblZOffset.AutoSize = true;
            this.lblZOffset.Location = new System.Drawing.Point(18, 121);
            this.lblZOffset.Name = "lblZOffset";
            this.lblZOffset.Size = new System.Drawing.Size(35, 13);
            this.lblZOffset.TabIndex = 3;
            this.lblZOffset.Text = "label3";
            // 
            // lblPosZ
            // 
            this.lblPosZ.AutoSize = true;
            this.lblPosZ.Location = new System.Drawing.Point(181, 121);
            this.lblPosZ.Name = "lblPosZ";
            this.lblPosZ.Size = new System.Drawing.Size(35, 13);
            this.lblPosZ.TabIndex = 6;
            this.lblPosZ.Text = "label3";
            // 
            // lblPosY
            // 
            this.lblPosY.AutoSize = true;
            this.lblPosY.Location = new System.Drawing.Point(181, 95);
            this.lblPosY.Name = "lblPosY";
            this.lblPosY.Size = new System.Drawing.Size(35, 13);
            this.lblPosY.TabIndex = 5;
            this.lblPosY.Text = "label2";
            // 
            // lblPosX
            // 
            this.lblPosX.AutoSize = true;
            this.lblPosX.Location = new System.Drawing.Point(181, 66);
            this.lblPosX.Name = "lblPosX";
            this.lblPosX.Size = new System.Drawing.Size(35, 13);
            this.lblPosX.TabIndex = 4;
            this.lblPosX.Text = "label1";
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(136, 19);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(80, 26);
            this.btnStart.TabIndex = 7;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
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
            this.grpAxisX.ResumeLayout(false);
            this.grpAxisY.ResumeLayout(false);
            this.grpAxisZ.ResumeLayout(false);
            this.grpCommands.ResumeLayout(false);
            this.grpCommands.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer tmrReceive;
        private System.Windows.Forms.Label lblRawValues;
        private SpPerfChart.PerfChart perfChart1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox grpAxisX;
        private System.Windows.Forms.GroupBox grpAxisY;
        private SpPerfChart.PerfChart perfChart2;
        private System.Windows.Forms.GroupBox grpAxisZ;
        private SpPerfChart.PerfChart perfChart3;
        private System.Windows.Forms.GroupBox grpCommands;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnCalibrate;
        private System.Windows.Forms.Label lblZOffset;
        private System.Windows.Forms.Label lblYOffset;
        private System.Windows.Forms.Label lblXOffset;
        private System.Windows.Forms.Label lblPosZ;
        private System.Windows.Forms.Label lblPosY;
        private System.Windows.Forms.Label lblPosX;
        private System.Windows.Forms.Button btnStart;
    }
}

