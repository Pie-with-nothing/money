#include "bank.hpp"

Money::Money(std::string cur, unsigned whole, unsigned fract){
    if(cur.empty()){
        throw std::invalid_argument("Wrong curency format");
    }
    currency = cur;
    whole_part = whole + fract / 100;
    fractional_part = fract % 100;
}
std::string Money::get_currency() const{
    return currency;
}
unsigned int Money::get_whole_part() const{
    return whole_part;
}
unsigned int Money::get_fractional_part() const{
    return fractional_part;
}
void Money::add_money(unsigned whole, unsigned fract){
    whole_part += whole + fract / 100;
    fractional_part += fract % 100;
}
void Money::subtract_money(unsigned whole, unsigned fract){
    if((whole_part * 100 + fractional_part) < (whole * 100 + fract)){
        throw std::invalid_argument("Not enough money");
    }
    if(fractional_part < fract % 100){
        whole_part--;
        fractional_part += 100;
    }
    whole_part -= whole + fract / 100;
    fractional_part -= fract % 100;
}
std::ostream& operator<<(std::ostream& os, const Money &m){
    os << m.currency << " " << m.whole_part << "." << m.fractional_part;
    return os;
}
void Exchange::add_exchange_rate(std::string cur, double rate){
    if(cur.empty()){
        throw std::invalid_argument("Wrong curency format");
    }
    exchange_rates[cur] = rate;
} 
double Exchange::get_exchange_rate(std::string cur) const{
    auto item = exchange_rates.find(cur);
    if(item != exchange_rates.end()){
        return item->second;
    }
    throw std::invalid_argument("Currency not found");
}
void Wallet::add_money(Money m){
    bool found_currency = false;
    for(auto &ml : money_list){
        if(ml.get_currency() == m.get_currency()){
            ml.add_money(m.get_whole_part(), m.get_fractional_part());
            found_currency = true;
            break;
        }
    } 
    if(!found_currency){
        money_list.push_back(m);
    }
}
void Wallet::subtract_money(Money m){
    for(auto &ml : money_list){
        if(ml.get_currency() == m.get_currency()){
            ml.subtract_money(m.get_whole_part(), m.get_fractional_part());
            break;
        }
    }
}
void Wallet::exchange_money(Money m, std::string new_curr, Exchange &ex){
    if(new_curr.empty()){
        throw std::invalid_argument("Wrong curency format");
    }
    double exchange_rate = ex.get_exchange_rate(m.get_currency());
    double new_exchange_rate = ex.get_exchange_rate(new_curr);
    double rate = exchange_rate / new_exchange_rate;
    subtract_money(m);
    unsigned new_whole = (unsigned)((m.get_whole_part() + m.get_fractional_part() / 100) * rate);
    unsigned new_fract = (unsigned)(std::round((m.get_fractional_part() % 100) * rate));
    add_money(Money(new_curr, new_whole, new_fract));
}
std::ostream &operator<<(std::ostream &os, const Wallet &w){
    for(auto &ml : w.money_list){
        os << ml << std::endl;
    }
    return os;
}
