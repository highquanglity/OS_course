#!/bin/bash

process_emptyfile(){
    item=$1
    echo "------------------------------------"
    echo "Wanna delete $item? "
    # Show menu and get user input
    ./menu n "$item"
    # Check the return status of the menu executable
    if [ $? -eq 0 ]; then
        # Delete the file
        rm -f "$item"
        echo "==========="
        echo "Deleted $item successfully."
    else
        echo "------------------------------------"
        echo "Kept $item."
    fi
}


# Compile menu.c and create the executable file: menu
if [ ! -x "./menu" ]; then
    echo "Compiling menu.c..."
    gcc menu.c -o menu
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Exiting."
        exit 1
    fi
fi

# Check if the user provided a path argument
if [ -z "$1" ]; then
    echo "Please provide the path to the folder as an argument."
    exit 1
fi

# Get empty files in the specified folder
path=$1
empty_files=$(find "$path" -type f -empty)

# Show menu for empty files and ask user for deletion option
./menu p $empty_files

# Iterate through empty files and ask user for deletion choice
for item in $empty_files; do
    process_emptyfile $item
done

# Announce successful completion
echo "-----------------------"
echo "Done. Exiting..."
