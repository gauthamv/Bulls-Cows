#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<cctype>
#include<cstdlib>

using namespace std;

map<string,int> Dictionary;
map<char,string> First_letter_Frequency;
map<char,string> Second_letter_Frequency;
map<char,string> Third_letter_Frequency;
map<char,string> Fourth_letter_Frequency;

void Initialize_Dictionary(); //Function to Initialize the words in the dictionary
void Initialize_Frequency();  //Fuction to Initialize the frequencies of the alphabets
void Arc_Consistency(string,int,int,int,int,int,map<char,int>,map<char,int>,map<char,int>,map<char,int>,class word []);
char Choose_Alphabet(int,map<char,int>);
map<char,int> Reduce_Domain(char,map<char,int>);
int Reduce_Size(char,map<char,int>,int);

int noOfGuesses=0; //Keeps Track of the number of Guesses
int victory=0; //Used to Detect the end of game
int E_3=0; //Used to check for e3
int E_4=0; //Used to check for e4

//Base Class Initialization and Definition
class word
{
  string s; //
  int bullCount,cowCount; //Keeps track of bullcount and cowcount

  public:

  word() { bullCount = 0; cowCount = 0; } //Constructor

  inline void setLetter(int pos, char c) {   s[pos] = c;    } 

  inline void setBullCow(int b,int c)  {   bullCount = b; cowCount = c;  } //sets the overall bull and cow count

  inline int getBull()  {   return bullCount;   } 

  inline int getCow()   {   return cowCount;    }

  inline int checkNull() {   return bullCount+cowCount;    } //Checks if the bullcount + cowcount = 0

  inline string getWord() {  return s; }  //Returns the word

  void guessWord(int);

  void setWord();
  
  inline char getLetter(int pos) { return s[pos]; } //Gives the letter corresponding to the position given

  int compare(string);

  int checkWord();
 
  int Check_with_Initial(string,class word []);

  map<char,int> removeFromDomain(map<char,int> domain)
    {
        int i;
        for(i=0;i<4;i++)
        {
            domain[tolower(s[i])]=0;
        }
        return domain;
    }

  inline void display() {   cout<<" "<<s[0]<<" "<<s[1]<<" "<<s[2]<<" "<<s[3];    }
};

 void display2(string Secret_Word) {   cout<<" "<<Secret_Word[0]<<" "<<Secret_Word[1]<<" "<<Secret_Word[2]<<" "<<Secret_Word[3];    }


//Class Fuction which assigns words to object inbuilt[]
void word::guessWord(int i)
{
   string temp[6] = {"step","word","hymn","back","flux","give"};
   s = temp[i];
}

//Class Function
void word::setWord()
{
   map<string,int>::iterator iter; //Required to choose the random word from dictionary
   srand(time(NULL));
   int randNumber = rand() % 3201;
   iter=Dictionary.begin();
   while(randNumber)
     {
	iter++;
	randNumber--;
     }
   s = iter->first;
}

//Class Function
int word::compare(string temp)
{
   int bull=0,cow=0;
   int i,j;
   for(i=0;i<4;i++)
   for(j=0;j<4;j++)
    {
     if((temp[i])==s[j])
       {
         if(i==j)
           bull++;
         else
           cow++;
         break;
       }
    }
    cout<<"  Bulls = "<<bull<<" Cows = "<<cow<<"\n";
    if(bull==4)
      return 1;
    else
      return 0;
}

//Class Function
int word::checkWord()
{
  int i,j,len;
  string temp;
  do
   {
     cout<<"  Enter the guess word ";
     cin>>temp;
     len=temp.length();
     for(i=0;i<4;i++)
     for(j=i+1;j<4;j++)
      if(temp[i]==temp[j])
        {
         len=5;
         break;
        }
   }while(len!=4);

  int result=compare(temp);
  return result;
}

int word::Check_with_Initial(string Secret_Word,class word inbuilt[])
{
  int bull=0,cow=0;
  int i,j,count=0;
  for(int k=0;k<6;k++)
   { 
     bull = 0; cow =0; 
     for(i=0;i<4;i++)
       {
         for(j=0;j<4;j++)
            {
    	      if((Secret_Word[i])==(inbuilt[k].getLetter(j)))
                 {
                    if(i==j)
                      {
                        bull++;
		      }
                    else
  		      {
           		cow++;
		      }  
         	    break;
	         }
            }     
        }
     if((inbuilt[k].getBull() == bull) && (inbuilt[k].getCow() == cow))
        {
          count++;
        }
   }
  if(count == 6)	
   {
     return 1;
   }
  return 0;
}



