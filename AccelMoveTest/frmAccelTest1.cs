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
        private USBDevice usb;
        private bool Calibrated = false;
        float axisX;
        float axisY;
        float axisZ;

        float OffsetX;
        float OffsetY;
        float OffsetZ;

        float VelaxisX;
        float VelaxisY;
        float VelaxisZ;

        float PosaxisX;
        float PosaxisY;
        float PosaxisZ;

        public frmAccelTest1()
        {
            InitializeComponent();
            usb = new USBDevice(0x3995, 0x0030);
            tmrReceive.Enabled = usb.HIDisOpen;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            usb.ReciveBuffer();
            usb.StreamReadBegin();
            axisX = usb.StreamReadFloat();
            axisY = usb.StreamReadFloat();
            axisZ = usb.StreamReadFloat();

            char WhoHeIs = usb.StreamReadChar();
            //Calibrated = usb.StreamReadChar()==(char)0x01;

            OffsetX = usb.StreamReadFloat();
            OffsetY = usb.StreamReadFloat();
            OffsetZ = usb.StreamReadFloat();

            VelaxisX = usb.StreamReadFloat();
            VelaxisY = usb.StreamReadFloat();
            VelaxisZ = usb.StreamReadFloat();

            PosaxisX = usb.StreamReadFloat();
            PosaxisY = usb.StreamReadFloat();
            PosaxisZ = usb.StreamReadFloat();


            lblRawValues.Text = ("X: " + axisX.ToString() + " Y: " + axisY.ToString() +  " Z: " + axisZ.ToString());
            lblXOffset.Text = "X Offset: " + OffsetX.ToString();
            lblYOffset.Text = "Y Offset: " + OffsetY.ToString();
            lblZOffset.Text = "Z Offset: " + OffsetZ.ToString();

            lblPosX.Text = "X: " + PosaxisX.ToString();
            lblPosY.Text = "Y: " + PosaxisY.ToString();
            lblPosZ.Text = "Z: " + PosaxisZ.ToString();

            perfChart1.AddValue((int)(axisX * 25) + 50);
            perfChart2.AddValue((int)(axisY * 25) + 50);
            perfChart3.AddValue((int)(axisZ * 25) + 50);
        }

        private void btnCalibrate_Click(object sender, EventArgs e)
        {
            usb.StreamWriteBegin();
            usb.StreamWriteChar((char)0x01);
            usb.SendBuffer();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            usb.StreamWriteBegin();
            usb.StreamWriteChar((char)0x02);
            usb.SendBuffer();
        }
    }
}
