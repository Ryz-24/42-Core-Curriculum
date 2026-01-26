*This project has been created as part of the 42 curriculum by rzaatreh.*

# minitalk

## Description

**minitalk** is a small communication program written in C that allows a **client** and a **server** to exchange messages using **UNIX signals** (`SIGUSR1` and `SIGUSR2`).

This project focuses on understanding:
- UNIX signals
- Inter-process communication (IPC)
- Bitwise operations
- Signal handling and synchronization

---
## Program Behavior

- The **server** must be launched first
- The server displays its **PID**
- The **client** sends a message to the server using the server PID
- Each character is sent as **8 bits**
- The server reconstructs and prints the received message

### Signal Encoding

- `SIGUSR1` → bit `1`
- `SIGUSR2` → bit `0`


## Bit Transmission Logic

Each character is represented using **8 bits**.

Example for character `'A'` (`01000001`):
- Bits are sent from **most significant bit (MSB)** to **least significant bit (LSB)**
    - MSB:
        - The leftmost bit
        - Has the highest value
    - LSB:
        - The rightmost bit
        - Has the lowest value
- The server shifts and stores each bit from **MSB** to **LSB**
- Once 8 bits are received, the character is printed

---
## Instructions

### Prerequisites
- Unix-based operating system (Linux or macOS)
- `cc`
- `make`


### Compilation

1) Clone the repository and compile the project using:

```bash
make
```
2) Start the server
```bash
./server
```
3) The server will print its PID:
```
Server PID: 4242
```

4) Send a message from the client
```bash
./client 4242 "Hello World!"
```
The server will display the received message on its terminal.

---
## Allowed Functions
- write
- malloc, free
- signal, sigaction
- kill
- getpid
- pause
- sleep, usleep
- exit

---
## Resources
[Step-by-Step Guide to MiniLibX](https://medium.com/@Kr1sNg/step-by-step-guide-to-minitalk-project-at-school-42-deacf16369ec)

[Minitalk 42 project : Guide](https://medium.com/@gamerazer007/minitalk-42-project-guide-be45d74f8dfa)

[Understanding Minitalk](https://medium.com/@digitalpoolng/42-minitalk-building-a-simple-client-server-communication-program-in-c-a5e6d96c97ec)

[Minitalk – 42 Project Gitbook](https://42-cursus.gitbook.io/guide/2-rank-02/minitalk)

[How Does Minitalk Work](https://github.com/leogaudin/minitalk/tree/main)

[Signals in C language](https://www.geeksforgeeks.org/c/signals-c-language/)


### AI Usage

---
AI tools were used as a learning and assistance resource, not as a code generator.

They were used to:
- Clarify project requirements and constraints.
- Understand Signal handling and Bitwise operations
- Improve code structure and readability
