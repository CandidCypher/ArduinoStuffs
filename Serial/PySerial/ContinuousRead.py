#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <www.candidcypher.com>
#
# Distributed under terms of the MIT license.

"""

"""

import serial
import time


ser = serial.Serial('/dev/ttyACM0', 9600)
while 1:
    start = time.time()
    val = ser.readline()
    format_input = str(val, 'ascii').split(",")
    AcX = format_input[0]
    AcY = format_input[1]
    AcZ = format_input[2]
    print("AcX {}, AcY {}, AcZ {}".format(AcX, AcY, AcZ))
    end = time.time()
    time_taken = end - start
    print("Time Elapsed:", time_taken)
