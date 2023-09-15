#!/bin/sh

if [ -f ./compile_commands.json ];then
    echo "compile_commands.json exited"
    sed -i "s/\"cc\"/\"arm-linux-gnueabihf-gcc\"/g" ./compile_commands.json
    sed -i "s/-fno-ipa-sra//g" ./compile_commands.json
    sed -i "s/-fno-var-tracking-assignments//g" ./compile_commands.json
    sed -i "s/-mno-thumb-interwork//g" ./compile_commands.json
    sed -i "s/-fconserve-stack//g" ./compile_commands.json
fi

