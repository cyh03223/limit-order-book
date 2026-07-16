#include "Order.h"


Order::Order(
    int id,
    double price,
    int quantity,
    Side side,
    long long timestamp
)
{
    this->id = id;
    this->price = price;
    this->quantity = quantity;
    this->side = side;
    this->timestamp = timestamp;
}
