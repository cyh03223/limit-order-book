#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>

#include "Order.h"
#include "PriceLevel.h"

class OrderBook {
public:
    // Add a new order to the book
    void addOrder(const Order& order);

    // Cancel an existing order by ID
    void cancelOrder(int orderId);

    // Match compatible buy and sell orders
    void matchOrders();

private:
    // Buy orders: highest price has priority
    std::map<double, PriceLevel, std::greater<double>> bids;

    // Sell orders: lowest price has priority
    std::map<double, PriceLevel> asks;
};

#endif
