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
            this.btnOpenHID = new System.Windows.Forms.Button();
            this.grpMetrics = new System.Windows.Forms.GroupBox();
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
            this.btnMoveCenter = new System.Windows.Forms.Button();
            this.grpMetrics.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numElevation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbElevator)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbAileron)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbRudder)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trbThrotle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPollTime)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numJoy)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOpenHID
            // 
            this.btnOpenHID.Location = new System.Drawing.Point(23, 15);
            this.btnOpenHID.Name = "btnOpenHID";
            this.btnOpenHID.Size = new System.Drawing.Size(104, 33);
            this.btnOpenHID.TabIndex = 0;
            this.btnOpenHID.Text = "Open HID";
            this.btnOpenHID.UseVisualStyleBackColor = true;
            this.btnOpenHID.Click += new System.EventHandler(this.btnOpenHID_Click);
            // 
            // grpMetrics
            // 
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
            this.grpMetrics.Location = new System.Drawing.Point(23, 70);
            this.grpMetrics.Name = "grpMetrics";
            this.grpMetrics.Size = new System.Drawing.Size(442, 231);
            this.grpMetrics.TabIndex = 1;
            this.grpMetrics.TabStop = false;
            this.grpMetrics.Text = "Wild Duck Controls";
            // 
            // chkUseJoystick
            // 
            this.chkUseJoystick.AutoSize = true;
            this.chkUseJoystick.Location = new System.Drawing.Point(298, 180);
            this.chkUseJoystick.Name = "chkUseJoystick";
            this.chkUseJoystick.Size = new System.Drawing.Size(86, 17);
            this.chkUseJoystick.TabIndex = 9;
            this.chkUseJoystick.Text = "Use Joystick";
            this.chkUseJoystick.UseVisualStyleBackColor = true;
            // 
            // numElevation
            // 
            this.numElevation.Location = new System.Drawing.Point(72, 178);
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
            this.trbElevator.Maximum = 254;
            this.trbElevator.Name = "trbElevator";
            this.trbElevator.Size = new System.Drawing.Size(375, 45);
            this.trbElevator.TabIndex = 8;
            // 
            // trbAileron
            // 
            this.trbAileron.Location = new System.Drawing.Point(61, 87);
            this.trbAileron.Maximum = 254;
            this.trbAileron.Name = "trbAileron";
            this.trbAileron.Size = new System.Drawing.Size(375, 45);
            this.trbAileron.TabIndex = 7;
            // 
            // trbRudder
            // 
            this.trbRudder.Location = new System.Drawing.Point(61, 55);
            this.trbRudder.Maximum = 254;
            this.trbRudder.Name = "trbRudder";
            this.trbRudder.Size = new System.Drawing.Size(375, 45);
            this.trbRudder.TabIndex = 6;
            // 
            // lblElevation
            // 
            this.lblElevation.AutoSize = true;
            this.lblElevation.Location = new System.Drawing.Point(15, 180);
            this.lblElevation.Name = "lblElevation";
            this.lblElevation.Size = new System.Drawing.Size(51, 13);
            this.lblElevation.TabIndex = 5;
            this.lblElevation.Text = "Elevation";
            // 
            // lblElevator
            // 
            this.lblElevator.AutoSize = true;
            this.lblElevator.Location = new System.Drawing.Point(15, 135);
            this.lblElevator.Name = "lblElevator";
            this.lblElevator.Size = new System.Drawing.Size(46, 13);
            this.lblElevator.TabIndex = 4;
            this.lblElevator.Text = "Elevator";
            // 
            // lblAileron
            // 
            this.lblAileron.AutoSize = true;
            this.lblAileron.Location = new System.Drawing.Point(15, 96);
            this.lblAileron.Name = "lblAileron";
            this.lblAileron.Size = new System.Drawing.Size(39, 13);
            this.lblAileron.TabIndex = 3;
            this.lblAileron.Text = "Aileron";
            // 
            // lblRudder
            // 
            this.lblRudder.AutoSize = true;
            this.lblRudder.Location = new System.Drawing.Point(15, 65);
            this.lblRudder.Name = "lblRudder";
            this.lblRudder.Size = new System.Drawing.Size(42, 13);
            this.lblRudder.TabIndex = 2;
            this.lblRudder.Text = "Rudder";
            // 
            // lblThrotle
            // 
            this.lblThrotle.AutoSize = true;
            this.lblThrotle.Location = new System.Drawing.Point(15, 29);
            this.lblThrotle.Name = "lblThrotle";
            this.lblThrotle.Size = new System.Drawing.Size(40, 13);
            this.lblThrotle.TabIndex = 1;
            this.lblThrotle.Text = "Throtle";
            // 
            // trbThrotle
            // 
            this.trbThrotle.Location = new System.Drawing.Point(61, 19);
            this.trbThrotle.Maximum = 254;
            this.trbThrotle.Name = "trbThrotle";
            this.trbThrotle.Size = new System.Drawing.Size(375, 45);
            this.trbThrotle.TabIndex = 0;
            // 
            // numPollTime
            // 
            this.numPollTime.Location = new System.Drawing.Point(203, 23);
            this.numPollTime.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numPollTime.Name = "numPollTime";
            this.numPollTime.Size = new System.Drawing.Size(46, 20);
            this.numPollTime.TabIndex = 2;
            this.numPollTime.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numPollTime.ValueChanged += new System.EventHandler(this.numPollTime_ValueChanged);
            // 
            // btnOpenJoystick
            // 
            this.btnOpenJoystick.Location = new System.Drawing.Point(296, 15);
            this.btnOpenJoystick.Name = "btnOpenJoystick";
            this.btnOpenJoystick.Size = new System.Drawing.Size(95, 33);
            this.btnOpenJoystick.TabIndex = 3;
            this.btnOpenJoystick.Text = "Open Joystick";
            this.btnOpenJoystick.UseVisualStyleBackColor = true;
            this.btnOpenJoystick.Click += new System.EventHandler(this.btnOpenJoystick_Click);
            // 
            // lblPollTime
            // 
            this.lblPollTime.AutoSize = true;
            this.lblPollTime.Location = new System.Drawing.Point(133, 25);
            this.lblPollTime.Name = "lblPollTime";
            this.lblPollTime.Size = new System.Drawing.Size(64, 13);
            this.lblPollTime.TabIndex = 4;
            this.lblPollTime.Text = "Polling Time";
            // 
            // numJoy
            // 
            this.numJoy.Location = new System.Drawing.Point(397, 23);
            this.numJoy.Name = "numJoy";
            this.numJoy.Size = new System.Drawing.Size(68, 20);
            this.numJoy.TabIndex = 5;
            // 
            // timer1
            // 
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btnMoveCenter
            // 
            this.btnMoveCenter.Location = new System.Drawing.Point(170, 170);
            this.btnMoveCenter.Name = "btnMoveCenter";
            this.btnMoveCenter.Size = new System.Drawing.Size(75, 41);
            this.btnMoveCenter.TabIndex = 10;
            this.btnMoveCenter.Text = "Move to center";
            this.btnMoveCenter.UseVisualStyleBackColor = true;
            this.btnMoveCenter.Click += new System.EventHandler(this.btnMoveCenter_Click);
            // 
            // frmHIDControllerTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(490, 326);
            this.Controls.Add(this.numJoy);
            this.Controls.Add(this.lblPollTime);
            this.Controls.Add(this.btnOpenJoystick);
            this.Controls.Add(this.numPollTime);
            this.Controls.Add(this.grpMetrics);
            this.Controls.Add(this.btnOpenHID);
            this.Name = "frmHIDControllerTest";
            this.Text = "Control Test";
            this.grpMetrics.ResumeLayout(false);
            this.grpMetrics.PerformLayout();
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

        private System.Windows.Forms.Button btnOpenHID;
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
    }
}

