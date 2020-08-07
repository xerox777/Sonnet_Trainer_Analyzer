
// Author : Grant Fonseca && Kunal Patel
// Date : NOVEMBER 2017
// CLASS : CS 242
// PROFESSOR : GURMAN GILL
//  sample.cpp
//
//
//  Copyright © 2017 Gurman Gill. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
float tallycol = 0.0;
float zeroprob = 0.0;
float newnum = 0.0;
float shaketally = 0.0;
float eliztally = 0.0;
float shaketally2 = 0.0;
float eliztally2 = 0.0;
vector<float> probability;
vector<float> tally;
vector<float> Eprobability;
std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int checkWord(string word, const vector<string>& sonnet)
{
    //Linear search to check if word exists in the array sonnet
    for (int i=0; i<sonnet.size(); ++i)
    {
        if (!sonnet[i].compare(word))
            return 1;
    }
    
    return 0;
    
}

void populateFeature(const vector<string>& sonnet, const vector<string>& dictionary, vector<int>& currentFeature)
{
    
    //Go through each word in dictinary and check if it exists in sonnet
  for (int i=0; i<dictionary.size(); ++i)
    {
      currentFeature[i] = checkWord(dictionary[i], sonnet);
    }

}


void wordinsonnet(vector < vector<int> > Poem, vector<float> &probability, int dsize, int othersize)
{
	for (int i = 0; i < dsize; i++)		// TODO FUNCTION TO AUTOMATE THE PROBABILITY CALCULATIONS!
	{
		for (int j = 0; j < othersize; j++)
		{
			tallycol += Poem.at(j).at(i);
		}
		zeroprob = (tallycol+1)/(othersize+2);
		probability.push_back(zeroprob);
		//cout << "#4 probs: " << zeroprob << endl;
		tallycol = 0.0;
		zeroprob = 0.0;
	}
}

void btheorem(vector < vector<int> > &stest, vector < vector<int> > &etest, vector<float> & Sprob, vector<float> & Eprob, int dsize, int ssize, int esize)
{

	
	float sTotal = 0.0;
	float eTotal = 0.0;
	float totalt = 0.0;
	float st = 0.0;
	float et = 0.0;
	//st = stest.size();
	//et = etest.size();
	st = ssize;
	et = esize;
	sTotal = st/(et + st);
	eTotal = et/(et + st);
	//cout << st << "\t"  << et + st << "\t" << et << "\t p(Eliz): " << eTotal << "\t p(Shake): " << sTotal;
	float shaketotalprobs = 0.0;
	float eliztotalprobs = 0.0;
	//cout << st << "\t" << sTotal << "\t" << et << "\t" <<  eTotal << "\n";
 	//shaketotalprobs = log(sTotal);
	//eliztotalprobs = log(eTotal);
	//cout << shaketotalprobs << "\t ElizProb --> " << eliztotalprobs << endl;
	for (int i = 0; i < stest.size(); i++)
	{
	

		   shaketotalprobs = log(sTotal);
		   eliztotalprobs = log(eTotal);
		
		for (int j = 0; j < dsize; j++)
		{

		  if (stest[i][j] == 1)
		  {
			
			shaketotalprobs += (log(Sprob[j]));// + log(sTotal));	// #5 probabilities
			eliztotalprobs += (log(Eprob[j]));//  + log(sTotal));
		  }
		   //eliztotalprobs += log(Eprob[j]);		//TODO SEE WHICH PROB IS BIGGER AND THAT BECOMES THE ESTIMATE (SHAKE/ ELIZ)
		  else
		  {
		  	shaketotalprobs += (log(1 - Sprob[j]));// + log(sTotal));
			eliztotalprobs += (log(1 - Eprob[j]));// + log(sTotal));

		  }
		  //eliztotalprobs += (1 - log(Eprob[j]));
		 }
		//cout << "index " << i << ": " << shaketotalprobs << "\n";
		  //cout << "\nShake: " << shaketotalprobs << " Eliz: " << eliztotalprobs;;
		  
		   if (shaketotalprobs > eliztotalprobs)
		   	shaketally++;

 	}
		
		shaketotalprobs = 0.0;
		eliztotalprobs = 0.0;// TODO SHOULD ADD UP TO NUMERATOR
	for (int i = 0; i < etest.size(); i++)
	{
		
		   shaketotalprobs = log(sTotal);
		   eliztotalprobs = log(eTotal);
		
		for (int j = 0; j < dsize; j++)
		{
		  if (etest[i][j] == 1)
		   {
		   	eliztotalprobs += log(Eprob[j]);// + log(eTotal);
			shaketotalprobs += log(Sprob[j]);// + log(sTotal);
		   }
		  else
		   {
		   	eliztotalprobs +=  log(1 - Eprob[j]);// + log(eTotal);
			shaketotalprobs += log(1- Sprob[j]);// + log(sTotal);
		   }

		 }
		
		  if (eliztotalprobs > shaketotalprobs)
		   	eliztally++;			// TODO SHOULD ADD UP TO NUMERATOR
		
	//	cout << "index " << i << ": eliz prob: " << eliztotalprobs << "\t" << "shakespeare prob: " << shaketotalprobs << "\n";
	}


}

