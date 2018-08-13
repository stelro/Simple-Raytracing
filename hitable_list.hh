//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_HITABLE_LIST_HH
#define OFFTRACER_HITABLE_LIST_HH

#include "hitable.hh"

class hitable_list : public hitable {
public:
    hitable_list() { }
    hitable_list(hitable **l, int n) { list = l; list_size = n; }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    hitable **list;
    int list_size;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_record;
    bool hit_anyting = false;

    double closest_so_far = t_max;
    for (auto i = 0; i < list_size; i++ ) {
        if ( list[i]->hit(r,t_min, closest_so_far, temp_record) ) {
            hit_anyting = true;
            closest_so_far = temp_record.t;
            rec = temp_record;
        }
    }

    return hit_anyting;
}

#endif //OFFTRACER_HITABLE_LIST_HH
