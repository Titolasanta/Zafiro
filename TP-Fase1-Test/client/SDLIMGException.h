#ifndef SDLIMGEXCEPTION_H
#define SDLIMGEXCEPTION_H
#include <typeinfo>
#include <exception>
#include <stdio.h>
#define BUF_LEN 256 
#include <stdarg.h>

class SDLIMGError : public std::exception {

private:
	char msg_error[BUF_LEN];

public:
	explicit SDLIMGError(const char* fmt, ...) noexcept;
	const char *what() const noexcept override;
	~SDLIMGError() override = default;
};

#endif
