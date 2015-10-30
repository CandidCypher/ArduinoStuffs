#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Virtual>
#
# Distributed under terms of the MIT license.

"""
This Python Script reads data from a soil moisture sensor
"""

from pyfirmata import ArduinoMega, util
from pyfirmata import INPUT
import time

port = "/dev/ttyACM0"
board = ArduinoMega(port)
sensor = board.get_pin('a:0:i')
# board.analog[0].mode = INPUT
it = util.Iterator(board)
it.start()
time.sleep(1)


def get_value():
    '''
    This method takes an integer input for the pin to be read. Appropriate
    values range 0-15 for analog pins.
    '''
    read_val = sensor.read()
    print(read_val)
    time.sleep(1.0)

while True:
    get_value()
