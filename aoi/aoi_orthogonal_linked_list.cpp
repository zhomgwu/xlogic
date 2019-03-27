#include "aoi_orthogonal_linked_list.h"

aoi_ol_obj::aoi_ol_obj(uint64_t id) 
:aoi_obj(id) {

}

aoi_ol_obj::~aoi_ol_obj() {

}

aoi_orthogonal_linked::aoi_orthogonal_linked()
: m_x_axis_header(nullptr)
, m_y_axis_header(nullptr)
{

}

aoi_orthogonal_linked::~aoi_orthogonal_linked() {

}

bool aoi_orthogonal_linked::aoi_add(aoi_obj * obj) {
	if (obj == nullptr) {
		return false;
	}
	aoi_ol_obj * ol_obj = static_cast<aoi_ol_obj*>(obj);
	if (!add_to_list(ol_obj)) {
		return false;
	}
	ol_obj->update_mode();
	return true;
}

bool aoi_orthogonal_linked::aoi_remove(aoi_obj * obj) {
	if (obj == nullptr) {
		return false;
	}
	aoi_ol_obj * ol_obj = static_cast<aoi_ol_obj*>(obj);
	ol_obj->remove_mode();
	return true;
}

bool aoi_orthogonal_linked::aoi_move(aoi_obj * obj, int32_t x, int32_t y, int32_t z) {
	if (obj == nullptr) {
		return false;
	}

	aoi_ol_obj * ol_obj = static_cast<aoi_ol_obj*>(obj);
	ol_obj->set_pos(x, y, z);
	// move to x prev
	if (ol_obj->m_x_prev && ol_obj->m_x_prev->x() > ol_obj->x()) {
		aoi_ol_obj * tmp = ol_obj->m_x_prev;
		// obj take out from list for a moment
		remove_from_x_list(ol_obj);
		// find new pos 
		while (tmp) {
			if (tmp->x() <= ol_obj->x()) {
				tmp->m_x_next->m_x_prev = ol_obj;
				ol_obj->m_x_next = tmp->m_x_next;
				tmp->m_x_next = ol_obj;
				ol_obj->m_x_prev = tmp;
				break;
			}

			if (tmp->m_x_prev == nullptr) {
				m_x_axis_header = ol_obj;
				tmp->m_x_prev = ol_obj;
				ol_obj->m_x_next = tmp;
				break;
			}
			tmp = tmp->m_x_prev;
		}
	}
	// move to x next
	else if (ol_obj->m_x_next && ol_obj->m_x_next->x() < ol_obj->x()){
		// find new pos 
		aoi_ol_obj * tmp = ol_obj->m_x_next;
		// obj take out from list for a moment
		remove_from_x_list(ol_obj);
		// find new pos 
		while (tmp) {
			if (tmp->x() >= ol_obj->x()) {
				tmp->m_x_prev->m_x_next = ol_obj;
				ol_obj->m_x_prev = tmp->m_x_prev;
				tmp->m_x_prev = ol_obj;
				ol_obj->m_x_next = tmp;
				break;
			}

			if (tmp->m_x_next == nullptr) {
				tmp->m_x_next = ol_obj;
				ol_obj->m_x_prev = tmp;
				break;
			}
			tmp = tmp->m_x_next;
		}
	}

	// move to y prev
	if (ol_obj->m_y_prev && ol_obj->m_y_prev->y() > ol_obj->y()) {
		aoi_ol_obj * tmp = ol_obj->m_y_prev;
		// obj take out from list for a moment
		remove_from_y_list(ol_obj);
		// find new pos 
		while (tmp) {
			if (tmp->y() <= ol_obj->y()) {
				tmp->m_y_next->m_y_prev = ol_obj;
				ol_obj->m_y_next = tmp->m_y_next;
				tmp->m_y_next = ol_obj;
				ol_obj->m_y_prev = tmp;
				break;
			}

			if (tmp->m_y_prev == nullptr) {
				m_y_axis_header = ol_obj;
				tmp->m_y_prev = ol_obj;
				ol_obj->m_y_next = tmp;
				break;
			}
			tmp = tmp->m_y_prev;
		}
	}
	// move to y next
	else if (ol_obj->m_y_next && ol_obj->m_y_next->y() < ol_obj->y()){
		// find new pos 
		aoi_ol_obj * tmp = ol_obj->m_y_next;
		// obj take out from list for a moment
		remove_from_y_list(ol_obj);
		// find new pos 
		while (tmp) {
			if (tmp->y() >= ol_obj->y()) {
				tmp->m_y_prev->m_y_next = ol_obj;
				ol_obj->m_y_prev = tmp->m_y_prev;
				tmp->m_y_prev = ol_obj;
				ol_obj->m_y_next = tmp;
				break;
			}

			if (tmp->m_y_next == nullptr) {
				tmp->m_y_next = ol_obj;
				ol_obj->m_y_prev = tmp;
				break;
			}
			tmp = tmp->m_y_next;
		}
	}

	ol_obj->update_mode();
	return true;
}

