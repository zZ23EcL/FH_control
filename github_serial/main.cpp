#include <CppLinuxSerial/SerialPort.hpp>
#include "RS232.h"
#include <unistd.h>
using namespace mn::CppLinuxSerial;

void PDcontrol(SerialPort& serial,bool&,int& a,int& d);
/*******************************************/
/** calculate the pidout
*
*
*  @param:
*  SerialPort serial serial info
*  bool Pdflag to control the stop of PD
*  int  actualpos
*  int  demandpos
*  @return:
*  @note:
*  @see:
*/

void SerialListen(SerialPort& serial,bool& ListenFlag,int& value);
void Enable(SerialPort& serial);
void Disable(SerialPort& serial);

int main() {
    RS232 FH;
    unsigned char controlw[8];
    unsigned char setMode[10];

    bool PDflag(true);
    bool ListenFlag(true);
    int value;
    int TargetPos=30000;//Position
    int f=0;


    // Create serial port object and open serial port at 57600 buad, 8 data bits, no parity bit, and one stop bit (8n1)
    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    // Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
    serialPort.SetTimeout(-1); // Block when reading until any data is received
    serialPort.Open();

    /**********************************/
    /*            enable              */
    /**********************************/
    Enable(serialPort);

    /**********************************/
    /*            PV Mode             */
    /**********************************/
    FH.writeOperationMode(setMode,0x03);
    string Op(setMode,setMode+10);
    serialPort.Write(Op);
    printf("Set PV Mode...\n");

    /**********************************/
    /*  thread 1 to listen for seiral */
    /*  thread 2 to calc PIDout       */
    /**********************************/
    printf("Start the thread of Listen and PID\n");
    thread Listen(SerialListen,ref(serialPort),ref(ListenFlag),ref(value));
    thread PID(PDcontrol,ref(serialPort),ref(PDflag),ref(value),ref(TargetPos));


    /**********************************/
    /* Disable Motor and close serial */
    /**********************************/
    while(1){
        printf("main value is %d\n",value);
        cin>>f;
        if(f!=0)
            break;
        sleep(5);
    }

    Disable(serialPort);

    Listen.join();
    PID.join();
    serialPort.Close();
    return 0;
}

void PDcontrol(SerialPort& serial,bool& flag,int& ActualPos,int& DemandPos){
    MiniPID PD(0.05,0);
    int SpeedControl;
    RS232 R;
    unsigned char data[13];
    PD.setOutputLimits(32700);
    while(flag){
        SpeedControl=PD.getOutput(ActualPos,DemandPos);
        printf("now PDout is %d\n",SpeedControl);
        printf(" AND the demand pos is %d\n",DemandPos);
        printf(" AND the actual pos is %d\n",ActualPos);
        R.getData(data,SpeedControl,1);
        string Sp(data,data+13);
        serial.Write(Sp);
        this_thread::sleep_for(chrono::milliseconds(10));
        //can not lease than 10
    }
}

void SerialListen(SerialPort& serial,bool& ListenFlag,int& value){
    while(ListenFlag){
        string readData;
        RS232 R;
        serial.Write(R.setPosRequest());
        serial.Read(readData);
        R.dealRXbuf(readData,value);
        //printf("now actual pos is: %d\n",value);
        //this_thread::sleep_for(chrono::milliseconds(1));
    }

}

void Enable(SerialPort& serial){
    RS232 FH;
    unsigned char controlw[8];
    FH.writeControlWord(controlw,0x06);
    string control1(controlw,controlw+8);
    serial.Write(control1);
    FH.writeControlWord(controlw,0x07);
    string control2(controlw,controlw+8);
    serial.Write(control2);
    FH.writeControlWord(controlw,0x0F);
    string control3(controlw,controlw+8);
    serial.Write(control3);
    printf("Enable the Motor...\n");
}

void Disable(SerialPort& serial){
    RS232 FH;
    unsigned char controlw[8];
    FH.writeControlWord(controlw,0x0D);
    string control1(controlw,controlw+8);
    serial.Write(control1);
    printf("Disable the Motor...\n");
}