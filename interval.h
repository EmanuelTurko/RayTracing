#pragma once

#include "helper.h"

class Interval{
    public:

    Interval() :
    _min(+infinity),
    _max(-infinity)
    {} // Default interval is empty

    Interval(double min,double max) :
    _min(min),
    _max(max)
    {}

    static const Interval empty, universe;

    auto size() const -> double {return _max-_min;}
    auto contains(double x) const -> double{return _min <= x && x <= _max;}
    auto sorrounds(double x) const -> double {return _min < x && x < _max;}
    auto getMax() const -> double {return _max;}
    auto getMin() const -> double {return _min;}
    auto clamp(double x) const -> double {
        return x < _min? _min : x > _max? _max : x;
    }

    private:
    double _min;
    double _max;

};

inline const Interval Interval::empty = Interval(+infinity, -infinity);
inline const Interval Interval::universe = Interval(-infinity,+infinity);