/*****************************************************************************
 Program file name:PRECN-main.cpp OS:Windows  Assignment #:FINAL
 Programmer:Ryan Rabello, Phe Wagner, Elliott Berger, Norman Sossong, Caleb Hunter	Class: 	Data Struct. I			Date:
 Compiler:GNU GCC
 
 Assistance/references:none
 Description:Searches an file quickly
 Inputs: Intbits.txt and Marbles.txt
 Outputs: addresses of found location and sorted marble array.
 
 Special Comments: Dr Klein and Victor are awesome :) Thanks for a great quarter.

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~

 Assignment Requirements ___/3.0

 Code Format/Cosmetics ___/3.0

 Header & Code Comments: ___/2.0

 Output Format/Cosmetics ___/2.0
 ***Does Not Compile***: ___ (-10.0)
 ***Late Work Deduction***: ___ (-0.5/day)
 Total Grade: ___/10.0

*****************************************************************************/

#include <iostream>
#include "stdio.h"
#include <sys/stat.h>
#include <ctime>
#include <stdint.h>
#include <fstream>

#define DATA_FILE       "./intbits.txt"


using namespace std;

inline void runMil(void)
{
    // get size of data file
    //
	struct stat st;
	int status = stat(DATA_FILE, &st);

	//exit(0)'s aren't working so we need to fix that.

	if (status < 0)
    {
        //exit(0);
        cout << "Cannot stat " << DATA_FILE << "\n";
    }

    // we need at least 28 chars for the pattern and some following
    //
    if (st.st_size < 29)
    {
        cout << "Size of data file is too small.\n";
        //exit(0);
    }

    // allocate array for data and read it in
    //
    char *pData = new char[st.st_size];

    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp)
    {
        cout << "Cannot open " << DATA_FILE << "\n";
        //exit(0);
    }

    fread(pData, st.st_size, 1, fp);
    fclose(fp);


    //  scan data starting 1 byte in
    //
    clock_t tStart = clock();

    int matches = 0;

//loop that runs mil times
for(int p = 0; p < 1000000; p++)
{
    //main searching loop.
    for (int i = 1; i < st.st_size-28; i++)
    {

        bool bFound = true;
        for (int j = 0; j < 28; j++)
        {
            if (pData[j] != pData[i+j])
            {
                bFound = false;
                break;
            }
        }
        if (bFound)
        {

        // found a match; set high bit to mark it
        //
        pData[i] |= 0x80;
        matches++;
        }
    }

}
    //grab end time.
    clock_t delta = (clock() - tStart);

    //cout Usefull information.
    cout << "Time: " << delta /1000000.0 << " uSec, Matches: " << matches << "\n";
    cout << "Time / Clock Ticks: " << delta /(float)CLOCKS_PER_SEC << endl;

    //address of array with the search term in it (including the first 28 bits)
    /*
    OUTPUT (to get the address without the search term subtract 28 from the following values)
    Match: 1566
    Match: 1663
    Match: 1691
    Match: 1916
    */
    for (int i = 1; i < st.st_size-28; i++)
    {
        if (!(pData[i] & 0x80))
            continue;

        // print match location
        //
        cout << "  Match: " << i << "\n";
    }
}

void sortMillMarbles(void)
{
    //array variables
    char omarbles[2000];
    char marbles[2000];

    //file variables
    ifstream marbleFile;

    //Time variables.
    clock_t sum = 0;
    clock_t tStart;

    //algorithm variables
    char temp;
    int r = 0;
    int i = 0;
    int b = 1999;
    //read file
    marbleFile.open("marbles.txt");
    for (int h = 0; h < 2000; h++)
    {
        marbleFile >> omarbles[h];
    }
    marbleFile.close();
    //out put marble array
    for (int j = 0; j < 2000; j++)
        {
            cout << omarbles[j] << " ";
        }
    cout << endl << endl;
    //Run marble sort a Million times.
    for(int count=1; count <=1000000; count ++)
    {
        //Reinitialize sorted array to original.
        for (int j = 0; j < 2000; j++)
        {
            marbles[j] = omarbles[j];
        }
        //Reset Variables.
        r = 0;
        i = 0;
        b = 1999;
        //Start your engines.
        tStart = clock();
        //Main algorithmic loop.
        // r marks the head of the sorted red marbles at the beginning of the array
        // b marks the tail of the sorted blue marbles at the end of the array
        // i marks the current marble to be sorted to either the red end or the blue end
        // Thus, r and b move inward towards each other, leaving the white marbles in the middle.
        // Once i has reached b, all the marbles have been sorted
        while(i <= b)
        {
            // Swap the marbles at b and i if i has a blue marble
            if (marbles[i] == 'B')
            {
                temp = marbles[b];
                marbles[b] = marbles[i];
                marbles[i] = temp;
                b--;
            }
            // else if i is pointing to a white marble, move the index forward
            else if (marbles[i] == 'W' || i <= r)
                i++;
            // else i is pointing to a red marble; switch it with r
            else
            {
                temp = marbles[r];
                marbles[r] = marbles[i];
                marbles[i] = temp;
                r++;
            }
        }
        sum = clock() - tStart + sum;
    }//end 100,000 for loop
        for (int j = 0; j < 2000; j++)
            cout << marbles[j] << " ";

        cout << "\n\nSorted 2000 marbles in " << sum / 1000000.0 << " uSeconds." << endl;
        cout << "Time / Clock Ticks: " << sum /(float)CLOCKS_PER_SEC << endl;

}

char prompt(char choice)
{
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Search through intbits.txt" << endl;
    cout << "\t2) Sort Marbles." << endl;
    cout << endl << "\t0) Quit." << endl;
    cout << endl << "Choice\n>>";
    cin >> choice;
    return choice;
}
//A function for laughs and giggles.
void banner(void)
{
        cout << "__________             _____                  _________" << endl
<< "___  ____/_____ _________  /_   ______ _____________  /" << endl
<< "__  /_   _  __ `/_  ___/  __/   _  __ `/_  __ \\  __  / " << endl
<< "_  __/   / /_/ /_(__  )/ /_     / /_/ /_  / / / /_/ /  " << endl
<< "/_/      \\__,_/ /____/ \\__/     \\__,_/ /_/ /_/\\__,_/   " << endl << endl;

cout << "________             _____                    ____________  " << endl
<< "___  __/___  ___________(_)_________  ____________/_/___| |____ " << endl
<< "__  /_ _  / / /_  ___/_  /_  __ \\  / / /_  ___/_  / ____  /__(_)" << endl
<< "_  __/ / /_/ /_  /   _  / / /_/ / /_/ /_(__  )_  /  ___  /___   " << endl
<< "/_/    \\__,_/ /_/    /_/  \\____/\\__,_/ /____/ / /   __/_/ _( )  " << endl
<< "                                              |_|   /_/   _|/   " << endl;
}
void goodbye()
{
    cout << "Goodbye.";
}
int main()
{
    banner();
    char choice;
    while(choice!='0')
    {
        choice = prompt(choice);
        switch(choice)
        {
            case '1':
                cout << "Searching...\n" << endl;
                runMil();
                break;
            case '2':
                cout << "Sorting...\n" << endl;
                sortMillMarbles();
                break;
            case '0':
                goodbye();
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
    return 0;
}
