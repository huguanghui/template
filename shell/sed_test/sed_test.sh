#!/usr/bin/env sh

VER=`grep "define NGINX_VERSION" txt/test | sed -e 's/^.*"\(.*\)".*/\1/'`
echo "VER=$VER"

NGINX_URL=http://nginx.org/download/nginx-1.16.1.tar.gz
echo "NGINX_URL=$NGINX_URL"

#NGINX_PACKAGE=`echo $NGINX_URL | sed -e 's/^.*\/\/\(.*\)\/\(.*\)/\2/'`
NGINX_PACKAGE=`echo $NGINX_URL | sed -e 's/^.*\/\(.*\)/\1/'`
echo "NGINX_PACKAGE=$NGINX_PACKAGE"

NGINX_DIR=`echo $NGINX_PACKAGE | sed -e 's/^\(.*\)\..*\..*/\1/'`
echo "NGINX_DIR=$NGINX_DIR"
