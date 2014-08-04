using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using USBInterface;
using JoytickInterop;

namespace WildDuckControl
{
    public partial class frmHIDControllerTest : Form
    {
        private USBDevice usb;
        private SDLJoystick joy;

        public frmHIDControllerTest()
        {
            InitializeComponent();
            SDLJoystick.InitJoystickSystem();
            numJoy.Maximum = SDLJoystick.Joysticks;
        }

        private void btnOpenHID_Click(object sender, EventArgs e)
        {
            usb = new USBDevice(0x3995, 0x0020, 16);
            timer1.Enabled = usb.HIDisOpen;
            btnOpenHID.Enabled = !usb.HIDisOpen;
        }
        private void btnOpenJoystick_Click(object sender, EventArgs e)
        {
            joy = new SDLJoystick((int)numJoy.Value);
            //timer1.Enabled = joy.IsOpen;
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
        }
        private void UpdateControlsWithJoystick()
        {
            joy.Update();

            float tmpThortle = joy.GetAxis(1);
            if (tmpThortle <= 0.0f)
                trbThrotle.Value = (int)(tmpThortle * -254.0f);
            trbRudder.Value = (int)(joy.GetAxis(0) * 127.0f) + 127;
            trbAileron.Value = (int)(joy.GetAxis(3) * 127.0f) + 127;
            trbElevator.Value = (int)(joy.GetAxis(2) * 127.0f) + 127;
        }
        private void SendReport()
        {
            usb.StreamWriteBegin();
            usb.StreamWriteChar((char)0x31);
            usb.StreamWriteChar((char)0x32);
            usb.StreamWriteChar((char)trbThrotle.Value);
            usb.StreamWriteChar((char)trbRudder.Value);
            usb.StreamWriteChar((char)trbAileron.Value);
            usb.StreamWriteChar((char)trbElevator.Value);
            usb.StreamWriteChar((char)numElevation.Value);
            usb.StreamWriteChar((char)0x00);
            usb.StreamWriteChar((char)0x00);
            usb.StreamWriteChar((char)0x00);
            usb.SendBuffer();
        }
    }
}
