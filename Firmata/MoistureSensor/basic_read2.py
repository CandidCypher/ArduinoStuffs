#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Virtual>
#
# Distributed under terms of the MIT license.

"""
This is a second attempt to reading analog
"""

from pyfirmata import ArduinoMega, util
import time
import os

port = '/dev/ttyACM0'
board = ArduinoMega(port)
time.sleep(5)
it = util.Iterator(board)
it.start()
sensor = board.get_pin('a:0:i')

try:
    while True:
        value = sensor.read()
        print value
        time.sleep(1)
except KeyboardInterrupt:
    board.exit()
    os._exit()
