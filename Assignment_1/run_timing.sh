#!/bin/bash

hashtagsPath="custom_input_product/input_product/input_product_100.csv"
purchasesPath="custom_input_product/input_customer/input_customer_300.csv"
pricesPath="input_price.csv"
groupsPath="input_groups.csv"
outputPath="outputQ1.csv"
outputPath2="outputQ2.csv"
outputPath3="Results"
newHashtagPath="input_newhashtags.csv"

# Directory containing the files to iterate over
input_directory="custom_input_product/input_customer"
# input_directory="custom_input_customer"

#custom_input_product/input_customer/timing_results.csv

# Ensure the CSV file has a header, only written once
if [ ! -f ./custom_input_product/input_customer/timing_results.csv ]; then
    echo "Custom_product.csv, Custom_purchase.csv, Data Structure Populating Time, Clustering Time, Memory Usage, Writing Time, Compute Time, Function Time" > ./custom_input_product/input_customer/timing_results.csv
fi

# # Loop through all files in the input directory
for input_file in "$input_directory"/*.csv; do
    # Check if there are files in the directory
    # echo "$input_file"
    if [ -e "$input_file" ]; then
        # Call the C++ executable with constant arguments and the iterating input file
        ./main  "$hashtagsPath" "$input_file" "$pricesPath" "$groupsPath" "$outputPath" "$outputPath2" "$outputPath3" "$newHashtagPath"
        # ./main "$hashtagsPath" "$input_file" "$pricesPath" "$groupsPath" "$outputPath" "$outputPath2" "$outputPath3" "$newHashtagPath"
    else
        echo "No CSV files found in $input_directory."
        break
    fi
done