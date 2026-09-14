#include "OrderBook.h"

void OrderBook::addOrder(const Order& order)
{
    const double price = order.getPrice();

    if (order.getSide() == Side::Buy)
    {
        auto it = bids.try_emplace(price, price).first;
        it->second.addOrder(order);
    }
    else
    {
        auto it = asks.try_emplace(price, price).first;
        it->second.addOrder(order);
    }
}

void OrderBook::cancelOrder(int orderId)
{
    for (auto it = bids.begin(); it != bids.end(); ++it)
    {
        if (it->second.removeOrder(orderId))
        {
            if (it->second.empty())
            {
                bids.erase(it);
            }
            return;
        }
    }

    for (auto it = asks.begin(); it != asks.end(); ++it)
    {
        if (it->second.removeOrder(orderId))
        {
            if (it->second.empty())
            {
                asks.erase(it);
            }
            return;
        }
    }
}

const PriceLevel* OrderBook::findPriceLevel(Side side, double price) const
{
    if (side == Side::Buy)
    {
        auto it = bids.find(price);
        return it == bids.end() ? nullptr : &it->second;
    }

    auto it = asks.find(price);
    return it == asks.end() ? nullptr : &it->second;
}

std::size_t OrderBook::priceLevelCount(Side side) const
{
    return side == Side::Buy ? bids.size() : asks.size();
}

void OrderBook::matchOrders()
{
    // TODO: Implement price-time priority matching
}
