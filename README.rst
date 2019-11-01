========
memwiper
========
Now you can overwrite with garbage your inmutable strings without issues.


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

.. |commits-since| image:: https://img.shields.io/github/commits-since/qlixed/python-memwiper/v0.8.0-dev.svg
    :alt: Commits since latest release
    :target: https://github.com/qlixed/python-memwiper/compare/v0.8.0-dev...master

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

Now you can overwrite with garbage your inmutable strings without breaking all.

* Free software: MIT license - Can I use this in a GPLed software?: Yes, see https://softwareengineering.stackexchange.com/questions/316393/what-to-do-when-using-mit-licensed-code-in-a-gpl-licensed-project for a quick overview of the matter.

Latest version v0.9.0.alpha

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

Platforms Supported:
====================

* Linux   - Main dev platform, tested and working.
* Mac     - Tested and working, requires more testing. You can check `Issue #2 <https://github.com/qlixed/python-memwiper/issues/2>`_
* Windows - Tested and working, requires more testing. You can check `Issue #1 <https://github.com/qlixed/python-memwiper/issues/1>`_

The code is full Python C API, not external libraries used, this was done to maximize the portability.
{I'm searching help with the Mac and Windows testing, so check the issues and leave a comment if you wanna help!

Why?:
=====

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

The del s1 never really delete the memory object because the string have another reference to it. Furthermore if you del all the related objects the memory space is not really deleted until the GC needs/wants to.

And the worst part of this: As the Python strings are inmutable you CAN'T overwrite it with something like this:

in[9]: s2="#####"

Becasue this will create the string "#####" in some memory possition and points s2 to it, leaving the old content in memory, this space might be reused and overwrited by another variable when the GC mark it as "free".

So with memwiper you can overwrite the underlying buffer of the string with 0x0's to avoid have lingering in memory sensitive information.
