#include "commonSDLTTFException.h"
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDLTTFError::SDLTTFError(const char* fmt, ...) noexcept {
	va_list args;
	va_start(args,fmt);
	int s = vsnprintf(msg_error, BUF_LEN, fmt, args);
	va_end(args);
	strncpy(msg_error+s, "\nsdler: ", (size_t)(BUF_LEN-s));

	strncpy(msg_error+s+8, TTF_GetError(), (size_t)(BUF_LEN-s - 9));
	msg_error[BUF_LEN-1] = 0;
}

const char* SDLTTFError::what() const noexcept{
	return msg_error;
}