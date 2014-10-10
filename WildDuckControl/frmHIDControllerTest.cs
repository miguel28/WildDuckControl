using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WildDuckLibrary;
using JoytickInterop;

namespace WildDuckControl
{
    public partial class frmHIDControllerTest : Form
    {
        private WildDuckConnection wildDuck;
        private SDLJoystick joy;
        float CalcThrottle = 0.0f;
        bool Arming = false;

        public frmHIDControllerTest()
        {
            InitializeComponent();
            SDLJoystick.InitJoystickSystem();
            numJoy.Maximum = SDLJoystick.Joysticks;
        }

        private void btnOpenConn_Click(object sender, EventArgs e)
        {
            wildDuck = new WildDuckConnection();
            wildDuck.ConnectionStart();
            //wildDuck.ReceiveReportType = ReportType.Sensors;
            cboxReport.SelectedIndex = 15;
            wildDuck.ReceiveReportType = ReportType.Nothing;
            timer1.Enabled = true;
            btnOpenConn.Enabled = false;
        }

        private void btnOpenJoystick_Click(object sender, EventArgs e)
        {
            joy = new SDLJoystick((int)numJoy.Value);
            btnOpenJoystick.Enabled = false;
            numJoy.Enabled = false;
        }
        private void numPollTime_ValueChanged(object sender, EventArgs e)
        {
            timer1.Interval = (int)numPollTime.Value;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (chkUseJoystick.Checked && joy != null && joy.IsOpen)
                UpdateControlsWithJoystick();
            SendReport();

            lblSensorH.Text = wildDuck.Received.sensorsReport.Elevation.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Front.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Back.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Left.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Right.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Debug1.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Debug2.ToString() + ",\r\n"
                            + wildDuck.Received.sensorsReport.Debug3.ToString();


        }
        private void UpdateControlsWithJoystick()
        {
            joy.Update();
            JoystickHatPositions pos = joy.GetHatNewPress(0);
            if (pos == JoystickHatPositions.HAT_UP)
                CalcThrottle += 100.0f;
            if (pos == JoystickHatPositions.HAT_RIGHTDOWN)
                CalcThrottle -= 100.0f;

            float tmpThortle = joy.GetAxis(1,0.10f);

            CalcThrottle += -tmpThortle * (trbSensibility.Value / 50.0f);
            if (CalcThrottle <= 0.0f)
                CalcThrottle = 0.0f;
            if (CalcThrottle >= 1022.0f)
                CalcThrottle = 1022.0f;

            if (joy.ButtonNewpress(2))
                CalcThrottle = 0.0f;

            wildDuck.Motor = joy.ButtonHeld(4);
            wildDuck.Arm = joy.ButtonHeld(10);
            wildDuck.DisArm = joy.ButtonHeld(9);

            Arming = (joy.ButtonHeld(10) || joy.ButtonHeld(9));
            /*if (Arming)
            {
                CalcThrottle = 0.0f;
                System.Threading.Thread.Sleep(2000);
                Arming = false;
            }*/
            if (Arming)
            {
                CalcThrottle = 0.0f;
                return;
            }
                

            trbThrotle.Value = (int)(CalcThrottle);
            trbRudder.Value = (int)((-joy.GetAxis(0, 0.10f)) * 511.0f) + 511;
            trbAileron.Value = (int)(joy.GetAxis(3, 0.10f) * 511.0f) + 511;
            trbElevator.Value = (int)(joy.GetAxis(2, 0.10f) * 511.0f) + 511;
        }
        private void SendReport()
        {
            wildDuck.Send.joystickReport.Throttle = (ushort)(trbThrotle.Value);
            wildDuck.Send.joystickReport.Aileron = (ushort)(trbAileron.Value);
            wildDuck.Send.joystickReport.Rudder = (ushort)(trbRudder.Value);
            wildDuck.Send.joystickReport.Elevator = (ushort)(trbElevator.Value);
            wildDuck.Send.joystickReport.ElevationTarget = (byte)numElevation.Value;
            wildDuck.Send.joystickReport.UChannel = (byte)trbUChannel.Value;
        }
        private void btnMoveCenter_Click(object sender, EventArgs e)
        {
            trbAileron.Value = 511;
            trbElevator.Value = 511;
            trbRudder.Value = 511;
            trbThrotle.Value = 0;
        }

        private void btnFly_Click(object sender, EventArgs e)
        {
            wildDuck.Arm = true;
            Arming = true;
            System.Threading.Thread.Sleep(2000);
            Arming = false;
        }

        private void btnDisArm_Click(object sender, EventArgs e)
        {
            wildDuck.DisArm = true;
            Arming = true;
            System.Threading.Thread.Sleep(2000);
            Arming = false;
        }

        private void cboxReport_SelectedIndexChanged(object sender, EventArgs e)
        {
            wildDuck.ReceiveReportType = (ReportType)cboxReport.SelectedIndex;
        }
    
    }
}
