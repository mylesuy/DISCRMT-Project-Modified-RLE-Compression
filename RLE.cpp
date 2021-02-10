#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

string encode(string input) { //function for encoding data to RLE
	string output = "";
	int count;
	
	for (int i=0; i<input.length(); i++) {
		count = 1; //resets counter to 1 for the next charater in the data
		while (input[i] == input[i+1]) {
			count++; //increment counter
			i++; //increment i
		}
		output += to_string(count) + input[i]; //compiles all of the data
	}
	return output; //returns the encoded data
}

string m_encode(string input) { //a modified function for encoding data to RLE
	string output = "";
	int count;
	
	for (int i=0; i<input.length(); i++) {
		count = 1; //resets counter to 1 for the next charater in the data
		while (input[i] == input[i+1]) {
			count++; //increment counter
			i++; //increment i
		}
		if (input[i]!='\n') {
			//compiles all of the data
			if (i<input.length()-1 && input[i+1]!='\n') { //checks if all of the inputted data as been processed or encoded
				output += to_string(count) + "," + input[i] + ","; //do this if this is not yet the last character of the input
			}
			else {
				output += to_string(count) + "," + input[i]; //do this if this is the last character of the input
			}
		} else {
			output += "\n";
		}
	}
	return output; //returns encoded data
}

string decode(string input) { //function for decoding RLE data
	string output = "";
	int count;
	char ch;
	
	for (int i=0; i<input.length(); i=i+2) {
		count = stoi(string(1, input[i])); //converts string to integer for counting how many times the character was repeated
		ch = input[i+1]; //converts string to character for identifiying what character should be repeated 
		output += string(count, ch); //compiles all of the data
	}
	return output; //returns decoded data
}

string m_decode(string input) { //a modified function for decoding RLE data
	string output = "";
	int count;
	string cha;
	char ch;
	
	vector<string> v;
	stringstream ss(input);
	while(ss.good()) { //while ss not empty
		string substr;
		getline(ss, substr, ','); //parses the data, and split the data for every comma
		v.push_back(substr); //stores the data
	}
	
	for (int i=0; i<v.size(); i=i+2) {
		stringstream n(v.at(i)); //gets the data from the vector
		n >> count; //gets the number of times the character was repeated
		//gets the number of times a character should be repeated
		cha = v[i+1];
		ch = cha[0];
		
		output += string(count, ch); //compiles all of the data
	}
	return output; //returns decoded data
}

int fileCom(string fileName){
	cout << "Compressing \"" + fileName + "\"..." << endl; //prompts the user that this function is running
	fstream origFile;
	string origData = "";
	origFile.open(fileName, ios::in); //open a file to perform read operation using file object
	if (origFile.is_open()) { //checking whether the file is open
		string origDataStream;
		while(getline(origFile, origDataStream)) { //read data from file object and put it into string.
			origData += origDataStream + "\n"; //stores the data from the text file
		}
		origFile.close(); //close the file object.
	}
	else {
		return 1;
	}
	
	string encoded;
	encoded = m_encode(origData); //encodes the data to RLE from the previously opened file
	
	fstream newfile;
	newfile.open("Compressed.txt",ios::out); // open a file to perform write operation using file object
	if(newfile.is_open()) { //checking whether the file is open
		newfile << encoded; //inserting text
		newfile.close(); //close the file object
	}
	else {
		return -1;
	}
	
	cout << "Output: Compressed.txt" << endl; //propts the user that this function is done running & a file is generated
	return 0;
	/*
	returns 1 if read file error
	returns 0 if read and write file is successful
	returns -1 if write file error
	*/
}

int fileDecom(string fileName){
	cout << "Decompressing \"" + fileName + "\"..." << endl; //prompts the user that this function is running
	fstream origFile;
	//string origData = "";
	string decoded = "";
	origFile.open(fileName, ios::in); //open a file to perform read operation using file object
	if (origFile.is_open()) { //checking whether the file is open
		string origDataStream;
		while(getline(origFile, origDataStream)) { //read data from file object and put it into string.
			decoded += m_decode(origDataStream) + "\n"; //decodes the data and store the decoded data
		}
		decoded.erase(decoded.end()-1, decoded.end()); //removes the extra "\n" from the data
      	origFile.close(); //close the file object.
	}
	else {
		return 1;
	}
	
	fstream newfile;
	newfile.open("Decompressed.txt",ios::out); // open a file to perform write operation using file object
	if(newfile.is_open()) { //checking whether the file is open
		newfile << decoded; //inserting text
		newfile.close(); //close the file object
	}
	else {
		return -1;
	}
	
	cout << "Output: Decompressed.txt" << endl; //propts the user that this function is done running & a file is generated
	return 0;
	/*
	returns 1 if read file error
	returns 0 if read and write file is successful
	returns -1 if write file error
	*/
}

