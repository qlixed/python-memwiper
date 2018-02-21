import pytest


def pytest_addoption(parser):
    parser.addoption("--basicfile",
                     action="append",
                     default=['tests/basictest.txt'],
                     help="File used to load strings for test, "
                     "we provide a default one (basictest.txt)")
    parser.addoption("--widefile",
                    action="append",
                    default=['tests/widetest.txt'],
                    help="A JSON file that let define the test "
                    "of the differents char wides.\n"
                    "We provide a default one (widetest.txt)")


def pytest_generate_tests(metafunc):
    if 'basicteststr' not in metafunc.fixturenames:
        return
    strings = None
    with open(metafunc.config.option.testfile[0], 'r', encoding='utf_8') as f:
        strings = f.readlines()
    metafunc.parametrize("basicteststr", strings)
