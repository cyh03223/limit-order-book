#ifndef ORDER_H
#define ORDER_H

enum class Side {
    Buy,
    Sell
};

class Order {

public:

    // Constructor
    Order(
        int id,
        double price,
        int quantity,
        Side side,
        long long timestamp
    );

private:

    int id;
    double price;
    int quantity;
    Side side;
    long long timestamp;

};

#endif // ORDER_H