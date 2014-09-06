#ifndef _REPORTS_H_
#define _REPORTS_H_

enum 
{
	Joystick = 0x00,
	Sensors = 0x01,
	cEmergencyLanding = 0x02,
	cConstants1 = 0x03,
	cConstants2 = 0x04,
	cConstants3 = 0x05,

	Nothing = 0xfe;
};

typedef struct
{
    unsigned short Throttle;
    unsigned short Rudder;
    unsigned short Aileron;
    unsigned short Elevator;
    unsigned char ElevationTarget;
    unsigned char UChannel;
    unsigned char UseTargetMode;
}ControllerReport;

typedef struct
{
    unsigned char Elevation;
    unsigned char Front;
    unsigned char Back;
    unsigned char Left;
    unsigned char Right;
}SensorsReport;

typedef struct
{
    unsigned char UseEmergencyLanding;
    unsigned char ConnectionTimeOut;
    unsigned char BreakOutOffHeight;
    unsigned short DownDecrementCoeficient;
    unsigned char DecrementTime;
}EmergencyLanding;

typedef struct
{
    unsigned char UseProtection;
    unsigned char ProtectionDistance;
    unsigned char HS_High_Limit;
    unsigned char HS_Medium_Limit;
    unsigned char HS_Low_Limit;
}Constants1;

typedef struct
{
     unsigned short HS_UltraHigh_Correction;
     unsigned short HS_High_Correction;
     unsigned short HS_Medium_Correction;
     unsigned short HS_Low_Correction;
}Constants2;

typedef struct
{
    unsigned char Prot_Medium_Limit;
    unsigned char Prot_Low_Limit;
    unsigned short Prot_High_Correction;
    unsigned short Prot_Medium_Correction;
    unsigned short Prot_Low_Correction;
}Constants3;

typedef struct
{
    char X,Y,Z;
}IMUReport;


#endif