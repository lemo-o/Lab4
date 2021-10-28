

#include <iostream>
using namespace std;
//#include <stdlib.h> //I'm using rand for the random number - Nevermind it's terrible
#include <random>
#include <algorithm>
#include <ctime>
//I actually found a fantastic stackoverflow article showing me how to do this
//https://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-does-it-work
//typedef mt19937 MyRNG;
////uint32_t seedvalue;
//originally I removed this, but then I realized that it works in the same way that for() works with it's variable
// it has to be global
//MyRNG taco;
/* I shouldn't need this
uniform_int_distribution<uint32_t> uint_dist;         // by default range [0, MAX]
or this, but I'm leaving it in here because I learned from it.
normal_distribution<double> normal_dist(mean, stddeviation);  // N(mean, stddeviation)
*/
//Okay above this is a mess of comments where I tried one method and got 82
//each time. Below I'm trying another method where you have to "warm up" the mersenne twister
//to increase randomness. Theres probably a really simple error in the above code that I could 
//find and fix, however, I'm learning. 
mt19937 twisting_time(size_t seed)
{
    //randomly learned about static vars here,
    //and constexpr - kinda neat
    static constexpr size_t NDISCARD= 1024;

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
    object():twister(twisting_time(rand_dev())){}
    object(size_t seed): twister(twisting_time(seed)){}

    int next() {return distribution(twister);}
    mt19937 twister;

    //This std::random_device brought me so much pain
    static std::random_device rand_dev;
    static uniform_int_distribution<int> distribution;
    //and this semicolon like what 
    //I mean it makes sense after the fact - it would make less sense without it there
};

random_device object::rand_dev;
uniform_int_distribution<int> object::distribution(0,9999);

//uniform_int_distribution<uint32_t> random(1, 100);
int userinput;
int guessed;
bool correct = false;
//I don't want the variables to be different
int holder=0;
//int holder = random(taco);
int main()
{
    //had to completely change this from my reference code because my reference code was borked
    //go figure - So I learned how to do overloading -----kinda
    {
        object a;
        cout << a.next();
    }
    //This also ended up being a little borked so that was cool
    /* Very borked,and I figured out how to fix the other code
    std::ostream operator<<(std::ostream os, const Object$ object)
    { //so no semicolons because its all one line...
        return os << "" << "1 random string" << a.next() << endl
                  << "" << "2 random string" << b.next() << endl
                  << "" << "3 random string" << c.next() << endl
                  << "" << "4 random string" << d.next() << endl;
    }
    */
    for (int counter = 0; correct == false; counter++)
    {
        cout << holder;
        cout << "Guess: \n";
        cin >> userinput;
        cout << "userinput: " << userinput << "holder: " << holder << endl;
        if (userinput == holder)
        {
            correct = true;
        }
        cout << "Var, correct: " << correct <<endl ;
        counter = guessed;
        cout << counter << endl;
    }
    cout << "Times guessed: " << guessed << endl;
    return 0;
}