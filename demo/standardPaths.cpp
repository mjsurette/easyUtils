#include "standardPaths.h"
using namespace easyUtils;

#include <iostream>
using namespace std;

int main()
{
    cout << myHome() << '\n';
    cout << myConfig() << '\n';
    cout << myConfig("standardPaths") << '\n';
    cout << myData() << '\n';
    cout << myData("standardPaths") << '\n';
    cout << myDesktop() << '\n';
    cout << myDocuments() << '\n';
    cout << myDownloads() << '\n';
    cout << myMusic() << '\n';
    cout << myPictures() << '\n';
    cout << myVideos() << endl;
}
