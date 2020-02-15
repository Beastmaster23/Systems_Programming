import sys
import os
import random
import string
diryo="./"
def random_date():
    return str(random.randint(1, 13))+"/"+str(random.randint(1, 33))+"/"+str    (random.randint(1900, 5000))

def random_last_name(maxv=7):
    last_name=random_letters(maxv)
    while random.randint(0, 4)>2:

        last_name+=" "+random_letters(maxv)
    return last_name

def random_letters(max_len=7):
    str_val=""
    for i in range(0, max_len):
        str_val+=random.choice(string.ascii_letters)
    return str_val

def create_test_data(maxv=5):
    for i in range(0, maxv):
        first_name=random_letters(9)
        last_name=random_last_name(12)
        start_date=random_date()
        end_date=random_date()
        balance=random.randint(-1000, 1000)
        f=open(diryo+ str(random.randint(111, 999))+".apt", "w")
        f.write(first_name+" "+last_name+"\n")
        f.write(start_date+" "+end_date+"\n")
        f.write(str(balance))

if len(sys.argv)==2:
    if not os.path.isdir(sys.argv[1]):
        os.mkdir(sys.argv[1])
    diryo=sys.argv[1]+"/"
    create_test_data(10)