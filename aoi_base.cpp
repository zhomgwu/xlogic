
#include "aoi_base.h"
#include <iostream>

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

void aoi_obj::set_x(int32_t x) {
	if (m_x != x) {
		m_x = x;
	}
}

void aoi_obj::set_y(int32_t y) {
	if (m_y != y) {
		m_y = y;
	}
}

void aoi_obj::set_z(int32_t z) {
	if (m_z != z) {
		m_z = z;
	}
}

void aoi_obj::set_pos(int32_t x, int32_t y, int32_t z) {
	if (m_x != x || m_y != y || m_z != z) {
		m_x = x; m_y = y; m_z = z;
	}
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

bool aoi_obj::is_update() {
	return m_mode & AOI_MODE_UPDATE;
}

bool aoi_obj::is_remove() {
	return m_mode & AOI_MODE_REMOVE;
}

void aoi_obj::update_mode() {
	set_mode(AOI_MODE_UPDATE);
}

void aoi_obj::remove_mode() {
	set_mode(AOI_MODE_REMOVE);
}

void aoi_obj::set_mode(int mode) {
	if (!(m_mode & mode)) {
		m_mode |= mode;
	}
}

void aoi_obj::cancel_mode(int mode) {
	if (m_mode & mode) {
		m_mode &= ~mode;
	}
}

void aoi_obj::clear_mode() {
	m_mode &= AOI_MODE_NONE;
}

void aoi_obj::aoi_message(const std::set<aoi_obj *> &objs) {

}

void aoi_obj::debug_print() {
	std::cout << "**********************************" << std::endl;
	std::cout << "m_id\t" << m_id << std::endl;
	std::cout << "m_mode\t" << m_mode << std::endl;
	std::cout << "m_radius2\t" << m_radius2 << std::endl;
	std::cout << "m_x\t" << m_x << std::endl;
	std::cout << "m_y\t" << m_y << std::endl;
	std::cout << "m_z\t" << m_z << std::endl;
	std::cout << "**********************************" << std::endl;
}

aoi_base::~aoi_base() {

}
