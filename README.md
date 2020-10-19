# The-Force
 Raspberry Pi and Arduino Based Exhibit Show Controller
 
## Introduction
Shortly before we shut down operations due to Covid-19, one of the exhibits at my place of employment had a hardware failure. After we re-opened, due to financial hardships, we were unable
to cover the cost of having the exhibit repaired. It would require all new hardware as well as new software. I decided to see what I could do with the equipment on hand.

## Hardware
![PCB Render](https://github.com/RyanAbsher/The-Force/blob/main/Photos/1.jpg?raw=true)

The exhibit uses 3 synchronized monitors to show a video, uses multiple DMX512 controlled lights, has an RS-232 controlled timer, and has multiple audio outputs. I decided to use 3 Raspberry Pis and
an Arduino Nano to replicate the original hardware.

I designed and etched a PCB that would hold the Arduino, as well as acting as the connection point for all of the different pieces. Each RPi has a cable which connects to this board. The DMX and RS-232 cables also plug into this board.
I put all of the requisite hardware for each of these protocols onboard.

For simply asthetic reasons I made the board fit the same form factor and mounting holes as a Raspberry Pi.

I laser cut the acrylic shelves and 3D printed the white plastic stand-offs.

## Software
When the user presses the start button, a python program on the center RPi detects it. It then signals the other 2 RPis to start the show on it's command. The center RPi also signals the Arduino to start the 
timer and begin the light show.

The timings for the light show require many entries into the Arduino program, and was too complicated to keep up with. I ended up creating a python program to help with that. I created a simle psuedo-scripting language (3 whole commands!) that allows me to create the light show in a more human-readable format. The python program then takes this input from def.txt, does all the math, and outputs the raw timings into def.h which can be used directly by the arduino program.
