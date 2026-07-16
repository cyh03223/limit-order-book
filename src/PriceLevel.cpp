#include "PriceLevel.h"


PriceLevel::PriceLevel(double price)
{
    this->price = price;
}

void PriceLevel::addOrder(const Order& order)
{
    orders.push_back(order);
}


void PriceLevel::removeOrder(int orderId)
{

    for(auto it = orders.begin(); it != orders.end(); ++it)
    {

        if(it->getId() == orderId)
        {
            orders.erase(it);
            return;
        }

    }

}
