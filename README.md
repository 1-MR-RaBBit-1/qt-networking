# Qt TCP Network Learning Project

A small networking project written in **C++ and Qt 6**.

The purpose of this project is to learn computer networking step by step by building a simple **TCP Client/Server application** and eventually using the network to control a **Qt3D object** on another computer.

This project is mainly for learning. The code will be developed gradually as new networking concepts are learned.

---

# 🎯 Main Goal

The final goal is to have two computers communicate over a network.

The first computer will control a 3D object, and its position will be sent through the network to the second computer.

For example:

```text
Computer 1                         Computer 2

   │                                  │
   │                                  │
   │       TCP connection             │
   │ ───────────────────────────────> │
   │                                  │
   │      x, y, z position            │
   │ ───────────────────────────────> │
   │                                  │
   ▼                                  ▼

Qt3D Object                       Qt3D Object

The project starts with communication between two programs on the same computer using localhost, and will later move to communication between two different computers.

📚 Learning Progress
Basic Networking
 Understand 127.0.0.1
 Understand localhost
 Understand IP addresses
 Understand ports
 Learn the basic purpose of TCP
 Learn the basic purpose of UDP
 Learn the ss command
 Learn the grep command
 Understand network interfaces in more detail
 Understand routing
 Understand private IP addresses
 Understand network masks
 Understand gateways
Qt Networking
 Create a QTcpServer
 Create a QTcpSocket
 Make a server listen on a port
 Connect a client to a server
 Detect a new client connection
 Use nextPendingConnection()
 Use the connected signal
 Use the readyRead signal
 Send data with write()
 Receive data with readAll()
 Learn QByteArray
 Learn basic QDataStream
 Send an integer
 Send a QString
 Understand TCP message boundaries
 Handle partial TCP data correctly
 Create a proper message protocol
 Handle connection errors
 Handle disconnections
 Support multiple clients
🖥️ Client / Server

The project currently consists of two separate Qt applications.

network/

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

The Server uses:

QTcpServer

The Client uses:

QTcpSocket
🔌 Current TCP Connection

At the moment, the Client connects to the Server using:

IP:   127.0.0.1
Port: 5000

127.0.0.1 refers to the local computer itself.

The current connection looks like this:

Client
  │
  │ QTcpSocket
  │
  │ connectToHost(127.0.0.1, 5000)
  │
  ▼
Server
  │
  │ QTcpServer
  │
  │ listen(127.0.0.1, 5000)
  ▼

The server and client currently run as independent applications.

📦 Current Data Transfer

The project uses QDataStream to serialize and transfer data.

For example, the Client can send a QString:

QString text = message->text();

QDataStream stream(socket);
stream << text;

The Server reads the data:

QDataStream stream(clientSocket);

QString text;
stream >> text;

The basic communication flow is:

Client

QLineEdit
   │
   │ QString
   ▼
QDataStream
   │
   ▼
TCP Socket
   │
   ▼
TCP Connection
   │
   ▼
TCP Socket
   │
   ▼
QDataStream
   │
   ▼
Server

QLineEdit

The Client currently has a QLineEdit for entering messages and a QPushButton for sending them.

The Server receives the message and displays it in its GUI.

🧠 Important Concepts Learned
localhost

localhost is a hostname that refers to the local computer.

It commonly resolves to:

127.0.0.1

When a program connects to 127.0.0.1, the connection stays inside the same computer.

IP Address

An IP address identifies a network interface or host on an IP network.

For example:

127.0.0.1
192.168.1.20
10.0.0.5

The project currently uses:

127.0.0.1

because both applications are running on the same computer.

Later, the project will use a real local-network IP address to communicate between two computers.

Port

A port identifies a network endpoint used by an application or service.

This project currently uses:

5000

So the Server listens on:

127.0.0.1:5000
🌐 TCP

TCP is a transport-layer protocol that provides a reliable, ordered byte stream between two endpoints.

One of the most important concepts learned during this project is:

TCP does not preserve application message boundaries.

For example, the Client might perform:

stream << "Hello";
stream << "World";

This does not guarantee that the Server will receive:

Hello
World

as two separate readyRead() events.

The data could arrive as:

HelloWorld

or:

Hel
loWorld

or in another segmentation.

Therefore, real applications need a way to define where one message ends and another begins.

This is called message framing.

📡 readyRead()

The readyRead signal indicates that new data is available to read from the socket.

For example:

connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {

    QDataStream stream(clientSocket);

    QString text;
    stream >> text;

    qDebug() << text;
});

However:

readyRead() != one complete message

A single signal may contain:

part of a message
one complete message
multiple messages

Understanding this behavior is one of the next major goals of the project.

📦 QByteArray

QByteArray is a Qt container for raw byte data.

Network communication ultimately works with bytes.

For example:

QByteArray data = socket->readAll();

reads the currently available bytes from the socket.

QByteArray will become particularly important when implementing TCP message framing manually.

📊 QDataStream

QDataStream provides serialization and deserialization of many Qt and C++ data types.

For example:

int number = 42;

stream << number;

writes an integer into the stream.

The receiving side can read it:

int number;

stream >> number;

The same concept works with types such as:

QString
int
float
double
QByteArray

The sender and receiver must agree on the order and structure of the data.

For example:

stream << number;
stream << word;

must be read in the same order:

stream >> number;
stream >> word;
🧩 Message Framing

The next major networking concept is message framing.

Because TCP is a byte stream, the application needs to define how messages are separated.

One possible approach is to send the message size before the message:

┌──────────────┬─────────────────────┐
│ Message Size │ Message Data        │
└──────────────┴─────────────────────┘

For example:

[5][Hello]

The receiver can then know that it must wait until all 5 bytes of the message have arrived.

The project will eventually implement this concept properly.

🧱 Partial TCP Data

TCP data may arrive in multiple pieces.

For example, the Client might send:

Hello World

but the Server could receive:

Hello

first and:

 World

later.

Therefore, the Server may need to store incoming data temporarily:

Incoming TCP data
       │
       ▼
Buffer
       │
       ├── incomplete message → wait
       │
       └── complete message → process

This will be implemented in the next stage of the project.

🏗️ Current Architecture

The current system looks like this:

┌──────────────────┐
│      Client      │
│                  │
│    QLineEdit     │
│        │         │
│        ▼         │
│   QDataStream    │
│        │         │
│        ▼         │
│   QTcpSocket     │
└────────┬─────────┘
         │
         │ TCP
         │
         │ 127.0.0.1:5000
         │
┌────────▼─────────┐
│      Server      │
│                  │
│   QTcpServer     │
│        │         │
│        ▼         │
│   QTcpSocket     │
│        │         │
│        ▼         │
│   QDataStream    │
│        │         │
│        ▼         │
│    GUI Display   │
└──────────────────┘
🛠️ Technologies
C++
Qt 6
Qt Widgets
Qt Network
Qt3D
CMake
TCP
UDP (planned)
🚧 Current Status

The project currently has a working TCP Client and Server running on the same computer.

The Client can:

connect to the Server
accept text input through a QLineEdit
send the text through TCP
serialize the data using QDataStream

The Server can:

listen for incoming connections
detect new clients
receive data
deserialize the QString
display the received message

The current system is intentionally simple because the main purpose is learning.

🗺️ Roadmap
Phase 1 — Networking Basics

Learn:

IP addresses
localhost
ports
TCP
UDP
sockets
Linux networking commands
Phase 2 — TCP Client / Server

Build:

TCP Server
TCP Client
connection handling
data sending
data receiving
QByteArray
QDataStream
message framing
partial data handling
basic message protocol
error handling
disconnection handling
multiple clients
Phase 3 — Two Computers

Move from:

localhost

to:

Computer 1
     │
     │ Ethernet / Wi-Fi
     │
     ▼
Computer 2

The Client and Server will communicate using the real IP address of the computer running the Server.

Phase 4 — Qt3D Networking

Send the position of a Qt3D object:

X
Y
Z

For example:

X = 10.5
Y = 2.0
Z = -4.5

The receiving computer will use the received coordinates to move its own Qt3D object.

The final concept will look like:

Computer 1                         Computer 2

Qt3D Object                        Qt3D Object
     │                                  ▲
     │                                  │
     │ position                         │ position
     │                                  │
     ▼                                  │
QTcpSocket ───────── TCP ─────────> QTcpSocket
Phase 5 — UDP

Implement the same basic position-transfer system using UDP.

Learn:

QUdpSocket
sending datagrams
receiving datagrams
packet-based communication
TCP vs UDP
reliability vs latency
real-time position updates

The goal is to compare TCP and UDP for continuously changing Qt3D object positions.

🎓 Purpose of the Project

This project is not intended to be a production networking framework.

The main purpose is to learn networking concepts by actually building them from the ground up.

Instead of learning networking only theoretically, each concept will be introduced and tested through code.

The project intentionally starts simple and becomes more advanced over time.

📍 Current Learning Point

The TCP Client/Server connection is working.

The next major concept to learn is:

TCP Message Framing
        │
        ▼
Partial TCP Data
        │
        ▼
Message Buffer
        │
        ▼
Complete Message

After understanding this, the project can safely move toward sending structured data such as:

X
Y
Z

and eventually controlling a Qt3D object over a real network.

🎯 Current Objective

Make two separate Qt applications communicate reliably over TCP, understand how TCP streams and message boundaries work, then use that connection to control a Qt3D object on another computer.
