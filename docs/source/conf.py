# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import os

# Documentation version
current_version = "latest"

# Check if the current version is "latest"; if not, display a warning
if os.getenv("READTHEDOCS_VERSION") and os.getenv("READTHEDOCS_VERSION") != current_version:
#    html_context = {
#        "display_lower_left": True,
#        "current_version": os.getenv("READTHEDOCS_VERSION"),
#        "warning_banner": "This documentation is outdated. Visit the latest version at: https://yourproject.readthedocs.io/en/latest/"
#    }
    html_theme_options = {
    "warning_banner": "This documentation is outdated. Visit the latest version at: https://yourproject.readthedocs.io/en/latest/"
    }

rtd_version = os.getenv("READTHEDOCS_VERSION", "NOT SET")
print(f"DEBUG: READTHEDOCS_VERSION = {rtd_version}")

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Charge Control C User Guide'
copyright = '2024, chargebyte GmbH'
author = 'chargebyte GmbH'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['linuxdoc.rstFlatTable', 'sphinx_copybutton']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

numfig = True

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'classic'
html_static_path = ['_static']
html_logo = '_static/cb_logo.png'
html_css_files = [
    'css/cb_theme.css',
]

# Disable link "index"
html_use_index = False

# Disable link "Show Source"
html_show_sourcelink = False

# -- Options for the linkcheck builder ---------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-the-linkcheck-builder

linkcheck_anchors = False
