using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using USBInterface;

namespace AccelMoveTest
{
    public partial class frmAccelTest1 : Form
    {
        USBDevice usb;
        public frmAccelTest1()
        {
            InitializeComponent();
            usb = new USBDevice(0x3995, 0x0030);
            timer1.Enabled = usb.HIDisOpen;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            usb.ReciveBuffer();
            usb.StreamReadBegin();
            float axisX = usb.StreamReadFloat();
            float axisY = usb.StreamReadFloat();
            float axisZ = usb.StreamReadFloat();

            label1.Text = ("X: " + axisX.ToString() + " Y: " + axisY.ToString() +  " Z: " + axisZ.ToString());
            perfChart1.AddValue((int)(axisX * 25) + 50);
            perfChart2.AddValue((int)(axisY * 25) + 50);
            perfChart3.AddValue((int)(axisZ * 25) + 50);
        }
    }
}
