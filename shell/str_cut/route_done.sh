# 查看eth0相关的路由个数
cnt=`route -n | grep "eth0" -c`

# 查看IP参数
route -n | grep eth0 -m 1 | awk -F " " '{print $1}'