void probcalc (vector<float> &prob, vector<float> source)
{
	for (int i = 0; i < source.size(); i++)
	{
		newnum += log(source[i]);// + (1 - source[i]));
		//cout << source[i]  << " ";
	}
	
	prob.push_back(newnum);
	newnum = 0.0;
}

int main(int argc, const char * argv[]) {

    
    //Define a random dictionary. (For the project 2, you will be reading the actual dictionary from a file)
    //string dictionary = "these are some words in a dictionary";
    //vector<string> dictWords = split(dictionary, ' '); //Creates a vector of strings = { "these", "are", "some", "words","in", "a", "dictonary" };
   ifstream s_train;
   ifstream e_train;
   ifstream s_data;
   ifstream e_data;
   ifstream dictionary;
   dictionary.open("dictionary.txt");
   cout << "Enter the names of the Shakespearean training file, Elizabethan training file, Shakespearean test file and Elizabethan test file (in that order): ";
   string sstrain;
   string eetrain;
   string ssdata;
   string eedata;

/*	string variable;
	cin >> variable;
	const char*newVar = variable.c_str();
*/
   cin >> sstrain >> eetrain >> ssdata >> eedata;
   const char*svar = sstrain.c_str();
   const char*spop = ssdata.c_str();
   const char*evar = eetrain.c_str();
   const char*epop = eedata.c_str();
   string temp;
   s_train.open(svar);
   e_train.open(evar);
   s_data.open(spop);
   e_data.open(epop);
   string intome;
   while (getline(s_data, temp))
   	intome += temp + "\n";

   vector<string> sdatatxt = split(intome, '\n');

   temp = "";
   intome = "";
   while (getline(e_data, temp))
   	intome += temp + "\n";
   vector<string> edatatxt = split(intome, '\n');
   temp = "";
   intome = "";
   while (getline(s_train, temp))
   	intome += temp + "\n";
    vector<string> straintxt = split(intome, '\n');
    temp = "";
    intome = "";
    while (getline(dictionary, temp))
    	intome = intome + temp + " ";
   
    vector<string> dictWords = split(intome, ' ');
   temp = "";
   intome = "";
   while(getline(e_train, temp))
   	intome += temp + "\n";
   
   vector<string> etraintxt = split(intome, '\n');
    cout << "Total number of words in dictionary: " <<  dictWords.size() << "\n";
   cout << "Total sonnet in ShakespeareData_train_50.txt are: "	<< straintxt.size() << "\nTotal sonnet in ElizabethanData_train_50.txt are: " << etraintxt.size() << "\n";
    //Define a random sonnet. (For the project 2, you will be reading actual sonnets from some files)
    
    int numWords = dictWords.size(); //Number of words in the dictionary
    
    //Define a vector whose size is equal to the size of the dictionary.
    vector<int> currentFeature(numWords);
    
    // Populate currentFeature with 1's and 0's indicating the presence/absence of dictionary words in the sonnet
    vector<vector<int> > data;
    string temp2;
    s_train.close();

    s_train.open(svar);
    for (int l = 0; l < straintxt.size(); l++)
    {
    	getline(s_train, temp2); 	// WAS S_TRAIN ORIGINALLY
	vector<string> CurrentSonnet = split(temp2, ' ');
	populateFeature(CurrentSonnet, dictWords, currentFeature);
	data.push_back(currentFeature);
    }
    for (int l = 0; l < straintxt.size(); l++)
    {
    	for (int d = 0; d < dictWords.size(); d++)
	{
	//	cout << " " << data.at(l).at(d);
	}
	//cout << endl << endl;
    }
  vector<vector<int> > Edata;
  temp2 = "";
  e_train.close();
 
   e_train.open(evar);
  e_data.close();

   e_data.open(epop);
     vector<int> currentfeature(numWords);
  for (int i = 0; i < etraintxt.size(); i++)	// was for e_train originally
  {
  	getline(e_train, temp2);
	vector<string> currentsonnet0 = split(temp2, ' ');
	populateFeature(currentsonnet0, dictWords, currentfeature);
	Edata.push_back(currentfeature);
  }
  e_data.close();

   e_data.open(epop);
  temp2 = "";
  vector<vector<int> > Edata2d;

  vector<int> currentfeature0(numWords);
  for (int i = 0; i < edatatxt.size(); i++)	// was for e_train originally
  {
  	getline(e_data, temp2);
	vector<string> currentsonnet1 = split(temp2, ' ');
	populateFeature(currentsonnet1, dictWords, currentfeature0);
	Edata2d.push_back(currentfeature0);
  }

  temp2 = "";
  vector<vector<int> > Sdata2d;
  s_data.close();
  
   s_data.open(spop);

  vector<int> currentfeature1(numWords);
  for (int i = 0; i < sdatatxt.size(); i++)	// was for e_train originally
  {
  	getline(s_data, temp2);
	vector<string> currentsonnet2 = split(temp2, ' ');
	populateFeature(currentsonnet2, dictWords, currentfeature1);
	Sdata2d.push_back(currentfeature1);
  }
//	cout << straintxt.size() << endl;
   vector<float> edataprob;
   vector<float> sdataprob;
    wordinsonnet(Edata2d, edataprob, dictWords.size(),  sdatatxt.size());
    wordinsonnet(Sdata2d, sdataprob, dictWords.size(),  sdatatxt.size());
   wordinsonnet(data, probability, dictWords.size(),  straintxt.size());
   for (int i = 0; i < probability.size(); i++)
   	{
//	cout << probability[i] << "\n";
	}
   //vector <float> fin;
   //probcalc(fin , probability); 
   //for (int i = 0; i < fin.size(); i++)
  // 	cout << fin[i] << " ";
	//cout << etraintxt.size() << endl;
   //cout << "Eliz: " << endl;
   wordinsonnet(Edata, Eprobability, dictWords.size(), etraintxt.size());
//cout << "\n" << "\n";
  for (int i = 0; i < Eprobability.size(); i++)
  	{
  	//cout << Eprobability[i] << "\n";
  	}
    btheorem(Sdata2d, Edata2d, probability, Eprobability, dictWords.size(), straintxt.size(), etraintxt.size());	//WAS btheorem(data, Edata, probability, Eprobability, dictWords.size());

   float ccacc = 0.0;
   ccacc = (eliztally + shaketally)/(edatatxt.size()+sdatatxt.size()) * 100;
   float classy = 0.0;
   classy = ((shaketally / sdatatxt.size()) * 100);
   //cout << eliztotalprobs << " " << shaketotalprobs << " ";
    //populateFeature(sonnetWords, dictWords, currentFeature);
    
    //Print out the feature vector

   cout << endl << "Total sonnet in" << spop << " are: " <<  sdatatxt.size()  << "\n" << "Classification accuracy " << "(" << shaketally << "/" << sdatatxt.size() << ")= " << classy;

 float supergenius = 0.0;
 supergenius = eliztally/edatatxt.size()  * 100;
 cout  << "\nTotal sonnet in " << epop << " are: " << edatatxt.size() << "\n" << "Classification accuracy " << "(" << eliztally << "/" << edatatxt.size() << ")= " << supergenius << "\nCombined Classification accuracy" << " (" << eliztally + shaketally<< "/" << edatatxt.size()+sdatatxt.size() << ")= " << ccacc << "\n";
for (int i=0; i<numWords; ++i)
    {
       //cout << currentFeature[i] << " ";
    }
    cout << endl;
    
        return 0;
}

