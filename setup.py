from setuptools import setup, Extension
# To use a consistent encoding
from codecs import open
from os import path

here = path.abspath(path.dirname(__file__))

# Get the long description from the README file
with open(path.join(here, 'README.rst'), encoding='utf-8') as f:
    long_description = f.read()

setup(
    name='memwiper',
    version='0.9.9',

    description='MemWiper, wipe strings filling them with NULLs',
    long_description=long_description,

    # The project's main homepage.
    url='https://github.com/pypa/sampleproject',

    # Author details
    author='QliXed - Ezequiel Hector Brizuela',
    author_email='qlixed@gmail.com',

    # Choose your license
    license='MIT',

    # See https://pypi.python.org/pypi?%3Aaction=list_classifiers
    classifiers=[
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 3 - Alpha',

        # Indicate who your project is intended for
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Libraries',
        'Topic :: Security',

        # Pick your license as you wish (should match "license" above)
        'License :: OSI Approved :: MIT License',

        'Operating System :: POSIX :: Linux',
        # Specify the Python versions you support here. In particular, ensure
        # that you indicate whether you support Python 2, Python 3 or both.
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: C',
    ],

    # What does your project relate to?
    keywords='security',

    # Alternatively, if you want to distribute just a my_module.py, uncomment
    # this:
    ext_modules = [
        Extension('memwiper',
            sources = ['memwiper/memwiper.c'])
    ]
)
