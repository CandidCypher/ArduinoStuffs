#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 CoroWare Robotics Solutions <corobot.net>
#
# Distributed under terms of the MIT license.
# Author: Cameron Owens
# Date: Oct 20, 2015


"""
This software is provided "AS-IS" and provides no warranty.
"""

from pyfirmata import ArduinoMega
import time
from pyfirmata import INPUT, OUTPUT, SERVO

# Constants to configure the board
port = "/dev/ttyACM0"
board = ArduinoMega(port)
time.sleep(2)

# Initializing Sequence
# servo_tilt = board.get_pin('d:#:o')
# servo_pan = board.get_pin('d:#:o')
board.digital[9].mode = SERVO
board.digital[8].mode = SERVO

board.digital[8].write(0)
board.digital[9].write(0)
i = 0
while i < 180:
    board.digital[8].write(i)
    time.sleep(0.1)
    i += 15
#for i in range(0, 180, 1):
#    board.digital[9].write(i)
#    time.sleep(00.01)
board.digital[9].write(90)

i = 0
while i < 180:
    board.digital[9].write(i)
    time.sleep(0.1)
    i += 15
# for some strange reason doesn't like increments below
#for i in range(0, 180, 1):
#    board.digital[8].write(i)
#    time.sleep(0.001)
board.digital[8].write(90)
board.digital[9].write(90)
