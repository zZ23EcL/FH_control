//
// Created by zz23ecl on 22-7-23.
//

#include "Control.h"
namespace py = pybind11;
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
    serial.SetDevice("/dev/ttyUSB0");
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
    PD.setPID(0.05,0);//the key is let f=0
}

void Control::PDcontrol() {
    while(PDflag){
        Speed=PD.getOutput(ActualPos,TargetPos);
//        printf("now PDout is %d\n",Speed);
//        printf(" AND the demand pos is %d\n",TargetPos);
//        printf(" AND the actual pos is %d\n",ActualPos);
        FH.getData(data,Speed,1);
        string Sp(data,data+13);
        serial.Write(Sp);
        this_thread::sleep_for(chrono::milliseconds(10));
        //this_thread::sleep_for(chrono::seconds(2));
        //can not lease than 10ms
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
        //     printf("in L APOS is %d\n",ActualPos);
        // this_thread::sleep_for(chrono::seconds(1));
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

float Control::getP(void) {
    return P;
}

float Control::getD(void) {
    return D;
}

bool Control::setPos(int Pos) {
    TargetPos=Pos;
    return 1;
}

bool Control::setFlag(bool Pflag, bool Lflag) {
    PDflag=Pflag;
    ListenFlag=Lflag;
    return 1;
}

int Control::getPos(void) {
    return ActualPos;
}

int Control::getSpeed(void) {
    return Speed;
}


PYBIND11_MODULE(FH_Motor,m)
{
py::class_<Control>(m,"Control")
    .def(py::init<>())
    .def("MotorEnable",&Control::MotorEnable)
    .def("MotorDisable",&Control::MotorDisable)
    .def("OpenSerial",&Control::OpenSerial)
    .def("MotorInit",&Control::MotorInit)
    .def("StartC",&Control::StartC)
    .def("OpenL",&Control::OpenL)
    .def("SetFlag",&Control::setFlag)
    .def("SetPos",&Control::setPos)
    .def("GetPos",&Control::getPos)
    .def("SetP",&Control::setP)
    .def("SetD",&Control::setD)
    .def("GetP",&Control::getP)
    .def("GetP",&Control::getD);

}