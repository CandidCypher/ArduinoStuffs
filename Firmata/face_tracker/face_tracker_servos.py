#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2015 cameron <cameron@Megatron-Dev>
#
# Distributed under terms of the MIT license.

"""
This is the second script for building the face tracker.
"""

import cv2
import pyfirmata
import time

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

port = "/dev/ttyACM0"
board = pyfirmata.ArduinoMega(port)
board.digital[11].mode = pyfirmata.SERVO  # Pan Servo
board.digital[10].mode = pyfirmata.SERVO  # Tilt Servo
board.digital[11].write(90)
board.digital[10].write(90)

pan_increment = 0
tilt_increment = 0
video_capture = cv2.VideoCapture(0)

while True:
    ret, frame = video_capture.read()
    gray_image = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray_image,
                                          scaleFactor=1.1,
                                          minNeighbors=5,
                                          minSize=(30, 30),
                                          flags=cv2.cv.CV_HAAR_SCALE_IMAGE
                                          )
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 2)
        center_point = ((x+(x+w))/2, (y+(y+h))/2)
        cv2.rectangle(frame, center_point, center_point, (255, 0, 0), 2)

        # Pan Servo Control
        if center_point[0] > 320:
            pan_increment += 10
            if 90+pan_increment >= 180:
                pan_increment = 89
            board.digital[11].write(90+pan_increment)
            time.sleep(0.1)
        elif center_point[0] < 320:
            pan_increment -= 10
            if 90+pan_increment <= 0:
                pan_increment = -89
            board.digital[11].write(90+pan_increment)
            time.sleep(0.1)
        else:
            board.digital[11].write(90)

        # Tilt Servo Control
        if center_point[1] > 240:
            tilt_increment += 10
            if 90+tilt_increment >= 180:
                tilt_increment = 89
            board.digital[10].write(90+tilt_increment)
        elif center_point[1] < 240:
            tilt_increment -= 10
            if 90+tilt_increment <= 0:
                tilt_increment = -89
            board.digital[10].write(90+tilt_increment)
        else:
            board.digital[10].write(90)
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
