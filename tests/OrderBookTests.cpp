#include <cassert>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "OrderBook.h"

static_assert(std::is_same_v<decltype(std::declval<PriceLevel&>().front()), Order&>);
static_assert(std::is_same_v<decltype(std::declval<const PriceLevel&>().front()), const Order&>);

void testQuantityReduction()
{
    Order order(7, 100.5, 20, Side::Sell, 123);
    order.reduceQuantity(0);
    assert(order.getQuantity() == 20);
    order.reduceQuantity(6);
    assert(order.getQuantity() == 14);

    for (int amount : {-1, 15})
    {
        bool rejected = false;
        try
        {
            order.reduceQuantity(amount);
        }
        catch (const std::invalid_argument&)
        {
            rejected = true;
        }
        assert(rejected);
        assert(order.getQuantity() == 14);
    }

    order.reduceQuantity(14);
    assert(order.getQuantity() == 0);
    order.reduceQuantity(0);
    assert(order.getQuantity() == 0);
    assert(order.getId() == 7);
    assert(order.getPrice() == 100.5);
    assert(order.getSide() == Side::Sell);
    assert(order.getTimestamp() == 123);
}

void testMatchingQueueAccess()
{
    PriceLevel level(100.0);
    level.addOrder(Order(1, 100.0, 10, Side::Buy, 1));
    level.addOrder(Order(2, 100.0, 20, Side::Buy, 2));
    const PriceLevel& view = level;

    level.front().reduceQuantity(4);
    assert(view.front().getQuantity() == 6);
    assert(view.front().getId() == 1);
    assert(level.size() == 2);
    level.front().reduceQuantity(6);
    assert(view.front().getQuantity() == 0);
    level.popFront();
    assert(level.size() == 1);
    assert(view.front().getId() == 2);
    assert(view.front().getQuantity() == 20);
    level.front().reduceQuantity(20);
    level.popFront();
    assert(level.empty());
    assert(level.size() == 0);
}

void testOrder()
{
    const Order order(7, 100.5, 20, Side::Sell, 123);
    assert(order.getId() == 7);
    assert(order.getPrice() == 100.5);
    assert(order.getQuantity() == 20);
    assert(order.getSide() == Side::Sell);
    assert(order.getTimestamp() == 123);
}

void testPriceLevel()
{
    PriceLevel level(100.0);
    assert(level.empty());
    assert(!level.removeOrder(99));
    level.addOrder(Order(1, 100.0, 10, Side::Buy, 1));
    level.addOrder(Order(2, 100.0, 20, Side::Buy, 2));
    level.addOrder(Order(3, 100.0, 30, Side::Buy, 3));
    assert(level.size() == 3);
    assert(level.front().getId() == 1);
    assert(level.removeOrder(2));
    assert(level.front().getId() == 1);
    assert(!level.removeOrder(99));
    assert(level.size() == 2);
    assert(level.removeOrder(1));
    assert(level.front().getId() == 3);
    assert(level.removeOrder(3));
    assert(level.empty());
}

void testBookSide(Side side, Side oppositeSide)
{
    OrderBook book;
    const OrderBook& view = book;
    assert(view.priceLevelCount(side) == 0);
    assert(view.findPriceLevel(side, 100.0) == nullptr);
    book.cancelOrder(99);

    book.addOrder(Order(1, 100.0, 10, side, 1));
    const PriceLevel* level = view.findPriceLevel(side, 100.0);
    assert(level != nullptr);
    assert(level->size() == 1);
    assert(view.priceLevelCount(oppositeSide) == 0);
    book.addOrder(Order(2, 100.0, 20, side, 2));
    book.addOrder(Order(3, 100.0, 30, side, 3));
    assert(view.findPriceLevel(side, 100.0) == level);
    assert(view.priceLevelCount(side) == 1);
    assert(level->size() == 3);
    assert(level->front().getId() == 1);

    book.addOrder(Order(4, 99.0, 40, side, 4));
    book.addOrder(Order(5, 101.0, 50, side, 5));
    book.addOrder(Order(6, 100.0, 60, oppositeSide, 6));
    assert(view.priceLevelCount(side) == 3);
    assert(view.priceLevelCount(oppositeSide) == 1);
    assert(view.findPriceLevel(side, 99.0)->front().getId() == 4);
    assert(view.findPriceLevel(side, 101.0)->front().getId() == 5);

    book.cancelOrder(99);
    assert(level->size() == 3);
    assert(view.priceLevelCount(side) == 3);
    assert(view.findPriceLevel(oppositeSide, 100.0)->size() == 1);
    book.cancelOrder(1);
    assert(level->size() == 2);
    assert(level->front().getId() == 2);
    book.cancelOrder(2);
    assert(level->front().getId() == 3);
    book.cancelOrder(3);
    assert(view.findPriceLevel(side, 100.0) == nullptr);
    assert(view.priceLevelCount(side) == 2);
    assert(view.findPriceLevel(oppositeSide, 100.0)->front().getId() == 6);
    book.cancelOrder(4);
    book.cancelOrder(5);
    book.cancelOrder(6);
    book.cancelOrder(6);
    assert(view.priceLevelCount(side) == 0);
    assert(view.priceLevelCount(oppositeSide) == 0);
}

int main()
{
    testOrder();
    testQuantityReduction();
    testMatchingQueueAccess();
    testPriceLevel();
    testBookSide(Side::Buy, Side::Sell);
    testBookSide(Side::Sell, Side::Buy);
    std::cout << "All order book tests passed.\n";
}
