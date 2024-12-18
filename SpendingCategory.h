#ifndef SPEND_H
#define SPEND_H

#include <iostream>
#include <string>

using namespace std;

class SpendingCategory{
    private:
        string categoryName;
        double limit;
        double currentSpend;

    public:
        SpendingCategory(string name, double limit)
            : categoryName(name), limit(limit), currentSpend(0){}

        void addSpend(double amount){
            currentSpend += amount;
            if (currentSpend > limit){
                cout << "Warning: You have exceeded the limit for " << categoryName << endl;
            }
        }

        void setCategoryLimit(double newLimit){
            limit = newLimit;
        }
        
        double getCurrentLimit(){
            return limit;
        }

        bool checkLimit(){
            return currentSpend <= limit;
        }

        string getName(){
            return categoryName;
        }

        void getCategoryStatistics(){
            cout << "Category: " << categoryName << " | Limit: " << limit
                << " | Current Spend: " << currentSpend << endl;
        }
};

#endif