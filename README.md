# Qt TCP Client-Server

A simple TCP Client/Server application built with **C++ and Qt 6**.

This project is a learning project created to understand how TCP networking works in Qt by building a Client and a Server from scratch.

---

## 📌 About

The project consists of two separate Qt applications:

```text
TCP-Networking/

├── client/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── mainwindow.cpp
│   └── mainwindow.h
│
├── server/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── mainwindow.cpp
│   └── mainwindow.h
│
└── README.md

The Server waits for incoming TCP connections.

The Client connects to the Server and can send text messages.

🖥️ Server

The Server is built using:

QTcpServer

It listens for incoming connections on:

127.0.0.1:5000

When a Client connects, the Server obtains its socket using:

server->nextPendingConnection();

The Server then waits for incoming data using:

readyRead

Received messages are displayed in the Server GUI.

💻 Client

The Client is built using:

QTcpSocket

It connects to:

127.0.0.1:5000

The Client GUI contains:

QLineEdit for entering a message
QPushButton for sending the message

The entered text is sent to the Server through the TCP socket.

🔌 Connection

The current connection is:

Client
   │
   │ QTcpSocket
   │
   │ 127.0.0.1:5000
   │
   ▼
Server
   │
   │ QTcpServer
   ▼

Both applications currently run on the same computer.

📦 Data Transfer

The project currently uses QDataStream to serialize data.

Client:

QString text = message->text();

QDataStream stream(socket);
stream << text;

Server:

QDataStream stream(clientSocket);

QString text;
stream >> text;

The data flow is:

QLineEdit
    │
    │ QString
    ▼
QDataStream
    │
    ▼
QTcpSocket
    │
    ▼
     TCP
    │
    ▼
QTcpSocket
    │
    ▼
QDataStream
    │
    ▼
Server GUI
🧠 Concepts Learned

This project currently covers the following concepts:

127.0.0.1
localhost
IP addresses
Ports
TCP
QTcpServer
QTcpSocket
nextPendingConnection()
connected signal
readyRead signal
QByteArray
readAll()
write()
QDataStream
Sending int
Sending QString
Basic Client/Server architecture
Qt signals and slots
Qt layouts and widgets
⚠️ TCP Stream

One important concept in this project is that TCP is a byte stream.

TCP does not preserve application-level message boundaries.

For example, if the Client sends:

Hello
World

the Server is not guaranteed to receive them as two separate pieces.

Data may arrive as:

HelloWorld

or:

Hel
loWorld

or in another segmentation.

Therefore, readyRead() does not necessarily mean that one complete message has arrived.

🚧 Current Limitations

This is a basic learning implementation.

Currently it does not properly handle:

TCP message framing
Partial messages
Multiple messages arriving together
Connection errors
Client disconnection
Multiple clients

These will be implemented as the project develops.

🎯 Current Goal

The current goal is to understand TCP communication between a Qt Client and Server.

The next step is to implement proper TCP message framing and learn how to correctly handle partial data.

🛠️ Technologies
C++
Qt 6
Qt Widgets
Qt Network
CMake
TCP
📖 Purpose

This project is primarily for learning.

Instead of using a ready-made networking system, the Client and Server are being built step by step to understand how TCP communication actually works in Qt
