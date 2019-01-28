
#include "aoi_base.h"

aoi_obj::aoi_obj(uint64_t id)
:m_id(id)
,m_mode(0) 
,m_radius2(0)
,m_x(0)
,m_y(0)
,m_z(0) {

}

aoi_obj::~aoi_obj() {

}

uint64_t aoi_obj::id() const {
	return m_id;
}

int32_t aoi_obj::x() const {
	return m_x;
}

int32_t aoi_obj::y() const {
	return m_y;
}

int32_t aoi_obj::z() const {
	return m_z;
}

void aoi_obj::move(int32_t x, int32_t y, int32_t z) {
	if (m_x != x || m_y != y || m_z != z) {
		m_x = x; m_y = y; m_z = z;
	}
}

void aoi_obj::aoi_message(const std::set<aoi_obj *> &objs, int aoi_mode) {

}

void aoi_obj::set_radius(int32_t radius) {
	if ((radius * radius) != m_radius2) {
		m_radius2 = radius * radius;
	}
}

bool aoi_obj::is_in_view(aoi_obj * obj) {
	if (!obj) {
		return false;
	}
	return m_radius2 >= dist2(m_x, m_y, m_z, obj->x(), obj->y(), obj->z());
}

bool aoi_obj::is_new() {
	return m_mode & AOI_MODE_NEW;
}

bool aoi_obj::is_update() {
	return m_mode & AOI_MODE_UPDATE;
}

bool aoi_obj::is_remove() {
	return m_mode & AOI_MODE_REMOVE;
}

void aoi_obj::new_mode() {
	if (!(m_mode & AOI_MODE_NEW)) {
		m_mode |= AOI_MODE_NEW;
	}
}

void aoi_obj::update_mode() {
	if (!(m_mode & AOI_MODE_UPDATE)) {
		m_mode |= AOI_MODE_UPDATE;
	}
}

void aoi_obj::remove_mode() {
	if (!(m_mode & AOI_MODE_REMOVE)) {
		m_mode |= AOI_MODE_REMOVE;
	}
}

void aoi_obj::clear_mode() {
	m_mode &= AOI_MODE_NONE;
}

aoi_base::~aoi_base() {

}
