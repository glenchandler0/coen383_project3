#include "Seller.h"

Seller::Seller(char seller_type, unsigned int seller_id)
{
   
    if(seller_type == 'L')
        service_time = rand() % 7 +4;
    else if(seller_type == 'M')
        service_time = rand() % 4 + 2;
    else if(seller_type == 'H')
        service_time = rand() % 2 + 1;
    else{
        throw std::runtime_error("Incorrect seller type");
    }

    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->tickets_sold = 0;
    // this->q = new std::priority_queue<Customer, std::vector<Customer>, Seller::CompareArrivalTime>;
}

void Seller::sellTicket()
{
    this->tickets_sold++;
}

char Seller::getSellerType(){
    return seller_type;
}

unsigned int Seller::getSellerId()
{
    return seller_id;
}

unsigned int Seller::getTicketsSold()
{
    return this->tickets_sold;
}
