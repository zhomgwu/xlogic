#ifndef _UID_FACTORY_H__
#define _UID_FACTORY_H__

#include <time.h>
#include <stdint.h>
/*
* 前端用的是js, js最大整型数54位，1位符号位所以实际使用53位
* 使用时请根据前端语言做一些调整，如果没有限制就使用64位
*/
enum UID_BIT_TYPE {
	UID_BIT_64 = 0,
	UID_BIT_53,
};

class uid_factory
{
private:
	uid_factory();
	~uid_factory();
public:

	static uid_factory *instance();
	static void destroy();

	void init(uint32_t world_id, uint32_t func_id, uint32_t bit_type = UID_BIT_53);
	void uninit(){}

	uint64_t create_id();

private:
	
	uint64_t create_id64();
	uint64_t create_id53();

private:
	static uid_factory *instance_;

	uint32_t 	bit_type_;  //uid位数
	uint32_t	world_id_;	//大区ID
	uint32_t	func_id_;	//功能ID
	time_t		self_time_;	//自适应时间
	int			seq_;		//序号
};

#endif //_UID_FACTORY_H__
