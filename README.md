# Console-Circle
Code to draw a circle in a Windows console.

Upon opening the executable, the user will be prompted to press a key to start the display.
Before pressing any key, make sure the console's buffer and window width coincide (no horizontal scrolling), and to resize the console prior to pressing the key.
The default values, 238x125, are the maximum buffer size I could have displayed on windows 8.1, with a resolution of 1920x1080, with Raster Fonts 8x8, so that the border of the console fits neatly onto the screen.
I highly recommend the font is set to Raster Fonts 8x8, and that console window size and buffer size coincide.
Additionally, it's vital to leave a trailing line in the console (set the buffer height to 126, but type 125 in data.txt), so that the console doesn't scroll down and remove the first line of display.
