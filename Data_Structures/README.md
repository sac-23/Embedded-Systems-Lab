# Embedded Data Structures

This directory contains implementations of fundamental data structures commonly used in embedded systems development.

The goal of these implementations is to strengthen understanding of data organization, memory management, and efficient data handling techniques used in resource-constrained embedded environments.

## Implementations

### Linked List

A singly linked list implementation developed using dynamic memory allocation.

Features:

* Node creation
* Insertion at beginning
* Insertion at end
* Insertion at a specific position
* Deletion at beginning
* Deletion at end
* Deletion by value
* List traversal
* List reversal
* Memory cleanup

Concepts Practiced:

* Pointers and pointer-to-pointer usage
* Dynamic memory allocation (`malloc`)
* Memory deallocation (`free`)
* Linked data structures
* List manipulation algorithms

---

### Circular Buffer (Ring Buffer)

A fixed-size FIFO (First-In First-Out) buffer implementation using an array-based design.

Features:

* Buffer initialization
* Read and write operations
* Full and empty detection
* Element count tracking
* Head and tail index management
* Circular wrap-around handling

Implementation Details:

* Buffer size is defined as a power of two.
* Wrap-around is implemented using bitwise AND operations instead of modulo operations.
* This approach avoids division-based remainder calculations and is commonly used in embedded systems for improved efficiency.

Concepts Practiced:

* FIFO data handling
* Circular indexing
* Memory-efficient buffering
* Bitwise operations
* Embedded optimization techniques

## Purpose

The implementations in this directory are intended to provide hands-on experience with data structures that are frequently used in embedded software, communication drivers, real-time systems, and memory-constrained applications.
