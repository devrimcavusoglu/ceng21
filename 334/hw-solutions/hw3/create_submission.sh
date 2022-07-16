#!/bin/sh
set -e

tar --exclude='hw3' --exclude='rsc/*' --exclude='fs-root/*' --exclude='fs2-root/*' --exclude='*.img' --exclude="*.bkp" --exclude="*.py" --exclude='*.txt' --exclude='*.o' -czf hw3.tar.gz .
sleep 2
mv hw3.tar.gz ~/lab
