
1����NDKĿ¼�µ�libnn.so libopenvx-nn.so libopenvx.so libsoft-nn.so�滻�� \sdk\out\target\xxxxxx\obj\lib\Ŀ¼

2����NDKĿ¼�ŵ�\sdk\��Ŀ¼�£�����һ����Ŀ¼��

3������NDKĿ¼�µ�example\inference\��ִ��mm�����inference����

4��ͨ��adb���ߣ���inference��ִ�г���ģ���ļ���ͼ���ļ����ϴ��������壬ִ��inference���Գ�����֤�������
   
   ���岽�裺
   
   adb shell
   mkdir /inference-verify/
   exit
   adb push inference /inference-verify/
   adb push ģ���ļ��������ļ� /inference-verify/
   adb shell
   cd /inference-verify/   
   ./inference
   exit
   adb pull /inference-verify/�����������.bin 		
