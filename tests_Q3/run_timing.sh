#!/bin/bash
hashtagsPath="custom_input_product/input_hashtags/input_product_hashtag_30.csv"
purchasesPath="custom_input_product/input_customer/input_customer_300.csv"
pricesPath="Inputs/input_price.csv"
groupsPath="Inputs/input_groups.csv"
outputPath="tests_q1/output1.csv"
outputPath2="tests_q1/output2.csv"
outputPath3="custom_input_product/output_q3"
newHashtagPath="custom_input_product/output_q3"

# Path to the profile file
profile_newhash_path="./custom_input_product/input_newhashtags/timing_results.csv"


# Directory containing the files to iterate over
newhash_directory="custom_input_product/input_newhashtags"


# Ensure the CSV file has a header, only written once
if [ ! -f $profile_newhash_path ]; then
    echo "Custom_product.csv, Custom_purchase.csv, Custom_newhashtags.csv,  Avg Batch Process Time, Memory Usage, Writing Time, Compute Time, Function Time" > "$profile_newhash_path"
fi

# # Loop through all files in the input directory
for input_file in "$newhash_directory"/*.csv; do
    # Check if there are files in the directory
    # echo "$input_file"
    if [ -e "$input_file" ]; then
        # Call the C++ executable with constant arguments and the iterating input file
        ./main "$hashtagsPath" "$purchasesPath" "$pricesPath" "$groupsPath" "$outputPath" "$outputPath2" "$outputPath3" "$input_file" "$profile_newhash_path"
    else
        echo "No CSV files found in $product_directory."
        break
    fi
done