int compFiles(string fileName1, string fileName2) {
	cout << "Comparing the original and decoded files..." << endl; //prompts the user that this function is running
	fstream file1;
	string data1 = "";
	
	file1.open(fileName1, ios::in); //open a file to perform read operation using file object
	if (file1.is_open()) { //checking whether the file is open
		string dataStream;
		while(getline(file1, dataStream)) { //read data from file object and put it into string.
			data1 += dataStream + "\n"; //stores the data fron the text file
		}
      	file1.close(); //close the file object.
	}
	else {
		return 1;
	}
	
	fstream file2;
	string data2 = "";
	file2.open(fileName2, ios::in); //open a file to perform read operation using file object
	if (file2.is_open()) {   //checking whether the file is open
		string dataStream;
		while(getline(file2, dataStream)) { //read data from file object and put it into string.
			data2 += dataStream + "\n"; //stores the data fron the text file
		}
      	file2.close(); //close the file object.
	}
	else {
		return 2;
	}
	
	if (data1.compare(data2)==0) {
		cout << fileName1 + " and " + fileName2 + " are the same." << endl;
	}
	else {
		cout << fileName1 + " and " + fileName2 + " are not the same." << endl;
	}
	return 0;
	/*
	returns 0 if reading all files are successful
	returns 1 if reading fileName1 failed
	returns 2 if reading fileName2 failed
	*/
}

int compFsize(string fileName1, string fileName2) {
	cout << "Comparing the the sizes of original and encoded files..." << endl; //prompts the user that this function is running
	fstream file1;
	string data1 = "";
	
	file1.open(fileName1, ios::in); //open a file to perform read operation using file object
	if (file1.is_open()) {   //checking whether the file is open
		string dataStream;
		while(getline(file1, dataStream)) { //read data from file object and put it into string.
			data1 += dataStream + "\n"; //stores the data fron the text file
		}
      	file1.close(); //close the file object.
	}
	else {
		return 1;
	}
	
	fstream file2;
	string data2 = "";
	file2.open(fileName2, ios::in); //open a file to perform read operation using file object
	if (file2.is_open()) {   //checking whether the file is open
		string dataStream;
		while(getline(file2, dataStream)) { //read data from file object and put it into string.
			data2 += dataStream + "\n"; //stores the data fron the text file
		}
      	file2.close(); //close the file object.
	}
	else {
		return 2;
	}
	
	cout << "The size of " + fileName1 + " is " + to_string(data1.size()) << endl;
	cout << "The size of " + fileName2 + " is " + to_string(data2.size()) << endl;
	/*
	returns 0 if reading all files are successful
	returns 1 if reading fileName1 failed
	returns 2 if reading fileName2 failed
	*/
}

void edc(string fileName) { //function for encoding, decoding, and comparing data
	fileCom(fileName); //compresses "consti.txt" file
	cout << "\n";
	fileDecom("Compressed.txt"); //decompreses "Compressed.txt" file
	cout << "\n";
	compFiles(fileName, "Decompressed.txt"); //compares contents of the original and decompressed files
	cout << "\n";
	compFsize(fileName, "Compressed.txt"); //compares the size of the original and compressed files
}

void basics() { //for testing or debugging only
	string x = "AAAABBBBCCCCCCCC/////1122225555***", y, z;
	cout << "Original: " + x + "\t\tLength: " + to_string(x.size()) << endl;
	
	cout << "*********RLE**********" << endl;
	y = encode(x);
	z = decode(y);
	cout << "Encoded: " + y + "\t\t\t\tLength: " + to_string(y.size()) << endl;
	cout << "Decoded: " + z + "\t\tLength: " + to_string(z.size()) + "\n" << endl;
	
	cout << "*****Modified RLE*****" << endl;
	y = m_encode(x);
	z = m_decode(y);
	cout << "Encoded: " + y + "\t\tLength: " + to_string(y.size()) << endl;
	cout << "Decoded: " + z + "\t\tLength: " + to_string(z.size()) << endl;
}

void enter() {
	cout << "Press Enter to Continue";
	getch();
}

int mainmenu() {
	system("CLS"); //clears the screen
	int x;
	//displays the main menu of the program
	cout << "Modified RLE Compression and Decompression Program" << endl;
	cout << "Select file:" << endl;
	cout << "0. RLE Intro" << endl;
	cout << "1. ASCII_Art Apple.txt" << endl;
	cout << "2. ASCII_Art Macintosh.txt" << endl;
	cout << "3. Batman.txt" << endl;
	cout << "4. Dell.txt" << endl;
	cout << "5. Pokemon.txt" << endl;
	cout << "6. Spiderman.txt" << endl;
	cout << "7. University.txt" << endl;
	cout << "8. Exit Program" << endl;
	cout << "Enter the number of the file you want to compress & decompress >> ";
	cin >> x; //waits for user's input
	cout << "\n";
	switch(x) { //the program will do certain tasks, depending on the user's selection
		case 0:
			basics();
			break;
		case 1:
			edc("assets/ASCII_Art Apple.txt");
			break;
		case 2:
			edc("assets/ASCII_Art Macintosh.txt");
			break;
		case 3:
			edc("assets/Batman.txt");
			break;
		case 4:
			edc("assets/Dell.txt");
			break;
		case 5:
			edc("assets/Pokemon.txt");
			break;
		case 6:
			edc("assets/Spiderman.txt");
			break;
		case 7:
			edc("assets/University.txt");
			break;
		case 8:
			cout << "Program Exiting" << endl;
			return -1;
			break;
		default:
			cout << "Invalid Selection: Program Exiting" << endl; //promts the user that they entered an invalid number and the program will exit
			return -1;
			break;
	}
	cout << "\n";
	enter();
	return x;
}

int main() {
	int x;
	while (x!=-1) {
		x = mainmenu();
	}
}

