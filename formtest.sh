#!/bin/bash

# A test to see how forms work in Bash

# Set up the dialog box
FORMBOX=${FORMBOX=dialog}

# Default Values:
TITLE="Default"
DESC="Test1"
HEIGHT=30
WIDTH=50
FORMHEIGHT=25
LABEL="Test_Entry"
LABHEIGHT=1
LABWIDTH=0
ITEM="Test"
ITEMHEIGHT=2
ITEMWIDTH=0
FORMLENGTH=15
ITEMLENGTH=10
FORM1=(1 0 "Test" 2 0 15 10)
FORM2=(3 0 "Second_Form" 4 0 15 15)

$FORMBOX --title "$TITLE" --form "$DESC" $HEIGHT $WIDTH $FORMHEIGHT "First Entry" ${FORM1[*]} "Second Entry" ${FORM2[*]} 2>testchoice.txt
cat testchoice.txt

