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
        private int FlyTimeOut = 0;
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
            if (chkUseJoystick.Checked && joy != null && joy.IsOpen && FlyTimeOut== 0)
                UpdateControlsWithJoystick();
            SendReport();
        }
        private void UpdateControlsWithJoystick()
        {
            joy.Update();

            float tmpThortle = joy.GetAxis(1);
            if (tmpThortle <= 0.0f)
                trbThrotle.Value = (int)(tmpThortle * -1023.0f);
            trbRudder.Value = (int)(joy.GetAxis(0) * 511.0f) + 511;
            trbAileron.Value = (int)(joy.GetAxis(3) * 511.0f) + 511;
            trbElevator.Value = (int)(joy.GetAxis(2) * 511.0f) + 511;
        }
        private void SendReport()
        {
            if(FlyTimeOut == 1)
                btnMoveCenter_Click(null, null);
            if (FlyTimeOut != 0)
                FlyTimeOut--;

            wildDuck.Send.joystickReport.Throttle = (ushort)(trbThrotle.Value);
            wildDuck.Send.joystickReport.Aileron = (ushort)(trbAileron.Value);
            wildDuck.Send.joystickReport.Rudder = (ushort)(trbRudder.Value);
            wildDuck.Send.joystickReport.Elevator = (ushort)(trbElevator.Value);
            wildDuck.Send.joystickReport.ElevationTarget = (char)numElevation.Value;
            wildDuck.Send.joystickReport.UChannel = (char)trbUChannel.Value;
        }
        private void btnMoveCenter_Click(object sender, EventArgs e)
        {
            trbAileron.Value = 511;
            trbElevator.Value = 511;
            trbRudder.Value = 511;
            trbThrotle.Value = 0;
        }
        private void LandOff()
        {
            trbThrotle.Value = 0;
            trbRudder.Value = 1022;
            trbAileron.Value = 0;
            trbElevator.Value = 0;
            Application.DoEvents();
            FlyTimeOut = 101;
            


        }
        private void btnFly_Click(object sender, EventArgs e)
        {
            LandOff();
        }

    }
}
