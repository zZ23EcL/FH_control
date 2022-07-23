//
// Created by zz23ecl on 22-7-23.
//

#ifndef FH_MOTOR_MINIPID_H
#define FH_MOTOR_MINIPID_H

class MiniPID{
public:
    MiniPID(){}
    MiniPID(float, float);
    MiniPID(float, float, float);
    void setP(float);
    void setD(float);
    void setF(float);
    void setPID(float, float);
    void setPID(float, float, float);
    void setOutputLimits(int);
    void setOutputLimits(int,int);
    void setDirection(bool);
    void setSetpoint(int);
    void reset();
    void setOutputRampRate(int);
    void setSetpointRange(int);
    void setOutputFilter(int);
    int getOutput();
    int getOutput(int);
    int getOutput(int, int);


private:
    int clamp(int, int, int);
    bool bounded(int, int, int);
    void checkSigns();
    void init();
    float P;
    float D;
    float F;

    int maxError;
    int errorSum;

    int maxOutput;
    int minOutput;

    int setpoint;

    int lastActual;

    bool firstRun;
    bool reversed;

    int outputRampRate;
    int lastOutput;

    int outputFilter;

    int setpointRange;
};


#endif //FH_MOTOR_MINIPID_H
