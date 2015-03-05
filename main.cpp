#import<iostream>

char prompt(void)
{
    char choice;
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Search through intbits.txt" << endl;
    cout << "\t2) Sort marbles.txt" << endl;
    cout << endl << "\t0) Quit." << endl;
    cout << endl << "Choice\n>>";
    cin >> choice;
    return choice;
}


int main()
{
    prompt();

}
