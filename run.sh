#!/bin/sh
path=`echo "$0" | sed -e "s/[^\/]*$//"`
oldpath=`pwd`
cd $path
./PolygonFury
cd $oldpath
