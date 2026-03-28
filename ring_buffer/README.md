# Ring Buffer Module

## Overview
This module provides a simple and lightweight **ring buffer (circular buffer)** implementation for embedded systems.  
It is designed to store byte data efficiently and is commonly used for UART, SPI, CAN, or other stream-based data handling.

## Features
- Fixed-size circular buffer
- Byte-oriented read and write
- Easy to integrate into embedded C projects
- Suitable for bare-metal and RTOS environments
- Simple API for initialization, read, and write operations

## Data Structure
The ring buffer uses a head and tail index to manage data flow:
- **Head**: points to the next write position
- **Tail**: points to the next read position
- **SizeFilled**: tracks how many bytes are currently stored

## API Functions
- `RingBuffer_Init()` ? Initialize the ring buffer
- `RingBuffer_Put_Data()` ? Write one byte into the buffer
- `u1_RingBuffer_Get_Data()` ? Read one byte from the buffer
- `u1_RingBufferIsFull()` ? Check if the buffer is full
- `u1_RingBufferIsEmpty()` ? Check if the buffer is empty
- `pu1_GetWritePointer()` ? Get pointer to the current write position
- `u1_GetReadPointer()` ? Read data using internal read pointer

## Typical Use Cases
- UART RX/TX buffering
- Interrupt-based data reception
- DMA data buffering
- Communication protocol handling

## Notes
- The buffer size is fixed and defined during initialization
- User must provide a valid memory buffer
- Thread safety must be handled externally if used in ISR/RTOS

## License
This module can be freely used and modified for embedded applications.
