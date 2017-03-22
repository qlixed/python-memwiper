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
