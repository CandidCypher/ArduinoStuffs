#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Dev>
#
# Distributed under terms of the MIT license.

"""
This is an experiement to create a breathing LED using Firmata and an
Arduino
"""

from pyfirmata import ArduinoMega
from pyfirmata import OUTPUT, INPUT, PWM
import time

port = "/dev/ttyACM0"
board = ArduinoMega(port)

ledPin = board.get_pin('d:2:p')


def increase_range(start, stop, step):
    r = start
    while r < stop:
        yield r
        r += step


def decrease_range(start, stop, step):
    down_step = start
    while down_step > stop:
        yield down_step
        down_step -= step


def Breathing(speed):
    i = increase_range(0.1, 1, 0.1)
    for x in i:
        ledPin.write(x)
        time.sleep(speed)
    i = decrease_range(1, 0.1, 0.1)
    for x in i:
        ledPin.write(x)
        time.sleep(speed)

while True:
    Breathing(0.055555)
