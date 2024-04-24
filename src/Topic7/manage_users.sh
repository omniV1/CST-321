#!/bin/bash

# Check if the correct number of arguments were provided
if [ "$#" -ne 3 ]; then
    echo "Error: You must enter exactly 3 command line arguments: the filename, the group name, and the operation flag."
    exit 1
fi

filename=$1
group=$2
operation=$3

# Check if the input file exists and is not empty
if [ ! -s "$filename" ]; then
    echo "Error: File does not exist or is empty."
    exit 1
fi

# Check if the group exists, if not, create it
if ! getent group "$group" > /dev/null 2>&1; then
    sudo groupadd "$group"
    echo "Group '$group' created."
fi

# Function to add users from the file
add_users() {
    while IFS=' ' read -r userid password; do
        if [ -z "$userid" ] || [ -z "$password" ]; then
            echo "Skipping blank line."
            continue
        fi

        echo "Adding user '$userid'..."
        sudo useradd -m -p "$password" -G "$group" "$userid"
        if [ "$?" -eq 0 ]; then
            echo "User '$userid' added successfully."
        else
            echo "Failed to add user '$userid'."
        fi
    done < "$filename"
}

# Function to remove users from the file
remove_users() {
    while IFS=' ' read -r userid password; do
        if [ -z "$userid" ]; then
            echo "Skipping blank line."
            continue
        fi

        echo "Removing user '$userid'..."
        sudo userdel -r "$userid"
        if [ "$?" -eq 0 ]; then
            echo "User '$userid' removed successfully."
        else
            echo "Failed to remove user '$userid'."
        fi
    done < "$filename"
}

# Determine the operation to perform
case "$operation" in
    -a)
        add_users
        ;;
    -r)
        remove_users
        ;;
    *)
        echo "Invalid operation flag. Use '-a' to add or '-r' to remove."
        exit 1
        ;;
esac
