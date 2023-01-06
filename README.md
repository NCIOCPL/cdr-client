# CDR Client Software

This repository contains software which runs on the users' machines,
mostly working within XMetaL, which is the commercial XML editor used
to create and modify the PDQ documents, and some within Microsoft
Word.

## CDR Loader

This script runs on the user's machine. It ensures that the CDR client
files are up to date, then launches XMetaL our own custom Python macros
enabled. To learn exactly how it does this, you can examine the
[script](XMetaL/Loader/cdr-loader.pyw), in particular the documentation
comments for the `_refresh_client_files()` method.

Instructions for installing the CDR Loader for a new user can be found
in the [Setup](XMetaL/Setup) folder.

## XMetaL CDR Macros

When XMetaL is launched for the CDR, our customized settings file
tells XMetaL to load Python macros from the file
[cdr.xml](XMetaL/Macros/cdr.xml).

These macros use the XMetaL APIs to provide an extensive range of
functionality required for the CDR work flow.

## XMetaL Formatting Rules

CSS files for controlling the display of documents being edited or
viewed in XMetaL are in the [XMetaL/Display](XMetaL/Display)
directory.

## XMetaL Rules

The [XMetaL/Rules](XMetaL/Rules) directory contains XML files with
custom rules controlling document type--specific behavior, such as
which optional child elements are included by default when a new
element block is inserted, or prompts for empty elements.

## XMetaL Templates

The [XMetaL/Template](XMetaL/Template/Cdr) directory contains XML
files controlling the default initial content for a newly created CDR
document. Each document type can have multiple templates, one for each
distinct use of that type (for example, a patient screening Summary
document will start with a different initial structure than that used
for a new prevention Summary).

## XMetaL Toolbar Icons

The [XMetaL/Icons](XMetaL/Icons) directory contains icons used for the
custom toolbars used for invoking the CDR macros.

## Client Installation Tools

The scripts used when installing CDR XMetaL for a new user are in the
[XMetaL/Setup](XMetal/Setup) directory.

## Microsoft Word Macros

The board managers run specialized QC reports (Bold/Underline and
Redline/Strikeout) in preparation for their board member meetings.
These QC reports are being imported into MS-Word and modified by using
customized Word macros.  The macros have to be setup on the users'
workstations.  The steps to setup those Word macros is listed
[here](https://cdr.cancer.gov/cgi-bin/cdr/Filter.py?DocId=CDR0000778025&Filter=name:Documentation+Help+Screens+Filter).

The macros themselves can be found in the
[MSWord/macros](MSWord/macros) directory.

The most recent version of the macros is always on the NIH network
drive at: L:\OCPL\_Cross\CDR\WordMacros\CDRMacros.bas.
