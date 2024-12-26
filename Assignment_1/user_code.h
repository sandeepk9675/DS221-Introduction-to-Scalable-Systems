#ifndef USER_CODE_H
#define USER_CODE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <set>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>
#include "fileIterator.h"
#include "fileWriter.h"

using namespace std;

// Global variable declaration for question 3
unordered_map<int, set<string>> globalproductHashtags;

//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param hashtags 
 * @param purchases 
 * @param prices 
 */

// Custom hash function for vector<string>
struct VectorStringHash {
    size_t operator()(const vector<string>& vec) const {
        size_t seed = vec.size();
        for (const auto& str : vec) {
            seed ^= hash<string>()(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};


void groupCustomersByHashtags(fileIterator& hashtags, fileIterator& purchases,fileIterator& prices, int k, string outputFilePath)
{
    // map product to hashtags
    unordered_map<int, set<string>> productHashtags;

    // Step 1: Read the hashtags and build a map of product to hashtags
    while (hashtags.hasNext()) {
        string line = hashtags.next();
        if(line.size() > 0){
            stringstream ss(line);
            int product;
            string temp;
            getline(ss, temp, ',');  // Read up to the first comma
            product = stoi(temp);    // Convert to intger
            while (getline(ss, temp, ',')) {
                // convert temp to lower case
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                productHashtags[product].insert(temp);   
            }
        }
    }
    

    // Map customer ID to their hashtag frequency (i.e., interests)
    unordered_map<int, unordered_map<string, int>> customerInterests;

    // Step 2: Read the purchases and build each customer's interest list based on purchased products' hashtags
    while (purchases.hasNext()) {
        string line = purchases.next();
        if (line.size() > 0){
            stringstream ss(line);
            int customer, product;
            string temp;
            getline(ss, temp, ',');
            customer = stoi(temp);
            getline(ss, temp, ',');
            product = stoi(temp);
            for (const auto& hashtag : productHashtags[product]) {
                customerInterests[customer][hashtag]++;
           }
        }
    }


    // Step 3: For each customer, extract the top-k most frequent hashtags
    unordered_map<vector<string>, vector<int>, VectorStringHash> groupedCustomers;
    for (auto& customerInterestPair : customerInterests) {
        int customer = customerInterestPair.first;
        auto& interestMap = customerInterestPair.second;
        // Sort hashtags by frequency (descending order) and then lexicographically
        vector<pair<string, int>> freqHashtags(interestMap.begin(), interestMap.end());

        sort(freqHashtags.begin(), freqHashtags.end(), [](const auto& a, const auto& b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second > b.second;
        });

        // Extract the top-k hashtags
        vector<string> topKHashtags;
        for (int i = 0; i < min(k, (int)freqHashtags.size()); ++i) {
            topKHashtags.push_back(freqHashtags[i].first);
        }
        //sort the topKHashtags
        sort(topKHashtags.begin(), topKHashtags.end());

        // Group customers who share the same top-k hashtags
        groupedCustomers[topKHashtags].push_back(customer);
    }

    
     // cout << "Grouped Customers: ";
    for(const auto& temp : groupedCustomers){
        writeOutputToFile(temp.second, outputFilePath);
    }
    return;
}

//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param customerList 
 * @param purchases 
 * @param prices
 */
float calculateGroupAverageExpense(vector<int> customerList, fileIterator& purchases,fileIterator& prices){

    unordered_map<int, vector<int>> customerPurchases;  // Maps customer ID to the list of product IDs
    unordered_map<int, float> productPrices;            // Maps product ID to price

    // Step 1: Load purchase data into a map
    while (purchases.hasNext()) {
        
        string line = purchases.next();
        if (line.size() != 0){
            stringstream ss(line);
            int customer, product;
            string temp;
            getline(ss, temp, ',');
            customer = stoi(temp);
            while (getline(ss, temp, ',')) {
                product = stoi(temp);
                customerPurchases[customer].push_back(product);   
            }
        }
    }
    // Step 2: Load price data into a map
    while (prices.hasNext()) {

        string line = prices.next();
        if (line.size() != 0){
            stringstream ss(line);
            string temp;
            int product;
            float price;
            getline(ss, temp, ',');
            product = stoi(temp);
            getline(ss, temp, ',');
            price = stof(temp);
            productPrices[product] = price; // Map product to price
        }
    }

    // Step 3: Calculate the total expense for the group
    float totalExpense = 0.0;
    int totalProducts = 0;

    for (int customer : customerList) {
        if (customerPurchases.find(customer) != customerPurchases.end()) {
            for (int product : customerPurchases[customer]) {
                if (productPrices.find(product) != productPrices.end()) {
                    totalExpense += productPrices[product];
                    totalProducts++;
                }
            }
        }
    }

    // Step 4: Calculate the average expense per customer
    float avgExpense = totalProducts > 0 ? totalExpense / customerList.size() : 0.0;    
    return avgExpense;
}


//////////////////////////////////////////////////////////////////////////////////
// MODIFY THIS SECTION
//////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Modify this code to solve the assigment. Include relevant document. Mention the prompts used prefixed by #PROMPT#.
 *        
 * 
 * @param hashtags 
 * @param purchases 
 * @param prices
 * @param newHashtags
 * @param k
 * @param outputFilePath
 */
void groupCustomersByHashtagsForDynamicInserts(fileIterator& hashtags, fileIterator& purchases,fileIterator& prices,vector<string> newHashtags, int k, string outputFilePath){

    //  Write your code here
    if (globalproductHashtags.empty()) {
        while (hashtags.hasNext()) {
            string line = hashtags.next();
            if(line.size() != 0){
                stringstream ss(line);
                int product;
                string temp;
                getline(ss, temp, ',');  // Read up to the first comma
                product = stoi(temp);    // Convert to intger
                while (getline(ss, temp, ',')) {
                    // convert temp to lower case
                    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                    globalproductHashtags[product].insert(temp);   
                }
            }
        }
    }

    // Update the productHashtags with new hashtags
    for(const auto& newHashtag : newHashtags) {
        if(newHashtag.size() > 0){
            stringstream ss(newHashtag);
            int product;
            string temp;
            getline(ss, temp, ',');  // Read up to the first comma
            product = stoi(temp);    // Convert to intger
            while (getline(ss, temp, ',')) {
                // convert temp to lower case
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                globalproductHashtags[product].insert(temp);  // Update the mapping with new hashtags

            }
        }
    }


    // Map customer ID to their hashtag frequency (i.e., interests)
    unordered_map<int, unordered_map<string, int>> customerInterests;

    // Step 2: Read the purchases and build each customer's interest list based on purchased products' hashtags
    while (purchases.hasNext()) {
        string line = purchases.next();
        if (line.size() != 0){
            stringstream ss(line);
            int customer, product;
            string temp;
            getline(ss, temp, ',');
            customer = stoi(temp);
            getline(ss, temp, ',');
            product = stoi(temp);
            for (const auto& hashtag : globalproductHashtags[product]) {
                customerInterests[customer][hashtag]++;
           }
        }
    }

    // Step 3: For each customer, extract the top-k most frequent hashtags
    unordered_map<vector<string>, vector<int>, VectorStringHash> groupedCustomers;
    for (auto& customerInterestPair : customerInterests) {
        int customer = customerInterestPair.first;
        auto& interestMap = customerInterestPair.second;
        // Sort hashtags by frequency (descending order) and then lexicographically
        vector<pair<string, int>> freqHashtags(interestMap.begin(), interestMap.end());

        sort(freqHashtags.begin(), freqHashtags.end(), [](const auto& a, const auto& b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second > b.second;
        });

        // Extract the top-k hashtags
        vector<string> topKHashtags;
        for (int i = 0; i < min(k, (int)freqHashtags.size()); ++i) {
            topKHashtags.push_back(freqHashtags[i].first);
        }
        //sort the topKHashtags
        sort(topKHashtags.begin(), topKHashtags.end());

        // Group customers who share the same top-k hashtags
        groupedCustomers[topKHashtags].push_back(customer);
    }


    // cout << "Grouped Customers: ";
    for(const auto& temp : groupedCustomers){
        vector<int> group;
        for(const auto& temp2 : temp.second){
            group.push_back(temp2);
  
        }
        writeOutputToFile(group, outputFilePath);
    }

    return;
    
}



#endif // USER_CODE_H
