
1、将NDK目录下的libnn.so libopenvx-nn.so libopenvx.so libsoft-nn.so替换到 \sdk\out\target\xxxxxx\obj\lib\目录

2、将NDK目录放到\sdk\根目录下（或任一级子目录）

3、进入NDK目录下的example\inference\，执行mm，完成inference编译

4、通过adb工具，将inference可执行程序及模型文件、图像文件，上传到开发板，执行inference测试程序并验证输出数据
   
   具体步骤：
   
   adb shell
   mkdir /inference-verify/
   exit
   adb push inference /inference-verify/
   adb push 模型文件和数据文件 /inference-verify/
   adb shell
   cd /inference-verify/   
   ./inference
   exit
   adb pull /inference-verify/所有输出数据.bin 		
