#!/bin/sh
set -e

tar --exclude='hw2' --exclude='*.txt' --exclude='*.o' -czf hw1.tar.gz .
mv hw1.tar.gz ~/lab
