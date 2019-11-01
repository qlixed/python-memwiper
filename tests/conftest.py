import json

import pytest  # noqa: F401


def pytest_addoption(parser):
    parser.addoption(
        "--basicfile",
        action="append",
        default=["tests/basictest.txt"],
        help="File used to load strings for test, "
        "we provide a default one (basictest.txt)",
    )
    parser.addoption(
        "--widefile",
        action="append",
        default=["tests/widetest.txt"],
        help="A JSON file that let define the test "
        "of the differents char wides.\n"
        "We provide a default one (widetest.txt)",
    )


def pytest_generate_tests(metafunc):  # pragma: no cover
    strings = None
    filename = None
    parametrize_to = None

    if "basicteststr" in metafunc.fixturenames:
        filename = metafunc.config.option.basicfile[0]
        parametrize_to = "basicteststr"
    if "wideteststr" in metafunc.fixturenames:
        filename = metafunc.config.option.widefile[0]
        parametrize_to = "wideteststr"
    if "widetestchar" in metafunc.fixturenames:
        filename = metafunc.config.option.widefile[0]
        parametrize_to = "widetestchar"

    if filename:
        with open(filename, "r", encoding="utf_8") as f:
            strings = f.readlines()

    if "wideteststr" in metafunc.fixturenames:
        strings = "".join([x for x in strings if not x.startswith("#")])
        strings = json.loads(strings)["strings"].values()
    if "widetestchar" in metafunc.fixturenames:
        strings = "".join([x for x in strings if not x.startswith("#")])
        strings = json.loads(strings)["chars"].values()

    if parametrize_to:
        metafunc.parametrize(parametrize_to, strings)
    return
