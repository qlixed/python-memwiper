import pytest
import memwiper

def test_wipe(basicteststr):
    """
    Basic test of the wipe function
    """
    assert memwiper.wipeit(basicteststr) == ''

def test_multiple_references(basicteststr):
    """
    Test with multiple references to the same string
    """
    s1=basicteststr
    s2=s1
    lenbasicteststr = len(basicteststr)
    memwiper.wipeit(s1)
    assert s1 == basicteststr
    assert len(s1) == lenbasicteststr
    assert s2 == basicteststr
    assert len(s2) == lenbasicteststr
    assert s1 == s2
    assert len(s1) == len(s2)

def test_long_string_wipe():
    """
    Test long (65k) string wipe
    """
    s1='C0FEE'
    # Make s1 size 65k besides the len of s1
    s1=s1*(65536/len(s1))
    lens1=len(s1)
    assert memwiper.wipeit(s1)==''
    assert len(s1) == lens1

def test_huge_string_wipe():
    """
    Test HUGE (100M) string wipe
    """
    # Make s1 size 65k besides the len of s1
    s1='DEADMEAT'
    s1=s1*(1024*1024*100/len(s1))
    lens1=len(s1)
    assert memwiper.wipeit(s1)==''
    assert len(s1) == lens1
