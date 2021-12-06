#ifndef CIRCLE_H
#define CIRCLE_H



// this class will be used to track and plot a circle at whichever coordinates it has, in the console.
class Circle
{
public:
    Circle();

    // method that checks whether 2 given points reside within the surface of the circle
    bool
        Contains(int xCoordinate, int yCoordinate) const;

    // access to reference (getter + setter) of the circle object's position
    std::vector<int>
        &position();

    // access to reference (getter + setter) of the circle object's radius
    int
        &radius();

private:
    // circle object's position
    std::vector<int>
        _position;

    // circle object's radius
    int
        _radius;
};

Circle::Circle()
{
    this->_radius = 5;
}

bool Circle::Contains(int xCoordinate, int yCoordinate) const
{
    // by using the circle's formula, r^2 = (x1-x2)^2 + (y1-y2)^2, we can know the perimeter of the circle.
    // if the equality turns into inequality, then it goes as follows:
    // r^2 < (x1-x2)^2 + (y1-y2)^2, will apply to all points outside the circle's area
    // r^2 > (x1-x2)^2 + (y1-y2)^2, will apply to all points within the circle's area
    // hence, checking r^2 >= (x1-x2)^2 + (y1-y2)^2 will result in all points that are either on the perimeter, or inside the circle
    if (this->_radius * this->_radius >= SquaredDistance(xCoordinate - this->_position[0], yCoordinate - this->_position[1]))
    {
        return 1;
    }

    return 0;
}

std::vector<int> &Circle::position()
{
    return this->_position;
}

int &Circle::radius()
{
    return this->_radius;
}



#endif // CIRCLE_H
