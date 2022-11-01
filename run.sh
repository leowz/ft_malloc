#!/bin/sh
export DYLD_LIBRARY_PATH=$PWD
export DYLD_INSERT_LIBRARIES=$PWD/libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
export LD_PRELOAD=$PWD/libft_malloc.so
$@
