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
import zmq

sensor_app = QtGui.QApplication([])
context = zmq.Context()
socket = context.socket(zmq.SUB)
print "Getting Data"
socket.connect("tcp://10.0.2.15:5556")


def get_value():
    read_val = socket.recv_string()
    lcd.display(read_val)

lcd = QtGui.QLCDNumber()
lcd.setDigitCount(8)

timer = QtCore.QTimer()
timer.timeout.connect(get_value)
timer.start(100)

lcd.show()

sensor_app.exec_()
