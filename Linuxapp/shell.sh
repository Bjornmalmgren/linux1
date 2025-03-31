#!/bin/bash
SOURCE_DIR="$1"
COPYRIGHT_FILE="$2"

add_copyright() {
    local file="$1"
    local temp_file=$(mktemp)
     
    cat "$COPYRIGHT_FILE" > "$temp_file"
    echo "" >> "$temp_file"
    cat "$file" >> "$temp_file"
    
    mv "$temp_file" "$file"
}

# Function to rename file extensions
rename_extensions() {
    find "$SOURCE_DIR" -name "*.cpp" | while read file; do
        mv "$file" "${file%.cpp}.cc"
    done  


    
    
    find "$SOURCE_DIR" -name "*.h" | while read file; do
        mv "$file" "${file%.h}.hpp"
    done
}

# Function to convert between float and double
convert_types() {
    local search_type="float"
    local replace_type="double"
    
    find "$SOURCE_DIR" -type f \( -name "*.c" -o -name "*.cc" -o -name "*.h" -o -name "*.hpp" \) | while read file; do
        sed -i "s/\b${search_type}\b/${replace_type}/g" "$file"
    done

    search_type="double"
    replace_type="float"

    find "$SOURCE_DIR" -type f \( -name "*.c" -o -name "*.cc" -o -name "*.h" -o -name "*.hpp" \) | while read file; do
        sed -i "s/\b${search_type}\b/${replace_type}/g" "$file"
    done
}

# Main execution
find "$SOURCE_DIR" -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) | while read file; do
    add_copyright "$file"
done

rename_extensions

convert_types