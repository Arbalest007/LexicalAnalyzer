/*
CPSC 323 - Project 1
Patrick Lin
ID: 887501237
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

/*
Checks to see if the char is an operator. We compare it to a C string of operators.
If the char matches with any of the buffers then return true
*/
int isOperator(char buffer) {
    char operators[] = "()=*/+-%<>";
    int i, flag = 0;

    //Loop through our operators C string and compare to our char buffer
    for(int i = 0; i < 10; i++) {
        if (buffer == operators[i])
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

int main() {
    char c, buffer[256];
    int i = 0;

    /*
    Checking to make sure that the input.txt and output.txt can 
    be opened without issue.
    */
    ifstream input("input.txt");
    if (!input.is_open()) {
        cout << "Input File Invalid\n";
        exit(0);
    }
    ofstream output;
    output.open("output.txt", ios::out);
    if (!output.is_open()) {
        cout << "Output File Invalid\n";
        exit(0);
    }

    //Iterate through the input.txt until we reach the end of the file
    while (!input.eof()) {
        //Retrieve a char
        c = input.get();

        /*
        If the char is an alpha-numeric character, then we add it to our buffer array
        and increment to next spot in the buffer
        */
        if (isalnum(c)) {
            buffer[i++] = c;
        }
        /*
        Otherwise we account for several situations:

        1) Next character is a space, newline, or tab
        2) Next character will be the End of File
        3) Next character will be an operator
        
        If either of these are true and buffer is not equal to 0 then that 
        means we have finished parsing in a word of some sort into our buffer char array.
        Therefore we output the buffer.
        */
        else if ((c == ' ' || c == '\n' || c == '\t' || input.peek() == EOF || isOperator(c) == 1) && (i != 0)) {
            //Terminate our char array
            buffer[i] = '\0';
            //Reset buffer array index counter
            i = 0;

            output << buffer << "\n";
        }

        /*
        Check if the char is an operator and if it is, then print it.
        We check the operator afterwards to make sure that the keyword/identifier
        is printed first before an operator.
        */
        if(isOperator(c) == 1) {
            output << c << "\n";
        }
    }

    //Close both the input and output files
    input.close();
    output.close();
    return 0;
}