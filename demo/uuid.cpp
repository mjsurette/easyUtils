#include "uuid.h"
using namespace easyUtils;

#include <cinttypes>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
    UUID t;
    cout << t.tostring() << endl;

    UUID t2(t.tostring());
    cout << t2.tostring() << endl;

    auto timeStamp = chrono::system_clock::to_time_t(t.timestamp());
    cout << ctime(&timeStamp) << endl;
}
