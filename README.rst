========
memwiper
========
Now you can overwrite with 0x0's your inmutable strings without issues.


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

Platforms Supported:
====================

* Linux   - Main dev platform, tested and working.
* Mac     - Tested and working, requires more tests. You can check `Issue #2 <https://github.com/qlixed/memwiper/issues/2>`_
* Windows - Not tested yet. You can check `Issue #1 <https://github.com/qlixed/memwiper/issues/1>`_

The code is full Python C API, not external libraries used, this will be done to maximize the portability.
I'm searching help with the Mac and Windows testing, so check the issues and leave a comment if you wanna help!
