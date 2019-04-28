/*
	Implemented by:

	#include <execinfo.h>
	int backtrace(void **buffer, int size);
	char **backtrace_symbols(void *const *buffer, int size);
	void backtrace_symbols_fd(void *const *buffer, int size, int fd);
	
	NOTES: -rdynamic
 	The symbol names may be unavailable without the use of special linker
       options.  For systems using the GNU linker, it is necessary to use
       the -rdynamic linker option.  Note that names of "static" functions
       are not exposed, and won't be available in the backtrace.
*/

#ifndef __BACKTRACE_INFO_H__
#define __BACKTRACE_INFO_H__

#include <string>

class backtrack_info
{
public:
	static std::string get_backtrace_info();
};

#define BT_STR	backtrack_info::get_backtrace_info()

#endif // __BACKTRACE_INFO_H__
