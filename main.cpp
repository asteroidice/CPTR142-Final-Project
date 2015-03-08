#include <iostream>
#include "stdio.h"
#include <sys/stat.h>
#include <ctime>
#include <stdint.h>
#include <fstream>

#define DATA_FILE       "./intbits.txt"


using namespace std;


extern "C"
{
	__inline__ uint64_t rdtsc()
	{
		uint32_t lo, hi;
		/* We cannot use "=A", since this would use %rax on x86_64 */
		__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));

		return (uint64_t)hi << 32 | lo;
	}
}

void runMil(void)
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
    uint64_t tStart = rdtsc();

    int matches = 0;


for(int p = 0; p < 1000000; p++)
{
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
        if (!bFound)
            continue;

        // found a match; set high bit to mark it
        //
        pData[i] |= 0x80;
        matches++;
    }

}

    uint64_t delta = (rdtsc() - tStart) / 1000000;


    cout << "Time: " << delta << " uSec, Matches: " << matches << "\n";

    for (int i = 1; i < st.st_size-28; i++)
    {
        if (!(pData[i] & 0x80))
            continue;

        // print match location
        //
        cout << "  Match: " << i << "\n";
    }
}
void searchIntbits(void)
{
    // get size of data file
    //
	struct stat st;
	int status = stat(DATA_FILE, &st);
	if (status < 0)
    {
        cout << "Cannot stat " << DATA_FILE << "\n";
        //exit(0);
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
    uint64_t tStart = rdtsc();

    int matches = 0;
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
        if (!bFound)
            continue;

        // found a match; set high bit to mark it
        //
        pData[i] |= 0x80;
        matches++;
    }

    uint64_t delta = rdtsc() - tStart;


    cout << "Time: " << delta << " uSec, Matches: " << matches << "\n";

    for (int i = 1; i < st.st_size-28; i++)
    {
        if (!(pData[i] & 0x80))
            continue;

        // print match location
        //
        cout << "  Match: " << i << "\n";
    }
}
void sortMarbles(void)
{
    char marbles[2000];
    ifstream marbleFile;

    marbleFile.open("marbles.txt");
    for (int h = 0; h < 2000; h++)
    {
        marbleFile >> marbles[h];
    }
    marbleFile.close();

    for (int j = 0; j < 2000; j++)
        cout << marbles[j] << " ";
    cout << endl;

    char temp;
    int r = 0;
    int i = 0;
    int b = 1999;
    uint64_t tStart = rdtsc();
    while(i <= b)
    {
        if (marbles[i] == 'B')
        {
            temp = marbles[b];
            marbles[b] = marbles[i];
            marbles[i] = temp;
            b--;
        }
        else if (marbles[i] == 'W' || i <= r)
            i++;
        else    // i is pointing to a red marble
        {
            temp = marbles[r];
            marbles[r] = marbles[i];
            marbles[i] = temp;
            r++;
        }
    }
    uint64_t delta = rdtsc() - tStart;
    for (int j = 0; j < 2000; j++)
        cout << marbles[j] << " ";
        
    cout << "\n\nSorted 2000 marbles in " << delta << " uSeconds."

}

char prompt(char choice)
{
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Search through intbits.txt" << endl;
    cout << "\t2) Search through intbits.txt 1000000 times and find average." << endl;
    cout << "\t3) Sort marbles.txt" << endl;
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
                searchIntbits();
                break;
            case '2':
                cout << "Searching...1000000 times...bear with us -______- ...\n" << endl;
                runMil();
                break;
            case '3':
                cout << "Sorting now?...\n" << endl;
                sortMarbles();
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
