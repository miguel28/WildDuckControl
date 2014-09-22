namespace WildDuckControl
{
    partial class frmHIDControllerTest
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
            this.grpMetrics = new System.Windows.Forms.GroupBox();
            this.lblThrSens = new System.Windows.Forms.Label();
            this.trbSensibility = new System.Windows.Forms.TrackBar();
            this.cboxReport = new System.Windows.Forms.ComboBox();
            this.lblSensorH = new System.Windows.Forms.Label();
            this.btnFly = new System.Windows.Forms.Button();
            this.trbUChannel = new System.Windows.Forms.TrackBar();
            this.lblUChannel = new System.Windows.Forms.Label();
            this.btnMoveCenter = new System.Windows.Forms.Button();
            this.chkUseJoystick = new System.Windows.Forms.CheckBox();
            this.numElevation = new System.Windows.Forms.NumericUpDown();
            this.trbElevator = new System.Windows.Forms.TrackBar();
            this.trbAileron = new System.Windows.Forms.TrackBar();
            this.trbRudder = new System.Windows.Forms.TrackBar();
            this.lblElevation = new System.Windows.Forms.Label();
            this.lblElevator = new System.Windows.Forms.Label();
            this.lblAileron = new System.Windows.Forms.Label();
            this.lblRudder = new System.Windows.Forms.Label();
            this.lblThrotle = new System.Windows.Forms.Label();
            this.trbThrotle = new System.Windows.Forms.TrackBar();
            this.numPollTime = new System.Windows.Forms.NumericUpDown();
            this.btnOpenJoystick = new System.Windows.Forms.Button();
            this.lblPollTime = new System.Windows.Forms.Label();
            this.numJoy = new System.Windows.Forms.NumericUpDown();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btnOpenConn = new System.Windows.Forms.Button();
            this.grpMetrics.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trbSensibility)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbUChannel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numElevation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbElevator)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbAileron)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbRudder)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbThrotle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPollTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numJoy)).BeginInit();
            this.SuspendLayout();
            // 
            // grpMetrics
            // 
            this.grpMetrics.Controls.Add(this.lblThrSens);
            this.grpMetrics.Controls.Add(this.trbSensibility);
            this.grpMetrics.Controls.Add(this.cboxReport);
            this.grpMetrics.Controls.Add(this.lblSensorH);
            this.grpMetrics.Controls.Add(this.btnFly);
            this.grpMetrics.Controls.Add(this.trbUChannel);
            this.grpMetrics.Controls.Add(this.lblUChannel);
            this.grpMetrics.Controls.Add(this.btnMoveCenter);
            this.grpMetrics.Controls.Add(this.chkUseJoystick);
            this.grpMetrics.Controls.Add(this.numElevation);
            this.grpMetrics.Controls.Add(this.trbElevator);
            this.grpMetrics.Controls.Add(this.trbAileron);
            this.grpMetrics.Controls.Add(this.trbRudder);
            this.grpMetrics.Controls.Add(this.lblElevation);
            this.grpMetrics.Controls.Add(this.lblElevator);
            this.grpMetrics.Controls.Add(this.lblAileron);
            this.grpMetrics.Controls.Add(this.lblRudder);
            this.grpMetrics.Controls.Add(this.lblThrotle);
            this.grpMetrics.Controls.Add(this.trbThrotle);
            this.grpMetrics.Location = new System.Drawing.Point(12, 54);
            this.grpMetrics.Name = "grpMetrics";
            this.grpMetrics.Size = new System.Drawing.Size(383, 374);
            this.grpMetrics.TabIndex = 1;
            this.grpMetrics.TabStop = false;
            this.grpMetrics.Text = "Wild Duck Controls";
            // 
            // lblThrSens
            // 
            this.lblThrSens.AutoSize = true;
            this.lblThrSens.Location = new System.Drawing.Point(10, 297);
            this.lblThrSens.Name = "lblThrSens";
            this.lblThrSens.Size = new System.Drawing.Size(92, 13);
            this.lblThrSens.TabIndex = 17;
            this.lblThrSens.Text = "Throttle Sensibility";
            // 
            // trbSensibility
            // 
            this.trbSensibility.Location = new System.Drawing.Point(18, 313);
            this.trbSensibility.Maximum = 200;
            this.trbSensibility.Name = "trbSensibility";
            this.trbSensibility.Size = new System.Drawing.Size(344, 45);
            this.trbSensibility.TabIndex = 16;
            this.trbSensibility.Value = 200;
            // 
            // cboxReport
            // 
            this.cboxReport.FormattingEnabled = true;
            this.cboxReport.Items.AddRange(new object[] {
            "Joystick",
            "Sensors",
            "EmergencyLanding",
            "Constants1",
            "Constants2",
            "Constants3",
            "...",
            "...",
            "...",
            "...",
            "...",
            "...",
            "...",
            "...",
            "...",
            "Nothing"});
            this.cboxReport.Location = new System.Drawing.Point(28, 260);
            this.cboxReport.Name = "cboxReport";
            this.cboxReport.Size = new System.Drawing.Size(121, 21);
            this.cboxReport.TabIndex = 15;
            this.cboxReport.SelectedIndexChanged += new System.EventHandler(this.cboxReport_SelectedIndexChanged);
            // 
            // lblSensorH
            // 
            this.lblSensorH.AutoSize = true;
            this.lblSensorH.Location = new System.Drawing.Point(269, 239);
            this.lblSensorH.Name = "lblSensorH";
            this.lblSensorH.Size = new System.Drawing.Size(16, 13);
            this.lblSensorH.TabIndex = 14;
            this.lblSensorH.Text = "...";
            // 
            // btnFly
            // 
            this.btnFly.Location = new System.Drawing.Point(180, 275);
            this.btnFly.Name = "btnFly";
            this.btnFly.Size = new System.Drawing.Size(75, 23);
            this.btnFly.TabIndex = 13;
            this.btnFly.Text = "Fly";
            this.btnFly.UseVisualStyleBackColor = true;
            this.btnFly.Click += new System.EventHandler(this.btnFly_Click);
            // 
            // trbUChannel
            // 
            this.trbUChannel.Location = new System.Drawing.Point(61, 161);
            this.trbUChannel.Maximum = 254;
            this.trbUChannel.Name = "trbUChannel";
            this.trbUChannel.Size = new System.Drawing.Size(311, 45);
            this.trbUChannel.TabIndex = 12;
            this.trbUChannel.Value = 220;
            // 
            // lblUChannel
            // 
            this.lblUChannel.AutoSize = true;
            this.lblUChannel.Location = new System.Drawing.Point(6, 161);
            this.lblUChannel.Name = "lblUChannel";
            this.lblUChannel.Size = new System.Drawing.Size(54, 13);
            this.lblUChannel.TabIndex = 11;
            this.lblUChannel.Text = "UChannel";
            // 
            // btnMoveCenter
            // 
            this.btnMoveCenter.Location = new System.Drawing.Point(180, 211);
            this.btnMoveCenter.Name = "btnMoveCenter";
            this.btnMoveCenter.Size = new System.Drawing.Size(75, 41);
            this.btnMoveCenter.TabIndex = 10;
            this.btnMoveCenter.Text = "Move to center";
            this.btnMoveCenter.UseVisualStyleBackColor = true;
            this.btnMoveCenter.Click += new System.EventHandler(this.btnMoveCenter_Click);
            // 
            // chkUseJoystick
            // 
            this.chkUseJoystick.AutoSize = true;
            this.chkUseJoystick.Location = new System.Drawing.Point(272, 212);
            this.chkUseJoystick.Name = "chkUseJoystick";
            this.chkUseJoystick.Size = new System.Drawing.Size(86, 17);
            this.chkUseJoystick.TabIndex = 9;
            this.chkUseJoystick.Text = "Use Joystick";
            this.chkUseJoystick.UseVisualStyleBackColor = true;
            // 
            // numElevation
            // 
            this.numElevation.Location = new System.Drawing.Point(101, 211);
            this.numElevation.Maximum = new decimal(new int[] {
            254,
            0,
            0,
            0});
            this.numElevation.Name = "numElevation";
            this.numElevation.Size = new System.Drawing.Size(57, 20);
            this.numElevation.TabIndex = 6;
            // 
            // trbElevator
            // 
            this.trbElevator.Location = new System.Drawing.Point(61, 121);
            this.trbElevator.Maximum = 1022;
            this.trbElevator.Name = "trbElevator";
            this.trbElevator.Size = new System.Drawing.Size(311, 45);
            this.trbElevator.TabIndex = 8;
            this.trbElevator.Value = 511;
            // 
            // trbAileron
            // 
            this.trbAileron.Location = new System.Drawing.Point(61, 87);
            this.trbAileron.Maximum = 1022;
            this.trbAileron.Name = "trbAileron";
            this.trbAileron.Size = new System.Drawing.Size(311, 45);
            this.trbAileron.TabIndex = 7;
            this.trbAileron.Value = 511;
            // 
            // trbRudder
            // 
            this.trbRudder.Location = new System.Drawing.Point(61, 55);
            this.trbRudder.Maximum = 1022;
            this.trbRudder.Name = "trbRudder";
            this.trbRudder.Size = new System.Drawing.Size(311, 45);
            this.trbRudder.TabIndex = 6;
            this.trbRudder.Value = 511;
            // 
            // lblElevation
            // 
            this.lblElevation.AutoSize = true;
            this.lblElevation.Location = new System.Drawing.Point(10, 215);
            this.lblElevation.Name = "lblElevation";
            this.lblElevation.Size = new System.Drawing.Size(85, 13);
            this.lblElevation.TabIndex = 5;
            this.lblElevation.Text = "Elevation Target";
            // 
            // lblElevator
            // 
            this.lblElevator.AutoSize = true;
            this.lblElevator.Location = new System.Drawing.Point(15, 121);
            this.lblElevator.Name = "lblElevator";
            this.lblElevator.Size = new System.Drawing.Size(46, 13);
            this.lblElevator.TabIndex = 4;
            this.lblElevator.Text = "Elevator";
            // 
            // lblAileron
            // 
            this.lblAileron.AutoSize = true;
            this.lblAileron.Location = new System.Drawing.Point(15, 87);
            this.lblAileron.Name = "lblAileron";
            this.lblAileron.Size = new System.Drawing.Size(39, 13);
            this.lblAileron.TabIndex = 3;
            this.lblAileron.Text = "Aileron";
            // 
            // lblRudder
            // 
            this.lblRudder.AutoSize = true;
            this.lblRudder.Location = new System.Drawing.Point(13, 55);
            this.lblRudder.Name = "lblRudder";
            this.lblRudder.Size = new System.Drawing.Size(42, 13);
            this.lblRudder.TabIndex = 2;
            this.lblRudder.Text = "Rudder";
            // 
            // lblThrotle
            // 
            this.lblThrotle.AutoSize = true;
            this.lblThrotle.Location = new System.Drawing.Point(15, 19);
            this.lblThrotle.Name = "lblThrotle";
            this.lblThrotle.Size = new System.Drawing.Size(40, 13);
            this.lblThrotle.TabIndex = 1;
            this.lblThrotle.Text = "Throtle";
            // 
            // trbThrotle
            // 
            this.trbThrotle.Location = new System.Drawing.Point(61, 19);
            this.trbThrotle.Maximum = 1022;
            this.trbThrotle.Name = "trbThrotle";
            this.trbThrotle.Size = new System.Drawing.Size(311, 45);
            this.trbThrotle.TabIndex = 0;
            // 
            // numPollTime
            // 
            this.numPollTime.Location = new System.Drawing.Point(131, 31);
            this.numPollTime.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numPollTime.Name = "numPollTime";
            this.numPollTime.Size = new System.Drawing.Size(46, 20);
            this.numPollTime.TabIndex = 2;
            this.numPollTime.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numPollTime.ValueChanged += new System.EventHandler(this.numPollTime_ValueChanged);
            // 
            // btnOpenJoystick
            // 
            this.btnOpenJoystick.Location = new System.Drawing.Point(183, 15);
            this.btnOpenJoystick.Name = "btnOpenJoystick";
            this.btnOpenJoystick.Size = new System.Drawing.Size(95, 30);
            this.btnOpenJoystick.TabIndex = 3;
            this.btnOpenJoystick.Text = "Open Joystick";
            this.btnOpenJoystick.UseVisualStyleBackColor = true;
            this.btnOpenJoystick.Click += new System.EventHandler(this.btnOpenJoystick_Click);
            // 
            // lblPollTime
            // 
            this.lblPollTime.AutoSize = true;
            this.lblPollTime.Location = new System.Drawing.Point(113, 15);
            this.lblPollTime.Name = "lblPollTime";
            this.lblPollTime.Size = new System.Drawing.Size(64, 13);
            this.lblPollTime.TabIndex = 4;
            this.lblPollTime.Text = "Polling Time";
            // 
            // numJoy
            // 
            this.numJoy.Location = new System.Drawing.Point(284, 25);
            this.numJoy.Name = "numJoy";
            this.numJoy.Size = new System.Drawing.Size(68, 20);
            this.numJoy.TabIndex = 5;
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btnOpenConn
            // 
            this.btnOpenConn.Location = new System.Drawing.Point(13, 13);
            this.btnOpenConn.Name = "btnOpenConn";
            this.btnOpenConn.Size = new System.Drawing.Size(94, 35);
            this.btnOpenConn.TabIndex = 6;
            this.btnOpenConn.Text = "Wild Duck Open Connection";
            this.btnOpenConn.UseVisualStyleBackColor = true;
            this.btnOpenConn.Click += new System.EventHandler(this.btnOpenConn_Click);
            // 
            // frmHIDControllerTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(787, 436);
            this.Controls.Add(this.btnOpenConn);
            this.Controls.Add(this.numJoy);
            this.Controls.Add(this.lblPollTime);
            this.Controls.Add(this.btnOpenJoystick);
            this.Controls.Add(this.numPollTime);
            this.Controls.Add(this.grpMetrics);
            this.Name = "frmHIDControllerTest";
            this.Text = "Control Test";
            this.grpMetrics.ResumeLayout(false);
            this.grpMetrics.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trbSensibility)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbUChannel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numElevation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbElevator)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbAileron)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbRudder)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbThrotle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPollTime)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numJoy)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox grpMetrics;
        private System.Windows.Forms.TrackBar trbThrotle;
        private System.Windows.Forms.NumericUpDown numPollTime;
        private System.Windows.Forms.Button btnOpenJoystick;
        private System.Windows.Forms.Label lblPollTime;
        private System.Windows.Forms.NumericUpDown numJoy;
        private System.Windows.Forms.Label lblThrotle;
        private System.Windows.Forms.NumericUpDown numElevation;
        private System.Windows.Forms.TrackBar trbElevator;
        private System.Windows.Forms.TrackBar trbAileron;
        private System.Windows.Forms.TrackBar trbRudder;
        private System.Windows.Forms.Label lblElevation;
        private System.Windows.Forms.Label lblElevator;
        private System.Windows.Forms.Label lblAileron;
        private System.Windows.Forms.Label lblRudder;
        private System.Windows.Forms.CheckBox chkUseJoystick;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btnMoveCenter;
        private System.Windows.Forms.Button btnOpenConn;
        private System.Windows.Forms.TrackBar trbUChannel;
        private System.Windows.Forms.Label lblUChannel;
        private System.Windows.Forms.Button btnFly;
        private System.Windows.Forms.Label lblSensorH;
        private System.Windows.Forms.ComboBox cboxReport;
        private System.Windows.Forms.TrackBar trbSensibility;
        private System.Windows.Forms.Label lblThrSens;
    }
}

