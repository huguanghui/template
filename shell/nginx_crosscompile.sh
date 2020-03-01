#!/usr/bin/env sh

echo "cross compile ..."
ROOT_PATH=`pwd`
CROSS_COMPILE=arm-himix200-linux-gcc
CROSS_HOST=arm-himix200-linux
CROSS_PREFIX=arm-himix200-linux-

NGINX_URL=http://nginx.org/download/nginx-1.16.1.tar.gz
NGINX_PACKAGE=nginx-1.16.1.tar.gz
NGINX_DIR=nginx-1.16.1
NGINX_AUTO_CONFIG=$ROOT_PATH/$NGINX_DIR/objs/ngx_auto_config.h

PCRE_URL=https://ftp.pcre.org/pub/pcre/pcre-8.44.tar.bz2
PCRE_PACKAGE=pcre-8.44.tar.bz2
PCRE_DIR=pcre-8.44

ZLIB_URL=http://prdownloads.sourceforge.net/libpng/zlib-1.2.11.tar.gz
ZLIB_PACKAGE=zlib-1.2.11.tar.gz
ZLIB_DIR=zlib-1.2.11

OPENSSL_URL=https://www.openssl.org/source/openssl-1.1.1d.tar.gz
OPENSSL_PACKAGE=openssl-1.1.1d.tar.gz
OPENSSL_DIR=openssl-1.1.1d

remote_get_content() {
    wget "$1"
#    if curl --version >/dev/null 2>&1
#    then
#        curl -fSL "$1"
#    elif wget --version >/dev/null 2>&1
#    then
#        wget "$1" -0 -     
#    fi
}

# "Prepare Package"

if [ ! -e $NGINX_DIR ]; then
    echo "$NGINX_DIR not found"
    if [ ! -e $NGINX_PACKAGE ]; then
        echo "$NGINX_PACKAGE not found"
        remote_get_content "$NGINX_URL"
    else
        echo "$NGINX_PACKAGE found"
    fi
    tar -xvf $NGINX_PACKAGE
else
    echo "$NGINX_DIR found"
fi

if [ ! -e $ZLIB_DIR ]; then
    echo "$ZLIB_DIR not found"
    if [ ! -e $ZLIB_PACKAGE ]; then
        echo "$ZLIB_PACKAGE not found"
        remote_get_content "$ZLIB_URL"
    else
        echo "$ZLIB_PACKAGE found"
    fi
    tar -xvf $ZLIB_PACKAGE
else
    echo "$ZLIB_DIR found"
fi

if [ ! -e $PCRE_DIR ]; then
    echo "$PCRE_DIR not found"
    if [ ! -e $PCRE_PACKAGE ]; then
        echo "$PCRE_PACKAGE not found"
        remote_get_content "$PCRE_URL"
    else
        echo "$PCRE_PACKAGE found"
    fi
    tar -xvf $PCRE_PACKAGE
else
    echo "$PCRE_DIR found"
fi

if [ ! -e $OPENSSL_DIR ]; then
    echo "$OPENSSL_DIR not found"
    if [ ! -e $OPENSSL_PACKAGE ]; then
        echo "$OPENSSL_PACKAGE not found"
        remote_get_content "$OPENSSL_URL"
    else
        echo "$OPENSSL_PACKAGE found"
    fi
    tar -xvf $OPENSSL_PACKAGE
else
    echo "$OPENSSL_DIR found"
fi

# Config
# 1.交叉编译器不需要进行编辑器检查
sed -i "s/ngx_feature_run=yes/ngx_feature_run=no/g" $NGINX_DIR/auto/cc/name
sed -i "s/ngx_size=\`\$NGX_AUTOTEST\`/ngx_size=4/g" $NGINX_DIR/auto/types/sizeof
# 2.pcre需要添加交叉编译参数
sed -i "s/^PCRE_CONF_OPT=/PCRE_CONF_OPT=--host=$CROSS_HOST/g" $NGINX_DIR/auto/options
# 3.替换openssl库的编译选项
sed -i "s/\&\& .\/config --prefix=/\&\& .\/Configure --prefix=\$ngx_prefix no-shared no-threads --cross-compile-prefix=$CROSS_PREFIX linux-generic32 \\ /g" $NGINX_DIR/auto/lib/openssl/make
# 4.运行配置
cd $ROOT_PATH/$NGINX_DIR;
if [ -d $ROOT_PATH/$NGINX_DIR/.tmp ]; then
    rm -rf $ROOT_PATH/$NGINX_DIR/.tmp       
fi
mkdir -p $ROOT_PATH/$NGINX_DIR/.tmp
./configure \
    --with-cc=$CROSS_HOST-gcc \
    --with-cpp=$CROSS_HOST-cpp \
    --prefix=.tmp \
    --with-pcre=$ROOT_PATH/pcre-8.44 \
    --with-zlib=$ROOT_PATH/zlib-1.2.11 \
    --with-mail \
	--with-http_auth_request_module				\
    --with-openssl=$ROOT_PATH/openssl-1.1.1d \
    --without-http_upstream_zone_module 

# 5.补充宏
cat << END >> $NGINX_AUTO_CONFIG

#ifndef NGX_SYS_NERR
#define NGX_SYS_NERR  132
#endif

END

cat << END >> $NGINX_AUTO_CONFIG

#ifndef NGX_HAVE_SYSVSHM
#define NGX_HAVE_SYSVSHM 1
#endif

END

# Build
make;make install
