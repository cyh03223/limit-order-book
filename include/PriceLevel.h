#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

#include <list>
#include "Order.h"


class PriceLevel {

public:

    // Constructor
    PriceLevel(double price);


    // Add order to this price level
    void addOrder(const Order& order);


    // Remove order by id
    void removeOrder(int orderId);

private:

    double price;

    std::list<Order> orders;

};


#endif
