#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import os.path as p
import sys

version = sys.version_info[ 0:3 ]

print (type(version))
print ("python verson", version)

if version > (2, 7, 1):
    print ("more than 2.7.1")

DIR_LOCAL = p.dirname(p.abspath(__file__))
print (DIR_LOCAL)

DIR_OF_OLD_LIB = p.join(DIR_LOCAL, 'python')
print (DIR_OF_OLD_LIB)

pparg = sys.argv[ 1: ]
print (pparg)

def CheckAll( args, **kwargs):
    print (args, kwargs)

CheckAll( [sys.executable] + sys.argv[ 1: ] )
