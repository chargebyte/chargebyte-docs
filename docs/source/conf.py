# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Charge Control Y User Guide'
copyright = '2025, chargebyte GmbH'
author = 'chargebyte GmbH'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['linuxdoc.rstFlatTable', 'sphinx_copybutton', 'sphinx_jinja2']

templates_path = ['_templates', '../../includes/_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

numfig = True

jinja2_contexts = {
  'target-info': {
    'PLATFORM_NAME': 'Charge Control Y',
    'MACHINE': 'parsley',
    'APT_CROSS_MACHINE_SPECIFIC': 'gcc-aarch64-linux-gnu g++-aarch64-linux-gnu binutils-aarch64-linux-gnu',
    'MACHINE_FILE_SIGNATURE': 'ELF 64-bit LSB pie executable, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, BuildID[sha1]=af8cd65df0ac1e3e6f0ed3adafcd5aec60ca8f15, for GNU/Linux 3.7.0, stripped'
  },
}

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_title = project
html_theme = 'classic'
html_static_path = ['_static', '../../includes/_static']
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
