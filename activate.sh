#!/bin/bash

if [ ! -e /tmp/my_malloc ]
then
    mkdir /tmp/my_malloc
fi
cp libmy_malloc.so /tmp/my_malloc/libmy_malloc.so

export LD_PRELOAD=/tmp/my_malloc/libmy_malloc.so
export LD_LIBRARY_PATH=/tmp/my_malloc/
