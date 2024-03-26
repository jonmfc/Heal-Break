Program was Developed in Winter 2023

In this program I developed a utility for splitting up and combining files of any file type. Whethers its a csv, txt, video or anything else, this program will split it up through the mybreak.c into smaller files that are more manageable. The program myheal.c can be called to recombine the file that has been split up no matter the size. I have included the file Test_File.txt to test

When opening this program, you will need to enter the following steps for running the files:

#1 type in "make" this is to compile both the mybreak.c file and the myheal.c file.

#2 you will want to likely first break up a file into a variety of smaller chunks, prior to healing it. To do this you will use "./mybreak"

After typing ./mybreak you will then need to enter in your source file (the file you want to break up) followed by the prefix. The prexic is what you want the file to be named that you entered. After you enter in the chunk size in kilobytes. Whatever value you enter is the number of kilobytes each file will have. An important thing to note is that the final file will not have the same amount of data in it as the others since in a sense it is the remainder.

After breaking up the file, it will print out that it is starting to break up with first files data, then the seocnds and then it will produce a done message confirming it has split up the file into however many chunks you wanted. if any error is present, it will let you know such as improper arguments entered or inability to open files/createfiles.

#3 After breaking up the file, you will likely want to heal the file. To heal a file, you will enter ./myheal and then you will enter your source, the document you want to move your data into, the prefix of the files you just broke up, the chunk size (this is the same value you entered for how much data you in each file earlier, once again in kilobytes) and finally the num chunks, which is the number of chunk files present. 

After you type in this command, it will let you know that the file has been properly healed. In the event chunk files are missing, it will let you know and additionally in the event files could not be healed it will also let you know. If all is well, it will confirm it was properly healed at the bottom. Issues with opening files, or missing data will also be presented.

In the event of an error, it will still transfer some data into the file, but only the files that were properly formatted. Improper files will not be transfered.