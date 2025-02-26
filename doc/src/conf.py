# -*- coding: utf-8 -*-

import os


# -- Project information -----------------------------------------------------

project = 'newtype'
copyright = '2023, Felix Morgner'
author = 'Felix Morgner'
version = '2.0'
release = '2.0.0'


# -- General configuration ---------------------------------------------------

master_doc = 'index'

extensions = [
    'sphinx.ext.todo',
    'sphinx.ext.githubpages',
]

highlight_language = 'c++'

pygments_style = 'tango'

exclude_patterns = []

numfig = True

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