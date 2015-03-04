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
   <<" _\\/ ._\\/____ /__ \\_//__\\\\/___\\_//__/_*/ ____\n"
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