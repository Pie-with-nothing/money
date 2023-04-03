#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <cmath>

class Money{
    private:
        std::string currency;
        unsigned int whole_part;
        unsigned int fractional_part;
    public:
        //explicit dont work
        Money(std::string currency, unsigned whole, unsigned fract);
        inline std::string get_currency() const;
        inline unsigned int get_whole_part() const;
        inline unsigned int get_fractional_part() const;
        //void set_currency(std::string curr);
        //void set_whole_part(int whole);
        //void set_fractional_part(int fract);
        friend std::ostream &operator<<(std::ostream &os, const Money &m);
        void add_money(unsigned whole, unsigned fract);
        void subtract_money(unsigned whole, unsigned fract);

        template <typename T> //no cast!!
        Money(std::string, T, T) = delete;

        template <typename T> //no cast!!
        void add_money(T, T) = delete;

        template <typename T> //no cast!!
        void subtract_money(T, T) = delete;
};

class Exchange{
    private:
        std::map<std::string, double> exchange_rates;
    public:
        void add_exchange_rate(std::string currency, double rate);
        double get_exchange_rate(std::string currency) const;
};

class Wallet{
    private:
        std::vector<Money> money_list;
    public:
        void add_money(Money m);
        void subtract_money(Money m);
        void exchange_money(Money m, std::string new_curr, Exchange &ex);
        friend std::ostream &operator<<(std::ostream &os, const Wallet &w);
};
