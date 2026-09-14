#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <cstddef>
#include <functional>

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

    // Returns nullptr if the price level does not exist.
    // The pointer remains valid until that level is erased or the book is destroyed.
    const PriceLevel* findPriceLevel(Side side, double price) const;
    std::size_t priceLevelCount(Side side) const;

private:
    // Buy orders: highest price has priority
    std::map<double, PriceLevel, std::greater<double>> bids;

    // Sell orders: lowest price has priority
    std::map<double, PriceLevel> asks;
};

#endif
