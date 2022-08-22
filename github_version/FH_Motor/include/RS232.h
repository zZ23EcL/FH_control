//
// Created by zz23ecl on 22-7-23.
//

#ifndef FH_MOTOR_RS232_H
#define FH_MOTOR_RS232_H

#include <iostream>
#include <thread>
#include <chrono>
#include "MiniPID.h"
using namespace std;



class RS232{
public:
    RS232(void){}
    ~RS232(void){}

public:
    uint8_t CalcCRCByte(uint8_t u8Byte,uint8_t u8CRC);
    /** CRC计算
    *
    *
    *  @param:  u8 Byte CRC
    *  @return: u8  CRC
    *  @note:
    *  @see:
    */

    void writeControlWord(uint8_t temp[],uint8_t );
    /*******************************************/
    /** 生成向FaulHaber写控制字的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8   controlword  0f 0d 06 07....
    *  @return:
    *  @note:
    *  @see:
    */

    void writeOperationMode(uint8_t temp[],int8_t type);
    /*******************************************/
    /** 生成向FaulHaber修改控制模式的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  u8  type 控制模式的种类
    *               1：PP
    *               3：PV
    *  @return:
    *  @note:
    *  @see:
    */

    void getData(uint8_t temp[],int32_t data,uint8_t type);
    /*******************************************/
    /** 生成向FaulHaber写数据的字符串
    *
    *
    *  @param:
    *  u8* temp 储存生成的数组
    *  int data 需要写入的数据
    *  u8  type 数据类型
    *               1：目标速度
    *               2：目标位置
    *  @return:
    *  @note:
    *  @see:
    */

    void dealRXbuf(string&,int& v);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :to get the RXbuf in pattern from the str
    *  int&v       :to get the data from in RXbuf
    *  @return:
    *  void
    *  @note:
    *  @see:
    */

    int getActualPos(string&);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  string& str :the RXbuf which need to deal with
    *  @return:
    *  int the actual position
    *  @note:
    *  @see:
    */

    string setPosRequest(void);
    /*******************************************/
    /** get realtime ActualPos
    *
    *
    *  @param:
    *  @return:
    *  get the buffer str of PosRequest
    *  @note:
    *  @see:
    */


};




#endif //FH_MOTOR_RS232_H
