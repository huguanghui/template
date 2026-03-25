## 定位程序运行过程内存占用情况

### busybox中的time -v

> 物理内存占用,包换代码段.bss,定位程序运行过程内存占用情况,参考性不大

### ubuntu下的memusage工具

> 统计比较准确, maloc和free次数判定少一次, 可以作为参考

```bash
> memusage ./output/x86/bin/jpeg_resize_v2 ./res/main_t3.jpg ./res/out.jpg 640 360
input_file: ./res/main_t3.jpg, output_file: ./res/out.jpg, w: 640, h: 360
Input: 2880x1620, Target: 640x360
Application transferred too few scanlines
Resize failed

Memory usage summary: heap total: 903592, heap peak: 214312, stack peak: 1744
         total calls   total memory   failed calls
 malloc|        392         903592              0
realloc|          0              0              0  (nomove:0, dec:0, free:0)
 calloc|          0              0              0
   free|        391         902568
Histogram for block sizes:
  160-175             2  <1%
  304-319             4   1%
  464-479             2  <1%
 1024-1039            1  <1%
 1296-1311            5   1%
 1680-1695            1  <1%
 1888-1903            1  <1%
 1920-1935          360  91% ==================================================
 2576-2591            2  <1%
 4096-4111            2  <1%
 4112-4127            1  <1%
 5776-5791            2  <1%
 6336-6351            1  <1%
 8640-8655            1  <1%
10256-10271           1  <1%
14416-14431           2  <1%
16304-16319           1  <1%
20112-20127           1  <1%
21408-21423           1  <1%
57616-57631           1  <1%
```

## valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./output/x86/bin/jpeg_resize_v2 ./res/main_t3.jpg ./res/out.jpg 640 360
```

```bash
valgrind --tool=massif --stacks=yes ./output/x86/bin/jpeg_resize_v2 ./res/main_t3.jpg ./res/out.jpg 640 360
# 会生成一个 massif.out.1601884 文件
ms_print massif.out.1601884 > report.txt
# 带GUI页面
sudo apt install massif-visualizer
massif-visualizer massif.out.12345
```
