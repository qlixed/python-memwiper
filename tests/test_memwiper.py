import pytest
import memwiper

def test_multibyte_repr():
    scs='你好朋友！'
    s1b='Hola amigo!'
    assert memwiper.wipeit(s1b) == ''
    assert memwiper.wipeit(scs) == ''


def test_multiple_references():
    s1='Hola amigo!'
    s2=s1
    ls1=len(s1)
    memwiper.wipeit(s1)
    assert len(s1) == ls1


