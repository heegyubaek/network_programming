#include <queue>
#include <time.h>
#include <iostream>
using namespace std;

enum class WeatherDataType
{
    Temperature,
    Wind
};

struct TempData
{
    int StationId;
    time_t time;
    double current;
    double max;
    double min;
};

struct WindData
{
    int StationId;
    time_t time;
    int speed;
    short direction;
};

struct Input
{
    WeatherDataType type;
    union
    {
        TempData temp;
        WindData wind;
    };
};

// Macro to print all members of a struct
#define PRINT_STRUCT_MEMBER(s, member) cout << #member ": " << s.member << endl;
#define PRINT_TEMP_DATA(s)            \
    PRINT_STRUCT_MEMBER(s, StationId) \
    PRINT_STRUCT_MEMBER(s, time)      \
    PRINT_STRUCT_MEMBER(s, current)   \
    PRINT_STRUCT_MEMBER(s, max)       \
    PRINT_STRUCT_MEMBER(s, min)

#define PRINT_WIND_DATA(s)            \
    PRINT_STRUCT_MEMBER(s, StationId) \
    PRINT_STRUCT_MEMBER(s, time)      \
    PRINT_STRUCT_MEMBER(s, speed)     \
    PRINT_STRUCT_MEMBER(s, direction)

// Functions that are specific to data types
void Process_Temp(TempData t)
{
    cout << "TempData: " << endl;
    PRINT_TEMP_DATA(t);
}
void Process_Wind(WindData w)
{
    cout << "WindData: " << endl;
    PRINT_WIND_DATA(w);
}

void Initialize(std::queue<Input> &inputs)
{
    Input first;
    first.type = WeatherDataType::Temperature;
    first.temp = {101, 1418855664, 91.8, 108.5, 67.2};
    inputs.push(first);

    Input second;
    second.type = WeatherDataType::Wind;
    second.wind = {204, 1418859354, 14, 27};
    inputs.push(second);
}

int main(int argc, char *argv[])
{
    // Container for all the data records
    queue<Input> inputs;
    Initialize(inputs);
    while (!inputs.empty())
    {
        Input const i = inputs.front();
        switch (i.type)
        {
        case WeatherDataType::Temperature:
            Process_Temp(i.temp);
            break;
        case WeatherDataType::Wind:
            Process_Wind(i.wind);
            break;
        default:
            break;
        }
        inputs.pop();
    }
    return 0;
}