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

int Order::getId() const
{
    return id;
}

double Order::getPrice() const
{
    return price;
}

int Order::getQuantity() const
{
    return quantity;
}

Side Order::getSide() const
{
    return side;
}

long long Order::getTimestamp() const
{
    return timestamp;
}
