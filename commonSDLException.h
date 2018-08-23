#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H
#include <typeinfo>
#include <exception>
#include <stdio.h>
#define BUF_LEN 256 
#include <stdarg.h>

class SDLError : public std::exception {
	private:
	char msg_error[BUF_LEN];

	public:
	explicit SDLError(const char* fmt, ...) noexcept;
	const char *what() const noexcept;
	virtual ~SDLError() noexcept;
};


#endif
