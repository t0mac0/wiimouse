#ifndef _SERIAL_COMM_
#define _SERIAL_COMM_

//#ifdef _cplusplus
#define EXPORT extern "C" __declspec(dllexport)
//#else
//#define EXPORT extern __declspec(dllexport)
//#endif

#define RESULT_SUCCESS 1
#define RESULT_FAILURE 0


#define DEFAULT_BAUD 115200
#define DEFAULT_BYTE_SIZE 8
#define DEFAULT_PARITY 0 // no parity
#define DEFAULT_STOPBITS 0 // 1 stopbit
#define DEFAULT_ABORT_ON_ERROR 1 // abort on error

#define DEFAULT_READ_INTERVAL_TIMEOUT 5000
#define DEFAULT_READ_TOTAL_TIMEOUT_CONSTANT 5000
#define DEFAULT_READ_TOTAL_TIMEOUT_MULTIPLIER 1000
#define DEFAULT_WRITE_TOTAL_TIMEOUT_CONSTANT 50
#define DEFAULT_WRITE_TOTAL_TIMEOUT_MULTIPLIER 10


typedef struct _SERIAL_COM_SETTINGS {
    int Baud;
    unsigned char ByteSize;
    unsigned char Parity;
    unsigned char StopBits;
    int AbortOnError;
    int InputBufferSize;
    int OutputBufferSize;
    int ReadIntervalTimeout;
    int ReadTotalTimeoutConstant;
    int ReadTotalTimeoutMultiplier;
    int WriteTotalTimeoutConstant;
    int WriteTotalTimeoutMulitplier;
} SERIAL_COM_SETTINGS;

EXPORT void* serial_comm_open(char* port, int use_default_settings );

EXPORT int serial_comm_set_settings(void *handle, SERIAL_COM_SETTINGS * settings);

EXPORT int serial_comm_send(void *handle, void *buffer, int size);

EXPORT int serial_comm_receive(void *handle, void *buffer, int size);

EXPORT int serial_comm_close(void *handle);

#endif