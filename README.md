# Limit Order Book

A simplified C++ limit order book implementation for learning trading system fundamentals, 
market microstructure, and high-performance system design.

The goal of this project is to build a small but realistic trading engine from scratch, 
focusing on clean C++ design, data structures, and performance considerations.

---

## Project Overview

A limit order book (LOB) is a core component of electronic trading systems.

This project simulates the basic workflow of an exchange:

- Receiving orders
- Maintaining buy and sell order queues
- Matching compatible orders
- Managing order lifecycle

The implementation is built in modern C++ with emphasis on:

- Object-oriented design
- Efficient data structures
- Low-latency programming concepts
- Clean and maintainable code

---

# Current Progress

## Core Components

- ✅ Project initialized
- ✅ Order class
- ✅ PriceLevel
- 🚧 OrderBook skeleton
- ⏳ Matching Engine

## Engineering

- ⏳ Unit testing
- ⏳ Performance benchmarking
- ⏳ Documentation

---

# Roadmap

## Phase 1 — Core Data Structures

Goal:
Build the fundamental components required for a limit order book.

### Order

Status: ✅ Completed

Responsibilities:

- Store order information
- Represent buy/sell direction
- Maintain order metadata

---

### PriceLevel

### PriceLevel

Status: ✅ Completed

Goal:

Represent all orders at the same price level.

Structure: 

PriceLevel

Price: 100.50

Order 1 → Order 2 → Order 3

Responsibilities:

- Store orders with the same price
- Maintain FIFO ordering
- Add new orders
- Remove orders by order ID


Implemented:

- PriceLevel class
- Header/source separation
- std::list<Order> order container
- Order insertion and removal logic
