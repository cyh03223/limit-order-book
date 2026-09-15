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
- ✅ OrderBook insertion and cancellation (including empty-level cleanup)
- ⏳ Matching Engine

## Engineering

- ✅ Basic assertion tests for insertion, FIFO, and cancellation
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


### OrderBook

Buy price levels use a descending `std::map`; sell price levels use an
ascending `std::map`. Each level stores orders in FIFO insertion order.
`addOrder()` uses C++17 `try_emplace(price, price)` to find or create a level:
the first argument is the map key and the second constructs `PriceLevel`.
Cancellation searches bids and asks and erases a level when its last order is removed.

Read-only inspection uses `findPriceLevel()` (null when absent),
`priceLevelCount()`, and `PriceLevel::empty()`, `size()`, and `front()`.
Only call `front()` on a nonempty level. A returned level pointer becomes invalid
when that level is erased or the book is destroyed.

Order IDs are expected to be unique; duplicate-ID validation is not implemented.
`addOrder()` only stores orders, and `matchOrders()` remains a placeholder.
Next: implement FIFO matching with full and partial fills, then trade records.
Benchmarking and optimization follow correctness tests.

Matching preparation is complete: `Order::reduceQuantity(amount)` updates the
remaining quantity and throws `std::invalid_argument` for negative amounts or
amounts above the remaining quantity. Zero is a no-op. Mutable `PriceLevel::front()`
allows updating the oldest order, while the const overload remains available for
inspection. `popFront()` removes that order and invalidates references to it.
Both front access and removal require a nonempty level. Tests cover quantity
reduction, rejected reductions, both front overloads, and FIFO removal.

## Build and test

From the repository root, using a C++17 compiler:

```bash
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/Order.cpp src/PriceLevel.cpp src/OrderBook.cpp main.cpp -o build/order_book
./build/order_book

g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/Order.cpp src/PriceLevel.cpp src/OrderBook.cpp tests/OrderBookTests.cpp -o build/order_book_tests
./build/order_book_tests
```

Tests cover order getters, removal success/failure, both sides of insertion,
price-level reuse, FIFO, multiple prices, cancellation on both sides, missing IDs,
and final-order cleanup. Build tests without `-DNDEBUG` so assertions execute.
