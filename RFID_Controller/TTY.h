#ifndef _TTY_
#define _TTY_

#define NOMINMAX 

#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

using namespace std;

struct TTY {

	TTY();
    virtual ~TTY();
    int fd;
	bool IsOK() const;

	void Connect(const string& port, int baudrate);
	void Disconnect();

    virtual void Write(const vector<unsigned char>& data);
	virtual void Read(vector<unsigned char>& data, int size);
#ifndef LINUX
    HANDLE m_Handle;
#else

#endif
private:
     struct termios m_options;
};

struct TTYException {

};

#endif
