Charge Control C Product Documentation
======================================

This repository contains the source files for the Charge Control C user documentation.
The documentation is written in reStructuredText and built with Sphinx.

The published documentation is available on Read the Docs:
https://chargebyte-docs.readthedocs.io/projects/everest-charge-control-c/en/


Repository Structure
--------------------

The main documentation sources are located in:

- `docs/source`

Shared content is maintained in the git submodule:

- `includes`


Repository Initialization
-------------------------

This repository uses git submodules. After cloning, initialize and update them with:

.. code-block:: bash

   git submodule update --init --recursive


Building the Documentation Locally
----------------------------------

Install the Python dependencies first:

.. code-block:: bash

   pip install -r docs/requirements.txt

Then build the HTML documentation from the `docs` directory:

.. code-block:: bash

   cd docs
   sphinx-build -b html source _build/html

The generated HTML files are written to `docs/_build/html`.


Contributing
------------

If you would like to contribute to the documentation, please fork the repository and create a pull
request with your changes. Please keep changes aligned with the existing repository structure and writing style:

- Documentation sources belong in `docs/source`.
- Images belong in `docs/source/_static/images`.
- CSS files belong in `docs/source/_static/css`.
- Static files such as example configurations belong in `docs/source/_static/files`.
- Shared include files belong in the `includes` submodule.
- Documentation files should be written in reStructuredText.
- Documentation files should start with a referenceable label, for example `.. _hardware.rst:`.
- Keep line length at 120 characters maximum, preferably around 100 characters.
- Sections and chapters should be separated by one blank line after the title and two blank lines before the title.
- Sections with a chapter title before them should have only one blank line before the title.
- Capitalize section and chapter titles consistently.


License
-------

See `LICENSE` for license rights and limitations (Apache 2.0).


Contact
-------

For support and product-related questions, please visit:
https://chargebyte.com/support
