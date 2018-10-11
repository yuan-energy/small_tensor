#!/usr/bin/env bash
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
echo '------------------------------------------'
echo 'ltensor'
cd $SCRIPT_DIR/ltensor
/usr/bin/time -f "%P %M" make
echo ' '
echo ' '

echo '------------------------------------------'
echo 'libxsmm'
cd $SCRIPT_DIR/libxsmm
/usr/bin/time -f "%P %M" make
echo ' '
echo ' '

echo '------------------------------------------'
echo 'smalltensor'
cd $SCRIPT_DIR/smalltensor
/usr/bin/time -f "%P %M" make
echo ' '
echo ' '

