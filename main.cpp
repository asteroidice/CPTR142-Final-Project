#include <iostream>

#include <sys/stat.h>
#include <ctime>
#include <stdint.h>

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


int main()
{
    // get size of data file
    //
	struct stat st;
	int status = stat(DATA_FILE, &st);
	if (status < 0)
    {
        cout << "Cannot stat " << DATA_FILE << "\n";
        exit(0);
    }

    // we need at least 28 chars for the pattern and some following
    //
    if (st.st_size < 29)
    {
        cout << "Size of data file is too small.\n";
        exit(0);
    }

    // allocate array for data and read it in
    //
    char *pData = new char[st.st_size];

    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp)
    {
        cout << "Cannot open " << DATA_FILE << "\n";
        exit(0);
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






    return 0;
}
