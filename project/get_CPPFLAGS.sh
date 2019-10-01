#!/bin/sh

make print-CPPFLAGS | grep 'CPPFLAGS = .*' | sed 's/CPPFLAGS = //'
