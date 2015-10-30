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
import zmq


port = '/dev/ttyACM0'
board = ArduinoMega(port)
time.sleep(5)
it = util.Iterator(board)
it.start()
sensor = board.get_pin('a:0:i')
context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://10.0.2.15:5556")


def get_value():
    discard_value = sensor.read()
    time.sleep(0.1)
    value = sensor.read()
    return value


def stream_value(message):
    socket.send(b'{}'.format(str(message)))

try:
    while True:
        value = get_value()
        stream_value(value)
        print "Sent Value"
        print value
        print type(value)
        time.sleep(1)
except KeyboardInterrupt:
    board.exit()
    os._exit()
