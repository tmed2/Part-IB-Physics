// This is C++ sample code for File I/O */
#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
using namespace std;

int main()
{
  
	char array[] = {'H','e','l','l','o',' ','W','o','r','l','d','!','\0'}; //array to write into file 
  
	ofstream fout("test.txt"); //opening an output stream for file test.txt
	/*checking whether file could be opened or not. If file does not exist or don't have write permissions, file
  stream could not be opened.*/
  if(fout.is_open())
	{
    //file opened successfully so we are here
    cout << "File Opened successfully!!!. Writing data from array to file" << endl;

		for(int i = 0; array[i] != '\0'; i++)
		{
      		for(int i = 0; array[i] != '\0'; i++){
      			fout << array[i]; //writing ith character of array in the file
			}	
		}
    cout << "Array data successfully saved into the file test.txt" << endl;
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	return 0;
}

