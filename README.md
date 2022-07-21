# FH_control
new version FaulHaber Motor Control By RS232 in Linux
安装方法 按找cppserial中的方法先把头文件和库添加到usr/local/include 和usr/local/lib中，然后参考现在的cmakelist.txt设置
# 存在的问题0719
串口发送不是一直能使用，时断时续，串口读取还没处理
# 0720
在线程中调用serial进行收发报错，发现是传递类参数的问题，等待解决
# 0721
PC端的位置控制基本完成，现在需要重新创建为动态库文件，并为python的引用留出接口
