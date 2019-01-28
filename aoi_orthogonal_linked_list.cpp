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
	return add_to_list(ol_obj);
}

bool aoi_orthogonal_linked::aoi_remove(aoi_obj * obj) {
	if (obj == nullptr) {
		return false;
	}
	aoi_ol_obj * ol_obj = static_cast<aoi_ol_obj*>(obj);
	ol_obj->remove_mode();
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

		std::set<aoi_obj *> new_set;
		std::set<aoi_obj *> update_set;
		std::set<aoi_obj *> remove_set;

		// traverse mover x prev 
		aoi_ol_obj *tmp = obj->m_x_prev;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			if (tmp->is_new()) {
				new_set.insert(tmp);
			}
			if (tmp->is_update()) {
				update_set.insert(tmp);
			}
			if (tmp->is_remove()) {
				remove_set.insert(tmp);
			}
			tmp = tmp->m_x_prev;
		}

		// traverse mover x next
		tmp = obj->m_x_next;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			if (tmp->is_new()) {
				new_set.insert(tmp);
			}
			if (tmp->is_update()) {
				update_set.insert(tmp);
			}
			if (tmp->is_remove()) {
				remove_set.insert(tmp);
			}
			tmp = tmp->m_x_next;
		}

		// traverse mover y prev 
		tmp = obj->m_y_prev;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			if (tmp->is_new()) {
				new_set.insert(tmp);
			}
			if (tmp->is_update()) {
				update_set.insert(tmp);
			}
			if (tmp->is_remove()) {
				remove_set.insert(tmp);
			}
			tmp = tmp->m_y_prev;
		}

		// traverse mover y next
		tmp = obj->m_y_next;
		while(tmp) {
			if (!obj->is_in_view(tmp)) {
				// out of sight
				break;
			}
			if (tmp->is_new()) {
				new_set.insert(tmp);
			}
			if (tmp->is_update()) {
				update_set.insert(tmp);
			}
			if (tmp->is_remove()) {
				remove_set.insert(tmp);
			}
			tmp = tmp->m_y_next;
		}

		if (new_set.size() > 0) {
			obj->aoi_message(new_set, AOI_MODE_NEW);	
		}
		if (update_set.size() > 0) {
			obj->aoi_message(update_set, AOI_MODE_UPDATE);	
		}
		if (remove_set.size() > 0) {
			obj->aoi_message(remove_set, AOI_MODE_REMOVE);	
		}
	}

	if (!final_remove_set.empty()) {
		for (auto & rmobj : final_remove_set) {
			remove_from_list(rmobj);
		}
	}
}

bool aoi_orthogonal_linked::add_to_list(aoi_ol_obj * obj) {
	if (m_aoi_objects.find(obj->id()) != m_aoi_objects.end()) {
		return false;
	}
	m_aoi_objects.insert({obj->id(), obj});

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
	return true;
}

bool aoi_orthogonal_linked::remove_from_list(aoi_ol_obj * obj) {
	if (m_aoi_objects.find(obj->id()) != m_aoi_objects.end()) {
		m_aoi_objects.erase(obj->id());
	}

	aoi_ol_obj * tmp = m_x_axis_header;
	while (tmp) {
		if (tmp == obj) {
			if (tmp == m_x_axis_header) {
				m_x_axis_header = tmp->m_x_next;
				m_x_axis_header->m_x_prev = nullptr;
			}
			else {
				tmp->m_x_next->m_x_prev = tmp->m_x_prev;
				tmp->m_x_prev->m_x_next = tmp->m_x_next;
			}
			break;
		}
	}

	tmp = m_y_axis_header;
	while (tmp) {
		if (tmp == obj) {
			if (tmp == m_y_axis_header) {
				m_y_axis_header = tmp->m_y_next;
				m_y_axis_header->m_y_prev = nullptr;
			}
			else {
				tmp->m_y_next->m_y_prev = tmp->m_y_prev;
				tmp->m_y_prev->m_y_next = tmp->m_y_next;
			}
			break;
		}
	}
	return true;
}

aoi_ol_obj *aoi_orthogonal_linked::get_aoi_obj(uint64_t id) {
	if (m_aoi_objects.find(id) != m_aoi_objects.end()) {
		return m_aoi_objects[id];
	}
	return nullptr;
}
