```
ssh -N -o ExitOnForwardFailure=yes -o ServerAliveInterval=60 -L 127.0.0.1:19190:127.0.0.1:9190 -p 3000 hgh@1.13.20.3
```

```
git config --global url."git@github.com:".insteadOf "https://github.com/"
```

nc -zv 192.168.168.31 9190

http://192.168.168.243:9091

ssh -N -o ExitOnForwardFailure=yes -o ServerAliveInterval=60 -L 127.0.0.1:19091:192.168.168.243:9091 -p 6022 hgh@1.13.20.3
