#include <iostream>
#include <random>
#include <time.h>
#include <fstream>
#include <sstream>
#include "header.h"

using namespace std;

const int MAX = 20;                                                 //max for arrays over entire scope

/*------Struct declarations--------------------------*/

struct Claim{

    int claimId;
    string description;
    int complexity;
    int uncertainty;
    int mechList[MAX];

    int claimCounter;

};

struct Mechanic {

    int mechanicId;
    string name;
    int ability;
    int variability;

};

/*------Global variables--------------------------*/

Claim claimList[MAX];
Mechanic mechanicList[MAX];

/*------ claim functons ----------------------------*/

Claim loadClaim(string str){

    Claim singleClaim;
    string firstHalf, secHalf, splitStr[MAX];
    size_t last = 0;
    size_t next = 0;

    while ((next = str.find( ":", last)) != string::npos) {         //while next is the string until delimiter (:) and is not the end of string
            firstHalf = str.substr(last, next-last);                //firstHalf is substring w/ position of the first character starting at last and length of substr (next-last)
            last = next + 1;                                        //firstHalf would print claimId,desc,complex,uncert,mechanic (1flat tire43mechanic:)
        }

    secHalf = str.substr(last);                                     //second half is the substring after delimiter. would print int,int...etc. (135)
    last = 0;
    next = 0;
    int k = 0;

    while ((next = firstHalf.find( ",", last)) != string::npos) {   //splits string at each comma
            splitStr[k++]= firstHalf.substr(last, next-last);       //each split from comma is entered into splitStr array
            last = next + 1;
    }

    splitStr[k++]= firstHalf.substr(last);
    last = 0;
    next = 0;
    k = 0;

    while ((next = secHalf.find( ",", last)) != string::npos) {     //splitting the commas for second half
            singleClaim.mechList[k++]= stoi( secHalf.substr(last, next-last) );     //accessing current claim's mechList and adding the string as an integer
            last = next + 1;
    }
    singleClaim.mechList[k++]= stoi(secHalf.substr(last));

    singleClaim.claimId = stoi(splitStr[0]);                        //accessing the split firstHalf string from array and assigning it to claim variables
    singleClaim.description = splitStr[1];
    singleClaim.complexity = stoi(splitStr[2]);
    singleClaim.uncertainty = stoi(splitStr[3]);

    singleClaim.claimCounter = k;                                   //claimCounter will be used in claim eval
    return singleClaim;

}

string printClaim(Claim currentClaim){

    string str = "";
     str+="-------------------------------------------\n";

        str+="Claim ID: "+ to_string(currentClaim.claimId) +"\n";
        str+="Description: "+currentClaim.description;
        str+="\nComplexity: "+to_string(currentClaim.complexity)+" Uncertainty: "+to_string(currentClaim.uncertainty);
        str+="\nMechanics: ";
        for(int i = 0; i<currentClaim.claimCounter; i++){
            if(i!=currentClaim.claimCounter - 1)                    //this will print the list of mechanics with a comma separating any mecanic that is a predecessor for another mecanic. else there will be no comma
                str+=to_string(currentClaim.mechList[i])+", ";
            else
                str+=to_string(currentClaim.mechList[i]);
        }
     str+="\n-------------------------------------------\n";
    return str;
}

/*-----mechanic functions---------------------------*/

void loadMechanics(string fileName){

    ifstream inFile(fileName);
    string str;
    string splitStr[MAX];
    int mechanicListSize = 0;

    if(!inFile.good())                                              //Checking status of file
        Error("Unable to access file titled: " + fileName);         //send message to error function

    while(getline(inFile, str)){

        size_t last = 0, next = 0; int i=0;
        while((next = str.find(",", last))!= string::npos){         //removing commas in same way as loadClaim

            splitStr[i++] = str.substr(last, next-last);
            last = next +1;
        }

        splitStr[i++] = str.substr(last);

        mechanicList[mechanicListSize].mechanicId = stoi(splitStr[0]);
        mechanicList[mechanicListSize].name = splitStr[1];
        mechanicList[mechanicListSize].ability = stoi(splitStr[2]);
        mechanicList[mechanicListSize].variability = stoi(splitStr[3]);

        mechanicListSize++;
    }

    cout<<printMechanics();

}

string printMechanics(){

    string str="";
    str+="=============List of Mechanics=============\n";

    for(int i=0; i<=10; i++){
        str+="--------------------------------------------\n";
        str+="Mechanic ID: "+ to_string(mechanicList[i].mechanicId) + " Name: "+mechanicList[i].name;
        str+="\nAbility: "+ to_string(mechanicList[i].ability)+" Variability: "+ to_string(mechanicList[i].variability)+"\n";
    }
    return str;


}

