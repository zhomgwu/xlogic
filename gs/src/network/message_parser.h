



class message_dispatcher {
public:
    template<typename T>
    void dispatch(void *data, uint32_t len);
};


template<typename H, typename T>
class message_parser {
public:
	message_parser(void *data, uint32_t length);
	~message_parser();

public:

	H* head();
	T *body();
	uint32_t body_length();

private:
	void * data;
	uint32_t length;
};

