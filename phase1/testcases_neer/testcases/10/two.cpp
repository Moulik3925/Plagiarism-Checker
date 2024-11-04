#include <stdio.h>
#include <sys/time.h>
#include<chrono>
#include <cstdlib>
#include <ctime>

int main()
{
    struct timeval tv,tv1,tv2;
    struct timezone tz,tz1;
    
    for(long k = 10;k<1000000;k+=500)
    {
        double d = 0;
        for(long r = 0; r<100;r++)
        {
            long guessindx = 0;
            long arr[k];
            for(long i=0;i<k;i++)
            {
                arr[i] = 0;
            }
            auto start = std::chrono::steady_clock::now();
            for(long p = 0;p<100;p++)
            {
                long l = arr[guessindx];
                

                std::srand(std::time(nullptr)); // use current time as seed for random generator
                int random_increment = 100 + std::rand() % 101; // random number between 100 and 200
                guessindx += random_increment;
                guessindx%=k;
            }
            auto end = std::chrono::steady_clock::now();
            d += ((double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())/100;
        }
        printf("%ld , %lf\n",(k),(d/100));

    }
}