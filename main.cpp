#include <iostream>

#include "Order.h"

int main(){

    Order order(
        1,
        100.5,
        200,
        Side::Buy,
        123456789
    ); // declare an order object

     std::cout << "Order created successfully!" << std::endl;

    return 0;
};