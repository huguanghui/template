# SD卡测试

## 华商SD卡测试

Test finished without errors.
You can now delete the test files \*.h2w or verify them again.
Writing speed: 15.3 MByte/s
Reading speed: 17.0 MByte/s
H2testw v1.4

## 安全检查

```bash
fsck.fat -n -v /dev/mmcblk0p1
```

## 坏簇扫描

```bash
fsck.fat -t -v /dev/mmcblk0p1
```
