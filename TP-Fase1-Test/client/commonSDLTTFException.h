#ifndef SDLTTFEXCEPTION_H
#define SDLTTFEXCEPTION_H
#include <typeinfo>
#include <exception>
#include <stdio.h>
#define BUF_LEN 256 
#include <stdarg.h>

class SDLTTFError : public std::exception {
	private:
	char msg_error[BUF_LEN];

	public:
	explicit SDLTTFError(const char* fmt, ...) noexcept;
	const char *what() const noexcept;
	virtual ~SDLTTFError() noexcept;
};


#endif
