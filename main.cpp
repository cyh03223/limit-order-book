#include <iostream>

#include "OrderBook.h"

int main()
{
    OrderBook orderBook;

    Order order(
        1,
        100.50,
        200,
        Side::Buy,
        123456789
    );

    orderBook.addOrder(order);
    orderBook.cancelOrder(1);
    orderBook.matchOrders();

    std::cout << "OrderBook skeleton compiled successfully."
              << std::endl;

    return 0;
}
