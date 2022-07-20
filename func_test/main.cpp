#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "MiniPID.h"

using namespace std;

int getActualPos(string&);
void dealRXbuf(string&);
void createRandData(bool,int&);
void PDcontrol(bool,int a,int d);

int main() {

    uint8_t testbuf[]={0x53,0x07,0x01,0x01,0x60,0x64,0x45,0x45,0x45,
    0x53,0x08,0x01,0x01,0x66,0x6f,0x00,0x22,0xff,0x45,
    0x53,0x0b,0x01,0x01,0x64,0x60,0x00,0x39,0x30,0x00,0x00,0xff,0x45,0x00,0x00};
    string s(testbuf,testbuf+sizeof(testbuf));
    /*******************************************************/
    dealRXbuf(s);
    int data;
    int Pos=30000;
    bool PDflag(true);
    bool ListenFlag(true);
    thread Listen(createRandData,ListenFlag,ref(data));
    thread PID(PDcontrol,PDflag,data,Pos);

    Listen.join();
    PID.join();
    while(1){
        char flag;
        cin>>flag;
        if(flag=='s'){
            PDflag=true;
            ListenFlag= true;
        }
        if(flag=='e'){
            PDflag= false;
            ListenFlag= false;
            break;
        }
    }
    cout<<"end please use any key to end"<<endl;
    getchar();
    return 0;
}

int getActualPos(string& str) {
    int v = 999999999;
    if(str.length()==13){
        auto i=str.begin();
        uint8_t length = uint8_t(*(i+1));
        uint8_t node = uint8_t(*(i+2));
        uint8_t command = uint8_t(*(i+3));
        uint8_t indexLB=uint8_t(*(i+4));
        uint8_t indexHB=uint8_t(*(i+5));
        uint16_t index=indexLB+(indexHB<<8);
        uint8_t subindex=uint8_t(*(i+6));
        if(index==0x6064)
            v=uint8_t(*(i+7))+(uint8_t(*(i+8))<<8)+(uint8_t(*(i+9))<<16)+(uint8_t(*(i+10))<<24);
    }
    return v;
}

void dealRXbuf(string& s){
    string RXbuf;
    int numS;
    int numE;
    int data;
    bool search(true);
    while(search){
        numS=s.find_first_of('S');
        numE=s.find_first_of('E');
        if(0<=numS&&numS<=s.size()&&0<=numE&&numE<=s.size()){
            for(int i=0;i<6;i++){
                //6的原因是最多int 4个 加CRC+E=6，其实不可能int4个0x45时的CRC是45
                string buf(s,numS,numE+1);
                if(uint8_t(buf[1])==numE-numS-1){
                    RXbuf=buf;
                    data=getActualPos(RXbuf);
                    if(data!=999999999)
                        printf("%d",data);
                    s.erase(numS,numE-numS+1);
                    break;
                }
                else{
                    numE=s.find_first_of('E',numE+1);
                }
            }
        }
        else
            search= false;
    }
}

void createRandData(bool flag,int& data){
    while(flag){
        srand(time(0));
        data=rand()%3000000;
    }
}

void PDcontrol(bool flag,int ActualPos,int DemandPos){
    MiniPID PD(20,1);
    int SpeedControl;
    PD.setOutputLimits(32700);
    while(flag){
        SpeedControl=PD.getOutput(ActualPos,DemandPos);
        printf("now PDout is %d\n",SpeedControl);
        //在这里writespeed
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}