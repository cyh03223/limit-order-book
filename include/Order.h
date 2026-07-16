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

    // const method to get the price level's price
    int getId() const; 

private:

    int id;
    double price;
    int quantity;
    Side side;
    long long timestamp;

};

#endif // ORDER_H