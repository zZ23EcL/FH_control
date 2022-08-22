#ifndef FH_MOTOR_LIBRARY_H
#define FH_MOTOR_LIBRARY_H

#include "RS232.h"
#include <pybind11/pybind11.h>
#include <CppLinuxSerial/SerialPort.hpp>

using namespace mn::CppLinuxSerial;
using namespace std;


class Control {
public:
    Control(){}
    ~Control(){}

public:
    void MotorEnable(void);
    void MotorDisable(void);
    void OpenSerial(void);
    void MotorInit(void);
    void PDcontrol();
    void StartC(void);
    void OpenListen(void);
    void OpenL(void);
    bool setP(float);
    bool setD(float);
    float getP(void);
    float getD(void);
    bool setPos(int);
    bool setFlag(bool,bool);
    int getPos(void);
    int getSpeed(void);

private:
    RS232 FH;
    SerialPort serial;
    MiniPID PD;
    unsigned char controlw[8];
    unsigned char setMode[10];
    unsigned char data[13];
    double P;
    double D;
    bool PDflag;
    bool ListenFlag;
    int ActualPos;
    int TargetPos;
    int Speed;
};


#endif //FH_MOTOR_LIBRARY_H
