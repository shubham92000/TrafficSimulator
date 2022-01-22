#include <iostream>
#include "Vehicle.h"
#include "Intersection.h"
#include "Street.h"


Street::Street()
{
    _type = ObjectType::objectStreet;
    _length = 1000.0; // in m
}

void Street::setInIntersection(std::weak_ptr<Intersection> in)
{
    _interIn = in;
    in.lock()->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}

void Street::setOutIntersection(std::weak_ptr<Intersection> out)
{
    _interOut = out;
    out.lock()->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}
