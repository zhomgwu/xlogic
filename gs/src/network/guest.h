#ifndef __GUEST_H__
#define __GUEST_H__

class guest {
public:
	guest();
	virtual ~guest();

public:

	virtual void on_recv_msg(void * data, uint32_t len);

	virtual bool send_msg(void * data, uint32_t len);

private:
	
	void * m_user_data;
	uint32_t m_data_size;
};

#endif // __GUEST_H__
