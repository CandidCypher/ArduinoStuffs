#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Virtual>
#
# Distributed under terms of the MIT license.

"""
This is a sketch that uses Firmata and Python to blink an LED
"""

# Standard imports
import pyfirmata
from time import sleep

# Blink Method


def MotorSpin(pin1, pin2)
    board.analog.
    sleep(1)
    board.digital[pin].write(0)
    sleep(1)
    print("Blinked")

port = '/dev/ttyACM0'
board = pyfirmata.ArduinoMega(port)

# Define pins
Motor_A = 7
Motor_B = 6

while True:
    Blinky(Led)

board.exit()
