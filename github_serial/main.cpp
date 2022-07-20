#include <CppLinuxSerial/SerialPort.hpp>
#include "RS232.h"

using namespace mn::CppLinuxSerial;

void PDcontrol(SerialPort serial,bool,int a,int d);
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

void SerialListen(SerialPort serial,bool ListenFlag,int& value);

int main() {
    RS232 FH;
    unsigned char controlw[8];
    unsigned char setMode[10];

    bool PDflag(true);
    bool ListenFlag(true);
    int value;
    int TargetPos=30000;//Position


    // Create serial port object and open serial port at 57600 buad, 8 data bits, no parity bit, and one stop bit (8n1)
    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    // Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
    serialPort.SetTimeout(-1); // Block when reading until any data is received
    serialPort.Open();

    /**********************************/
    /*            enable              */
    /**********************************/
    FH.writeControlWord(controlw,0x06);
    string control1(controlw,controlw+8);
    serialPort.Write(control1);
    FH.writeControlWord(controlw,0x07);
    string control2(controlw,controlw+8);
    serialPort.Write(control2);
    FH.writeControlWord(controlw,0x0F);
    string control3(controlw,controlw+8);
    serialPort.Write(control3);

    /**********************************/
    /*            PV Mode             */
    /**********************************/
    FH.writeOperationMode(setMode,0x03);
    string Op(setMode,setMode+10);
    serialPort.Write(Op);

    /**********************************/
    /*  thread 1 to listen for seiral */
    /*  thread 2 to calc PIDout       */
    /**********************************/
    thread Listen(SerialListen,serialPort,ListenFlag,ref(value));
    //thread PID(PDcontrol,serialPort,PDflag,value,TargetPos);


    /**********************************/
    /* Disable Motor and close serial */
    /**********************************/
    getchar();
    FH.writeControlWord(controlw,0x0D);
    string control4(controlw,controlw+8);
    serialPort.Write(control4);
    Listen.join();
    //PID.join();
    serialPort.Close();
    return 0;
}

void PDcontrol(SerialPort serial,bool flag,int ActualPos,int DemandPos){
    MiniPID PD(20,1);
    int SpeedControl;
    RS232 R;
    unsigned char data[13];
    PD.setOutputLimits(32700);
    while(flag){
        SpeedControl=PD.getOutput(ActualPos,DemandPos);
        //printf("now PDout is %d\n",SpeedControl);
        R.getData(data,SpeedControl,1);
        string Sp(data,data+13);
        serial.Write(Sp);
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void SerialListen(SerialPort serial,bool ListenFlag,int& value){

    while(ListenFlag){
        string readData;
        RS232 R;
        serial.Read(readData);//fangzai xianchengzhong youwenti
        //terminate called after throwing an instance of 'std::system_error'
        //  what():  Bad address
        //R.dealRXbuf(readData,value);
        //this_thread::sleep_for(chrono::milliseconds(5));
    }

}