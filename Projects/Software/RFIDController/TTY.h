#ifndef _TTY_
#define _TTY_

#define NOMINMAX 
#include <windows.h>

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

    HANDLE m_Handle;

};

struct TTYException {
};

#endif