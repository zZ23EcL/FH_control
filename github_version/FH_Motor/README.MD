# Record 

## Q1
当使用pybind类的时候，封装有问题，具体表现在
```c++
PYBIND11_MODULE(tt,m)
{
py::class_<test>(m,"test")
.def(py::init<>())
.def("tp",&test::tp);

}
```
直接调用后没有相应的输出  
...调用这些类需要加上() 例如调用项目tt中的test类中的tp函数需要  
```python
import tt

T=tt.test()
T.tp()

```
# Q2
当尝试打开串口时，出现error：  
Could not open device /dev/ttyUSB0. Is the device name correct and do you have read/write permission?  
应当是没有权限  
解决方法是每次电脑重新启动后在命令行中输入：  
sudo chmod 777 /dev/ttyUSB0

# Q3
数据传输bug测试  
直接传递没有达到传递的效果    
例如
```python
    FH=FH_Motor.Control()
    FH.SetPos(1000)
    print(FH.GetPos())
```
ans is 32762,并未赋值成功,需要引用传递之类的操作
通过测试发现没有大问题，是setpos 和getpos操作的变量不一致导致的

