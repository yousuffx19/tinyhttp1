# Tinyhttp1

A very basic HTTP 1.1 Server written in C

## Features
- Serves HTML, CSS, JS and image files
- Handles multiple connections at once
- Can serve large files completely
- Custom routes displaying messages
- Reliable response codes
- Supports very small amount of MIME types but enough for general use
- Logs incoming requests onto the terminal

## How to run
- clone the repository into your computer
- run ``make`` and it generates the binary in bin/
- ``./bin/server`` to run the server
- server runs at localhost:8080
- Upload the files you want to serve inside the www folder
- access them by appending their path after localhost:8080

## Built With
- TCP Request Handling
- C POSIX sockets
- POSIX threads for handling mutltiple connections

## Limitations
- Cannot handle very large amount of connections simultaneously
- Only implements 'Connection: Close' and no keep-alive 
- So no chunked transfer-encoding for very large files
- Made with POSIX specific system calls, only expected to work in Unix-like platforms