void Prune_Domains(map<char,int> &,map<char,int> &,map<char,int> &,map<char,int> &,class word);

void switch1()
{
  word secret;
  word inbuilt[6];

  map<char,int> domain1; //Hash containing the Domain
  map<char,int> domain2;
  map<char,int> domain3;
  map<char,int> domain4;
  map<char,int>::iterator iter;

  int i;
  int bullCheck=0,cowCheck=0; //Used to keep track of the overall bull and cow count
  int bull,cow;     // SWITCH CASE 1, keep track of bull and cow count for each word 
  char temp; 

  //Assign the initial six word to object inBuilt
  for(i=0;i<6;i++)
    inbuilt[i].guessWord(i);

  //Initializing the domain with all alphabets
  for(temp='a';temp<='z';temp++)
   {
     domain1[temp]=1;
     domain2[temp]=1;
     domain3[temp]=1;
     domain4[temp]=1;
   }
 
  //Word Guessing Starts
  for(i=0;i<6;i++)
   {
    if(bullCheck+cowCheck!=4) // consider case where words have J, Q, Z - total count may not add up to 4
      {
	noOfGuesses++;
        cout<<noOfGuesses<<". ";
        inbuilt[i].display();
        cout<<"  Enter number of bulls and cows ";
        cin>>bull>>cow;
        inbuilt[i].setBullCow(bull,cow);
        if(inbuilt[i].getBull()==4)
         {
          cout<<"  The word has been found! \n";
          cout<<" ";
          inbuilt[i].display();
          victory=1;
          break;
         }
        if(inbuilt[i].checkNull()==0)
         {
          domain1=inbuilt[i].removeFromDomain(domain1);
          domain2=inbuilt[i].removeFromDomain(domain2);
          domain3=inbuilt[i].removeFromDomain(domain3);
          domain4=inbuilt[i].removeFromDomain(domain4);

          /*for(iter=domain.begin();iter!=domain.end();iter++)
            {
              cout<<iter->first<<" "<<iter->second<<"\n";
            }*/
          }
         else
          {
           bullCheck+=bull;
           cowCheck+=cow;
          }
      }
    else                      // bullCount + cowCount = 4
      {
       
	if(inbuilt[0].getBull()!=0 || inbuilt[0].getCow()!=0)   // Checking if there are any letters in STEP
         {
          //cout<<"In E check ";
           noOfGuesses++;
          cout<<noOfGuesses<<". ";
          inbuilt[5].display();
          cout<<"  Enter number of bulls and cows ";
          cin>>bull>>cow;
          inbuilt[5].setBullCow(bull,cow);
          if(inbuilt[5].checkNull()==0)      // letters from GIVE not present
           {
               domain1=inbuilt[5].removeFromDomain(domain1);
               domain2=inbuilt[5].removeFromDomain(domain2);
               domain3=inbuilt[5].removeFromDomain(domain3);
               domain4=inbuilt[5].removeFromDomain(domain4);
             // call recursion ? Don't think so.
           }
          else                            // E is present
           {
             //if(inbuilt[0].getBull() && inbuilt[0].getCow()==0 && cow==1)
             //secret.setLetter(2,'E');  // call recursion ?
             //else if(bull==1)
             //secret.setLetter(3,'E');  // call recursion ?
             //else // E either letter 1 or 2
             //secret.setLetter(0,'E'); or secret.setLetter(1,'E');
	     domain1['g'] = 0;
 	     domain1['i'] = 0;
      	     domain1['v'] = 0;
       	     domain2['g'] = 0;
             domain2['i'] = 0;
             domain2['v'] = 0;
             domain3['g'] = 0;
             domain3['i'] = 0;
             domain3['v'] = 0;
             domain4['g'] = 0;
             domain4['i'] = 0;
             domain4['v'] = 0;
           }
         }
        else
         {
	     domain1=inbuilt[5].removeFromDomain(domain1);
             domain2=inbuilt[5].removeFromDomain(domain2);
             domain3=inbuilt[5].removeFromDomain(domain3);
             domain4=inbuilt[5].removeFromDomain(domain4);
         } 
        for(int j=i;j<5;j++)
          {
            if(inbuilt[j].checkNull()==0)
             {
	       domain1=inbuilt[j].removeFromDomain(domain1);
	       domain2=inbuilt[j].removeFromDomain(domain2);
	       domain3=inbuilt[j].removeFromDomain(domain3);
 	       domain4=inbuilt[j].removeFromDomain(domain4);	  
             }
          }
       domain1['j'] = 0;
       domain1['q'] = 0;
       domain1['z'] = 0;
       domain2['j'] = 0;
       domain2['q'] = 0;
       domain2['z'] = 0;
       domain3['j'] = 0;
       domain3['q'] = 0;
       domain3['z'] = 0;
       domain4['j'] = 0;
       domain4['q'] = 0;
       domain4['z'] = 0;
       break;
      }
   }

   if(victory==1) 
     {
       return;
     } //If word is already found return
   //Pre-Processing => Arc consistency step using constraints
   for(int k=0;k<6;k++)
     { 
       Prune_Domains(domain1,domain2,domain3,domain4,inbuilt[k]);
     }
   //Call Main recursion
   string Secret_Word = "____";
   int Domain_Size1=0,Domain_Size2=0,Domain_Size3=0,Domain_Size4=0;
   for(iter=domain1.begin();iter!=domain1.end();iter++)
     {
        if(iter->second == 1)
          {
	    Domain_Size1++;
          }
     }
   for(iter=domain2.begin();iter!=domain2.end();iter++)
     {
        if(iter->second == 1)
          {
            Domain_Size2++;
          }
     }
   for(iter=domain3.begin();iter!=domain3.end();iter++)
     {
        if(iter->second == 1)
          {
            Domain_Size3++;
          }
     }
   for(iter=domain4.begin();iter!=domain4.end();iter++)
     {
        if(iter->second == 1)
          {
           Domain_Size4++;
          }
     }
   
   Arc_Consistency(Secret_Word,0,Domain_Size1+1,Domain_Size2+1,Domain_Size3+1,Domain_Size4+1,domain1,domain2,domain3,domain4,inbuilt); 
   if(victory == 1)
     {
	return;
     }
   else
     {
	cout<<" I ACCEPT DEFEAT!  "<<endl;
     }
}

