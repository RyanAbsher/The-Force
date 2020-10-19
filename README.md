# The-Force
 Raspberry Pi and Arduino Based Exhibit Show Controller
 
## Introduction
Shortly before we shut down operations due to Covid-19, one of the exhibits at my place of employment had a hardware failure. After we re-opened, due to financial hardships, we were unable
to cover the cost of having the exhibit repaired. I would require all new hardware as well as new software. I decided to see what I could do with the equipment on hand.

## Hardware
The exhibit uses 3 synchronized monitors to show a video, uses multiple DMX512 controlled lights, has an RS-232 controlled timer, and has multiple audio outputs. I decided to use 3 Raspberry Pis and
an Arduino Nano to replicate the original hardware.

I designed and etched a PCB that would hold the Arduino, as well as acting as the connection point for all of the different pieces. Each RPi has a cable which connects to this board. The DMX and RS-232 cables also plug into this board.
I put all of the requisite hardware for each of these protocols onboard.

## Software
When the user presses the start button, a python program on the center RPi detects it. It then signals the other 2 RPis to start the show on it's command. The center RPi also signals the Arduino to start the 
timer and begin the light show.
