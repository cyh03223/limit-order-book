#include "PriceLevel.h"


PriceLevel::PriceLevel(double price)
{
    this->price = price;
}

void PriceLevel::addOrder(const Order& order)
{
    orders.push_back(order);
}

bool PriceLevel::empty() const
{
    return orders.empty();
}

std::size_t PriceLevel::size() const
{
    return orders.size();
}

const Order& PriceLevel::front() const
{
    return orders.front();
}

Order& PriceLevel::front()
{
    return orders.front();
}

void PriceLevel::popFront()
{
    orders.pop_front();
}


bool PriceLevel::removeOrder(int orderId)
{

    for(auto it = orders.begin(); it != orders.end(); ++it)
    {

        if(it->getId() == orderId)
        {
            orders.erase(it);
            return true;
        }

    }

    return false;

}
