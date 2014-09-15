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
        Constans3 = 0x05,

        Nothing = 0x0f
    }
    
    public struct JosytickReport
    {
        public byte UseTargetMode;
        public ushort Aileron;
        public ushort Elevator;
        public ushort Throttle;
        public ushort Rudder;
        public ushort ElevationTarget;
        public byte UChannel;
    }

    public struct SensorsReport
    {
        public byte Elevation;
        public byte Front;
        public byte Back;
        public byte Left;
        public byte Right;
        public byte Debug1;
        public byte Debug2;
        public byte Debug3;
    }

    public struct EmegencyLanding
    {
        public byte UseEmergencyLanding;
        public byte ConnectionTimeOut;
        public byte BreakOutOffHeight;
        public ushort DownDecrementCoeficient;
        public byte DecrementTime;
    }

    public struct Constants1
    {
        public byte UseProtection;
        public byte ProtectionDistance;
        public byte HS_High_Limit;
        public byte HS_Medium_Limit;
        public byte HS_Low_Limit;
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
        public byte Prot_Medium_Limit;
        public byte Prot_Low_Limit;
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