void switch2() //(word& secret)
{
    word secret;
    secret.setWord();
    int guessCount=0;
    int flag=0;

    do
    {
        if(guessCount==10)
        {
         cout<<"\n  You lost the game ";
         cout<<"\n  The word is";
         secret.display();
         flag++;
         break;
        }
        cout<<"\n  Guess number "<<1+guessCount++<<"\n";

    }while(secret.checkWord()!=1);

    if(flag==0)
    cout<<"\n  You have guessed the word!\n  You win!\n";
}


int main()
{
  int i;            // ITERATOR
  int switchNumber;
  int repeat;       // PLAY AGAIN ?

  Initialize_Dictionary(); //Initializing Dictionary
  Initialize_Frequency(); //Initializing individual alphabet frequency

    noOfGuesses = 0;
    cout<<"\n  Welcome! There are 2 game modes \n\n";
    cout<<"  1. Computer guesses the word \n  2. Player guesses the word \n\n  Select the game mode : ";
    cin>>switchNumber;

    switch(switchNumber)
     {
      case 1:
      cout<<"\n  Think of a 4 letter word \n\n";
      cout<<"  The word should not have any repeating letters. \n\n";
      cout<<"  _ _ _ _ \n\n";
      switch1();
      break;

      case 2:
      cout<<"\n  The computer has thought of a 4 letter word \n";
      cout<<"  It's your turn to guess it (in 10 turns) \n";
      cout<<"  The guess word should not have any repeating letters. \n";
      switch2();
      break;

      default: cout<<"\n  Invalid input! \n";
     }


  return 0;
} 


