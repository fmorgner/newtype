# -*- coding: utf-8 -*-

import os


# -- Project information -----------------------------------------------------

project = 'newtype'
copyright = '2019, Felix Morgner'
author = 'Felix Morgner'
version = '1.0'
release = '1.0.0'


# -- General configuration ---------------------------------------------------

master_doc = 'new_type'

extensions = [
    'sphinx.ext.todo',
    'sphinx.ext.githubpages',
]

highlight_language = 'c++'

pygments_style = 'tango'

exclude_patterns = []

# -- Options for HTML output -------------------------------------------------

html_theme = 'haiku'
html_theme_options = {
}

# -- Options for manual page output -------------------------------------------------

man_pages = [
    (
        "index",
        "newtype",
        "A library of types and functions to create strong type aliases",
        ["Felix Morgner <felix.morgner@gmail.com>"],
        3,
    ),
]