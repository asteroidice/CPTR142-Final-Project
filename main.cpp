/*#import<iostream>
char BinSrchTree::miniMenu(bool isMiniMenu)
//A menu that prints options, and takes the user's choice
{
    char choice;
    if (isMiniMenu){
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    cout << "\t1) Build a binary search tree." << endl;
    cout << "\t2) Traverse the tree using InOrder." << endl;
    cout << "\t3) Traverse the tree using LevelOrder." << endl;
    cout << "\t4) Traverse the tree using PostOrder." << endl;
    cout << "\t5) Delete a specific node." << endl;
    cout << "\t6) Clear the tree." << endl;
    cout << "\t7) Run the case specified in the homework." << endl;
    cout << endl << "\t0) Quit." << endl;
    }
    else
    {
        cout << "\n\n1)Build\t\t2)InOrder\t3)LevelOrder\t4)PostOrder\t5)Delete\t\t6)Clear\t\t7)HWCase\n";
    }
    cout << endl;
    cout << ">>>";
    //choice = getchar();
    cin >> choice;
    cout << endl;
    return choice;
}
int BinSrchTree::menu()
{

    char option = NULL;
    bool printMenu = true;
    cout <<"            ,@@@@@@@,\n"
    <<"    ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
    <<" ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
   <<",%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
   <<"%&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
   <<"%&&%/ %&%%&&@@\\ \V /@@' `88\\8 `/88'\n"
   <<"`&%\\ ` /%&'    |.|        \\ '|8'\n"
   <<"    |o|        | |         | |\n"
   <<"    |.|        | |         | |\n"
   <<" _\\/ ._\\/____ /__ \\_//__\\\\/___\\_//__/_/ ____\n"
    <<"( \\/\\/ )( ___)(  )  / __)(  _  )(  \\/  )( ___)\n"
    <<" )    (  )__)  )(__( (__  )(_)(  )    (  )__) \n"
    <<"(__/\\__)(____)(____)\\___)(_____)(_/\\/\\_)(____)\n";

    while(option!='0')
    {
        option = miniMenu(printMenu);
        switch(option)
        {
            case '0': cout << "  _____             ____\n"
                << " / ___/__  ___  ___/ / /  __ _____ \n"
                << "/ (_ / _ \\/ _ \\/ _  / _ \\/ // / -_)\n"
                << "\\___/\\___/\\___/\\_,_/_.__/\\_, /\\__/ \n"
                << "                        /___/      \n";
            break;
            case '1':
                int n;
                cout << "Enter how many integers you would like to enter into the tree: ";
                cin >> n;
                for(int i=1; i<=n; i++)
                    {
                        fillNode();
                        insertNode();
                    }
                printMenu = false;
                break;
            case '2': inOrder(); printMenu = false; break;
            case '3': levelOrder(); printMenu = false; break;
            case '4': postOrder(); printMenu = false; break;
            case '5':
                int del;
                cout << "Please enter the data value of the node you would like to delete: ";
                cin >> del;
                deleteNode(del);
                printMenu = false;
                break;
            case '6': clearTree(); printMenu = false; break;
            case '7':
                cout << "Clearing existing trees and executing the homework case." << endl;
                break;
            default : cerr << "\nERROR: '" << option << "' is not a valid menu option.\n\n"; printMenu = true; break;
        }
    }
    return(0);
}

int main()
{
    BinSrchTree a;
   a.menu();

}
*/

#include <iostream>

using namespace std;

char menu(int choice)
{
    cout << "Menu:\n";
    cout << "1: 'Write'\n";
    cout << "2: 'Search'\n";
    cout << "0: Exit the program.'\n";
    cout << "Input here: ";
    cin >> choice;
    return choice;
}

int main()
{
    int choice;
    menu(choice);
    while(choice!=0)
    {
        switch(choice)
        {
            case '1':
                cout << "Writing now?..." << endl;
                break;
            case '2':
                cout << "Searching now?..." << endl;
                break;
        }
    }
    return 0;
}