void Arc_Consistency(string Secret_Word,int Secret_word_Position,int Domain_Size1,int Domain_Size2,int Domain_Size3,int Domain_Size4,map<char,int> Domain1,map<char,int> Domain2,map<char,int> Domain3,map<char,int> Domain4,class word inbuilt[])
{
  if(Secret_word_Position < 4)
    {
      while((Domain_Size1!=0)&&(Domain_Size2!=0)&&(Domain_Size3!=0)&&(Domain_Size4!=0))
        {
          if(Secret_word_Position == 0)
            {
              char alpha = Choose_Alphabet(Secret_word_Position,Domain1);
              Secret_Word[Secret_word_Position] = alpha;
              Domain1 = Reduce_Domain(alpha,Domain1);
              Domain_Size1--;
	      Arc_Consistency(Secret_Word,Secret_word_Position+1,Domain_Size1,Reduce_Size(alpha,Domain2,Domain_Size2),Reduce_Size(alpha,Domain3,Domain_Size3),Reduce_Size(alpha,Domain4,Domain_Size4),Domain1,Reduce_Domain(alpha,Domain2),Reduce_Domain(alpha,Domain3),Reduce_Domain(alpha,Domain4),inbuilt);
            }
          else if(Secret_word_Position == 1)
            {
              char alpha = Choose_Alphabet(Secret_word_Position,Domain2);
              Secret_Word[Secret_word_Position] = alpha;
	      Domain2 = Reduce_Domain(alpha,Domain2);
              Domain_Size2--;
              Arc_Consistency(Secret_Word,Secret_word_Position+1,Domain_Size1,Domain_Size2,Reduce_Size(alpha,Domain3,Domain_Size3),Reduce_Size(alpha,Domain4,Domain_Size4),Domain1,Domain2,Reduce_Domain(alpha,Domain3),Reduce_Domain(alpha,Domain4),inbuilt);
            }
	  else if(Secret_word_Position == 2)
            {
              char alpha = Choose_Alphabet(Secret_word_Position,Domain3);
              Secret_Word[Secret_word_Position] = alpha;
              Domain3 = Reduce_Domain(alpha,Domain3);
              Domain_Size3--;
              Arc_Consistency(Secret_Word,Secret_word_Position+1,Domain_Size1,Domain_Size2,Domain_Size3,Reduce_Size(alpha,Domain4,Domain_Size4),Domain1,Domain2,Domain3,Reduce_Domain(alpha,Domain4),inbuilt);
            }
	  else if(Secret_word_Position == 3)
            {
              char alpha = Choose_Alphabet(Secret_word_Position,Domain4);
              Secret_Word[Secret_word_Position] = alpha;
              Domain4 = Reduce_Domain(alpha,Domain4);
              Domain_Size4--;
              Arc_Consistency(Secret_Word,Secret_word_Position+1,Domain_Size1,Domain_Size2,Domain_Size3,Domain_Size4,Domain1,Domain2,Domain3,Domain4,inbuilt);
            }
        }
    }
  else
    {
      if((Dictionary[Secret_Word] == 1) && (inbuilt[0].Check_with_Initial(Secret_Word,inbuilt)) && (victory!=1)) //inbuilt[0] => Dummy
        {
          if(noOfGuesses<=7)
            {
           	int bull,cow;
	   	noOfGuesses++;
           	cout<<noOfGuesses<<". ";
           	display2(Secret_Word);
           	cout<<"  Enter number of bulls and cows ";
           	cin>>bull>>cow;
           	if(bull==4)
            	   {
            		cout<<"  The word has been found! \n";
            		cout<<" ";
            		victory=1;
           	   }
            }
          else
            {
               if(victory == 0)
	         {
                   victory=0;
		 }
	    }
   	}
    }
}


