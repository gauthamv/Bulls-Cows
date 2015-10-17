

open(DATA1,"<Webpage.txt");
open(DATA2,">Dictionary.txt");

while(<DATA1>)
 {
   while($_=~m/(<li class="defLink"><a href="\/word\/(\w+)\/">\w+<\/a><\/li>)/)
     {
      my $count = 0;
      my $word = $2;
      my $write_word = $word;
      #$_=~s/$word//g;
      $_=~s/<li class="defLink"><a href="\/word\/$word\/">$word<\/a><\/li>//g;
      $word=~m/(\w)(\w)(\w)(\w)/;
      my $first_word = $1;
      my $second_word = $2; 
      my $third_word = $3;
      my $fourth_word = $4;
      if($word=~s/$first_word//g)
        {
	  $count++;
        }
      if($word=~s/$second_word//g)
        {
	  $count++;
        }
      if($word=~s/$third_word//g)
        {
          $count++;
        }
      if($word=~s/$fourth_word//g)
        {
          $count++;
        }
      if($count == 4)
        {
          print DATA2 $write_word;
          print DATA2 "\n";
        }
     }
 }

close DATA1;
close DATA2;


#This is the Part where the Frequency of alphapbets are calculated

open(DATA1,"<Dictionary.txt");
open(DATA2,">Frequency_one.txt");
open(DATA3,">Frequency_two.txt");
open(DATA4,">Frequency_three.txt");
open(DATA5,">Frequency_four.txt");

my @alphabet_list = ("a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z");
my %frequency_hash_first = {}; #Stores frequency of alphabets when they occur as the first character
my %frequency_hash_second = {}; #Stores frequency of alphabets when they occur as the second character
my %frequency_hash_third = {}; #Stores frequency of alphabets when they occur as the third character
my %frequency_hash_fourth = {}; #Stores frequency of alphabets when they occur as the fourth character
my $line; #To get the individual lines

#To get First Alphabet
while(<DATA1>)
 {
   $line = $_;
   foreach $alpha (@alphabet_list)
     {
       if($line=~m/^$alpha\w\w\w/)
	 {
	   $frequency_hash_first{$alpha} = $frequency_hash_first{$alpha} + 1;
	 }
     }   
 }   

seek(DATA1,0,0);

my $frequency = 0;
foreach $key (sort keys %frequency_hash_first)
 { 
   $frequency = ($frequency_hash_first{$key}/3201) * 100;
   print DATA2 "$frequency\n"
 } 


#To get Second Alphabet
while(<DATA1>)
 {
   $line = $_;
   foreach $alpha (@alphabet_list)
     {
       if($line=~m/\w$alpha\w\w/)
         {
           $frequency_hash_second{$alpha} = $frequency_hash_second{$alpha} + 1;
         }
     }
 }

seek(DATA1,0,0);

my $frequency = 0;
foreach $key (sort keys %frequency_hash_second)
 {
   $frequency = ($frequency_hash_second{$key}/3201) * 100;
   print DATA3 "$frequency\n"
 }


#To get Third Alphabet
while(<DATA1>)
 {
   $line = $_;
   foreach $alpha (@alphabet_list)
     {
       if($line=~m/\w\w$alpha\w/)
         {
           $frequency_hash_third{$alpha} = $frequency_hash_third{$alpha} + 1;
         }
     }
 }

seek(DATA1,0,0);

my $frequency = 0;
foreach $key (sort keys %frequency_hash_third)
 {
   $frequency = ($frequency_hash_third{$key}/3201) * 100;
   print DATA4 "$frequency\n"
 }


#To get fourth Alphabet
while(<DATA1>)
 {
   $line = $_;
   foreach $alpha (@alphabet_list)
     {
       if($line=~m/\w\w\w$alpha/)
         {
           $frequency_hash_fourth{$alpha} = $frequency_hash_fourth{$alpha} + 1;
         }
     }
 }

seek(DATA1,0,0);

my $frequency = 0;
foreach $key (sort keys %frequency_hash_fourth)
 {
   $frequency = ($frequency_hash_fourth{$key}/3201) * 100;
   print DATA5 "$frequency\n"
 }













