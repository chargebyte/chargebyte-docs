Charge SOM Product Documentation
================================

This is the product documentation project for the Charge SOM, a product of chargebyte GmbH.
This documentation is intended for users, developers, and administrators of the Charge SOM.
This documentation is hosted on Read the Docs and can be accessed at
https://chargebyte-docs.readthedocs.io/en/latest/.


Contents:
---------

- Charge SOM User Guide

Repo initialization:
-------------------
This repository is using git submodules to share documents between the user guides.
After cloning of the project please execute the following command:

git submodule update --init --force --remote


Building the documentation locally:
-----------------------------------

To build the documentation locally, you need to have Python and pip installed on your system.
You can install the required dependencies by running the following command:

pip install -r requirements.txt

After installing the dependencies, you can build the documentation by running the following command:

sphinx-build -a docs/source {output_directory}

The output directory is the directory where the generated HTML files will be stored.


Contributing:
-------------

If you would like to contribute to the documentation, please fork the repository and create a pull
request with your changes. Please make sure to follow the guidelines for contributing to the
documentation:

- The branch name for the pull request should be `everest/csom_{your_branch_name}`.
- Maximum line length should be 120 characters (Preferably 100 characters).
- Images should be stored in the `docs/source/_static/images` directory
- CSS files should be stored in the `docs/source/_static/css` directory
- Source and config files should be stored in the `docs/source/_static/files` directory
- A documentation file should be written in reStructuredText format
- A documentation file should start with referenceable label of the file name (e.g. ".. _hardware.rst:")
- Sections and chapters should be separated by one blank line after the title and two blank lines before the title
- Sections with a chapter title before, need to have only one blank line before the title
- First letters of section and chapter titles should be capitalized (e.g. "Charge SOM User Guide")


License:
--------

See the LICENSE file for license rights and limitations (Apache 2.0).


Contact:
--------

If you have any questions or inquiries, please contact our support team at https://chargebyte.com/support.

Thank you for using products from chargebyte GmbH!
