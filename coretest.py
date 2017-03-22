import os
import codecs
import getpass
import multiprocessing
import memwiper


def supersecretinfogenerator():
    """
    Generate a file with the rot_13(super secret string)
    """
    s = getpass.getpass('Write your secret string:')
    srot13 = codecs.encode(s, 'rot_13')
    with open('supersecretinfo.txt', 'w') as f:
        f.write(srot13)

if __name__ == "__main__":
    p = multiprocessing.Process(target=supersecretinfogenerator)
    p.start()
    p.join()
    with open("supersecretinfo.txt", 'r') as f:
        sfromfile = f.read()
    print ('The super secret info is:', sfromfile)
    s = codecs.encode(sfromfile, 'rot_13')
    print("Now go and check all out, I will wait here")
    print(""" To do it:
1) Run gdb and attach it to my process ({pid})
      gdb -ex generate-core-file -ex detach -ex quit -p {pid}
   This will generate the file core.{pid}
2) Run:
      strings core.{pid} | grep 'your secret strings'
      Now you can see the super secret info decoded! :o
""".format(pid=os.getpid()))
    input()
    print ("Now, we are going to repeat this, but let me first wipe it")
    memwiper.wipeit(s)
    print("""Now go and check all out, I will wait here.
Again:
1) Run gdb and attach it to my process ({pid})
      gdb -ex generate-core-file -ex detach -ex quit -p {pid}
   This will generate the file core.{pid}
2) Run:
      strings core.{pid} | grep 'your secret strings'
""".format(pid=os.getpid()))
    input()
    print ("Magic?!")
