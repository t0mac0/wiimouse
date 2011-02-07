#include <Windows.h>
#include <stdio.h>

#include "serial_Comm.h"


EXPORT void* serial_comm_open(char* port, int use_default_settings )
{
    HANDLE handle = NULL;

    if(port == NULL)
        return NULL;

    handle = CreateFile(port, 
		                GENERIC_READ | GENERIC_WRITE,
		                0, // exclusive access
		                NULL, // no security
		                OPEN_EXISTING,
		                0, // no overlapped I/O
		                NULL); // null template 

    if(handle == NULL)
    {
        return NULL;
    }

    if(use_default_settings)
    {
        SERIAL_COM_SETTINGS settings;
        
        settings.Baud = DEFAULT_BAUD;
        settings.ByteSize = DEFAULT_BYTE_SIZE;
        settings.Parity = DEFAULT_PARITY;
        settings.StopBits = DEFAULT_STOPBITS;
        settings.AbortOnError = DEFAULT_ABORT_ON_ERROR;
        settings.ReadIntervalTimeout = DEFAULT_READ_INTERVAL_TIMEOUT;
        settings.ReadTotalTimeoutConstant = DEFAULT_READ_TOTAL_TIMEOUT_CONSTANT;
        settings.ReadTotalTimeoutMultiplier = DEFAULT_READ_TOTAL_TIMEOUT_MULTIPLIER;
        settings.WriteTotalTimeoutConstant = DEFAULT_WRITE_TOTAL_TIMEOUT_CONSTANT;
        settings.WriteTotalTimeoutMulitplier = DEFAULT_WRITE_TOTAL_TIMEOUT_MULTIPLIER;

        if(serial_comm_set_settings(handle, &settings) != RESULT_SUCCESS)
        {
            CloseHandle(handle);
            return NULL;
        }
     }

    printf(__FUNCTION__": handle %X\n", handle);

    return handle;
}

EXPORT int serial_comm_set_settings(void *handle, SERIAL_COM_SETTINGS * settings)
{
    BOOL port_ready;
    DCB comm_state;
    COMMTIMEOUTS timeouts;

    if(handle == NULL)
        return RESULT_FAILURE;

    port_ready = SetupComm(handle, settings->InputBufferSize, settings->OutputBufferSize);

    if(!port_ready)
        return RESULT_FAILURE;

    port_ready = GetCommState(handle, &comm_state);

    if(!port_ready)
        return RESULT_FAILURE;

    comm_state.BaudRate = settings->Baud;
    comm_state.ByteSize = settings->ByteSize;
    comm_state.Parity = settings->Parity;
    comm_state.StopBits = settings->StopBits;
    comm_state.fAbortOnError = settings->AbortOnError;

    port_ready = SetCommState(handle, &comm_state);

    if(!port_ready)
        return RESULT_FAILURE;

    port_ready = GetCommTimeouts (handle, &timeouts);

    if(!port_ready)
        return RESULT_FAILURE;

    timeouts.ReadIntervalTimeout = settings->ReadIntervalTimeout;
    timeouts.ReadTotalTimeoutConstant = settings->ReadTotalTimeoutConstant;
    timeouts.ReadTotalTimeoutMultiplier = settings->ReadTotalTimeoutMultiplier;
    timeouts.WriteTotalTimeoutConstant = settings->WriteTotalTimeoutConstant;
    timeouts.WriteTotalTimeoutMultiplier = settings->WriteTotalTimeoutMulitplier;

    port_ready = SetCommTimeouts (handle, &timeouts);

    if(!port_ready)
        return RESULT_FAILURE;


    return RESULT_SUCCESS;
}

EXPORT int serial_comm_send(void *handle, void *buffer, int size)
{
    DWORD bytes_sent = 0;

    if(!WriteFile(handle, buffer, size, &bytes_sent, NULL))
    {
        return RESULT_FAILURE;
    }

    return bytes_sent;
}

EXPORT int serial_comm_receive(void *handle, void *buffer, int size)
{
    DWORD bytes_received = 0;

    if(!ReadFile(handle, buffer, size, &bytes_received, NULL))
    {
        return RESULT_FAILURE;
    }

    return bytes_received;
}

EXPORT int serial_comm_close(void *handle)
{

    CloseHandle(handle);

    return RESULT_SUCCESS;
}
