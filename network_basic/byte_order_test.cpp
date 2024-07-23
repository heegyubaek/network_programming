#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main()
{
    uint16_t hostShort = 0x3412;
    uint32_t hostLong = 0x78563412;

    uint16_t networkShort = htons(hostShort);
    uint32_t networkLong = htonl(hostLong);

    cout << "Host short (0x3412): " << hex << hostShort << endl;
    cout << "Network short: " << hex << networkShort << endl;
    cout << "Host long (0x78563412): " << hex << hostLong << endl;
    cout << "Network long: " << hex << networkLong << endl;

    uint16_t ntohostShort = ntohs(networkShort);
    uint32_t ntohostLong = ntohl(networkLong);

    cout << "Converted Host Short: " << hex << ntohostShort << endl;
    cout << "Converted Host Long: " << hex << ntohostLong << endl;

    return 0;
}