============
Contributing
============

Contributions are welcome, and they are greatly appreciated! Every
little bit helps, and credit will always be given.

Bug reports
===========

When `reporting a bug <https://github.com/qlixed/python-memwiper/issues>`_ please include:

    * Your operating system name and version.
    * Any details about your local setup that might be helpful in troubleshooting.
    * Detailed steps to reproduce the bug.

Documentation improvements
==========================

python-memwiper could always use more documentation, whether as part of the
official python-memwiper docs, in docstrings, or even on the web in blog posts,
articles, and such.

Feature requests and feedback
=============================

The best way to send feedback is to file an issue at https://github.com/qlixed/python-memwiper/issues.

If you are proposing a feature:

* Explain in detail how it would work.
* Keep the scope as narrow as possible, to make it easier to implement.
* Remember that this is a volunteer-driven project, and that code contributions are welcome :)

Development
===========

To set up `python-memwiper` for local development:

1. Fork `python-memwiper <https://github.com/qlixed/python-memwiper>`_
   (look for the "Fork" button).
2. Clone your fork locally::

    git clone git@github.com:your_name_here/python-memwiper.git

3. Create a branch for local development::

    git checkout -b name-of-your-bugfix-or-feature

   Now you can make your changes locally.

4. When you're done making changes, please run the test in your venv running on the project root::

    pytest

5. Commit your changes and push your branch to GitHub::

    git add .
    git commit -m "Your detailed description of your changes."
    git push origin name-of-your-bugfix-or-feature

6. Submit a pull request through the GitHub website.

Recommendations:
----------------

- Use a virtualenv then clone the repo inside, it will be much easier to destroy-all-the-things in the venv.
- If you're adding code to the C part of this project and need some debug mesages get printed, use the following pattern::

    #ifdef MEMWIPER_DEBUG
        PySys_WriteStderr("...", ...);
    #endif

  And then when you build/install the module in the venv use::

    CFLAGS="-O0 -g -DMEMWIPER_DEBUG" python3 setup.py install

  This will also let you use gdb for further debug.

Pull Request Guidelines
-----------------------

If you need some code review or feedback while you're developing the code just make the pull request.

For merging, you should:

1. Include passing tests (run ``pytest``).
2. Update documentation when there's new API, functionality etc.
3. Add a note to ``CHANGELOG.rst`` about the changes.
4. Add yourself to ``AUTHORS.rst``.


Tips
----

To run a subset of tests::

    pytest -k test_myfeature

