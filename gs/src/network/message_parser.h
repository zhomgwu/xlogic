

template<typename T>
class message_parser {
public:
	message_parser(void *data, uint32_t length);
	~message_parser();

public:

	T* head();
	void *body();
	uint32_t body_length();

private:
	void * data;
	uint32_t length;
};

