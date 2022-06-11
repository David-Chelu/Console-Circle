#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// this function sets the console cursor (used by printf and cout) at the given coordinates
void SetCursor(SHORT xCursor = 0, SHORT yCursor = 0)
{
    // console output handle
    static HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // function that sets the cursor
    SetConsoleCursorPosition(consoleOutputHandle, {xCursor, yCursor});
}

// this function reads the file "data.txt", which is supposed to contain the console buffer width and height
std::vector<int> ReadBufferSizeFromFile(const char *directory)
{
    std::ifstream
        fileReader;

    std::vector<int>
        bufferSize;

    // resizing the vector to 2 elements, so that bufferSize[0] is the width, and bufferSize[1] is the height
    bufferSize.resize(2);

    // attempting to open file
    fileReader.open(directory);

    // handling the scenarios where file loading fails, and when it succeeds, respectively
    if (!fileReader.is_open())
    {
        // using the default assumed values, if the file can't be read from
        bufferSize[0] = Default::bufferWidth;
        bufferSize[1] = Default::bufferHeight;
    }
    else
    {
        // fileLine reads all lines inside the file, one by one
        // fileLineFirstHalf is used to know what's left of the '=' in the file line, to know which variable to assign the value to (that way, the order in which variables are written in the file doesn't matter)
        // fileLineSecondHalf is used to know what's right of the '=' in the file line, to know what value to assign to the variable
        std::string
            fileLine,
            fileLineFirstHalf,
            fileLineSecondHalf;

        // since the fstream classes don't have a method overload for putting file contents into std::string objects, this is a handle variable of sorts, used to read from the file, to then copy its contents into the fileLine variable
        char
            _fileLine[256];

        // the file is parsed, one line at a time
        while (fileReader.getline(_fileLine, 256))
        {
            // copying the current file line into the fileLine variable
            fileLine = _fileLine;

            // fileLineFirstHalf will receive all characters from the beginning of the line, and until the '=' character is found (which is a separator in this case)
            // fileLineSecondHalf will receive all characters from just after the '=' character, and until the end of the line
            fileLineFirstHalf  = fileLine.substr(0, fileLine.find('='));
            fileLineSecondHalf = fileLine.substr(fileLine.find('=') + 1);

            // if the line's first half contains the substring "bufferWidth", then bufferSize[0] (the width) receives the value
            if (fileLineFirstHalf.find("bufferWidth") != std::string::npos)
            {
                bufferSize[0] = std::stoi(fileLineSecondHalf);
            }

            // if the line's first half contains the substring "bufferHeight", then bufferSize[1] (the height) receives the value
            if (fileLineFirstHalf.find("bufferHeight") != std::string::npos)
            {
                bufferSize[1] = std::stoi(fileLineSecondHalf);
            }
        }

        // closing the opened file
        fileReader.close();
    }

    // the resulted vector will be returned, be it containing the default hard coded values, or the ones read from the file
    return bufferSize;
}

// this function makes use of windows functions to directly check the buffer size of the console
std::vector<int> ReadBufferSizeFromWindow()
{
    PCONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo = new CONSOLE_SCREEN_BUFFER_INFO;

    std::vector<int>
        bufferSize;

    BOOL
        result = GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                                            consoleBufferInfo);

    if (!result)
    {
        return ReadBufferSizeFromFile("data.txt");
    }

    bufferSize.push_back(consoleBufferInfo->dwSize.X);
    bufferSize.push_back(consoleBufferInfo->srWindow.Bottom - consoleBufferInfo->srWindow.Top);

    delete consoleBufferInfo;

    std::cout << bufferSize[0] << ", "
              << bufferSize[1];

    return bufferSize;
}

// this function calculates the squared distance between 2 points.
// that is, it doesn't calculate square root, so that unnecessary extra calculations won't be done.
// instead, this value is compared against squared radius, which is all we need to determine whether 2 points are within [radius] distance.
int SquaredDistance(int xDistance, int yDistance)
{
    return xDistance * xDistance + yDistance * yDistance;
}



#endif // FUNCTIONS_H
