#include "uid_factory.h"

const int32_t MAX_SEQ = (1 << 6) - 1;

uid_factory::uid_factory()
: bit_type_(UID_BIT_53)
, world_id_(0)
, func_id_(0)
, self_time_(0)
, seq_(0) {
}

uid_factory::~uid_factory() {

}

uid_factory *uid_factory::instance_ = nullptr;
uid_factory *uid_factory::instance() {
	if (instance_ == nullptr) {
		instance_ = new uid_factory();
	}
	return instance_;
}

void uid_factory::destroy() {
	if (instance_ != nullptr) {
		delete instance_;
		instance_ = nullptr;
	}
}

void uid_factory::init(uint32_t world_id, uint32_t func_id, uint32_t bit_type) {
	bit_type_ = bit_type;
	world_id_ = world_id;
	func_id_ = func_id;
	self_time_ = time(NULL);
	seq_ = 0;
}

struct UID_TYPE {
	union {
		struct {
			uint64_t world_id:14;		//0~0x3FFF
			uint64_t func_id:5;			//0~0xF
			uint64_t time_data:32;		//0~0xFFFFFFFF
			uint64_t seq_data:13;		//0~0x1FFF
		};
		uint64_t _uin64_data;
	};
};

uint64_t uid_factory::create_id() {
	if (bit_type_ == UID_BIT_64) {
		return create_id64();
	}
	return create_id53();
}

uint64_t uid_factory::create_id64() {
	UID_TYPE uid;
	uid._uin64_data = 0;
	uid.world_id = world_id_;
	uid.func_id = func_id_;
	
	time_t cur_time = time(NULL);
	if (self_time_ < cur_time) {
		self_time_ = cur_time;
	}

	if (seq_ >= MAX_SEQ) {
		self_time_++;
		seq_ = 0;
	}
	else {
		seq_++;
	}

	uid.time_data = (self_time_ & 0xffffffff);
	uid.seq_data = seq_;

	return uid._uin64_data;
}

uint64_t uid_factory::create_id53() {
	uint64_t uid = 0;
	time_t cur_time = time(NULL);
	if (self_time_ < cur_time) {
		self_time_ = cur_time;
	}

	if (seq_ >= MAX_SEQ) {
		self_time_++;
		seq_ = 0;
	}
	else {
		seq_++;
	}

	uid = (uid << 10) | (world_id_ & 0x3FF);
	uid = (uid << 5) | (func_id_ & 0x1F);
	uid = (uid << 32) | (self_time_ & 0xFFFFFFFF);
	uid = (uid << 6) | (seq_ & 0x3F);
	return uid;
}