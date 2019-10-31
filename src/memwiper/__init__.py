import memwiper.c_src.memwiper_utils as utils
from memwiper.c_src.memwiper_core import wipeit

VERSION = '0.9.0.dev'
__version__ = VERSION
__all__ = [
    "wipeit",
    "utils",
]
