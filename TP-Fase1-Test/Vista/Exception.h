#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <typeinfo>
#include <exception>
#include <stdio.h>
#define BUF_LEN 256 
#include <stdarg.h>

class OSError : public std::exception {
	private:
	char msg_error[BUF_LEN];

	public:
	explicit OSError(const char* fmt, ...) noexcept;
	const char *what() const noexcept;
	virtual ~OSError() noexcept;
};

class Finalizo_conexion : public std::exception {
};

class accept_fail : public std::exception {
};

#endif
