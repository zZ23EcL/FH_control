//
// Created by zz23ecl on 2022/7/20.
//

#ifndef FUNC_TEST_MINIPID_H
#define FUNC_TEST_MINIPID_H

class MiniPID{
public:
    MiniPID(int, int);
    MiniPID(int, int, int);
    void setP(int);
    void setD(int);
    void setF(int);
    void setPID(int, int);
    void setPID(int, int, int);
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
    int P;
    int D;
    int F;

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

#endif //FUNC_TEST_MINIPID_H
