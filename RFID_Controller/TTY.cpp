#include "TTY.h"
#include <iostream>
#include <assert.h>

using namespace std;


static int TIMEOUT = 1000;

TTY::TTY() {
#ifndef LINUX
	m_Handle = INVALID_HANDLE_VALUE;
#else

#endif
}

TTY::~TTY() {
	Disconnect();
}

bool TTY::IsOK() const {
    #ifndef LINUX
	return m_Handle != INVALID_HANDLE_VALUE;
#else

#endif
}

void TTY::Connect(const string& port, int baudrate) {

	Disconnect();
#ifndef LINUX

	m_Handle =
		CreateFile(
			port.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

	if (m_Handle == INVALID_HANDLE_VALUE) {
		throw TTYException();
	}

	SetCommMask(m_Handle, EV_RXCHAR);
	SetupComm(m_Handle, 1500, 1500);

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

	if (!SetCommTimeouts(m_Handle, &CommTimeOuts)) {
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		throw TTYException();
	}

	DCB ComDCM;

	memset(&ComDCM, 0, sizeof(ComDCM));
	ComDCM.DCBlength = sizeof(DCB);
	GetCommState(m_Handle, &ComDCM);
	ComDCM.BaudRate = DWORD(baudrate);
	ComDCM.ByteSize = 8;
	ComDCM.Parity = NOPARITY;
	ComDCM.StopBits = ONESTOPBIT;
	ComDCM.fAbortOnError = TRUE;
	ComDCM.fDtrControl = DTR_CONTROL_DISABLE;
	ComDCM.fRtsControl = RTS_CONTROL_DISABLE;
	ComDCM.fBinary = TRUE;
	ComDCM.fParity = FALSE;
	ComDCM.fInX = FALSE;
	ComDCM.fOutX = FALSE;
	ComDCM.XonChar = 0;
	ComDCM.XoffChar = (unsigned char)0xFF;
	ComDCM.fErrorChar = FALSE;
	ComDCM.fNull = FALSE;
	ComDCM.fOutxCtsFlow = FALSE;
	ComDCM.fOutxDsrFlow = FALSE;
	ComDCM.XonLim = 128;
	ComDCM.XoffLim = 128;

	if (!SetCommState(m_Handle, &ComDCM)) {
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		throw TTYException();
    }
#else

    if (baudrate == 9600) {
        baudrate = B9600;
    } else if (baudrate == 19200){
        baudrate = B19200;
    }else if  (baudrate == 38400){
        baudrate = B38400;
    }else if  (baudrate == 57600){
        baudrate = B57600;
    }else if (baudrate == 115200){
        baudrate = B115200;
    }else if (baudrate == 230400){
        baudrate = B230400;
    }


      fd = open(("/dev/ttyUSB" + port).c_str(), O_RDWR | O_NOCTTY |O_NONBLOCK);
     if (fd == -1)
     {
         throw TTYException();
     }
     else{
         tcgetattr(fd, &m_options);
                m_options.c_cflag &= ~PARENB;
                m_options.c_cflag &= ~CSTOPB;
                m_options.c_cflag &= ~CSIZE;
                m_options.c_cflag |= CS8;
                m_options.c_lflag = 0;
                m_options.c_oflag &= ~OPOST;
                m_options.c_iflag = 0;
                m_options.c_iflag &= ~ (INLCR | IGNCR | ICRNL);
                tcsetattr(fd, TCSANOW, &m_options);

            if (cfsetispeed(&m_options, baudrate) == -1) {
                throw TTYException();
            }
            if (cfsetospeed(&m_options, baudrate) == -1) {
                throw TTYException();
            }
       }
}
#endif


void TTY::Disconnect() {
#ifndef LINUX
	if (m_Handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
	}
#else
    close(fd);
#endif
}

void TTY::Write(const vector<unsigned char>& data) {
#ifndef LINUX
	if (m_Handle == INVALID_HANDLE_VALUE) {
		throw TTYException();
	}

	DWORD feedback;
	if (!WriteFile(m_Handle, &data[0], (DWORD)data.size(), &feedback, 0) || feedback != (DWORD)data.size()) {
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		throw TTYException();
	}
#else

#endif
}

void TTY::Read(vector<unsigned char>& data, int size) {
    #ifndef LINUX
	char buf[300];
	if (m_Handle == INVALID_HANDLE_VALUE) {
		throw TTYException();
	}
	DWORD feedback = 0;

	DWORD len = (DWORD)size;
	len = (sizeof(buf) < len) ? sizeof(buf) : len;

	if (!ReadFile(m_Handle, buf, len, &feedback, NULL)) {
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		throw TTYException();
	}

	for (int i = 0; i < feedback; i++) {
		data.push_back(buf[i]);
	}
#else
    tcflush(fd, TCIFLUSH);

            char read_buffer[32];
            int  bytes_read = 0;
            int i = 0;

            bytes_read = read(fd,&read_buffer,32);

            printf("\n\n  Bytes Rxed -%d", bytes_read);
            printf("\n\n  ");


            for(i=0;i<bytes_read;i++){}
}
#endif



