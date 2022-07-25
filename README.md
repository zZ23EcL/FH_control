# FH_control
new version FaulHaber Motor Control By RS232 in Linux
安装方法 按找cppserial中的方法先把头文件和库添加到usr/local/include 和usr/local/lib中，然后参考现在的cmakelist.txt设置
# 存在的问题0719
串口发送不是一直能使用，时断时续，串口读取还没处理
# 0720
在线程中调用serial进行收发报错，发现是传递类参数的问题，等待解决
# 0721
PC端的位置控制基本完成，现在需要重新创建为动态库文件，并为python的引用留出接口  
两个问题：1.是否需要设置python版本的路径 2.pycharm中的包路径为啥不对


链接：https://rec.ustc.edu.cn/share/43b9d9d0-0be7-11ed-a129-d3e825eca4e8
