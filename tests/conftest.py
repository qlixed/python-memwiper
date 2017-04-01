import pytest


def pytest_addoption(parser):
    parser.addoption("--testfile",
                     action="append",
                     default=['tests/basictest.txt'],
                     help="File used to load strings for test, "
                     "we provide a default (basictest.txt)")


def pytest_generate_tests(metafunc):
    if 'teststring' not in metafunc.fixturenames:
        return
    strings = None
    with open(metafunc.config.option.testfile[0], 'r', encoding='utf_8') as f:
        strings = f.readlines()
    metafunc.parametrize("teststring", strings)
