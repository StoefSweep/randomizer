#!/bin/bash
# RandomGen.sh: This Bash script serves as an interface for the random.c file, generating a form box for the user to input the minimum number, maximum number,
# amount of random numbers to generate, and if they would like to remove duplicate numbers (if possible). Then, these entries will then be passed into the
# random executable file.
# Author: Aidan Stoeffler

# Specify the form:
FORMBOX=${FORMBOX=dialog}

# Specify the title, description, coordinates, and the height of the dialog box here.
TITLE="Random Number Generator"
DESC="This is a random number generator, that can generate random numbers given a range, an amount of numbers to generate, and if you would like \n
to remove duplicates from the random number pool, if possible. In order to begin, please specify the minimum value, maximum value, amount of \n
random numbers to generate, and if you would like to remove duplicates (if possible) in the fields below."
HEIGHT=50
WIDTH=75
FORMHEIGHT=0
#Call the form box, and pass the output into randData.txt, a file that wiil store the user's input.
$FORMBOX --title "$TITLE" --form "$DESC" $HEIGHT $WIDTH $FORMHEIGHT \
       	"Minimum: " 1 0 0 2 0 15 10 \
       	"Maximum: " 3 0 1 4 0 15 10 \
	"Amount to Generate:" 5 0 1 6 0 15 10 \
	"Remove duplicates? (y/n)" 7 0 "y" 8 0 20 1 2>randData.txt
#Initialize an array that will contain the user input, called userInput
userInput=(0 0 0 0)
#Set the delimiter to the newline character, since the entries in randData.txt are separated by a newline.
IFS="\n"
COUNT=0
# Read randData.txt, and pass every line into each cell of userInput.
clear
#A garbage value that will store the file ender.
while read -r VAL; do
	userInput[COUNT]=$VAL
	COUNT="`expr $COUNT + 1`"
done <randData.txt
export IFS=" "
# Call random, using the data in userInput as parameters. If possible, send the output to stdout.
# echo ${userInput[*]}
exec ./random "bashmode" ${userInput[*]}
# END OF SCRIPT
