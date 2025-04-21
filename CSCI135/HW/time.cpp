/*
Author: Rian M Alif
Course: CSCI-135
Instructor: Tong Yi
Assignment: Lab 10 E
*/
/*
This program makes two functions using time.
*/
/**/

#include <iostream>
#include <string>
using namespace std;

class Time
{
public:
    int hours;
    int minutes;
};

int minutesSinceMidnight(Time time)
{
    return time.hours * 60 + time.minutes;
}

int minutesUntil(Time earlier, Time later)
{
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
}

Time addMinutes(Time time0, int mins)
{
    int total = minutesSinceMidnight(time0) + mins;
    Time result;
    result.hours = total / 60;
    result.minutes = total % 60;
    return result;
}

struct TimeSlot
{
    string title;
    string genre;
    int duration;
    Time start;
};

void printTimeSlot(TimeSlot ts)
{
    Time end = addMinutes(ts.start, ts.duration);

    cout << ts.title
         << " " << ts.genre
         << " (" << ts.duration << " min) "
         << "[starts at "
         << ts.start.hours << ":"
         << (ts.start.minutes < 10 ? "0" : "") << ts.start.minutes
         << ", ends by "
         << end.hours << ":"
         << (end.minutes < 10 ? "0" : "") << end.minutes
         << "]";
}

struct Movie
{
    string title;
    string genre;
    int duration;
};

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie)
{
    Time nextStart = addMinutes(ts.start, ts.duration);
    TimeSlot result;
    result.title = nextMovie.title;
    result.genre = nextMovie.genre;
    result.duration = nextMovie.duration;
    result.start = nextStart;
    return result;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2)
{
    int start1 = minutesSinceMidnight(ts1.start);
    int end1 = start1 + ts1.duration;
    int start2 = minutesSinceMidnight(ts2.start);
    int end2 = start2 + ts2.duration;
    // overlap if each starts before the other ends
    return (end1 > start2 && end2 > start1);
}

int main()
{
    // define five slots
    TimeSlot slots[] = {
        {"Back to the Future", "COMEDY", 116, {9, 15}},
        {"Black Panther", "ACTION", 134, {12, 15}},
        {"Black Panther", "ACTION", 134, {16, 45}},
        {"Inception", "SCI-FI", 148, {18, 30}},
        {"The Lion King", "ANIMATION", 88, {20, 30}}};

    int count = sizeof(slots) / sizeof(slots[0]);
    for (int i = 0; i < count; ++i)
    {
        printTimeSlot(slots[i]);
        cout << endl;
    }

    // test timeOverlap
    cout << boolalpha;

    // overlapping example
    TimeSlot overlapSlot = {"Morning Drama", "DRAMA", 60, {10, 0}};
    cout << "Overlap between \"" << slots[0].title
         << "\" and \"" << overlapSlot.title << "\": "
         << timeOverlap(slots[0], overlapSlot) << endl;

    // non‐overlapping example (starts exactly when slot[0] ends)
    Movie nextMov = {"The Avengers", "ACTION", 143};
    TimeSlot avengersSlot = scheduleAfter(slots[0], nextMov);
    cout << "Overlap between \"" << slots[0].title
         << "\" and \"" << avengersSlot.title << "\": "
         << timeOverlap(slots[0], avengersSlot) << endl;

    return 0;
}