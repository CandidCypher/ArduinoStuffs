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
import numpy

global GY88_output

class GY88_python():
    def __init__(self, port = "/dev/ttyACM0", baud = "9600"):
        self.port = port
        self.baud = baud
        ser = serial.Serial(self.port, self.baud)
    def readInput
    GY88_ouput = str(val, 'ascii').split(",")
