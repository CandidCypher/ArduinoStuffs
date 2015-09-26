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


def Blinky(pin):
    board.digital[pin].write(1)
    sleep(1)
    board.digital[pin].write(0)
    sleep(1)
    print("Blinked")

port = '/dev/ttyACM0'
board = pyfirmata.ArduinoMega(port)

# Define pins
Led = 12

while True:
    Blinky(Led)

board.exit()
