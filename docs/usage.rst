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

A memory dump example:
======================

Here another classic example: a core dump. For this we make a script,
coretest.py that you can use to check for yourself, it requires:

* A linux platform, We are tracking options to make this on other platforms on
  `Issue #6 <https://github.com/qlixed/python-memwiper/issues/6>`_
* Any modern gdb version installed.

Here is an example run of coretest.py::

 Generating the supersecretinfo.txt file:
 Attaching to process 4181
 Reading symbols from /home/qlixed/srced/memwiper/bin/python3...Reading symbols from /home/qlixed/srced/memwiper/bin/python3...(no debugging symbols found)...done.
 (no debugging symbols found)...done.
 Reading symbols from /lib64/libpthread.so.0...Reading symbols from /usr/lib/debug/usr/lib64/libpthread-2.24.so.debug...done.
 done.
 [Thread debugging using libthread_db enabled]
 Using host libthread_db library "/lib64/libthread_db.so.1".
 0x00007f43e0953f8a in __waitpid (pid=4188, stat_loc=0x7fff998c1fd4, options=0) at ../sysdeps/unix/sysv/linux/waitpid.c:29
 29	  return SYSCALL_CANCEL (wait4, pid, stat_loc, options, NULL);
 Saved corefile core-pre.4181
 Detaching from program: /home/qlixed/srced/memwiper/bin/python3, process 4181
 Attaching to process 4181
 Reading symbols from /home/qlixed/srced/memwiper/bin/python3...Reading symbols from /home/qlixed/srced/memwiper/bin/python3...(no debugging symbols found)...done.
 (no debugging symbols found)...done.
 Reading symbols from /lib64/libpthread.so.0...Reading symbols from /usr/lib/debug/usr/lib64/libpthread-2.24.so.debug...done.
 done.
 [Thread debugging using libthread_db enabled]
 Using host libthread_db library "/lib64/libthread_db.so.1".
 0x00007f43e0953f8a in __waitpid (pid=4200, stat_loc=0x7fff998c1fd4, options=0) at ../sysdeps/unix/sysv/linux/waitpid.c:29
 29	  return SYSCALL_CANCEL (wait4, pid, stat_loc, options, NULL);
 Saved corefile core-pos.4181
 Detaching from program: /home/qlixed/srced/memwiper/bin/python3, process 4181
 The super secret info is: Zl njrfbzr cnffjbeq
 Generating core-pre.4181:
 gdb -q -ex 'set auto-solib-add 0' -ex 'attach 4181' -ex 'gcore core-pre.4181' -ex detach -ex quit
 Now we're going to overwrite the memory,
 Generating core-pos.4181:
 gdb -q -ex 'set auto-solib-add 0' -ex 'attach 4181' -ex 'gcore core-pos.4181' -ex detach -ex quit
 Well, all done now you can check the files using:
 
 # strings core-pre.4181 | grep 'My awesome password'
 # strings core-pos.4181 | grep 'My awesome password'
 
 The core-pre.4181 contains the secret, as object was active in memory.
 The core-pos.4181 don't contains the secret, because we wipeit() from memory.

So, if you execute the commands mentioned you get::

 # strings core-pre.4181 | grep 'My awesome password'
 My awesome password
 # strings core-pos.4181 | grep 'My awesome password'
 
 #

As you can see the core dump in the core-pos.<pid> file don't contains the sensitive data in the memory dump.
