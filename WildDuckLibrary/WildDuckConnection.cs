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
        private ReportType _RequestReport;

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

        public WildDuckConnection(int pollData = 20)
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
        public ReportType SendReportType
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
        public ReportType ReceiveReportType
        {
            get
            {
                return _RequestReport;
            }
            set
            {
                _RequestReport = value;
            }
        }

        private void UpdateDataTransfer(object sender, EventArgs e)
        {
            SendReport();
            //ReceiveReport();
        }

        #region Send Reports
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
                    SendConstants1();
                    break;
                case ReportType.Constans2:
                    SendConstants2();
                    break;
                case ReportType.Constans3:
                    SendConstants3();
                    break;
                case ReportType.EmergencyLanding:
                    SendEmegencyLandingReport();
                    break;
            }
        }
        private void WriteReport(char[] buffer)
        {
            usb.StreamWriteBegin();
            for (int i = 0; i < buffer.Length; i++)
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


            if (Send.joystickReport.Aileron == 511)
                Send.joystickReport.Aileron = 512;

            if (Send.joystickReport.Elevator == 511)
                Send.joystickReport.Elevator = 512;

            if (Send.joystickReport.Rudder == 511)
                Send.joystickReport.Rudder = 512;

            if (Send.joystickReport.Throttle == 511)
                Send.joystickReport.Throttle = 512;


            if (Send.joystickReport.Aileron >= 1022)
                Send.joystickReport.Aileron = 1022;

            if (Send.joystickReport.Elevator >= 1022)
                Send.joystickReport.Elevator = 1022;

            if (Send.joystickReport.Rudder >= 1022)
                Send.joystickReport.Rudder = 1022;

            if (Send.joystickReport.Throttle >= 1022)
                Send.joystickReport.Throttle = 1022;

            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.Joystick;
            buffer[1] = (char)_RequestReport;

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
        private void SendEmegencyLandingReport()
        {
            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.EmergencyLanding;
            buffer[1] = (char)_RequestReport;
            buffer[2] = Send.emergencyLanding.UseEmergencyLanding;
            buffer[3] = Send.emergencyLanding.ConnectionTimeOut;
            buffer[4] = Send.emergencyLanding.BreakOutOffHeight;
            buffer[5] = (char)(Send.emergencyLanding.DownDecrementCoeficient & 0xff);
            buffer[6] = (char)((Send.emergencyLanding.DownDecrementCoeficient >> 8) & 0xff);
            buffer[7] = Send.emergencyLanding.DecrementTime;
            buffer[8] = (char)0x00;
            buffer[9] = (char)0x00;
            WriteReport(buffer);
        }
        private void SendConstants1()
        {
            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.Constans1;
            buffer[1] = (char)_RequestReport;
            buffer[2] = Send.constant1.UseProtection;
            buffer[3] = Send.constant1.ProtectionDistance;
            buffer[4] = Send.constant1.HS_High_Limit;
            buffer[5] = Send.constant1.HS_Medium_Limit;
            buffer[6] = Send.constant1.HS_Low_Limit;
            buffer[7] = (char)0x00;
            buffer[8] = (char)0x00;
            buffer[9] = (char)0x00;
            WriteReport(buffer);
        }
        private void SendConstants2()
        {
            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.Constans1;
            buffer[1] = (char)_RequestReport;
            buffer[2] = (char)((Send.constant2.HS_UltraHigh_Correction >> 0) & 0x0ff);
            buffer[3] = (char)((Send.constant2.HS_UltraHigh_Correction >> 8) & 0x0ff);
            buffer[4] = (char)((Send.constant2.HS_High_Correction >> 0) & 0x0ff);
            buffer[5] = (char)((Send.constant2.HS_High_Correction >> 8) & 0x0ff);
            buffer[6] = (char)((Send.constant2.HS_Medium_Correction >> 0) & 0x0ff);
            buffer[7] = (char)((Send.constant2.HS_Medium_Correction >> 8) & 0x0ff);
            buffer[8] = (char)((Send.constant2.HS_Low_Correction >> 0) & 0x0ff);
            buffer[9] = (char)((Send.constant2.HS_Low_Correction >> 8) & 0x0ff);
            WriteReport(buffer);
        }
        private void SendConstants3()
        {
            char[] buffer = new char[10];
            buffer[0] = (char)ReportType.Constans1;
            buffer[1] = (char)_RequestReport;
            buffer[2] = Send.constant3.Prot_Medium_Limit;
            buffer[3] = Send.constant3.Prot_Low_Limit;
            buffer[4] = (char)((Send.constant3.Prot_High_Correction >> 0) & 0xff);
            buffer[5] = (char)((Send.constant3.Prot_High_Correction >> 8) & 0xff);
            buffer[6] = (char)((Send.constant3.Prot_Medium_Correction >> 0) & 0xff);
            buffer[7] = (char)((Send.constant3.Prot_Medium_Correction >> 8) & 0xff);
            buffer[8] = (char)((Send.constant3.Prot_Low_Correction >> 0) & 0xff);
            buffer[9] = (char)((Send.constant3.Prot_Low_Correction >> 8) & 0xff);
            WriteReport(buffer);
        }
        #endregion

        #region Receive Reports
        private void ReceiveReport()
        {
            int i;
            char[] buffer = new char[10];
            usb.ReciveBuffer();
            usb.StreamReadBegin();

            for (i = 1; i < buffer.Length; i++)
            {
                buffer[i] = usb.StreamReadChar();
            }

            switch((ReportType)buffer[0])
            {
                case ReportType.Joystick:
                    DecodeJoystickReport(buffer);
                    break;
                case ReportType.Sensors:
                    DecodeSensorsReport(buffer);
                    break;
                case ReportType.Constans1:
                    DecodeConstants1(buffer);
                    break;
                case ReportType.Constans2:
                    DecodeConstants2(buffer);
                    break;
                case ReportType.Constans3:
                    DecodeConstants3(buffer);
                    break;
                case ReportType.EmergencyLanding:
                    DecodeEmergencyLandingReport(buffer);
                    break;
            }

        }
        private void DecodeJoystickReport(char[] buffer)
        {
            char temp;
            temp = (char)((buffer[6] >> 6) & 0x03);
            _Received.joystickReport.Throttle = (ushort)((buffer[2]) | (temp << 8));
            
            temp = (char)((buffer[6] >> 4) & 0x03);
            _Received.joystickReport.Rudder = (ushort)((buffer[3]) | (temp << 8));

            temp = (char)((buffer[6] >> 2) & 0x03);
            _Received.joystickReport.Aileron = (ushort)((buffer[4]) | (temp << 8));

            temp = (char)((buffer[6] >> 0) & 0x03);
            _Received.joystickReport.Elevator = (ushort)((buffer[5]) | (temp << 8));

            _Received.joystickReport.ElevationTarget = buffer[7];
            _Received.joystickReport.UChannel = buffer[8];
            _Received.joystickReport.UseTargetMode = buffer[9];
        }
        private void DecodeSensorsReport(char[] buffer)
        {
            _Received.sensorsReport.Elevation = buffer[2];
            _Received.sensorsReport.Front = buffer[3];
            _Received.sensorsReport.Back = buffer[4];
            _Received.sensorsReport.Left = buffer[5];
            _Received.sensorsReport.Right = buffer[6];
        }
        private void DecodeEmergencyLandingReport(char[] buffer)
        {
            _Received.emergencyLanding.UseEmergencyLanding = buffer[2];
            _Received.emergencyLanding.ConnectionTimeOut = buffer[3];
            _Received.emergencyLanding.BreakOutOffHeight = buffer[4];
            _Received.emergencyLanding.DownDecrementCoeficient = (char)((buffer[6]<<8) | buffer[5]);
            _Received.emergencyLanding.DecrementTime = buffer[7];
        }
        private void DecodeConstants1(char[] buffer)
        {
            _Received.constant1.UseProtection = buffer[2];
            _Received.constant1.ProtectionDistance = buffer[3];
            _Received.constant1.HS_High_Limit = buffer[4];
            _Received.constant1.HS_Medium_Limit = buffer[5];
            _Received.constant1.HS_Low_Limit = buffer[6];
        }
        private void DecodeConstants2(char[] buffer)
        {
            _Received.constant2.HS_UltraHigh_Correction = (ushort)((buffer[3]<<8) | buffer[2]);
            _Received.constant2.HS_High_Correction = (ushort)((buffer[5] << 8) | buffer[4]);
            _Received.constant2.HS_Medium_Correction = (ushort)((buffer[7] << 8) | buffer[6]);
            _Received.constant2.HS_Low_Correction = (ushort)((buffer[9] << 8) | buffer[8]);
        }
        private void DecodeConstants3(char[] buffer)
        {
            _Received.constant3.Prot_Medium_Limit = buffer[2];
            _Received.constant3.Prot_Low_Limit = buffer[3];
            _Received.constant3.Prot_High_Correction = (ushort)((buffer[5] << 8) | buffer[4]);
            _Received.constant3.Prot_Medium_Correction = (ushort)((buffer[7] << 8) | buffer[6]);
            _Received.constant3.Prot_Low_Correction = (ushort)((buffer[9] << 8) | buffer[8]);
        }
        #endregion
    }
}
