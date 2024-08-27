Author: Niket Mittal
Roll Number: 2024201076

"CS3.304 - Advanced Operating Systems (Assignment - 1)"


HOW TO USE(q1.cpp):
- to compile the c++ code use: g++ 2024201076_A1_Q1.cpp -o 2024201076_A1_Q1.out
- to run the program use: ./2024201076_A1_Q1.out <input_file_name> <flag> (either 0 or 1) <start_index> <end_index>
- input_file_name: name of the file containing the data
- flag: 0 for reversing the contents of the entire file
- flag: 1 for reversing the contents of the file in two parts: from the beginning to the start_index, and from the end_index to the end of the document
- after running the program, a new folder will be created called "Assignment1" where the output files will be created namely "0_<input_file_name>" if the input flag is 0, and "1_<input_file_name>" if the input flag is 1.


HOW TO USE(q2.cpp):
- to compile the c++ code use: g++ 2024201076_A1_Q2.cpp -o 2024201076_A1_Q2.out
- to run the program use: ./2024201076_A1_Q2.out <newfile_path> <oldfile_path> <directory_path>
- newfile_path: path to the new file
- oldfile_path: path to the old file
- directory_path: path to the directory
- after running the program, it will check for 2 things
    1. Check the permissions for the two files and the directory.
    2. Check whether the content in the new file are the reverse of the old file.