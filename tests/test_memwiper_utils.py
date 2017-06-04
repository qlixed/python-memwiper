import pytest

import memwiper.utils as mwutils

UNICODE_KIND = [
    "Wide Char",
    "1 Byte",
    "2 Byte",
    "4 Byte"
]

s1 = "'Hello friend!' in spanish: '¡Hola amigo!'"
# Japanese text using 2 Byte wide unicode simbols
s2 = "'Hello friend!' in spanish: 'こんにちは！'"
# Pi definition, uses 4 byte wide unicode simbols
s3 = "Pi definition: 𝝅=𝑪/𝐝"


def test_memwiper_utils_kind():
    assert mwutils.kind(s1) in UNICODE_KIND
    assert mwutils.kind(s1) == UNICODE_KIND[1]
    assert mwutils.kind(s2) in UNICODE_KIND
    assert mwutils.kind(s2) == UNICODE_KIND[2]
    assert mwutils.kind(s3) in UNICODE_KIND
    assert mwutils.kind(s3) == UNICODE_KIND[3]


def test_memwiper_utils_codepoints():
    assert mwutils.codepoints(s1) == len(s1)
    assert mwutils.codepoints(s2) == len(s2)
    assert mwutils.codepoints(s3) == len(s3)


def test_memwiper_utils_size():
    assert mwutils.size(s1) == len(s1)
    assert mwutils.size(s2) == len(s2)*2
    assert mwutils.size(s3) == len(s3)*4
