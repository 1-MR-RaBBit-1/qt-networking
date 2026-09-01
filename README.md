# Qt TCP Network Learning Project

A small networking project written in **C++ and Qt 6**.

The purpose of this project is to learn computer networking step by step by building a simple **TCP Client/Server application** and eventually using the network to control a **Qt3D object** on another computer.

This project is mainly for learning. The code will be developed gradually as new networking concepts are learned.

---

## 🎯 Main Goal

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
```

The project will start with communication between two programs on the same computer using `localhost`, and later move to communication between two different computers.

---

# 📚 Learning Progress

## Basic Networking

* [x] Understand `127.0.0.1`
* [x] Understand `localhost`
* [x] Understand IP addresses
* [x] Understand ports
* [x] Learn the basic purpose of TCP
* [x] Learn the basic purpose of UDP
* [x] Learn the `ss` command
* [x] Learn the `grep` command
* [ ] Understand network interfaces in more detail
* [ ] Understand routing
* [ ] Understand private IP addresses
* [ ] Understand network masks
* [ ] Understand gateways

## Qt Networking

* [x] Create a `QTcpServer`
* [x] Create a `QTcpSocket`
* [x] Make a server listen on a port
* [x] Connect a client to a server
* [x] Detect a new client connection
* [x] Use `nextPendingConnection()`
* [x] Use the `connected` signal
* [x] Use the `readyRead` signal
* [x] Send data with `write()`
* [x] Receive data with `readAll()`
* [x] Learn `QByteArray`
* [x] Learn basic `QDataStream`
* [x] Send an integer
* [x] Send a `QString`
* [ ] Understand TCP message boundaries
* [ ] Handle partial TCP data correctly
* [ ] Create a proper message protocol

## Client / Server

* [x] Create a separate Server project
* [x] Create a separate Client project
* [x] Run the Server independently
* [x] Run the Client independently
* [x] Connect Client to Server using `localhost`
* [ ] Communicate between two computers
* [ ] Send data over a real network
* [ ] Handle connection errors
* [ ] Handle disconnections
* [ ] Allow multiple clients

## Qt3D

* [x] Create a Qt3D window
* [x] Create a sphere
* [x] Change sphere position
* [x] Change sphere rotation
* [x] Animate the sphere
* [x] Change the sphere color
* [ ] Send sphere coordinates through TCP
* [ ] Receive coordinates on another computer
* [ ] Move the remote sphere using received data

## UDP

* [x] Learn the basic idea of UDP
* [ ] Create a `QUdpSocket`
* [ ] Send a UDP packet
* [ ] Receive a UDP packet
* [ ] Compare TCP and UDP
* [ ] Test UDP for real-time position updates

---

# 🏗️ Current Architecture

The project currently consists of two separate applications:

```text
network/
│
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
```

The Server uses:

```cpp
QTcpServer
```

The Client uses:

```cpp
QTcpSocket
```

---

# 🔌 Current TCP Connection

At the moment, the Client connects to the Server using:

```text
IP: 127.0.0.1
Port: 5000
```

`127.0.0.1` refers to the local computer itself.

The current connection looks like this:

```text
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
```

---

# 📦 Data Transfer

The project has also started using `QDataStream` to transfer structured data.

For example:

```cpp
int number = 42;
QString word = "hello";

stream << number;
stream << word;
```

The Server reads the data in the same order:

```cpp
int number;
QString word;

stream >> number;
stream >> word;
```

The basic idea is:

```text
Client

int
QString
 │
 ▼
QDataStream
 │
 ▼
TCP
 │
 ▼
QDataStream
 │
 ▼
Server

int
QString
```

---

# 🧠 Important Concepts Learned

## localhost

`localhost` is another name for the local computer.

It normally resolves to:

```text
127.0.0.1
```

When a program connects to `127.0.0.1`, the connection stays inside the same computer.

---

## Port

A port identifies a particular network service or endpoint on a computer.

This project currently uses:

```text
5000
```

So the Server listens on:

```text
127.0.0.1:5000
```

---

## TCP

TCP is a transport-layer protocol that provides a reliable ordered byte stream between two endpoints.

One important thing learned during this project is that TCP does **not** preserve application message boundaries.

A call to:

```cpp
write()
```

does not necessarily correspond to exactly one call to:

```cpp
readyRead()
```

Therefore, a real application needs to define how messages are separated or framed.

---

## QByteArray

`QByteArray` is a Qt container for byte data.

Network communication ultimately deals with bytes, so Qt uses `QByteArray` in many networking APIs.

For example:

```cpp
QByteArray data = socket->readAll();
```

means that the currently available received bytes are read into a `QByteArray`.

---

## QDataStream

`QDataStream` provides a convenient way to serialize and deserialize Qt/C++ data types.

For example:

```cpp
stream << number;
```

writes a value into the stream.

And:

```cpp
stream >> number;
```

reads it back.

---

# 🛠️ Technologies

* **C++**
* **Qt 6**
* **Qt Widgets**
* **Qt Network**
* **Qt3D**
* **CMake**
* **TCP**
* **UDP** (planned)

---

# 🚧 Current Status

The project currently has a working TCP Client and Server running on the same computer.

The next major step is to move the communication from:

```text
localhost
```

to:

```text
Computer 1
        │
        │ Ethernet / Network
        │
        ▼
Computer 2
```

After that, the plan is to send the position of a Qt3D object over the network.

---

# 🗺️ Roadmap

### Phase 1 — Networking Basics

Learn:

* IP addresses
* localhost
* ports
* TCP
* UDP
* sockets
* basic Linux networking commands

### Phase 2 — TCP Client/Server

Build:

* TCP Server
* TCP Client
* connection handling
* data sending
* data receiving
* message framing

### Phase 3 — Two Computers

Connect two physical computers and send data between them.

### Phase 4 — Qt3D Networking

Send:

```text
X
Y
Z
```

coordinates through TCP.

The receiving computer will use those coordinates to move a Qt3D object.

### Phase 5 — UDP

Implement the same basic idea using UDP and compare it with TCP, especially for real-time movement.

---

# 🎓 Purpose of the Project

This project is not intended to be a production networking framework.

The main purpose is to learn networking concepts by actually building them from the ground up.

Instead of learning networking only theoretically, each concept will be introduced and tested through code.

---

## Current Objective

> Make two separate Qt applications communicate over TCP, then use that connection to control a Qt3D object on another computer.
