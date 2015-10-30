#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Virtual>
#
# Distributed under terms of the MIT license.

"""
This module starts to integrate the analog read of a sensor into PySide
"""

from PySide import QtGui, QtCore
from pyfirmata import ArduinoMega, util
import time

sensor_app = QtGui.QApplication([])
port = "/dev/ttyACM0"
board = ArduinoMega(port)
sensor = board.get_pin('a:0:i')
iterator = util.Iterator(board)
iterator.start()
time.sleep(1)


def get_value():
    read_val = sensor.read()
    lcd.display(read_val)

lcd = QtGui.QLCDNumber()
lcd.setDigitCount(8)

timer = QtCore.QTimer()
timer.timeout.connect(get_value)
timer.start(1000)

lcd.show()

sensor_app.exec_()
