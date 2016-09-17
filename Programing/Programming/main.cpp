#include "option.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;



void localtime(){
    time_t rawtime;
    time (&rawtime);
    printf ("The current local time is: %s", ctime (&rawtime));
}
void secondssince(){
    time_t timer;
    struct tm y2k = {0};
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 1970-1900; y2k.tm_mon = 0; y2k.tm_mday = 1; // La référence est 1900.
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer,mktime(&y2k));
    
    printf ("%.f seconds since January 1, 1970 in the current timezone", seconds);
    
}


void secondsuntil(int year){
    time_t timer;
    struct tm y2k = {0};
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = year-1900; y2k.tm_mon = 0; y2k.tm_mday = 1;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(mktime(&y2k),timer);
    printf("%.f", seconds);
    cout << " seconds until January 1, " << year << " in the current timezone" << endl;
    
}

// Probleme dans la lecture des options. --vers marche et renvoie --version,
// alors que decode devrait renvoyer une erreur.
int main(int argc,char * argv[]){
 
    bool help,version,seconds,time;
    int annee;
    command::CmdLine cmd;
    cmd.add(command::make_option('h',"help",help));
    cmd.add(command::make_option('v',"version",version));
    cmd.add(command::make_option('t',"time",time));
    cmd.add(command::make_option('s',"seconds",seconds));
    cmd.add(command::make_option('a',"annee",annee));
    cmd.process(argv,argc);
    if(help){
        cout<<"Les options que vous pouvez appelees sont:"<<endl;
        cout<<"-v ou --version pour avoir la version du programme"<<endl;
        cout<<"-s ou --secondes pour le nombre de secondes de puis le 01/01/1970"<<endl;
        cout<<"-t ou --time pour l'heure actuelle"<<endl;
        cout<<"-a year ou --annee=year pour le nombre de secondes ecoulees depuis year"<<endl;
    }
    if(version){
        cout<<"version = 1.0"<<endl;
    }
    if(seconds){
        secondssince();
    }
    if(annee){
        secondsuntil(annee);
    }    
    if(time){
        localtime();
        printf("hi");
    }
    return 0;
}


