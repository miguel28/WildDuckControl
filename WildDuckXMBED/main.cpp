#include "mbed.h"
#include "esc.h"
#include "Receiver.h"


//#include "SRF05.h"
//#include "L3GD20.h"
//#include "SRF10.h"
//#include "SRF08.h"
//SRF10 highSensor(D7, D6);
//SRF08 sensor(A4,A5, 0xE0);//0xe0
//SRF08 sensor(D7,D6, 0xE0);//0xe0
//SRF08 sensor(D14,D15, 0xE0);//0xe0
//L3GD20 gyro(D14,D15);

Serial pc(USBTX, USBRX); // tx, rx
RFInfoReceiver reporter(true);

//SRF05 sensor(D9,D8);
DigitalOut Led(LED2);

ESC Aileron(D5);
ESC Elevator(D4);
ESC Throtle(D3);
ESC Rudder(D2);
ESC UChannel(D8);

int ssensor = 255;
float ax, ay,az;

void UpdateESC()
{
    ControllerReport report = reporter.GetControllerReport();
    
    Aileron = (float)( ((float)report.Aileron)/1022.0f);        
    Throtle= (float)((float)(report.Throttle)/1022.0f);  
    Elevator = (float)((float)(report.Elevator)/1022.0f);  
    Rudder = (float)((float)(report.Rudder)/1022.0f);  
    UChannel = (float)((float)(report.UChannel)/254.0f);
    
    Aileron();
    Throtle();    
    Elevator();
    Rudder();
    UChannel();
}

void ShowReport()
{
    ControllerReport report = reporter.GetControllerReport();
    pc.printf("#### Report #%d\r\n",reporter.bufPointer);
	pc.printf("Throttle #%d\r\n", report.Throttle);
    pc.printf("Rudder #%d\r\n",report.Rudder);
    pc.printf("Aileron #%d\r\n",report.Aileron);
    pc.printf("Elevator #%d\r\n",report.Elevator);
    pc.printf("Elevation #%d\r\n\r\n",report.ElevationTarget);
    pc.printf("UChannel #%d\r\n\r\n",report.UChannel);

    /*pc.printf("BUFFER %d,%d,%d,%d,%d,%d,%d,%d,%d,%d \r\n",
        reporter.buffer[0],
        reporter.buffer[1],
        reporter.buffer[2],
        reporter.buffer[3],
        reporter.buffer[4],
        reporter.buffer[5],
        reporter.buffer[6],
        reporter.buffer[7],
        reporter.buffer[8],
        reporter.buffer[9]);
    //pc.printf("Range #%d Error: %d\n\n",highSensor.CurrentRange, highSensor.Error);
    //pc.printf("Range #%d\r\n\r\n",sensor.read());
    
    /*sensor.startRanging();
    ssensor = sensor.getRange();
    pc.printf("Range #%d\r\n",ssensor);  */  
    
    //gyro.read(&ax,&ay,&az);
    //pc.printf("X: %3.3f, Y: %3.3f, Z: %3.3f\r\n", ax,ay,az);
    
} 

int main() {
    pc.baud(115200);
    
    while(1) 
    {
        UpdateESC();
        ShowReport();
        wait_ms(19);
		//Led = 0;
		//wait_ms(19);
		//Led = 1;
    }
}
