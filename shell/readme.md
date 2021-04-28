# shell 脚本的技巧

## find -print0 和 xargs -0原理及用法

> find 默认对结果是使用换行符 xargs 识别字符段标识默认也是使用换行
> find -print0 和 xargs -0将标识换成NULL
