using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WildDuckLibrary
{
    public enum ReportType
    {
        Joystick = 0x00,
        Sensors = 0x01,
        EmergencyLanding = 0x02,
        Constans1 = 0x03,
        Constans2 = 0x04,
        Constans3 = 0x05
    }
    
    public struct JosytickReport
    {
        public char UseTargetMode;
        public ushort Aileron;
        public ushort Elevator;
        public ushort Throttle;
        public ushort Rudder;
        public ushort ElevationTarget;
        public char UChannel;
    }

    public struct SensorsReport
    {
        public char Elevation;
        public char Front;
        public char Back;
        public char Left;
        public char Right;
    }

    public struct EmegencyLanding
    {
        public char UseEmergencyLanding;
        public char ConnectionTimeOut;
        public char BreakOutOffHeight;
        public ushort DownDecrementCoeficient;
        public char DecrementTime;
    }

    public struct Constants1
    {
        public char UseProtection;
        public char ProtectionDistance;
        public char HS_High_Limit;
        public char HS_Medium_Limit;
        public char HS_Low_Limit;
    }

    public struct Constants2
    {
        public ushort HS_UltraHigh_Correction;
        public ushort HS_High_Correction;
        public ushort HS_Medium_Correction;
        public ushort HS_Low_Correction;
    }

    public struct Constants3
    {
        public char Prot_Medium_Limit;
        public char Prot_Low_Limit;
        public ushort Prot_High_Correction;
        public ushort Prot_Medium_Correction;
        public ushort Prot_Low_Correction;
    }

    public struct Reports
    {
        public JosytickReport joystickReport;
        public SensorsReport sensorsReport;
        public EmegencyLanding emergencyLanding;
        public Constants1 constant1;
        public Constants2 constant2;
        public Constants3 constant3;
    }
}
