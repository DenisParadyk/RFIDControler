#include "TTY.h"
#include <iostream>
#include <assert.h>
#include <windows.h>

using namespace std;

static int TIMEOUT = 1000;

TTY::TTY() {
	m_Handle = INVALID_HANDLE_VALUE;
}

TTY::~TTY() {
	Disconnect();
}

bool TTY::IsOK() const {
	return m_Handle != INVALID_HANDLE_VALUE;
}

void TTY::Connect(const string& port, int baudrate) {

	Disconnect();

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

}

void TTY::Disconnect() {

	if (m_Handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
	}

}

void TTY::Write(const vector<unsigned char>& data) {

	if (m_Handle == INVALID_HANDLE_VALUE) {
		throw TTYException();
	}

	DWORD feedback;
	if (!WriteFile(m_Handle, &data[0], (DWORD)data.size(), &feedback, 0) || feedback != (DWORD)data.size()) {
		CloseHandle(m_Handle);
		m_Handle = INVALID_HANDLE_VALUE;
		throw TTYException();
	}


}

void TTY::Read(vector<unsigned char>& data, int size) {
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
}