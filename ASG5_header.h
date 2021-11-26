#include <iostream>
#include <fstream>
#include<string>
#include <algorithm>

using namespace std;


class BST
{
    public:
            // Strcture of a node which contains letter , it's morse code and two child
            struct Node
            {
                string letter;
                string code;
                Node *left;
                Node *right;
            };
            Node *root;

            /*!
            * @brief A constructor of BST class
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            */
            BST()
            {
                // Setting root Null by default
                root = NULL;
            }

            /*!
            * @brief This method will create a node and set letter and it's code to it along with two child
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            * @param Node*&r Binary tree with all nodes containing it's letter and code
            * @param letter A letter of a node
            * @param code A morse code of a letter node
            * @return NA
            */
            void Insert(Node *&r, string letter, string code)
            {
                // Setting the letter and code to a node and setting Null to both child nodes
                if(r == NULL)
                {
                    r = new Node;   // Creatign a node 
                    r->letter = letter;     // Setting letter
                    r->code = code;     // Setting code of the same letter
                    r->left = r->right = NULL;      // Setting child node pointer Null
                }
            }

            /*!
            * @brief This method will insert a node and set letter and it's code to it along with two child at right place
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            * @param letter A letter of a node
            * @param code A morse code of a letter node
            * @return NA
            */
            void Insert(string letter, string code)
            {
                // Insert the code at the appropriate position using pointers
                Node **r = &root;
                if(*r != NULL)
                {
                    for(std::string::size_type i = 0; i < code.length(); i++)
                    {
                        if(code[i] == '.') r = &((*r)->left);   // Go to left if code is '.'
                        else if(code[i] == '-') r = &((*r)->right);     // Go to right if code is '-'
                        else break;
                    }
                    Insert(*r, letter, code);   // Recursion
                }
                else Insert(root, letter, code);    // Recursion
            }

            /*!
            * @brief This method will encode the given string into morse code
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            * @param Node*&r Binary tree with all nodes containing it's letter and code
            * @param user_msg User inputed string
            * @param encoded_str Encoded string usign morse code
            * @return Encoded string 
            */
            string encode(struct Node* root, string user_msg, string &encoded_str)
            {                       
                string msg;
                // This will take character by character from input string and 
                // scan the tree for it's code.
                for (unsigned int i=0; i< user_msg.length(); i++)
                {
                    msg = user_msg[i];  // Getting every character

                    // Search for a character in a binary tree and update 'encoded_str' with it's code
                    if (root != NULL)
                    {
                        encode(root->left, msg, encoded_str);
                        if(root->letter == msg)
                        {
                            if(root->letter == "@") // Looking for a space(' ') and update the encoded_str
                                encoded_str += " ";

                            else
                                encoded_str += (root->code + " ");  // Update the encoded_str with relavant code of the same letter
                            break;
                        }
                        encode(root->right, msg, encoded_str);
                    }
                }

                return encoded_str;
            }

            /*!
            * @brief This method will count the total number of occurances of a character in a string 
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            * @param str User inputed string
            * @param ch Character to be counted
            * @return Encoded string 
            */
            int count(string str, char ch)
            {
                unsigned int len = 0;
                for(auto ch1: str)
                    if(ch1 == ch)
                        len++;
                
                return len + 1; 
            }

            /*!
            * @brief This method will create an arrat of given string and stores word seprated by space
            * @author Jaydeep Prajapati
            * @date Nov 22, 2021
            * @param arr[] An array to store the words
            * @param str A string for getting the words
            * @return NA
            */
            void str_to_array(string arr[], string str)
            {   
                string word = "";
                unsigned int index = 0;

                for(unsigned int i=0; i< str.size(); i++)
                {
                    char ch = str[i];
                    if (ch == ' ')  // Word end
                    {   
                        if(word.length() != 0)
                        {
                            arr[index++] = word;    // Append word to an array and update a word to blank
                            word = "";
                        }
                        if(ch == ' ' && str[i+1] == ' ')    // Space found 
                        {
                            arr[index++] = "----";  // Append "----" in an array
                            word = "";
                        }
                    }
                    else
                        word = word + ch;   // Append character to word
                }
                arr[index] = word;  // Append last word to an array
            }

            /*!
            * @brief This method will decode the given morse code 
            * @author Jaydeep Prajapati
            * @date Nov 23, 2021
            * @param  Node* root Binary tree
            * @param encoded_str Encoded string to be decode
            * @param &decoded_string A blank string which will be append by letter
            * @param encoded_len Length of encoded words 
            * @param count A counter of total number of encoded words
            * @return Return a letter of given morse code
            */
            string decode(struct Node* root, string encoded_str, string &decoded_string, unsigned int encoded_len, unsigned int count)
            {
                string ch;
                if (root != NULL)
                {
                    decode(root->left, encoded_str, decoded_string, encoded_len, count);
                    if(root->code == encoded_str)
                    {
                        ch = root->letter;
                        if(encoded_str == "----")   // Space found and update decoded_str by adding a space
                            decoded_string+= " ";
    
                        else
                            decoded_string+= root->letter;  // Update decoded_str with appropriate letter of the code

                        return ch;
                    }
                    decode(root->right, encoded_str, decoded_string, encoded_len, count);
                }
                if(count == (encoded_len-1))    // Return the encoded string
                    return decoded_string;
                else
                    return "NA";    // Return "NA" if decode is not completed
            }

            /*!
            * @brief This method will convert character to upper case 
            * @author Jaydeep Prajapati
            * @date Nov 23, 2021
            * @param ch A character 
            * @return Return upper case of character
            */
            char char_upper(char ch)
            {
                if('a'<= ch && ch <= 'z')
                    return ch-'a'+'A';  // Return upper case letter of given alphabet if it is not already
                else
                    return ch;  // Return the same character as it is already in upper case
            }
           
            /*!
            * @brief This method will convert string to upper case by calling char_upper method
            * @author Jaydeep Prajapati
            * @date Nov 23, 2021
            * @param str A string 
            * @return Return upper case of string
            */
            string string_upper(string str)
            {
                string result = "";
                for (unsigned int i=0; i< str.length(); i++)
                    result += char_upper(str[i]);   // Getting string in upper case by getting every charareter in upper case by calling function 

                return result;
            }

            
            // void display_code(struct Node* root)
            // {
            //     if (root != NULL)
            //     {
            //         display_code(root->left);
            //         cout<<root->code<< "**"<< endl;
            //         display_code(root->right);
            //     }
            // }

            /*!
            * @brief This method will create two arrays of letter and it's morse code from text file
            * @author Jaydeep Prajapati
            * @date Nov 23, 2021
            * @param morse_letters An array to store all letters
            * @param morse_codes An array to store all morse codes 
            * @return NA
            */
            void get_morse_code_array(string morse_letters[], string morse_codes[])
            {
                ifstream file("Morse_code.txt");    // Reading a text file 
                string str;
                unsigned int letter_index = 0, code_index = 0;
                while (getline(file, str))  // Getting line by line from file
                {
                    string word = "";
                    // Scannning through every character in whole string 
                    for(unsigned int i=0; i< str.size(); i++)
                    {
                        char ch = str[i];
                        if (ch == ' ')
                        {   
                            if(word.length() != 0)
                            {
                                // cout<< "Letter :"<< word<< endl;
                                morse_letters[letter_index++] = word;   // Append letter to array
                                word = "";
                            }
                        }
                        else
                            word = word + ch;   // Add character to word
                    }
                    morse_codes[code_index++] = word;   // Append code to array
                }
            }

};