char Choose_Alphabet(int Secret_word_Position,map<char,int> Domain)
{
  float Max = 0;
  char Max_Char;
  map<char,string>::iterator iter;
  if(Secret_word_Position == 0)
    {
      iter = First_letter_Frequency.begin();
      while(iter!=First_letter_Frequency.end())
        {
	  if(Max < stof(iter->second))
	    {
               if(Domain[iter->first] == 1)
	          {
                    Max = stof(iter->second);
	            Max_Char = iter->first;
		  }
	    }	   
	  iter++;
        }
    }
  else if(Secret_word_Position == 1)
    {
      iter = Second_letter_Frequency.begin();
      while(iter!=Second_letter_Frequency.end())
        {
          if(Max < stof(iter->second))  
            {
	       if(Domain[iter->first] == 1)
                  {
                    Max = stof(iter->second);
                    Max_Char = iter->first;
                  }
            }
          iter++;
        }
    }
  else if(Secret_word_Position == 2)
    {
     // Max = 0;
      iter = Third_letter_Frequency.begin();
      while(iter!=Third_letter_Frequency.end())
        {
          if(Max < stof(iter->second))
            {
                if(Domain[iter->first] == 1)
                  {
                    Max = stof(iter->second);
                    Max_Char = iter->first;
                  }
            }
          iter++;
        }
    }
  else if(Secret_word_Position == 3)
    {
     // Max = 0;
      iter = Fourth_letter_Frequency.begin();
      while(iter!=Fourth_letter_Frequency.end())
        {
          if(Max < stof(iter->second))
            {
                if(Domain[iter->first] == 1)
                  {
                    Max = stof(iter->second);
                    Max_Char = iter->first;
                  }
            }
          iter++;
        }
    }
  return Max_Char;
}

map<char,int> Reduce_Domain(char alpha,map<char,int> Domain)
{
  Domain[alpha] = 0;
  return Domain;
}

int Reduce_Size(char alpha,map<char,int> Domain,int Domain_Size)
{
  if(Domain[alpha] == 0)
    {
      return Domain_Size;
    }	
  else
    {
      return Domain_Size-1;
    }
}

//Fucntion where arc consistency happens
void Prune_Domains(map<char,int> &domain1,map<char,int> &domain2,map<char,int> &domain3,map<char,int> &domain4,class word obj)
{
  int bull_count = 0,cow_count=0;
  string s = obj.getWord();
  if(obj.checkNull() != 0)
    {
      bull_count = obj.getBull();
      cow_count = obj.getCow();
      if(bull_count && (cow_count == 0))
        {
	  domain1 = Reduce_Domain(s[1],domain1);
	  domain1 = Reduce_Domain(s[2],domain1);	 
          domain1 = Reduce_Domain(s[3],domain1);
          domain2 = Reduce_Domain(s[0],domain2);
	  domain2 = Reduce_Domain(s[2],domain2);
	  domain2 = Reduce_Domain(s[3],domain2);
 	  domain3 = Reduce_Domain(s[0],domain3);
          domain3 = Reduce_Domain(s[1],domain3);
          domain3 = Reduce_Domain(s[3],domain3);
          domain4 = Reduce_Domain(s[0],domain4);
          domain4 = Reduce_Domain(s[1],domain4);
          domain4 = Reduce_Domain(s[2],domain4);
        }
       else if((bull_count==0) && (cow_count))
        {
          domain1 = Reduce_Domain(s[0],domain1);
          domain2 = Reduce_Domain(s[1],domain2);
          domain3 = Reduce_Domain(s[2],domain3);
          domain4 = Reduce_Domain(s[3],domain4);
        } 	
    }
}


//Function to Initialize the words in the dictionary
void Initialize_Dictionary()
{
  string word;
  ifstream inFile("Dictionary.txt");
  while(getline(inFile,word))
    {
      Dictionary[word] = 1; 	
    }
  inFile.close();
}

//Fuction to Initialize the frequencies of the alphabets
void Initialize_Frequency()
{
  ifstream inFile_first("Frequency_one.txt");
  ifstream inFile_second("Frequency_two.txt");
  ifstream inFile_third("Frequency_three.txt");
  ifstream inFile_fourth("Frequency_four.txt");
  string First_Frequency,Second_Frequency,Third_Frequency,Fourth_Frequency;
  for(char i='a';i<='z';i++)
    {
      getline(inFile_first,First_Frequency);
      getline(inFile_second,Second_Frequency);
      getline(inFile_third,Third_Frequency);
      getline(inFile_fourth,Fourth_Frequency);
      First_letter_Frequency[i] = First_Frequency;
      Second_letter_Frequency[i] = Second_Frequency;
      Third_letter_Frequency[i] = Third_Frequency;
      Fourth_letter_Frequency[i] = Fourth_Frequency;      
    }  
}
















