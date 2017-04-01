import pytest
import memwiper


def test_wipe(teststring):
    """
    Basic test of the wipe function
    """
    assert memwiper.wipeit(teststring) == ''

def test_multiple_references(teststring):
    """
    Test with multiple references to the same string
    """
    s1=teststring
    s2=s1
    lenteststring = len(teststring)
    memwiper.wipeit(s1)
    assert s1 == teststring
    assert len(s1) == lenteststring
    assert s2 == teststring
    assert len(s2) == lenteststring
    assert s1 == s2
    assert len(s1) == len(s2)

def test_long_string_wipe():
    """
    Test long (65k+) string wipe
    """
    s1='C0FFEE'*65536
    lens1=len(s1)
    assert memwiper.wipeit(s1)==''
    assert len(s1) == lens1

def test_huge_string_wipe():
    """
    Test HUGE (100M+) string wipe
    """
    s1='C0FEE'*(100 * 1024 * 1024)
    lens1=len(s1)
    assert memwiper.wipeit(s1)==''
    assert len(s1) == lens1
