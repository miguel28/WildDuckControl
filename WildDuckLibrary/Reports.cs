using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WildDuckLibrary
{
    public enum ReportType
    {
        Joystick,
        Sensors,
        EmergencyLanding,
        Constans1,
        Constans2,
        Constans3
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

    public struct Reports
    {
        public JosytickReport joystickReport;
        public SensorsReport sensorsReport;
        public EmegencyLanding emergencyLanding;
        public Constants1 constant1;
        public Constants2 constant2;
    }
}