/*------Trial generator ---------------------------*/

int trialGenerator(Claim claim, Mechanic mech){

    int mean = mech.ability - claim.complexity;
    int stdDeviation = claim.uncertainty + mech.variability;

    default_random_engine randEng(time(NULL));                      //a random decice provides better seeding
    normal_distribution<> dist(mean, stdDeviation);                 //calculate normal distribution via mean and std deviation

    return round(dist(randEng));                                    //returns a random number according to standard deviation of uncertainty and variability

}
/*------Claim evaluation ---------------------------*/

void claimEvaluation(string inputFile, string outputFile){

    ofstream outFile;
    outFile.open(outputFile);

    ifstream inFile;
    inFile.open( inputFile );

    string str;

    if(!inFile.good()) {                                             //test if input file opens correctly
            Error("Unable to open file " + inputFile);}
    if(!outFile.good())  {                                           //test if output file created correctly
            Error("Unable to create file " + outputFile);}


    outFile<<printMechanics();                                          //prints list of mechanics to output.txt


    cout<<"\n===============List of Claims==============="<<endl;
    outFile<<"\n===============List of Claims==============="<<endl;
    while(getline(inFile, str)){
        Claim singleClaim = loadClaim(str);
        cout<<printClaim(singleClaim);                                   //prints all claims to cmd using printClaim() method
        outFile<<printClaim(singleClaim);                               //by making printClaim() return a string I can use it with the outFile<< operator
    }

    inFile.close();

    inFile.open( inputFile );                                           //to read the same file again from the start after looping to print claims list

    cout<<"\n============= Evaluating Claims ============="<<endl;
    outFile<<"\n============= Evaluating Claims ============="<<endl;

    while(getline(inFile, str)){                                     //accessing the claims file

        Claim singleClaim = loadClaim(str);                         //sends the string just read to load claim which will separate commas and create a claim object

        cout<<"============================================"<<endl;
        outFile<<"============================================"<<endl;

        outFile<<"Claim "<<singleClaim.claimId<<endl;
        cout<<"Claim "<<singleClaim.claimId<<endl;                  //printing the claim num

        outFile<<"Description: "<<singleClaim.description<<"\nComplexity: "<<singleClaim.complexity<<"\nUncertainty: "<<singleClaim.uncertainty<<"\n"<<endl;
        cout<<"Description: "<<singleClaim.description<<"\nComplexity: "<<singleClaim.complexity<<"\nUncertainty: "<<singleClaim.uncertainty<<"\n"<<endl;


        bool failure = true;                                        //used to break out of loop in the case of success

        for(int i = 0; i<singleClaim.claimCounter;i++){

            int mechId = singleClaim.mechList[i];

            cout<<"Trial with mechanic "<<mechanicList[mechId].mechanicId<<", '"<<mechanicList[mechId].name<<"': ";
            outFile<<"Trial with mechanic "<<mechanicList[mechId].mechanicId<<", '"<<mechanicList[mechId].name<<"': ";

            int trialResult = trialGenerator(singleClaim, mechanicList[mechId]);

            if(trialResult<=50){
                cout<<"Trial failed with an outcome of "<<trialResult<<endl;
                outFile<<"Trial failed with an outcome of "<<trialResult<<endl;

                cout<<"--------------------------------------------"<<endl;
                outFile<<"--------------------------------------------"<<endl;
            }else if(trialResult>50){
                 cout<<"Trial succeeded with an outcome of "<<trialResult<<endl;
                outFile<<"Trial succeeded with an outcome of "<<trialResult<<endl;

                cout<<"--------------------------------------------"<<endl;
                outFile<<"--------------------------------------------"<<endl;

                cout<<"Current claim evaluation is completed."<<endl;
                outFile<<"Current claim evaluation is completed."<<endl;

                cout<<"============================================\n"<<endl;
                outFile<<"============================================\n"<<endl;

                failure = false;                                    //if no mechanic succeeds failure remains true and will be processed in next if loop
                break;                                              //this will break out of loop rather than continue testing mechanics is the list
            } //end of if-else statement
        } //end of for loop

        if(failure){
            cout<<"The car cannot be fixed and is scrap."<<endl;
            outFile<<"The car cannot be fixed and is scrap."<<endl;

            cout<<"============================================\n"<<endl;
            outFile<<"============================================\n"<<endl;
        }//end of if loop

    } //end of while loop

    outFile.close();
    inFile.close();
} //end of method



/*------Error message------------------------------*/

int Error(string message){

    cerr<<"\nError: "<< message<<"\nExiting."<<endl;                  //will take a string message for a variety of errors
    exit(1);
}
