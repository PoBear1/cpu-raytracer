#ifndef __PBRT_HITTABLE_LIST_H
#define __PBRT_HITTABLE_LIST_H
#include "hittable.h"
#include <memory>
#include <vector>
class hittable_list : public hittable {
public:
	std::vector<std::shared_ptr<hittable>> objects;
	hittable_list() {}
	hittable_list(std::shared_ptr<hittable> object) {objects.push_back(object);}
	void add(std::shared_ptr<hittable> object) {objects.push_back(object);}
	bool hit(const ray& r, interval t, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		interval t_current = t;
		for(const std::shared_ptr<hittable>& object: objects) {
			if(object -> hit(r, t_current, temp_rec)) {
				hit_anything = true;
				t_current.max_v = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
};
#endif