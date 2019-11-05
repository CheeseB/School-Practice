#!/usr/bin/python3

import os

f = os.popen("ls -aFl /root")
lines = f.readlines()

isdir=0
isfile=0
for line in lines[3:]:
    if line[len(line)-2]=='/':
        isdir+=1
    else:
        isfile+=1

print("directory:"+str(isdir)+", file:"+str(isfile))

for line in lines[3:]:
    print(line[43:len(line)-1]+" "+line[25:29]+" "+line[:10])


