#include "bank.hpp"

int main(int argc, char const *argv[]){
    Money m1("USD", 5u, 25u);
    std::cout << m1 << std::endl;

    m1.add_money(5u, 25u);
    std::cout << m1 << std::endl;

    m1.subtract_money(3u, 75u);
    std::cout << m1 << std::endl;

    Exchange ex;
    ex.add_exchange_rate("EUR", 84.11);
    ex.add_exchange_rate("USD", 77.32);
    ex.add_exchange_rate("RUB", 1);

    Wallet w;
    w.add_money(Money("USD", 20u, 0u));
    w.add_money(Money("EUR", 15u, 50u));
    w.add_money(Money("RUB", 5u, 75u));
    std::cout << w << std::endl;

    w.subtract_money(Money("USD", 5u, 50u));
    std::cout << w << std::endl;

    w.exchange_money(Money("USD", 2u, 10u), "EUR", ex);
    std::cout << w << std::endl;

    w.exchange_money(Money("EUR", 15u, 5u), "RUB", ex);
    std::cout << w << std::endl;
    return 0;
}