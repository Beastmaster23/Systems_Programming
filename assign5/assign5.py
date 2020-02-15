import argparse
import os
import subprocess
import re
#template file
template="test.html"
#data directory 
data_dir="./data"
#output directory
output_dir="./output"
#date to be replaced
date="00/00/00"
#template arguments that can be recognized
template_args={
    "first_name":None,
    "last_name":None,
    "lease_start":None,
    "lease_end":None,
    "balance":None,
    "apt_number":None,
    "date":None
}

parser=argparse.ArgumentParser()

parser.add_argument("data", nargs=1, metavar="datadir", help="Data directory")
parser.add_argument("template", nargs=1, metavar="temp", help="Template file")
parser.add_argument("date", nargs=1, metavar="date", help="Date to be replaced")
parser.add_argument("output", nargs=1, metavar="outputdir", help="Output data directory")

parser.add_argument("-s", nargs=2, metavar=("<<", ">>"), help="Argument buffers")
parser.add_argument("-t", nargs="?", metavar="t_args", help="Template arguments")

args=parser.parse_args()

if os.path.isdir(args.data[0]):
    data_dir=args.data[0]
else:
    print("Data directory must be made")
    exit(-1)
try:
    #Make sure to have read access
    f=open(args.template[0], "r")
    f.close()
    template=args.template[0]
except OSError:
    print("Error at: "+args.template[0])
    exit(-1)
#Make output directory if non-existent
if not os.path.isdir(args.output[0]):
    os.mkdir(args.output[0])

output_dir=args.output[0]

if args.t!=None:
    template_args={}
    if type(args.t)==list:        
        for x in args.t:
            template_args[x]=None
    else:
        template_args[args.t]=None

def read_apt(file):
    apt=dict()
    l=list(template_args.keys())
    try:
        f=open(file, "r")
    except OSError:
        print("Error at: "+file)
        exit(-1)
    p=0
    #get names
    names=f.readline().split(" ", 1)
    for n in range(len(names)):
        names[n]=names[n].rstrip("\n\r")
    #print(apt[l[p]])
    apt[l[p]]=names[0]
    p+=1
    apt[l[p]]=names[1]
    p+=1
    line =f.readline()
    while line !="":
        entries=line.split(" ")
        for n in range(len(entries)):
            entries[n]=entries[n].rstrip("\n\r")
        for e in entries:
            apt[l[p]]=e
            p+=1
        line =f.readline()
    f.close()
    apt[l[p]]=os.path.splitext(os.path.basename(file))[0]
    p+=1
    apt[l[p]]=date
    return apt

def fill_template(line, apt, temp_args=template_args, l="<<", r=">>"):
    for i in apt.keys():
        line=re.sub(l+"[ ]*"+i+"[ ]*"+r, apt[i], line)
    return line

def create_file(path, access="w", indx=1):    
    if os.path.isfile(path):
        temp=os.path.splitext(path)        
        while os.path.isfile(''.join([temp[0], str(indx), temp[1]])):
            indx+=1
        path=''.join([temp[0], str(indx), temp[1]])
    f=open(path, access)
    return f

for f in os.listdir(data_dir):
    apt=read_apt(data_dir+"/"+f)
    f=open(template, "r")    
    out=create_file(output_dir+"/"+apt["last_name"]+".mail", "w")
    l=f.readline()
    while l!="":
        if args.s==None:
            out.write(fill_template(l, apt))
        elif len(args.s)==1:
            out.write(fill_template(l, apt, l=args.s[0]))
        elif len(args.s)==2:
            out.write(fill_template(l, apt, l=args.s[0], r=args.s[1]))
        l=f.readline()
    f.close()
    out.close()