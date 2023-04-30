# 🛰️ minitalk

![Grade Badge](https://img.shields.io/badge/Grade-125-brightgreen)
![Norminette Badge](https://github.com/evandotsh/minitalk/actions/workflows/main.yml/badge.svg)

## Newly Learned Functions
```c
signal();
kill();
sigemptyset();
sigaddset();
sigaction();
getpid();
pause();
```

## Pain Points
- One of the main pain points of this project is that many people tend to forget the part of the subject that explicitly asks you to "print the message once it has been **fully** received." Therefore, printing each character one by one is considered invalid.
- Additionally, only using `signal()` instead of `sigaction()` can result in undefined behavior, where packets are sometimes lost for unknown reasons.

## Implementation
The goal of this project is to create a client-server communication pair that uses UNIX signals to communicate between processes.

In my implementation, the client first checks if the message is valid and the correct number of arguments are passed. Then, for each character, it sends each bit one by one, using `SIGUSR1` to represent a `0` and `SIGUSR2` to represent a `1` it then waits for a `SIGUSR1` signal back to acknowledge that it received and processed the bit before moving on to the next bit.

In the server implementation, each bit is received one by one as either `SIGUSR1` or `SIGUSR2` signal. The bits are processed in order to recreate the character and add it to the buffer. Once the null character `\0` is reached, the server prints the buffer, and then sends a `SIGUSR2` signal back to the client, indicating that the message has been fully received and displayed on the server's side.

```
Example exchange for the letter 'B' (01100010):
client -> SIGUSR1 (0) -> server
server -> SIGUSR1 (ACK) -> client
client -> SIGUSR2 (1) -> server
server -> SIGUSR1 (ACK) -> client
...
```

## How to Run it
📦 Git clone it: `git clone https://github.com/evandotsh/minitalk` \
⚙️ Compile it: `make all` \
Then simply launch `./server` and `./client <server pid> <message>`

⚠️ This version is a cleaned up version of my minitalk, it only contains the bonus part. The subject's rules requires you to submit both the mandatory and bonus part separately. If you're looking for the file structure for bonuses you should take a look at the `defense` branch.

evan.sh • 2023
