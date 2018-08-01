#ifndef _TTY_
#define _TTY_

#define NOMINMAX 

#include <vector>
#include <string>

using namespace std;

struct TTY {

	TTY();
    virtual ~TTY();

	bool IsOK() const;

	void Connect(const string& port, int baudrate);
	void Disconnect();

	virtual void Write(const vector<unsigned char>& data);
	virtual void Read(vector<unsigned char>& data, int size);
#ifndef LINUX
    HANDLE m_Handle;
#else

#endif
};

struct TTYException {

};

#endif
