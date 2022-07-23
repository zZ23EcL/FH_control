#include "Control.h"

void Control::MotorEnable() {
    FH.writeControlWord(controlw,0x06);
    string control1(controlw,controlw+8);
    serial.Write(control1);
    FH.writeControlWord(controlw,0x07);
    string control2(controlw,controlw+8);
    serial.Write(control2);
    FH.writeControlWord(controlw,0x0F);
    string control3(controlw,controlw+8);
    serial.Write(control3);
}

void Control::MotorDisable() {
    FH.writeControlWord(controlw,0x0D);
    string control1(controlw,controlw+8);
    serial.Write(control1);
}

void Control::OpenSerial() {
    serial.SetDevice("/dec/ttyUSB0");
    serial.SetBaudRate(BaudRate::B_115200);
    serial.SetNumDataBits(NumDataBits::EIGHT);
    serial.SetNumStopBits(NumStopBits::ONE);
    serial.SetParity(Parity::NONE);
    serial.SetTimeout(-1);
    serial.Open();
}

void Control::MotorInit() {
    //Set PV Mode
    FH.writeOperationMode(setMode,0x03);
    string Op(setMode,setMode+10);
    serial.Write(Op);
    PD.setOutputLimits(32700);
    PD.setPID(0.05,0);
}

void Control::PDcontrol() {
    while(PDflag){
        Speed=PD.getOutput(ActualPos,TargetPos);
//        printf("now PDout is %d\n",SpeedControl);
//        printf(" AND the demand pos is %d\n",TargetPos);
//        printf(" AND the actual pos is %d\n",ActualPos);
        FH.getData(data,Speed,1);
        string Sp(data,data+13);
        serial.Write(Sp);
        this_thread::sleep_for(chrono::milliseconds(10));
        //can not lease than 10
    }
}

void Control::StartC() {
    PDflag=true;
    thread PDC(&Control::PDcontrol,this);
    PDC.detach();
}

void Control::OpenListen() {
    while(ListenFlag){
        string readData;
        serial.Write(FH.setPosRequest());
        serial.Read(readData);
        FH.dealRXbuf(readData,ActualPos);
    }
}
void Control::OpenL(){
    ListenFlag=true;
    thread SL(&Control::OpenListen,this);
    SL.detach();
}

bool Control::setP(float PP) {
    P=PP;
    return 1;
}

bool Control::setD(float DD) {
    D=DD;
    return 1;
}

bool Control::setFlag(bool Pflag, bool Lflag) {
    PDflag=Pflag;
    ListenFlag=Lflag;
    return 1;
}

int Control::getPos() {
    return ActualPos;
}

int Control::getSpeed() {
    return Speed;
}