# Tinyhttp1

A very basic HTTP 1.1 Server written in C

## Features
- Serves HTML, CSS, JS and image files
- Handles multiple connections at once
- Can serve large files completely
- Custom routes displaying messages
- Reliable response codes
- Logs incoming requests onto the terminal

## How to run
- clone the repository into your computer
- run ``make`` and it generates the binary in bin/
- ``cd bin`` and then ``./server`` to run the server
- server runs at localhost:8080
- Upload the files you want to serve inside the bin folder
- access them by appending their path after localhost:8080

## Built With
- TCP Request Handling
- C POSIX sockets
- POSIX threads for handling mutltiple connections

  

