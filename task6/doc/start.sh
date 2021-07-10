#!/bin/sh
service mosquitto start &
cd project && ./main &
mosquitto_sub -t detection
