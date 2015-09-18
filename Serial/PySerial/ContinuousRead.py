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
ser = serial.Serial('/dev/ttyACM0', 9600)
while 1:
    val = ser.readline()
    format_input = str(val, 'ascii').split(",")
    print(format_input)
    print("AcX: {}".format(format_input[0]))
