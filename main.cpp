#include <iostream>

using namespace std;

int getActualPos(const string& str);
//string 作为参数输入的问题还没解决
int main() {
    uint8_t t[]={0x53,0x0b,0x01,0x01,0x60,0x64,0x00,0x39,0x30,0x00,0x00,0xff,0x45};
    string str(t,t+sizeof (t));
    int x= getActualPos(str);
    cout<<x<<endl;
//    uint8_t testbuf[]={0x53,0x07,0x01,0x01,0x60,0x64,0x45,0x45,0x45,
//    0x53,0x08,0x01,0x01,0x66,0x6f,0x00,0x22,0xff,0x45,
//    0x53,0x0b,0x01,0x01,0x60,0x64,0x00,0x39,0x30,0x00,0x00,0xff,0x45,0x00,0x00};
//    string s(testbuf,testbuf+sizeof(testbuf));
//    /*******************************************************/
//    string RXbuf;
//    int numS;
//    int numE;
//    bool search(true);
//    while(search){
//        numS=s.find_first_of('S');
//        numE=s.find_first_of('E');
//        if(0<numS&&numS<s.size()&&0<numE&&numE<s.size()){
//            for(int i=0;i<6;i++){
//                //6的原因是最多int 4个 加CRC+E=6，其实不可能int4个0x45时的CRC是45
//                string buf(s,numS,numE+1);
//                if(uint8_t(buf[1])==numE-numS-1){
//                    RXbuf=buf;
//                    //printf("%d", getActualPos(RXbuf));
//                    s.erase(numS,numE-numS+1);
//                    break;
//                }
//                else{
//                    numE=s.find_first_of('E',numE+1);
//                }
//            }
//        }
//        else
//            search= false;
//
//
//        //直接以string返回，然后去函数里用迭代器读
//        //printf("%d",getActualPos(RXbuf));
//        cout<<endl;
//    }

    return 0;
}

int getAcutalPos(const string& str) {
    int v = 999999999;
//    if(str.length()==13){
//        auto i=str.begin();
//        uint8_t length = uint8_t(*i+1);
//        uint8_t node = uint8_t(*i+2);
//        uint8_t command = uint8_t(*i+3);
//        uint16_t index=uint8_t(*i+4)+uint8_t(*i+5)<<8;
//        uint8_t subindex=uint8_t(*i+6);
//        if(index==0x6064)
//            v=uint8_t(*i+6)+uint8_t(*i+7)<<8+uint8_t(*i+8)<<16+uint8_t(*i+9)<<24;
//    }
    return v;
}