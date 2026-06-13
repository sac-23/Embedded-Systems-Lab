/*
I have Implemented a ring buffer in C.
Instead of using modulo Operation, I have used bitwise AND Operation to wrap around
The size of the buffer is defined as a power of 2 (8 in this case), 
this is efficient because the Modula uses the remainder operation of divison,
in MCUs, the division operation is expensive in terms of clock cycles, and it can be avoided by using bitwise AND operation.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 8 // Buffer Size

// Ring buffer structure
typedef struct {
    uint8_t buffer[SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} ring_buffer_t;

ring_buffer_t rb;

// Initialize the ring buffer
void vInit_ring_buffer(void) {

    rb.head = 0;
    rb.tail = 0;
    rb.count = 0;

}

// Check if the ring buffer is empty
bool xIs_ring_buffer_empty(void) {

    return (rb.count == 0);

}

// Check if the ring buffer is full
bool xIs_ring_buffer_full(void) {

    return (rb.count == SIZE);

}

// Get the current count of elements in the ring buffer
uint8_t xGet_ring_buffer_count(void) {

    return rb.count;

}


// Read a byte from the ring buffer
uint8_t xRead_ring_buffer(void) {

    if (xIs_ring_buffer_empty()) {
        printf("[READ] (Empty) -> FAIL (buffer empty) \n");
        return 0; 
    }

    uint8_t data = rb.buffer[rb.tail];
    rb.tail = (rb.tail + 1) & (SIZE - 1);  // Wrap around the tail index using bitwise AND
    rb.count--; // Decrement the count of Elements in the buffer

    printf("[READ]  -> 0x%02X (count=%u)\n", data, rb.count);
    return data;

}

// Write a byte to the ring buffer
bool xWrite_ring_buffer(uint8_t data) {

    if (xIs_ring_buffer_full()) {
        printf("[WRITE] 0x%02X -> FAIL (buffer full) \n", data);
        return false;
    }

    rb.buffer[rb.head] = data;
    rb.head = (rb.head + 1) & (SIZE - 1); // Wrap around the head index using bitwise AND
    rb.count++; // Increment the count of Elements in the buffer

    if(rb.count == SIZE)
    {
        printf("[WRITE] 0x%02X -> OK (count=%u) FULL \n", data, rb.count);
    }
    else
    {
        printf("[WRITE] 0x%02X -> OK (count=%u) \n", data, rb.count);
    }
    return true;

}

// Test the ring buffer implementation
int main(void) {

    vInit_ring_buffer();

    xWrite_ring_buffer(0x41);
    xWrite_ring_buffer(0x42);
    xWrite_ring_buffer(0x43);
    xWrite_ring_buffer(0x44);
    xWrite_ring_buffer(0x45);
    xWrite_ring_buffer(0x46);
    xWrite_ring_buffer(0x47);
    xWrite_ring_buffer(0x48);
    xWrite_ring_buffer(0x99); 
    
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();

    xWrite_ring_buffer(0x49);
    xWrite_ring_buffer(0x4A);
    xWrite_ring_buffer(0x4B);

    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();
    xRead_ring_buffer();

    return 0;
}