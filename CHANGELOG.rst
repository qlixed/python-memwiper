
Changelog
=========

* Version 0.9.0-dev:

  - Added MEMWIPER_DEBUG for debug features in the C code.
  - Added a bunch of verbose output on debug mode.
  - As the string could be shared between multiple threads add the 
      related GIL management code.
  - Added sanity checks for the string object after and before 
      changes are made.
  - Added code to handle single referenced strings efficiently 
      using PyUnicode_FILL().
  - Change the wipeit() signature to return nothing, now it only 
      modify the string.

* Version 0.8.0-dev:

  - Added a few more tests.
  - Added some valgrind test on tests/valgrind_tests/ still not automated.

* Versio 0.5.0-dev:

  - Initial Release.
  - Some basic test are in place.
  - Subpackage utils with a few usefull functions for the memwiper code.
