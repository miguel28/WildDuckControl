using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Management; 

namespace WildDuckLibrary
{
   
    public class WildDuckConnection
    {
        #region private members
        private SerialPort serial;
        private Timer timer, timer2;
        private ReportType _reportType;
        private ReportType _RequestReport;

        private const ushort VendorID = 0x3995;
        private const ushort ProductID = 0x0020;
        private const int HidReportLength = 16;

        private const int TimesSendCommand = 5;
        private const int CommandResponseTimeOut = 10;
        private int ReportQueque = 0;

        private byte _LandOff = 0;
        private byte _LandOn = 0;
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
        public bool Arm
        {
            set
            {
                _LandOff = value ? (byte)(1 << 4) : (byte)0;
            }
        }
        public bool DisArm
        {
            set
            {
                _LandOn = value ? (byte)(1 << 5) : (byte)0;
            }
        }
        #endregion

        public WildDuckConnection(int pollData = 50)
        {
            timer = new Timer();
            timer.Interval = pollData;
            timer.Tick += new EventHandler(UpdateDataTransfer);
            timer2 = new Timer();
            timer2.Interval = 10;
            timer2.Tick += new EventHandler(UpdateDataTransfer2);


            _reportType = ReportType.Joystick;

            serial = new SerialPort();
            serial.ReadBufferSize = 32;
            serial.PortName = GetPortName();
            serial.BaudRate = 19200;
            serial.Open();

        }
        public void ConnectionStart()
        {
            timer.Enabled = true;
            timer2.Enabled = true;
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
        private void UpdateDataTransfer2(object sender, EventArgs e)
        {
            //SendReport();
            ReceiveReport();
        }
        private string GetPortName()
        {
            string ret = "";
            using (var searcher = new ManagementObjectSearcher("SELECT * FROM WIN32_SerialPort"))
            {
                string[] portnames = SerialPort.GetPortNames();
                var ports = searcher.Get().Cast<ManagementBaseObject>().ToList();
                var tList = (from n in portnames
                             join p in ports on n equals p["DeviceID"].ToString()
                             select n + " - " + p["Caption"]).ToList();

                foreach (string iport in tList)
                {
                    if (iport.Contains("Silicon"))
                    {
                        ret = iport.Substring(0, 5);
                        ret.Replace(" ", "");
                        break;
                    }
                }
            }
            return ret;
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
        private void WriteReport(byte[] buffer)
        {
            buffer[10] = (byte)0xff;
            buffer[11] = (byte)0xff;
            serial.Write(buffer, 0, 12);
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

            byte[] buffer = new byte[12];
            buffer[0] = (byte)((byte)(ReportType.Joystick) | (_LandOn) | (_LandOff));
            //buffer[0] = (byte)(ReportType.Joystick);
            buffer[1] = (byte)_RequestReport;

            buffer[2] = (byte)(Send.joystickReport.Throttle & 0xff);
            buffer[3] = (byte)(Send.joystickReport.Rudder & 0xff);
            buffer[4] = (byte)(Send.joystickReport.Aileron & 0xff);
            buffer[5] = (byte)(Send.joystickReport.Elevator & 0xff);

            byte temp1 = (byte)((byte)((Send.joystickReport.Throttle >> 8) << 6) & 0xff);
            byte temp2 = (byte)((byte)((Send.joystickReport.Rudder >> 8) << 4) & 0xff);
            byte temp3 = (byte)((byte)((Send.joystickReport.Aileron >> 8) << 2) & 0xff);
            byte temp4 = (byte)((byte)((Send.joystickReport.Elevator >> 8) << 0) & 0xff);
            byte temp5 = (byte)((temp1 | temp2 | temp3 | temp4) & 0xff);

            buffer[6] = temp5;
            buffer[7] = (byte)Send.joystickReport.ElevationTarget;
            buffer[8] = (byte)Send.joystickReport.UChannel;
            buffer[9] = (byte)Send.joystickReport.UseTargetMode;

            WriteReport(buffer);

            _LandOn = (byte)0;
            _LandOff = (byte)0;
        }
        private void SendEmegencyLandingReport()
        {
            byte[] buffer = new byte[12];
            buffer[0] = (byte)ReportType.EmergencyLanding;
            buffer[1] = (byte)ReportType.EmergencyLanding;
            buffer[2] = (byte)Send.emergencyLanding.UseEmergencyLanding;
            buffer[3] = (byte)Send.emergencyLanding.ConnectionTimeOut;
            buffer[4] = (byte)Send.emergencyLanding.BreakOutOffHeight;
            buffer[5] = (byte)(Send.emergencyLanding.DownDecrementCoeficient & 0xff);
            buffer[6] = (byte)((Send.emergencyLanding.DownDecrementCoeficient >> 8) & 0xff);
            buffer[7] = (byte)Send.emergencyLanding.DecrementTime;
            buffer[8] = (byte)0x00;
            buffer[9] = (byte)0x00;
            WriteReport(buffer);
        }
        private void SendConstants1()
        {
            byte[] buffer = new byte[12];
            buffer[0] = (byte)ReportType.Constans1;
            buffer[1] = (byte)ReportType.Constans1;
            buffer[2] = (byte)Send.constant1.UseProtection;
            buffer[3] = (byte)Send.constant1.ProtectionDistance;
            buffer[4] = (byte)Send.constant1.HS_High_Limit;
            buffer[5] = (byte)Send.constant1.HS_Medium_Limit;
            buffer[6] = (byte)Send.constant1.HS_Low_Limit;
            buffer[7] = (byte)Send.constant1.DangerProtectionDivide;
            buffer[8] = (byte)0x00;
            buffer[9] = (byte)0x00;
            WriteReport(buffer);
        }
        private void SendConstants2()
        {
            if (Send.constant2.HS_UltraHigh_Correction == 255 || Send.constant2.HS_UltraHigh_Correction == 511)
                Send.constant2.HS_UltraHigh_Correction++;

            if (Send.constant2.HS_High_Correction == 255 || Send.constant2.HS_High_Correction == 511)
                Send.constant2.HS_High_Correction++;

            if (Send.constant2.HS_Medium_Correction == 255 || Send.constant2.HS_Medium_Correction == 511)
                Send.constant2.HS_Medium_Correction++;

            if (Send.constant2.HS_Low_Correction == 255 || Send.constant2.HS_Low_Correction == 511)
                Send.constant2.HS_Low_Correction++;

            byte[] buffer = new byte[12];
            buffer[0] = (byte)ReportType.Constans2;
            buffer[1] = (byte)ReportType.Constans2;
            buffer[2] = (byte)((Send.constant2.HS_UltraHigh_Correction >> 0) & 0x0ff);
            buffer[3] = (byte)((Send.constant2.HS_UltraHigh_Correction >> 8) & 0x0ff);
            buffer[4] = (byte)((Send.constant2.HS_High_Correction >> 0) & 0x0ff);
            buffer[5] = (byte)((Send.constant2.HS_High_Correction >> 8) & 0x0ff);
            buffer[6] = (byte)((Send.constant2.HS_Medium_Correction >> 0) & 0x0ff);
            buffer[7] = (byte)((Send.constant2.HS_Medium_Correction >> 8) & 0x0ff);
            buffer[8] = (byte)((Send.constant2.HS_Low_Correction >> 0) & 0x0ff);
            buffer[9] = (byte)((Send.constant2.HS_Low_Correction >> 8) & 0x0ff);
            WriteReport(buffer);
        }
        private void SendConstants3()
        {
            byte[] buffer = new byte[12];
            buffer[0] = (byte)ReportType.Constans3;
            buffer[1] = (byte)ReportType.Constans3;
            buffer[2] = (byte)Send.constant3.Prot_Medium_Limit;
            buffer[3] = (byte)Send.constant3.Prot_Low_Limit;
            buffer[4] = (byte)((Send.constant3.Prot_High_Correction >> 0) & 0xff);
            buffer[5] = (byte)((Send.constant3.Prot_High_Correction >> 8) & 0xff);
            buffer[6] = (byte)((Send.constant3.Prot_Medium_Correction >> 0) & 0xff);
            buffer[7] = (byte)((Send.constant3.Prot_Medium_Correction >> 8) & 0xff);
            buffer[8] = (byte)((Send.constant3.Prot_Low_Correction >> 0) & 0xff);
            buffer[9] = (byte)((Send.constant3.Prot_Low_Correction >> 8) & 0xff);
            WriteReport(buffer);
        }
        #endregion

        #region Receive Reports
        private void ReceiveReport()
        {
            int size = serial.BytesToRead;
            if (size < 13)
                return;
            byte[] data = new byte[size];
            byte[] RevBuffer = new byte[size];
            serial.Read(data, 0, data.Length);
           
            for(int i = 0; i< size-1; i++)
            {
                if(data[i] == (byte)0xff && data[i+1] == (byte)0xff && i>=10)
                {
                    for(int j = 0; j< 12;j++)
                    {
                        RevBuffer[j] = data[i - 10 + j];
                    }
                    DecodeReport(RevBuffer);
                }
            }

        }

        private void DecodeReport(byte[] buffer)
        {
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

        private void DecodeJoystickReport(byte[] buffer)
        {
            byte temp;
            temp = (byte)((buffer[6] >> 6) & 0x03);
            _Received.joystickReport.Throttle = (ushort)((buffer[2]) | (temp << 8));
            
            temp = (byte)((buffer[6] >> 4) & 0x03);
            _Received.joystickReport.Rudder = (ushort)((buffer[3]) | (temp << 8));

            temp = (byte)((buffer[6] >> 2) & 0x03);
            _Received.joystickReport.Aileron = (ushort)((buffer[4]) | (temp << 8));

            temp = (byte)((buffer[6] >> 0) & 0x03);
            _Received.joystickReport.Elevator = (ushort)((buffer[5]) | (temp << 8));

            _Received.joystickReport.ElevationTarget = buffer[7];
            _Received.joystickReport.UChannel = buffer[8];
            _Received.joystickReport.UseTargetMode = buffer[9];
        }
        private void DecodeSensorsReport(byte[] buffer)
        {
            _Received.sensorsReport.Elevation = buffer[2];
            _Received.sensorsReport.Front = buffer[3];
            _Received.sensorsReport.Back = buffer[4];
            _Received.sensorsReport.Left = buffer[5];
            _Received.sensorsReport.Right = buffer[6];
            _Received.sensorsReport.Debug1 = buffer[7];
            _Received.sensorsReport.Debug2 = buffer[8];
            _Received.sensorsReport.Debug3 = buffer[9];
        }
        private void DecodeEmergencyLandingReport(byte[] buffer)
        {
            _Received.emergencyLanding.UseEmergencyLanding = buffer[2];
            _Received.emergencyLanding.ConnectionTimeOut = buffer[3];
            _Received.emergencyLanding.BreakOutOffHeight = buffer[4];
            _Received.emergencyLanding.DownDecrementCoeficient = (byte)((buffer[6]<<8) | buffer[5]);
            _Received.emergencyLanding.DecrementTime = buffer[7];
        }
        private void DecodeConstants1(byte[] buffer)
        {
            _Received.constant1.UseProtection = buffer[2];
            _Received.constant1.ProtectionDistance = buffer[3];
            _Received.constant1.HS_High_Limit = buffer[4];
            _Received.constant1.HS_Medium_Limit = buffer[5];
            _Received.constant1.HS_Low_Limit = buffer[6];
            _Received.constant1.DangerProtectionDivide = buffer[7];
        }
        private void DecodeConstants2(byte[] buffer)
        {
            _Received.constant2.HS_UltraHigh_Correction = (ushort)((buffer[3]<<8) | buffer[2]);
            _Received.constant2.HS_High_Correction = (ushort)((buffer[5] << 8) | buffer[4]);
            _Received.constant2.HS_Medium_Correction = (ushort)((buffer[7] << 8) | buffer[6]);
            _Received.constant2.HS_Low_Correction = (ushort)((buffer[9] << 8) | buffer[8]);
        }
        private void DecodeConstants3(byte[] buffer)
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
