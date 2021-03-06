#ifndef _G_CODE_PIPE_H_
#define _G_CODE_PIPE_H_

class GcodePipe {
public:
	virtual bool clean() = 0;
	virtual bool getLine(char* dest) = 0;
	virtual bool getLine(char* dest, int buffer_size) = 0;
	virtual bool sendLine(const char* dest) = 0;
	virtual bool sendAck() = 0;
	virtual bool sendErr() = 0;
	virtual ~GcodePipe() = 0;
};

#endif
