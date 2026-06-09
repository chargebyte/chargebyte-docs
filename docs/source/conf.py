# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Charge Control C User Guide'
copyright = '2025, chargebyte GmbH'
author = 'chargebyte GmbH'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['linuxdoc.rstFlatTable', 'sphinx_copybutton', 'sphinx_jinja2']

templates_path = ['_templates', '../../includes/_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

numfig = True
numfig_format = {
    'figure': 'Fig. %s:',
    'table': 'Table %s:',
    'code-block': 'Listing %s',
    'section': 'Section %s',
}

jinja2_contexts = {
  'target-info': {
    'PLATFORM_NAME': 'Charge Control C',
    'MACHINE': 'tarragon',
    'APT_CROSS_MACHINE_SPECIFIC': 'gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf binutils-arm-linux-gnueabihf',
    'MACHINE_FILE_SIGNATURE': 'ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=cf7fc6ab427435ba5e30254eb234e3dba5fad685, for GNU/Linux 3.2.0, stripped'
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
html_js_files = [
    'js/cb_theme.js',
]

# Disable link "index"
html_use_index = False

# Disable link "Show Source"
html_show_sourcelink = False

# -- Options for the linkcheck builder ---------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-the-linkcheck-builder

linkcheck_anchors = False
