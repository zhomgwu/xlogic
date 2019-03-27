#ifndef __AOI_BASE_H__
#define __AOI_BASE_H__

#include <stdint.h>
#include <set>
#include <unordered_map>

#define AOI_MODE_NONE		0
#define AOI_MODE_REMOVE 	1
#define AOI_MODE_UPDATE		2

static int32_t dist2(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) {
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2);
}

class aoi_obj {
public:
	aoi_obj(uint64_t id);
	virtual ~aoi_obj();

	virtual uint64_t id() const;
	virtual int32_t x() const;
	virtual int32_t y() const;
	virtual int32_t z() const;
	virtual void set_x(int32_t x);
	virtual void set_y(int32_t y);
	virtual void set_z(int32_t z);
	virtual void set_pos(int32_t x, int32_t y, int32_t z);
	virtual void set_radius(int32_t radius);
	virtual bool is_in_view(aoi_obj * obj);
	virtual bool is_update();
	virtual bool is_remove();
	virtual void update_mode();
	virtual void remove_mode();
	virtual void set_mode(int mode);
	virtual void cancel_mode(int mode);
	virtual void clear_mode();
	virtual void aoi_message(const std::set<uint64_t> &view_ids);

	virtual void debug_print();

protected:
	uint64_t m_id;
	int32_t m_mode;
	int32_t m_radius2;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	std::set<uint64_t> m_view_ids;
};

class aoi_base {
public:
	virtual ~aoi_base() = 0;

	virtual bool aoi_add(aoi_obj * obj) = 0;
	virtual bool aoi_remove(aoi_obj * obj) = 0;
	virtual bool aoi_move(aoi_obj * obj, int32_t x, int32_t y, int32_t z) = 0;
	virtual void aoi_update() = 0;
};

#endif //__AOI_BASE_H__
