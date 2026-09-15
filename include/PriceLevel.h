#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

#include <list>
#include <cstddef>
#include "Order.h"


class PriceLevel {

public:

    // Constructor
    PriceLevel(double price);


    // Add order to this price level
    void addOrder(const Order& order);


    // Remove order by id
    bool removeOrder(int orderId);

    bool empty() const;
    std::size_t size() const;
    // Requires a nonempty price level.
    Order& front();
    const Order& front() const;

    // Requires a nonempty price level; invalidates references to the removed order.
    void popFront();

private:

    double price;

    std::list<Order> orders;

};


#endif
