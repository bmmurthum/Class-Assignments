# Simple Shell Program

This program is an exercise of simple shell methods. In a nutshell, it (1) 
displays files within the current directory, (2) counts files and filesizes, and
(3) creates a directory at a particular location.

## Contents

- [Initial Lab Document PDF]()
- [Program Code]()

## Program Requirements

- *Task 1:* Shell script supports only one command line argument: "-c", "-l", "-d" or "--help"
  - If no argument is provided, it displays "Must provide an argument"
    then exits.
  - If "-c", displays "The number of files" and "How many bytes"
  - If "-l", displays "List all the files"
  - If "-d", creates a directory "backup" at "/home/brendon/".
  - If "--help", displays "How to run this script"
- *Task 2:* Create a directory "backup" in your home directory. If does not exist
  create it, otherwise do nothing.
- *Task 3:* Count the bumber of files and directories in the current page, and 
  display that. Also, display the amount of bytes these files and
  directories consume.
  
## Quick Shell Guide

To run program: `bash lab5.sh -l`

To change permissions of shell program: `sudo chmod 777 lab5.sh`

```shell
# This is a comment

```


