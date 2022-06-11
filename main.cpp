#define _WIN32_WINNT 0x0500

// these two macros are used for the PlotCircle function, to make it more explicit for the programmer
#define ERASE false
#define DRAW  true

#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>

// defining a namespace to keep default values & other, to not have them in the global scope
namespace Default
{
    // this handle will be used to get the console buffer size
    HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // these values assume the console is on a 1920x1080 monitor, windows 8, with Raster Fonts, 8x8 font size, with 238x126 console buffer and window sizes.
    // The number 125 is chosen instead of 126, because that leaves a trailing line for the cursor to rest, without the image being scrolled down.
    int
        bufferWidth  = 238,
        bufferHeight = 125;
}

#include "Classes.h"



int main()
{
    // declaration sections
    Circle
        targetCircle;

    std::vector<int>
        velocity;



    // the radius is set to whichever value (10 is a good size for a 238x125 console
    // the coordinates are set to the value of radius, so that the circle starts within the console's screen, in the top left corner
    targetCircle.radius() = 10;
    targetCircle.position().push_back(targetCircle.radius());
    targetCircle.position().push_back(targetCircle.radius());

    // the speed at which the circle moves (like a screensaver), on either axis
    velocity.push_back(3);
    velocity.push_back(2);

    std::cout<<"Press a key (except escape) to start the display.";

    if (getch() != VK_ESCAPE)
    {
        ConsoleDisplay
            targetConsole(ReadBufferSizeFromWindow());

        // at first, the program is waiting on the user to press a key.
        // if the key is escape, then the program terminates.
        // while the display is ongoing, pressing a key will stop it from moving.
        // if escape is pressed, then the program exits; otherwise, it continues with the moving display.
        do
        {
            // this is where the movement of the display happens
            while (1)
            {
                // checks whether the escape key is pressed, to stop the movement (by breaking out of the loop that causes the movement).
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    break;
                }

                // function call to draw the circle on the string, ready to be displayed in the console
                PlotCircle(targetConsole,
                           targetCircle);

                // resets the console cursor at 0.
                // this method of replacing the old output with new output, is faster than clearing the console for every frame (and avoids the flickers that clearing the console may cause)
                SetCursor();
                std::cout<<targetConsole.characterArray();

                // function call to erase the circle from the string, where it stands, so that no circle remnants stay in the image next time around
                PlotCircle(targetConsole,
                           targetCircle,
                           ERASE);

                // the circle moves with the given velocity, per unit of time
                targetCircle.position()[0] += velocity[0];
                targetCircle.position()[1] += velocity[1];

                // checks whether the x coordinate is going to go out of bounds (if one more unit of time passes, and maintaining velocity)
                if (targetCircle.position()[0] + velocity[0] >= targetConsole.bufferWidth()  - targetCircle.radius() ||
                    targetCircle.position()[0] + velocity[0] <= targetCircle.radius())
                {
                    // if the circle does collide with the borders of the console, then the axis velocity becomes the opposite.
                    velocity[0] = -velocity[0];
                }

                // checks whether the y coordinate is going to go out of bounds (if one more unit of time passes, and maintaining velocity)
                if (targetCircle.position()[1] + velocity[1] >= targetConsole.bufferHeight() - targetCircle.radius() ||
                    targetCircle.position()[1] + velocity[1] <= targetCircle.radius())
                {
                    // if the circle does collide with the borders of the console, then the axis velocity becomes the opposite.
                    velocity[1] = -velocity[1];
                }

                // 33ms between each frame results in 1000/33 = 30 frames per second
                Sleep(33);
            }

            // when escape is pressed in the while loop, the input is caught by this getch.
            // that way, the loop which checks for program exit can verify the input after the display is frozen.
            getch();
        } while (getch() != VK_ESCAPE);
    }

    return 0;
}
