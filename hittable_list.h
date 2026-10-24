#pragma once

#include "helper.h"
#include "hittable.h"

#include <ctime>
#include <vector>



class HittableList : public Hittable {
public:
  std::vector<shared_ptr<Hittable>> objects;

  HittableList() {}
  HittableList(shared_ptr<Hittable> object) { add(object); }

  auto clear() -> void { objects.clear(); }

  auto add(shared_ptr<Hittable> object) -> void { objects.push_back(object); }

  auto hit(const Ray &ray,Interval interval, hitRecord &record) const->bool override{

    hitRecord tempRecord{};
    bool hitAnything{};
    auto closestSoFar = interval.getMax();

    for(const auto& object : objects){
        if(object->hit(ray,Interval(interval.getMin(),closestSoFar), tempRecord)){
            hitAnything = true;
            closestSoFar = tempRecord._t;
            record = tempRecord;
        }
    }

    return hitAnything;
  }
};