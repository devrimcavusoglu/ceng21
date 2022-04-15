#!/bin/sh

tar --exclude='hw1' --exclude='*.txt' --exclude='*.o' -czf hw1.tar.gz .
mv hw1.tar.gz ~/lab
