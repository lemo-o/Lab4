/*Ben Hall
Section 05
9/21
Lab 4
Most of the work I did was making a better number generator - which doesn't seem too hard, but I actually spent quite a few hours looking through 
it and finding information on number generation to making this work. Originally, I was going to use rand(), but rand() sucks, it gave me the same
number 80% of the time. Then I moved to a better solution using the mersenne twister. The first solution, in hindsight would've worked if I was 
clever about how i executed it, however, I really didn't understand it that well so I wouldn't have been able to be clever in the first place.
Then I found another piece of code on the mt19937 and then I learned about static vars, constexpr, and overloading, and overloading was an accident.
Turns out the guy's code was just hard to read. I already understood how to do for() loops, so the rest of the assignment wasn't too hard,
then I ended up wondering why I was so ambitious when choosing what to do as an extra learning activity. 

Anyway, I'll attach two files, one will be a really messy piece of code with lots of explanation, named main.cpp. The other is this one, final.cpp.
I split them up like this because main.cpp has so many ideas bouncing around in it that it got incredibly hard to read. I left some stuff in here,
but I cut most of it out. 
*/
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <math.h>
using namespace std;

//Below I'm trying another method where you have to "warm up" the mersenne twister
mt19937 twisting_time(size_t seed)
{
    //randomly learned about static vars here,
    //and constexpr - kinda neat
    static constexpr size_t NDISCARD = 1024;

    //This is a number generator
    minstd_rand lcg(seed);
    lcg.discard(NDISCARD);

    size_t seeds[mt19937::state_size];
    //generate_n is the one thing that goes over my head here - I understand that it's performing something to
    //whatever is going on in the parantheses, but I don't get what that something is mathematically. I also get
    //what the goal of the something is. Its like a "something --> *Magic* --> Something else" trick
    generate_n(seeds, mt19937::state_size, lcg);

    seed_seq seed_sequence(begin(seeds), end(seeds));
    mt19937 twister{seed_sequence};
    twister.discard(NDISCARD);

    return twister;
}
struct object
{
    object() : twister(twisting_time(rand_dev())) {}
    object(size_t seed) : twister(twisting_time(seed)) {}

    int next() { return distribution(twister); }
    mt19937 twister;

    //This std::random_device brought me so much pain
    static std::random_device rand_dev;
    static uniform_int_distribution<int> distribution;
    //and this semicolon like what
    //I mean it makes sense after the fact - it would make less sense without it there
};

random_device object::rand_dev;
uniform_int_distribution<int> object::distribution(1000, 9999);
//This is a really lazy way to make that between 100
uniform_int_distribution<uint32_t> uint_dist100(0, 100);
typedef mt19937 transcendance;
//globally define
int userinput;
int guessed;
bool correct = false;
int holder;
//int *pointer;
int really;

int main()
{

    {
        object a;
        holder = a.next();
    }
    //haha I gave up and just used some math to make it work
    holder = trunc(holder / 100);

    for (int counter = 0; correct == false; counter += 1)
    {
        //so that it displays the correct answer at the beginning
        cout << "Correct Answer is: " << holder << endl;
        cout << "Guess: \n";
        cin >> userinput;
        if (userinput == holder)
        {
            correct = true;
        }
        else if(userinput < holder)
        {
            cout << "Too low\n";
        }
        else if( userinput > holder)
        {
            cout << "Too high \n";
        }
        //get the var out
        guessed = counter +1;
    }
    cout << "Times guessed: " << guessed << endl;
    return 0;
}