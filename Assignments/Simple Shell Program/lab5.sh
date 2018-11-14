# /bin/bash

# Lab 5 - Linux Shell Script
# Brendon Murthum - Nov 14 2018
# GVSU - Comp Sci. - Prof. Xiang Cao

# Task 1: Shell script supports only one command line argument: "-c" "-l" 
#         or "--help"
#         - If no argument is provided, it displays "Must provide an argument"
#           then exits.
#         - If "-c", displays "The number of files" and "How many bytes"
#         - If "-l", displays "List all the files"
#         - If "--help", displays "How to run this script"
# Task 2: Create a directory "backup" in your home directory. If does not exist
#         create it, otherwise do nothing.
# Task 3: Count the bumber of files and directories in the current page, and 
#         display that. Also, display the amount of bytes these files and
#         directories consume.
# User may need to give this shell program permissions: "chmod 777 lab5.sh"


# If user gives zero arguments. Bad usage.
if test $# -eq 0
    then
        echo "Error: Must provide an argument"
        echo "For correct usage help, use the argument --help"
        exit 1
fi


# If user gives more than one argument. Bad usage.
if test $# -gt 1
    then
        echo "Error: More than one argument"
        echo "For correct usage help, use the argument --help"
fi


# If user gives one argument. Correct usage.
if test $# -eq 1
    then
        # Count the size of files/directories in current path.
        if test "$1" = "-c"
            then
            let totalCount=0
            let totalByteCount=0
            # Loop files and dir in current path.
            for j in *
            do
                if [ -d "$j" ]
                    then
                    let currentDirSize=$(du -b $j | cut -f1)
                    let totalByteCount=totalByteCount+currentDirSize
                    let totalCount=totalCount+1
                elif [ -f "$j" ]
                    then
                    let currentSize=$(wc -c < "$j")
                    let totalByteCount=totalByteCount+currentSize
                    let totalCount=totalCount+1
                fi
            done
            echo "  Number of Files and Directories: $totalCount"
            echo "  Total Size in Bytes: $totalByteCount"
        # List files/directories in current path.
        elif test "$1" = "-l"
            then
            # Loop files and dir in current path.
            for i in * 
            do
                if [ -d "$i" ]
                    then
                    echo "  ./$i"
                elif [ -f "$i" ]
                    then
                    echo "  $i"
                fi
            done
        # Create a directory "backup" in /home/brendon/
        elif test "$1" = "-d"
            then
            createPath="/home/brendon/backup"
            if [ -d "$createPath" ]
                then
                    echo "  Directory $createPath already created."
                else
                    mkdir -p "$createPath"
                    echo "  Created directory $createPath"
            fi
        # Display correct program usage to the user.
        elif test "$1" = "--help"
            then
            echo "Program Usage:"
            echo "  bash ./lab5.sh -l"
            echo "This shell program takes exclusively one argument."
            echo "  -l : Shows a list of files in current directory."
            echo "  -c : Displays number of files/directories and bytes."
            echo "  -d : Creates directory, BACKUP, in ~/home."
        # If invlaid argument, display help statement.
        else
            echo "For correct usage help, use the argument --help"
            exit 1
        fi
fi



