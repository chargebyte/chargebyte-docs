chargebyte Shared Documentation Includes
========================================

This repository contains shared documentation building blocks used by chargebyte product documentation
projects.

The content in this repository is intended to be consumed as a git submodule by product-specific
documentation repositories. It contains reusable reStructuredText include files, Sphinx templates,
and shared static assets.


Contents
--------

Typical content in this repository includes:

- shared `.inc` files for user guides and developer documentation
- shared Sphinx templates in `_templates`
- shared static assets referenced by documentation projects


Usage
-----

Product documentation repositories include files from this repository via standard Sphinx
`.. include::` directives and shared template/static paths.

Changes in this repository may affect multiple documentation projects. Please keep shared content
generic where possible and product-specific where necessary.


Contributing
------------

When updating shared content:

- keep wording and structure reusable across documentation projects where possible
- avoid introducing assumptions that only apply to one product unless the file is explicitly product-specific
- keep reStructuredText formatting consistent with the consuming repositories


License
-------

See `LICENSE` for license rights and limitations.


Contact
-------

For support and product-related questions, please visit:
https://chargebyte.com/support
