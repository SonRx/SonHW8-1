#!/bin/bash

# 2
config-pin -a p9.12 out
config-pin -a p8.16 in

g++ control_GPIO.cpp -o control_GPIOcpp

