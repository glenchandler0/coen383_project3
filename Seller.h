#ifndef __SELLER_H__
#define __SELLER_H__

#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <queue> 

#include "Customer.h"

struct CompareArrivalTime {
    bool operator()(Customer* &lhs, Customer* &rhs) {
       return lhs->getArrivalTime() > rhs->getArrivalTime();
    }
};

typedef std::priority_queue<Customer*, std::vector<Customer*>, CompareArrivalTime> pq;
typedef std::queue<Customer*> q;

class Seller
{
    private:
        unsigned int service_time;
        char seller_type;
        unsigned int seller_id;
        unsigned int tickets_sold;
        unsigned int N;

        pq *waiting;
        q *ready;

    public:

        // Constructor
        Seller(char seller_type, unsigned int seller_id, unsigned int N);

        // Getters
        char getSellerType();
        unsigned int getSellerId();
        unsigned int getTicketsSold();
        bool customers_left();

        // Setters/Helpers
        void addToWaitingQueue(Customer *new_customer);
        unsigned int purge_queues();
        void sellTicket();

        // Call this every new minute
        void update(unsigned int current_minute);

        // For debugging
        pq* getWaitingQueue(){return this->waiting;}
        q* getReadyQueue(){return this->ready;}


};


#endif