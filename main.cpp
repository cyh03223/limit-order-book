#include "PriceLevel.h"
#include <iostream>


int main()
{

    Order order(
        1,
        100.5,
        200,
        Side::Buy,
        123456
    );


    PriceLevel level(100.5);


    level.addOrder(order);


    std::cout << "PriceLevel works!"
              << std::endl;


    return 0;
}
