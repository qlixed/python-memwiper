========
Overview
========

.. start-badges

.. list-table::
    :stub-columns: 1

    * - docs
      - |docs|
    * - tests
      - | |travis| |appveyor|
        | |coveralls| |codecov|
    * - package
      - | |version| |wheel| |supported-versions| |supported-implementations|
        | |commits-since|

.. |docs| image:: https://readthedocs.org/projects/python-memwiper/badge/?style=flat
    :target: https://readthedocs.org/projects/python-memwiper
    :alt: Documentation Status

.. |travis| image:: https://travis-ci.org/qlixed/python-memwiper.svg?branch=master
    :alt: Travis-CI Build Status
    :target: https://travis-ci.org/qlixed/python-memwiper

.. |appveyor| image:: https://ci.appveyor.com/api/projects/status/github/qlixed/python-memwiper?branch=master&svg=true
    :alt: AppVeyor Build Status
    :target: https://ci.appveyor.com/project/qlixed/python-memwiper

.. |coveralls| image:: https://coveralls.io/repos/qlixed/python-memwiper/badge.svg?branch=master&service=github
    :alt: Coverage Status
    :target: https://coveralls.io/r/qlixed/python-memwiper

.. |codecov| image:: https://codecov.io/github/qlixed/python-memwiper/coverage.svg?branch=master
    :alt: Coverage Status
    :target: https://codecov.io/github/qlixed/python-memwiper

.. |version| image:: https://img.shields.io/pypi/v/memwiper.svg
    :alt: PyPI Package latest release
    :target: https://pypi.python.org/pypi/memwiper

.. |commits-since| image:: https://img.shields.io/github/commits-since/qlixed/python-memwiper/v1.0.0.svg
    :alt: Commits since latest release
    :target: https://github.com/qlixed/python-memwiper/compare/v1.0.0...master

.. |wheel| image:: https://img.shields.io/pypi/wheel/memwiper.svg
    :alt: PyPI Wheel
    :target: https://pypi.python.org/pypi/memwiper

.. |supported-versions| image:: https://img.shields.io/pypi/pyversions/memwiper.svg
    :alt: Supported versions
    :target: https://pypi.python.org/pypi/memwiper

.. |supported-implementations| image:: https://img.shields.io/pypi/implementation/memwiper.svg
    :alt: Supported implementations
    :target: https://pypi.python.org/pypi/memwiper


.. end-badges

Now you can overwrite with 0x0's your inmutable strings without issues

* Free software: BSD license

Installation
============

::

    pip install memwiper

Documentation
=============

https://python-memwiper.readthedocs.io/

Development
===========

To run the all tests run::

    tox

Note, to combine the coverage data from all the tox environments run:

.. list-table::
    :widths: 10 90
    :stub-columns: 1

    - - Windows
      - ::

            set PYTEST_ADDOPTS=--cov-append
            tox

    - - Other
      - ::

            PYTEST_ADDOPTS=--cov-append tox
memwiper
==========
.. image:: https://travis-ci.org/qlixed/memwiper.svg?branch=master
    :target: https://travis-ci.org/qlixed/memwiper
Now you can overwrite with 0x0's your inmutable strings without issues.

Platforms Supported:
====================

* Linux   - Main dev platform, tested and working.
* Mac     - Tested and working, requires more tests. You can check `Issue #2 <https://github.com/qlixed/memwiper/issues/2>`_
* Windows - Not tested yet. You can check `Issue #1 <https://github.com/qlixed/memwiper/issues/1>`_

The code is full Python C API, not external libraries used, this will be done to maximize the portability.
I'm searching help with the Mac and Windows testing, so check the issues and leave a comment if you wanna help!

Why I do this?:
===============

All your sensitive information belongs to the memory!

Well that obvious, I know, but is a weird issue to handle in most of the
languages that uses garbage collection for memory management and inmutable
strings, let me show a quick ipython example::

 In [1]: s1="Secret Agent data"

 In [2]: s2=s1

 In [3]: id(s1)
 Out[3]: 139856402094672

 In [4]: id(s2)
 Out[4]: 139856402094672

 In [5]: del s1

 In [6]: id(s1)
 ---------------------------------------------------------------------------
 NameError                                 Traceback (most recent call last)
 <ipython-input-6-4e7c3ecb85de> in <module>()
 ----> 1 id(s1)

 NameError: name 's1' is not defined

 In [7]: id(s2)
 Out[7]: 139856402094672

 In [8]: help(id)
 Help on built-in function id in module builtins:

 id(obj, /)
    Return the identity of an object.

    This is guaranteed to be unique among simultaneously existing objects.
    (CPython uses the object's memory address.)

 In [3]: print(s2)
 Out[3]: Secret Agent data

I delete the s1 string, but the s2 points to the same string, 
as you can see in the help showed there id show the memory address of
the object, so s1 and s2 points to the same memory position.

The del s1 never really delete the memory object because the string have another reference to it.

An Example:
===========

As you can see in the previous code chunck, we have a problem with our sensitive info, but don't worry, here comes memwiper to the rescue::

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
  `Issue #6 <https://github.com/qlixed/memwiper/issues/6>`_
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
