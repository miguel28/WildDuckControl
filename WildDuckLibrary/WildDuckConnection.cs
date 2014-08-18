using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using USBInterface;

namespace WildDuckLibrary
{
    public class WildDuckConnection
    {
        #region private members
        private USBDevice usb;
        private Timer timer;
        private ReportType _reportType;
        private const ushort VendorID = 0x3995;
        private const ushort ProductID = 0x0020;
        private const int HidReportLength = 16;

        private const int TimesSendCommand = 5;
        private const int CommandResponseTimeOut = 10;
        private int ReportQueque = 0;
        #endregion

        #region Reports
        private Reports _Received;
        public Reports Received
        {
            get
            {
                return _Received;
            }
        }
        public Reports Send;
        #endregion

        public WildDuckConnection(int pollData = 10)
        {
            timer = new Timer();
            timer.Interval = pollData;
            timer.Tick += new EventHandler(UpdateDataTransfer);

            _reportType = ReportType.Joystick;

            usb = new USBDevice(VendorID, ProductID, HidReportLength);
            if(!usb.HIDisOpen)
                throw new Exception("USB Device Couldn't be opened! Check if Freescale Freedom is connected!");
        }
        public void ConnectionStart()
        {
            timer.Enabled = true;
        }
        public ReportType ReceiveReportType
        {
            get
            {
                return _reportType;
            }
            set
            {
                _reportType = value;
                if (value != ReportType.Joystick)
                    ReportQueque = TimesSendCommand; 
            }
        }

        private void UpdateDataTransfer(object sender, EventArgs e)
        {
            SendReport();
            ReceiveReport();
        }

        private void SendReport()
        {
            ReportType report;
            if (ReportQueque > 0)
            {
                report = _reportType;
                ReportQueque--;
            }
            else report = ReportType.Joystick;
            
            switch(report)
            {
                case ReportType.Joystick:
                    SendJoystickReport();
                    break;
                case ReportType.Constans1:
                    break;
                case ReportType.Constans2:
                    break;
                case ReportType.EmergencyLanding:
                    break;
            }
        }

        private void WriteReport(char[] buffer)
        {
            usb.StreamWriteBegin();
            for (int i = 0; i < 10; i++)
                usb.StreamWriteChar(buffer[i]);
            usb.SendBuffer();
        }

        private void SendJoystickReport()
        {
            if (Send.joystickReport.Aileron == 255)
                Send.joystickReport.Aileron = 256;

            if (Send.joystickReport.Elevator == 255)
                Send.joystickReport.Elevator = 256;

            if (Send.joystickReport.Rudder == 255)
                Send.joystickReport.Rudder = 256;

            if (Send.joystickReport.Throttle == 255)
                Send.joystickReport.Throttle = 256;


            if (Send.joystickReport.Aileron >= 1023)
                Send.joystickReport.Aileron = 1023;

            if (Send.joystickReport.Elevator == 1023)
                Send.joystickReport.Elevator = 1023;

            if (Send.joystickReport.Rudder == 1023)
                Send.joystickReport.Rudder = 1023;

            if (Send.joystickReport.Throttle == 1023)
                Send.joystickReport.Throttle = 1023;

            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.Joystick;
            buffer[1] = (char)_reportType;

            buffer[2] = (char)(Send.joystickReport.Throttle & 0xff);
            buffer[3] = (char)(Send.joystickReport.Rudder & 0xff);
            buffer[4] = (char)(Send.joystickReport.Aileron & 0xff);
            buffer[5] = (char)(Send.joystickReport.Elevator & 0xff);

            char temp1 = (char)((char)((Send.joystickReport.Throttle >> 8) << 6) & 0xff);
            char temp2 = (char)((char)((Send.joystickReport.Rudder >> 8) << 4) & 0xff);
            char temp3 = (char)((char)((Send.joystickReport.Aileron >> 8) << 2) & 0xff);
            char temp4 = (char)((char)((Send.joystickReport.Elevator >> 8) << 0) & 0xff);
            char temp5 = (char)((temp1 | temp2 | temp3 | temp4) & 0xff);

            buffer[6] = temp5;
            buffer[7] = (char)Send.joystickReport.ElevationTarget;
            buffer[8] = (char)Send.joystickReport.UChannel;
            buffer[9] = (char)Send.joystickReport.UseTargetMode;
            
            WriteReport(buffer);
        }

        private void ReceiveReport()
        {

        }
    }
}
