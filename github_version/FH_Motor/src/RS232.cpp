//
// Created by zz23ecl on 22-7-23.
//
#include "RS232.h"

//CRC cal
uint8_t RS232::CalcCRCByte(uint8_t u8Byte, uint8_t u8CRC) {
    uint8_t i;
    u8CRC = u8CRC ^ u8Byte;
    for (i = 0; i <8 ; i++) {
        if (u8CRC & 0x01) {
            u8CRC = (u8CRC >> 1) ^ 0xD5;
        }
        else {
            u8CRC >>= 1;
        }
    }
    return u8CRC;
}

//写控制字
void RS232::writeControlWord(uint8_t temp[], uint8_t ctrlwlb) {
    temp[0] = 'S';
    temp[1] = 0x06;
    temp[2] = 0x01;
    temp[3] = 0x04;
    temp[4] = ctrlwlb;
    temp[5] = 0x00;
    uint8_t CRC = 0xFF;
    for (uint8_t i = 1; i <6; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[6] = CRC;
    temp[7] = 'E';
}

//写控制模式
void RS232::writeOperationMode(uint8_t temp[],int8_t type){
    uint8_t length = 0x08;
    temp[0] = 'S';
    temp[1] = 0x08;
    temp[2] = 0x01;
    temp[3] = 0x02;
    temp[4] = 0x60;
    temp[5] = 0x60;
    temp[6] = 0x00;
    if(type==1)
        temp[7]=0x01;
    if(type==3)
        temp[7] =0X03;
    uint8_t CRC = 0xFF;
    for (uint8_t i = 1; i <length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[8] =CRC;
    temp[9]='E';
}
//写目标数据
void RS232::getData(uint8_t temp[], int32_t data, uint8_t type) {
    uint8_t length = 0x0b;
    uint8_t command = 0x02;
    uint8_t NodeNum = 0x01;
    uint8_t indexHB;
    uint8_t indexLB;
    switch (type) {
        //速度
        case 1: {
            indexLB = 0xFF;
            indexHB = 0x60;
            break;
        }
            //位置
        case 2: {
            indexLB = 0x7A;
            indexHB = 0x60;
            break;
        }
        default: {
            printf("Erorr Data Type!");
            break;
        }
    }

    temp[0] = 'S';
    temp[1] = length;
    temp[2] = NodeNum;
    temp[3] = command;
    temp[4] = indexLB;
    temp[5] = indexHB;
    temp[6] = 0x00;//subindex
    /********************************************/
    /*  这里有个问题是写入数据是按低位写还是高位优先写？ */
    /*               问题解决，按低位写            */
    /********************************************/
    //先按照低位先的来
    temp[7] = data & 0xff;
    temp[8] = data >> 8 & 0xff;
    temp[9] = data >> 16 & 0xff;
    temp[10] = data >> 24 & 0xff;
    uint8_t CRC = 0xFF;
    for (int i = 1; i < length; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[11] = CRC;
    temp[12] = 'E';
}


int RS232::getActualPos(string& str) {
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

void RS232::dealRXbuf(string& s,int& v){
    string RXbuf;
    int numS;
    int numE;
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
                    int datatemp=getActualPos(RXbuf);
                    if(datatemp!=999999999)
                        v=datatemp;
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

string RS232::setPosRequest(void){
    uint8_t temp[13];
    temp[0]='S';
    temp[1]=0x07;
    temp[2]=0x01;
    temp[3]=0x01;
    temp[4]=0x64;
    temp[5]=0x60;
    temp[6]=0x00;
    uint8_t CRC = 0xFF;
    for (int i = 1; i < 7; i++)
        CRC = CalcCRCByte(temp[i], CRC);
    temp[7]=CRC;
    temp[8]='E';
    string str(temp,temp+9);
    return str;
}

