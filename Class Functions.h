#ifndef CLASS_FUNCTIONS_H
#define CLASS_FUNCTIONS_H



// this function plots the given circle onto the console, with 2 modes: DRAW and ERASE
// DRAW mode draws the 219 character (a filled rectangle), in all string locations that are on the circle's surface.
// ERASE mode draws the 32 character (a space, or ' '), in all string locations that are on the circle's surface
int PlotCircle(ConsoleDisplay &targetConsole,
               Circle &targetCircle,
               bool mode = DRAW)
{
    // declaring variables to store the start and end points, in terms of string coordinates, where drawing can occur
    // to make sure drawing doesn't occur out of the string's scope, min and max are used to restrain the drawing limits to the console buffer
    // the combination makes sure that the values are at least 0, and at most the width/height of the buffer
    // these 2 points mark the region only around the circle, where characters could exist, to be checked (for increased performance)
    int
        xStart = std::min(std::max(targetCircle.position()[0] - targetCircle.radius(), 0), targetConsole.bufferWidth() - 1),
        xStop  = std::min(std::max(targetCircle.position()[0] + targetCircle.radius(), 0), targetConsole.bufferWidth() - 1),
        xParse,
        yStart = std::min(std::max(targetCircle.position()[1] - targetCircle.radius(), 0), targetConsole.bufferHeight() - 1),
        yStop  = std::min(std::max(targetCircle.position()[1] + targetCircle.radius(), 0), targetConsole.bufferHeight() - 1),
        yParse,
        // and a counter for the amount of characters drawn or erased
        drawnCharacters = 0;

    // parsing the string on height
    for (yParse = yStart; yParse <= yStop; yParse++)
    {
        // using the operator, only once per loop iteration will the address be marked.
        // this reduces the number of executions for each string element.
        targetConsole(yParse);

        // parsing the string on width
        for (xParse = xStart; xParse <= xStop; xParse++)
        {
            // checks whether the current coordinates belong to the circle
            if (targetCircle.Contains(xParse, yParse))
            {
                // using a ternary operator, the string elements are assigned either a filled rectangle or a space, depending on the mode
                targetConsole[xParse] = (mode == DRAW? 219 : 32);

                //if the point belongs to the circle, then it is counted
                drawnCharacters++;
            }
        }
    }

    // returns the number of characters drawn
    return drawnCharacters;
}

// an overload for the printf function, with its only usage being less main code whenever a ConsoleDisplay object's image is to be displayed
int printf(ConsoleDisplay &targetConsole)
{
    return printf(targetConsole.characterArray());
}

// an operator overload, which returns the vector, but with all its elements opposite the original
std::vector<int> operator -(std::vector<int> targetVector)
{
    // parsing is done via vector iterators
    for (std::vector<int>::iterator address = targetVector.begin(); address != targetVector.end(); ++address)
    {
        (*address) = -(*address);
    }

    return targetVector;
}



#endif // CLASS_FUNCTIONS_H
