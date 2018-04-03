TODO:
----

- Rehash the string. See Issue #XX
- Acelerate the for loop on large strings.
  - Evaluate the usage of memcpy, not sure yet if is the same that 
    use the PyUnicode_Write(), further test required.
- Make test for single reference strings specifically to measure
  the performance of PyUnicode_Fill().
- Make performance-related tests.

