#include <CppLinuxSerial/SerialPort.hpp>
#include "RS232.h"
using namespace mn::CppLinuxSerial;

int main() {
    RS232 FH;
    unsigned char controlw[8];
    unsigned char setMode[10];
    unsigned char data[13];
    // Create serial port object and open serial port at 57600 buad, 8 data bits, no parity bit, and one stop bit (8n1)
    SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    // Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
    serialPort.SetTimeout(-1); // Block when reading until any data is received
    serialPort.Open();

    FH.writeControlWord(controlw,0x06);
    string control1(controlw,controlw+8);
    serialPort.Write(control1);
    FH.writeControlWord(controlw,0x07);
    string control2(controlw,controlw+8);
    serialPort.Write(control2);
    FH.writeControlWord(controlw,0x0F);
    string control3(controlw,controlw+8);
    serialPort.Write(control3);

    FH.writeOperationMode(setMode,0x03);
    string Op(setMode,setMode+10);
    serialPort.Write(Op);

    FH.getData(data,-4000,1);
    string Sp(data,data+13);
    serialPort.Write(Sp);

//    std::string readData;
//    while(1){
//        serialPort.Read(readData);
//        cout<<readData<<endl;
//        if(getchar())
//            break;
//    }

    getchar();
    FH.getData(data,0,1);
    string Sp1(data,data+13);
    serialPort.Write(Sp1);
    FH.writeControlWord(controlw,0x0D);
    string control4(controlw,controlw+8);
    serialPort.Write(control4);
    serialPort.Close();


    // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
    //std::string readData;
    //serialPort.Read(readData);

    // Close the serial port
    //serialPort.Close();
}