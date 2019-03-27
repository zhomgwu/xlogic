#ifndef __AOI_ORTHOGONAL_LINKED_LIST__
#define __AOI_ORTHOGONAL_LINKED_LIST__

#include "aoi_base.h"

class aoi_ol_obj : public aoi_obj {
public:
	aoi_ol_obj(uint64_t id);
	~aoi_ol_obj();

	aoi_ol_obj * m_x_prev;
	aoi_ol_obj * m_x_next;
	aoi_ol_obj * m_y_prev;
	aoi_ol_obj * m_y_next;
};

class aoi_orthogonal_linked : public aoi_base {
public:
	aoi_orthogonal_linked();
	~aoi_orthogonal_linked();

public:
	virtual bool aoi_add(aoi_obj * obj);
	virtual bool aoi_remove(aoi_obj * obj);
	virtual bool aoi_move(aoi_obj * obj, int32_t x, int32_t y, int32_t z = 0);
	virtual void aoi_update();
	
	bool add_to_list(aoi_ol_obj * obj);
	void add_to_x_list(aoi_ol_obj * obj);
	void add_to_y_list(aoi_ol_obj * obj);

	void remove_from_list(aoi_ol_obj * obj);
	void remove_from_x_list(aoi_ol_obj * obj);
	void remove_from_y_list(aoi_ol_obj * obj);
	
	aoi_ol_obj *get_aoi_obj(uint64_t id);
	bool add_to_objects(aoi_ol_obj * obj);
	void remove_from_objects(uint64_t id);

	void debug_print_objects();
	void debug_print_x_axis();
	void debug_print_y_axis();

private:
	aoi_ol_obj * m_x_axis_header;		//order by x, header is least
	aoi_ol_obj * m_y_axis_header;		//order by y, header is least
	std::unordered_map<uint64_t, aoi_ol_obj*> m_aoi_objects;
};

#endif //__AOI_ORTHOGONAL_LINKED_LIST__
