#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

const std::vector<std::string> categories = {
    "outdoor", "adventure", "camping", "hiking", "fishing", "boating",
    "kitchen", "cooking", "baking", "appliances", "utensils", "cutlery",
    "office", "supplies", "furniture", "stationery", "electronics", "chairs",
    "garden", "tools", "plants", "outdoor", "seeds", "fertilizers",
    "pets", "supplies", "food", "toys", "grooming", "accessories",
    "baby", "clothing", "toys", "furniture", "strollers", "diapers",
    "automotive", "parts", "accessories", "tools", "tires", "batteries",
    "music", "instruments", "accessories", "audio", "sheet music", "recording",
    "photography", "cameras", "lenses", "accessories", "tripods", "lighting",
    "books", "literature", "novels", "comics", "magazines", "textbooks",
    "movies", "DVDs", "Blu-ray", "streaming", "posters", "memorabilia",
    "games", "video games", "board games", "puzzles", "card games", "dice",
    "fitness", "equipment", "gear", "apparel", "nutrition", "accessories",
    "beauty", "makeup", "skincare", "haircare", "fragrance", "nail care",
    "health", "supplements", "vitamins", "equipment", "medications", "first aid",
    "travel", "luggage", "accessories", "gear", "guides", "maps",
    "fashion", "clothing", "shoes", "accessories", "jewelry", "handbags",
    "electronics", "gadgets", "devices", "accessories", "batteries", "chargers",
    "home", "furniture", "decor", "appliances", "lighting", "bedding",
    "sports", "equipment", "gear", "apparel", "footwear", "accessories",
    "crafts", "supplies", "tools", "kits", "patterns", "materials",
    "jewelry", "rings", "necklaces", "bracelets", "earrings", "watches",
    "toys", "games", "puzzles", "action figures", "dolls", "building sets",
    "art", "supplies", "paint", "canvas", "brushes", "easels",
    "technology", "computers", "software", "hardware", "networking", "accessories",
    "food", "groceries", "snacks", "beverages", "condiments", "spices",
    "cleaning", "supplies", "tools", "equipment", "detergents", "disinfectants",
    "education", "books", "supplies", "software", "courses", "tutoring",
    "outdoor", "furniture", "decor", "lighting", "heating", "cooling",
    "automotive", "maintenance", "cleaning", "detailing", "fluids", "accessories",
    "home improvement", "tools", "materials", "hardware", "paint", "lighting",
    "office", "furniture", "supplies", "electronics", "software", "accessories",
    "pets", "food", "toys", "bedding", "grooming", "health",
    "travel", "gear", "accessories", "luggage", "guides", "maps",
    "fitness", "equipment", "gear", "apparel", "nutrition", "accessories",
    "beauty", "makeup", "skincare", "haircare", "fragrance", "nail care",
    "health", "supplements", "vitamins", "equipment", "medications", "first aid",
    "fashion", "clothing", "shoes", "accessories", "jewelry", "handbags",
    "electronics", "gadgets", "devices", "accessories", "batteries", "chargers",
    "home", "furniture", "decor", "appliances", "lighting", "bedding",
    "sports", "equipment", "gear", "apparel", "footwear", "accessories",
    "crafts", "supplies", "tools", "kits", "patterns", "materials",
    "jewelry", "rings", "necklaces", "bracelets", "earrings", "watches",
    "toys", "games", "puzzles", "action figures", "dolls", "building sets",
    "art", "supplies", "paint", "canvas", "brushes", "easels",
    "technology", "computers", "software", "hardware", "networking", "accessories",
    "food", "groceries", "snacks", "beverages", "condiments", "spices",
    "cleaning", "supplies", "tools", "equipment", "detergents", "disinfectants",
    "education", "books", "supplies", "software", "courses", "tutoring",
    "outdoor", "furniture", "decor", "lighting", "heating", "cooling"
};

void generate_data(int num_products, int num_categories, std::ofstream &outfile) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= num_products; ++i) {
        outfile << i << ",";
        std::vector<std::string> product_categories;
        for (int j = 0; j < num_categories; ++j) {
            int index = rand() % categories.size();
            product_categories.push_back(categories[index]);
        }
        for (int j = 0; j < product_categories.size(); ++j) {
            outfile << product_categories[j];
            if (j < product_categories.size() - 1) {
                outfile << ",";
            }
        }
        outfile << std::endl;
    }
}

void generate_customer_product_mapping(int num_customers, int num_products, std::ofstream &outfile) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 1; i <= num_customers; ++i) {
        int num_purchases = rand() % 5 + 1; // Each customer can buy between 1 and 5 products
        std::unordered_set<int> purchased_products;
        for (int j = 0; j < num_purchases; ++j) {
            int product_id;
            do {
                product_id = rand() % num_products + 1;
            } while (purchased_products.find(product_id) != purchased_products.end());
            purchased_products.insert(product_id);
            outfile << 100 + i << "," << product_id << std::endl;
        }
    }
}

int main() {
    //creat an array num_products having the numbers {10, 20,40,80,160,320,640,1280,2560,5120}
    int num_customers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200,300,
                           400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000}; // Number of products to generate    
    int num_products[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300,
                           400, 500, 600, 700, 800, 900, 1000}; // Number of customers to generate
    int num_product0 = 100;
    int num_customer0 = 300;

    for(auto num_customer : num_customers){
        std::ofstream outfile("input_customer_" + std::to_string(num_customer) + ".csv"); // Fix the line

        if (!outfile) {
            std::cerr << "Error opening file for writing" << std::endl;
            return 1;
        }

        outfile << " customer_id,product_id" << std::endl;
        generate_customer_product_mapping(num_customer, num_product0, outfile);

        outfile.close();
    }
    
    for(auto num_product : num_products){
        std::ofstream outfile("input_product_" + std::to_string(num_product) + ".csv"); // Fix the line

        if (!outfile) {
            std::cerr << "Error opening file for writing" << std::endl;
            return 1;
        }

        outfile << "product_id,hashtags" << std::endl;
        generate_data(num_product, num_customer0, outfile);


        outfile.close();
    }
    
    return 0;
}