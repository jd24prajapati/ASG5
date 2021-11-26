/*!
 * @brief	Main file which implement the Morse code in binary tree with encoding and decoding functionaliy to given string
 * @author	Jaydeep Prajapati
 * @date	Nov 21, 2021
*/

#include <iostream>
#include <fstream>
#include<string>
#include <algorithm>
#include"ASG5_header.h"
using namespace std;
 
/*!
 * @brief	Main function
 * @author	Jaydeep Prajapati
 * @date	Nov 21,  2021
 * @details This is a main method of the program, which has implementation the morse code functionality using binary tree. 
*/

int main() 
{   
    BST t;  // Creting an object of a class

    // Declarign two arrays for letters and codes to store alphabets and it's codes respectively
    string morse_letters[28], morse_codes[28], str;
    char ch;

    t.get_morse_code_array(morse_letters, morse_codes);     // Storing the letters and codes ina an array

    // Generatign a binary tree
    for(int i = 0; i < 28; i++)
    {
        t.Insert(morse_letters[i], morse_codes[i]); 
    }
    

	string msg;
    cout<< "Enter a message :";     // Getting a message from user to encode it
    getline (cin, msg);
    msg = t.string_upper(msg);      // Convert the user message in upper case
    replace(msg.begin(), msg.end(), ' ', '@'); // Replacing the space with '@' for decoding purpose
    string user_ch, encoded_str = "";

    encoded_str = t.encode(t.root, msg, encoded_str);   // Encoding the user message
    encoded_str.pop_back();
    cout<< "Coded message :"<< encoded_str<< endl;  // Display endoded message


    int encoded_len = t.count(encoded_str, ' ');
    string decoded_str, arr[encoded_len], decoded_string;

    t.str_to_array(arr, encoded_str);   // Converting the encoded string into an array having endoded characters

    // Decoding the encoded message
    for(int i=0; i< encoded_len; i++)
    {
        decoded_str = t.decode(t.root, arr[i], decoded_string, encoded_len, i);
        if(decoded_str != "NA")
            cout<< "Decoded message : "<< decoded_str<< endl;   // Display the decoded message
    }

    return 0;
}