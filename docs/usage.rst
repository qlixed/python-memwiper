=====
Usage
=====

To use python-memwiper in a project::

	import memwiper

As you can see in the code chunk showed on the readme, we have a problem with our sensitive info, but don't worry, here comes memwiper to the rescue::

 In [1]: s1="Another secret agent info"

 In [2]: s2=s1

 In [3]: id(s1)
 Out[3]: 139880143611344

 In [4]: id(s1)==id(s2)
 Out[4]: True

 In [5]: import memwiper

 In [6]: memwiper.wipeit(s1)
 Out[6]: ''

 In [7]: id(s1)
 Out[7]: 139880143611344

 In [8]: id(s1)==id(s2)
 Out[8]: True

 In [9]: s1==s2
 Out[9]: True

 In [10]: print(s1)


 In [11]: print(s2)


 In [12]: s1
 Out[12]: '\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

 In [13]: s2
 Out[13]: '\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

 In [14]: del s1


 In [15]: print(s1)
 ---------------------------------------------------------------------------
 NameError                                 Traceback (most recent call last)
 <ipython-input-15-69407075beda> in <module>()
 ----> 1 print(s1)
 
 NameError: name 's1' is not defined
 
 In [16]: print(s2)

So here we can see what wipeit() do: It overwrite the underlying inmutable
buffer of the string object with 0x0's.


