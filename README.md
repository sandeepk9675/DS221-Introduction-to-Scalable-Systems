# DS221-Introduction-to-Scalable-Systems

### PROBLEM CONTEXT

You are given details about product hashtags and customer purchases of products on an eCommerce website. Each product (int) is assigned a set of one or more hashtags (strings). Each customer (int) has purchased one or more products (ints). Each product has an associated price (float). The same product may have been purchased multiple times.

### QUESTIONS
-----------------------------------------------------------------------------------------------------------------------

#### Q1.
Group customers into clusters based on the similarity of their primary interests. A customer who purchases a product is associated with all its hashtags. Each purchase adds those hashtags to the customer's interest list. The number of occurrences of a hashtag in their interest list reflects its popularity. A customer's top-k most frequent hashtags in descending order represent their primary interests. Two customers are said to have similar interests if their primary interest hashtag lists exactly match. The goal is to identify and group customers with similar interests. 

***(A)*** Complete the code template you are provided. Ensure that the code is correct for different inputs. You are provided one sample, but need to generate others using the oracle link provided below. Provide in-line documentation of the prompts used in different parts of your code by prefixing the line with '//#PROMPT#'.

* INPUT: Three iterators over (1) Products and their hashtags (2) Customers and their purchases and (3) products and their prices, and *k*, the number of top hashtags to use for grouping.

* OUTPUT: Return a list of customers (int), one per clustered group.
The order of groups in the output file does not matter.

* Function signature ``void groupCustomersByHashtags(fileIterator& hashtags, fileIterator& purchases, fileIterator& prices, int k, string outputFilePath)``

Sample input and output for sanity check:  
* tests_Q1/input_product.csv  
* tests_Q1/input_customer.csv  
* tests_Q1/input_prices.csv  
* tests_Q1/output_groups.csv  

You should generate additional input datasets to verify the correctness of your code. You can use this oracle link to generate valid outputs for any given input: https://codecheck.io/files/24090204303mnr174bmc8t0ja307paa78a6

-----------------------------------------------------------------------------------------------------------------------

#### Q2.
The *average spend* of a group indicates how much they each spend on average on their purchases. Given a list of customers, find the average of the total expenses that they incur for all the products that they have purchased. Report this average spend for each group that is provided to you.

* INPUT: A list of customers belonging to a group, given as vector <int>, and an iterator over the products purchased and the prices of products. 

* OUPUT: Return an average of the total expenses of customers in the given list. (float)

* Function signature: ``float calculateGroupAverageExpense(vector<int> customerList, fileIterator& purchases, fileIterator& prices)``

Sample input and output for sanity check (k=2):  
* tests_Q2/input_customer.csv
* tests_Q2/input_prices.csv
* tests_Q2/input_groups.csv
* tests_Q2/output_groupavgprice.csv

-----------------------------------------------------------------------------------------------------------------

#### Q3.
Products may get new reviews and as a result their hashtags may change over time. Optimize the customer grouping function in Q1 to support dynamic insertions of new hashtag(s) to a product and consequently re-evaluating the clustering of customers based on the updated interest list. 

* INPUT: Three iterators over (1) Products and their hashtags, (2) Customers and their purchases, and (3) Products and their prices. These are fixed and do not vary.  
Dynamic insertions: This function will be called with a vector of strings that represent `m` products that are being updated with new hashtags. Each string is a product and its new hastag(s). We will read these updates from an input file and pass it to you as a vector. 

* OUTPUT:  Perform the same grouping operation as Q1 and return a new list of customers (int), one per clustered group. 

* Function signature: ``void groupCustomersByHashtagsDynamic(fileIterator& hashtags, fileIterator& purchases, fileIterator& prices, string newHastags, int k, string outputFilePath)``

Sample input and output for sanity check (k=2, m=5):
* tests_Q3/input_product.csv
* tests_Q3/input_customer.csv
* tests_Q3/input_prices.csv
* tests_Q3/input_newhashtags.csv
* tests_Q3/output_dynamicgroups.csv


