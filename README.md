# Raycaster-STM32L432KC
Real-time raycaster game engine written from scratch for a STM32 L432KC prototype board.


# Mathematics
The approach implemented here is my own take on the raycasting. It does not use a traditional 2D array to represent the world (like in Wolfenstein 3D). Instead, the world here is represented in a complex space where each wall is just a pair of points (and an assigned texture). What is great about this approach is that it allows to create more complicated rooms or even move walls (doors) in real-time, although this feature is still waiting to be implemented... 😉

This code was written in C99 to take benefit of the _complex_ floating-point types. It runs on an 80MHz STM32 MCU with only 64kB of SRAM, and it does it quite smoothly.


# Parts
* Development board: [STM32 NUCLEO-L432KC](https://botland.com.pl/stm32-nucleo/7607-stm32-nucleo-l432kc-stm32l432kcu6-arm-cortex-m4.html)
* Screen module: [Waveshare 10514](https://botland.com.pl/wyswietlacze-oled/4432-wyswietlacz-oled-kolorowy-graficzny-095-b-96x64px-spi-proste-zlacza-waveshare-10514.html)
* Joystick: [This one](https://allegro.pl/oferta/mikroprzycisk-joystick-off-4x-on-100ma-12v-9980607801)


# Demonstration
Click to view on YouTube:

[![video](https://img.youtube.com/vi/6Xx6dUbavZc/0.jpg)](https://www.youtube.com/watch?v=6Xx6dUbavZc)


# Board layout

## With all the components
![photo 1](https://i.imgur.com/aJfXv4j.jpg)

## Connections
![photo 2](https://i.imgur.com/NFfxQ64.jpg)
