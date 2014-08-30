#include "mbed.h"
#include "esc.h"
#include "Receiver.h"

#ifdef PC_UART_DEBUG
Serial pc(USBTX, USBRX); // tx, rx
#endif

RFInfoReceiver reporter(true);
DigitalOut Led(LED2);

ESC Aileron(D5);
ESC Elevator(D4);
ESC Throtle(D3);
ESC Rudder(D2);
ESC UChannel(D8);

void UpdateESC()
{
    ControllerReport report = reporter.GetControllerReport();
    
    Aileron = (float)(((float)report.Aileron)/1022.0f);        
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

void ShowControllerReport()
{
#ifdef PC_UART_DEBUG
	ControllerReport report = reporter.GetControllerReport();
    pc.printf("#### Report #%d\r\n",reporter.bufPointer);
	pc.printf("Throttle #%d\r\n", report.Throttle);
    pc.printf("Rudder #%d\r\n",report.Rudder);
    pc.printf("Aileron #%d\r\n",report.Aileron);
    pc.printf("Elevator #%d\r\n",report.Elevator);
    pc.printf("Elevation #%d\r\n\r\n",report.ElevationTarget);
    pc.printf("UChannel #%d\r\n\r\n",report.UChannel);
#endif
} 

void ShowBufferReport()
{
#ifdef PC_UART_DEBUG
	pc.printf("BUFFER %d,%d,%d,%d,%d,%d,%d,%d,%d,%d \r\n",
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
#endif
}

void ShowSensorsReport()
{

}

int main() {

    while(1) 
    {
		Led = !Led;
		UpdateESC();
		ShowControllerReport();
		//ShowBufferReport();

		//reporter.SendReport();
		
		wait_ms(REFRESH_TIMEOUT_MS);
    }
}
