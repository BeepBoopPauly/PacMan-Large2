# PacMan-Large2
It prints PacMan, PacMan eating a ghost, and the four ghosts at ramdom times and they never repet themselves.

![pacman](https://user-images.githubusercontent.com/22283815/217530110-a6474737-0ac5-4f5e-b5b6-589a49f50f75.gif)

## Note from jmshearer (dad)
This displays animated PacMan figures on a string of 50 WS2811 LED's ("NeoPixel") arranged in the following order:
            
     ┏━━━ 330 ohm resistor ━━━ Arduino Pin 9
     ┃
     ┗  0 ━  1 ━  2 ━  3 ━ 4 ━ 5 ━ 6 ┓
     ┏ 13 ━ 12 ━ 11 ━ 10 ━ 9 ━ 8 ━ 7 ┛
     ┗ 14 ━ 15 ━ 16 ━ 17 ━ 18 ━ 19 ━ 20 ┓
     ┏ 27 ━ 26 ━ 25 ━ 24 ━ 23 ━ 22 ━ 21 ┛
     ┗ 28 ━ 29 ━ 30 ━ 31 ━ 32 ━ 33 ━ 34 ┓
     ┏ 41 ━ 40 ━ 39 ━ 38 ━ 37 ━ 36 ━ 35 ┛
     ┗ 42 ━ 43 ━ 44 ━ 45 ━ 46 ━ 47 ━ 48 ━━━━ 49 (unused)

The code is code isn't the cleanest--we were just playing around--but it is a good demo of some key concepts.
