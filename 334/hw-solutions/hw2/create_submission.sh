#!/bin/sh
set -e

tar --exclude='hw2' --exclude='*.txt' --exclude='*.o' -czf hw2.tar.gz .
mv hw2.tar.gz ~/lab