void aoi_orthogonal_linked::aoi_update() {
	std::set<aoi_ol_obj *> final_remove_set;

	for (auto & it : m_aoi_objects) {
		aoi_ol_obj * obj = it.second;
		if (obj->is_remove()) {
			final_remove_set.insert(obj);
			continue;
		}

		std::set<uint64_t> view_set;
		// traverse mover x prev 
		aoi_ol_obj *tmp = obj->m_x_prev;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			view_set.insert(tmp->id());
			tmp = tmp->m_x_prev;
		}

		// traverse mover x next
		tmp = obj->m_x_next;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			view_set.insert(tmp->id());
			tmp = tmp->m_x_next;
		}

		// traverse mover y prev 
		tmp = obj->m_y_prev;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			view_set.insert(tmp->id());
			tmp = tmp->m_y_prev;
		}

		// traverse mover y next
		tmp = obj->m_y_next;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			view_set.insert(tmp->id());
			tmp = tmp->m_y_next;
		}

		if (view_set.size() > 0) {
			obj->aoi_message(view_set);
		}
	}

	if (!final_remove_set.empty()) {
		for (auto & rmobj : final_remove_set) {
			remove_from_list(rmobj);
		}
	}

	for (auto & it : m_aoi_objects) {
		aoi_ol_obj * obj = it.second;
		obj->clear_mode();
	}
}

bool aoi_orthogonal_linked::add_to_list(aoi_ol_obj * obj) {
	if (!add_to_objects(obj)) {
		return false;
	}
	add_to_x_list(obj);
	add_to_y_list(obj);	
	return true;
}

void aoi_orthogonal_linked::add_to_x_list(aoi_ol_obj * obj) {
	if (!m_x_axis_header) {
		m_x_axis_header = obj;
	}
	else {
		aoi_ol_obj * tmp = m_x_axis_header;
		while(tmp) {
			if (obj->x() < tmp->x()) {
				// insert obj at header
				if (tmp == m_x_axis_header) {
					m_x_axis_header->m_x_prev = obj;
					obj->m_x_next = m_x_axis_header;
					m_x_axis_header = obj;
				}
				else {
					obj->m_x_prev = tmp->m_x_prev;
					tmp->m_x_prev->m_x_next = obj;
					obj->m_x_next = tmp;
					tmp->m_x_prev = obj;
				}
				break;
			}
			// insert obj at tail
			if (!tmp->m_x_next) {
				tmp->m_x_next = obj;
				obj->m_x_prev = tmp;
				break;
			}
			tmp = tmp->m_x_next;
		}
	}
}

void aoi_orthogonal_linked::add_to_y_list(aoi_ol_obj * obj) {
	if (!m_y_axis_header) {
		m_y_axis_header = obj;
	}
	else {
		aoi_ol_obj * tmp = m_y_axis_header;
		while(tmp) {
			if (obj->y() < tmp->y()) {
				// insert obj at header
				if (tmp == m_y_axis_header) {
					m_y_axis_header->m_y_prev = obj;
					obj->m_y_next = m_y_axis_header;
					m_y_axis_header = obj;
				}
				else {
					obj->m_y_prev = tmp->m_y_prev;
					tmp->m_y_prev->m_y_next = obj;
					obj->m_y_next = tmp;
					tmp->m_y_prev = obj;
				}
				break;
			}
			// insert obj at tail
			if (!tmp->m_y_next) {
				tmp->m_y_next = obj;
				obj->m_y_prev = tmp;
				break;
			}
			tmp = tmp->m_y_next;
		}
	}
}

void aoi_orthogonal_linked::remove_from_list(aoi_ol_obj * obj) {
	if (m_aoi_objects.find(obj->id()) != m_aoi_objects.end()) {
		m_aoi_objects.erase(obj->id());
	}

	remove_from_x_list(obj);
	remove_from_y_list(obj);
}

void aoi_orthogonal_linked::remove_from_x_list(aoi_ol_obj * obj) {
	if (m_x_axis_header == obj) {
		m_x_axis_header = obj->m_x_next;
	}
	if (obj->m_x_prev) {
		obj->m_x_prev->m_x_next = obj->m_x_next;	
	}
	if (obj->m_x_next) {
		obj->m_x_next->m_x_prev = obj->m_x_prev;	
	}
	obj->m_x_prev = nullptr;
	obj->m_x_next = nullptr;
}

void aoi_orthogonal_linked::remove_from_y_list(aoi_ol_obj * obj) {
	if (m_y_axis_header == obj) {
		m_y_axis_header = obj->m_y_next;
	}
	if (obj->m_y_prev) {
		obj->m_y_prev->m_y_next = obj->m_y_next;	
	}
	if (obj->m_y_next) {
		obj->m_y_next->m_y_prev = obj->m_y_prev;	
	}
	obj->m_y_prev = nullptr;
	obj->m_y_next = nullptr;
}

aoi_ol_obj *aoi_orthogonal_linked::get_aoi_obj(uint64_t id) {
	if (m_aoi_objects.find(id) != m_aoi_objects.end()) {
		return m_aoi_objects[id];
	}
	return nullptr;
}

bool aoi_orthogonal_linked::add_to_objects(aoi_ol_obj * obj) {
	if (m_aoi_objects.find(obj->id()) != m_aoi_objects.end()) {
		return false;
	}
	m_aoi_objects.insert({obj->id(), obj});
	return true;
}

void aoi_orthogonal_linked::remove_from_objects(uint64_t id) {
	if (m_aoi_objects.find(id) != m_aoi_objects.end()) {
		m_aoi_objects.erase(id);
	}
}

void aoi_orthogonal_linked::debug_print_objects() {
	for (auto & it : m_aoi_objects) {
		it.second->debug_print();
	}
}

void aoi_orthogonal_linked::debug_print_x_axis() {
	aoi_ol_obj * tmp = m_x_axis_header;
	while (tmp) {
		tmp->debug_print();
		tmp = tmp->m_x_next;
	}
}

void aoi_orthogonal_linked::debug_print_y_axis() {
	aoi_ol_obj * tmp = m_y_axis_header;
	while (tmp) {
		tmp->debug_print();
		tmp = tmp->m_y_next;
	}
}
