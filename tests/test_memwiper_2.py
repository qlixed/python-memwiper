import pytest

import subprocess
import shlex

def test_interned_issue():
    cmd=shlex.split("python3 -c \"import memwiper;s='hola';memwiper.wipeit(s);\"")
    p = subprocess.Popen(cmd)
    cout, cerr = p.communicate()
    print("-"*50)
    print("cout:\n", cout)
    print("-"*50)
    print("cerr:\n", cerr)
    print("-"*50)
    assert p.returncode == 0


