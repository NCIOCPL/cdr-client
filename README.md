# CDR Client Software

This repository contains software which runs on the users' machines,
mostly working within XMetaL, which is the commercial XML editor used
to create and modify the PDQ documents, and some within Microsoft
Word.

## CDR Loader

This program runs on the user's machine. It ensures that the CDR
client files are up to date, then launches XMetaL with the custom CDR
DLL (see below). To learn exactly how it does this, you can read the
extensive in-code documentation, especially in
[CdrClient.cpp](XMetaL/CdrClient/CdrClient.cpp) and
[CdrClient.h](XMetaL/CdrClient/CdrClient.h).

Scripts for building and installing the program (and optionally other
parts of the CDR) are in the
[cdr-tools](https://github.com/NCIOCPL/cdr-tools/tree/master/Build)
repository.

Instructions for installing the CDR Loader for a new user can be found
in the [CDR online
documentation](https://cdr.cancer.gov/cgi-bin/cdr/Filter.py?DocId=CDR0000000263&Filter=name:Documentation+Help+Screens+Filter)
(see the section titled Installing CDR Loader).

## XMetaL CDR Macros

When XMetaL is launched for the CDR, our customized settings file
tells XMetaL to load JavaScript macros from the file
[Macros/Cdr.mcr](https://github.com/NCIOCPL/cdr-client/blob/master/XMetaL/Macros/Cdr.mcr).

These macros use the XMetaL APIs as well as custom functionality
implement in the CDR DLL (see below) to provide an extensive range of
functionality required for the CDR work flow. Deployment of updates to
the macros are handled by the scripts found in the
[cdr-tools](https://github.com/NCIOCPL/cdr-tools/tree/master/Build)
repository.

## CDR DLL

Client functionality needed by CDR XMetaL users which is not provided
by the stock XMetaL program, and which cannot be implemented by using
the XMetaL APIs, is handled by a custom DLL which is loaded by the
JavaScript macros described above when XMetaL is launched. An example
of such functionality is communication with the CDR Tunneling
Server. The DLL is implemented using C++ and MFC, and the source code
is located in the [XMetaL/DLL](XMetaL/DLL) directory.

Building and deployment of the DLL is handled by scripts in the
[cdr-tools](https://github.com/NCIOCPL/cdr-tools/tree/master/Build)
repository.

## XMetaL Formatting Rules

CSS files for controlling the display of documents being edited or
viewed in XMetaL are in the [XMetaL/Display](XMetaL/Display)
directory.

## XMetaL Proprietary Forms

The [XMetaL/Forms](XMetaL/Forms/CDR) directory contains two binary
compiled forms creating using tools which the XMetaL vendor no longer
supports. The forms still work, however, and at least one of them is
still used, so unless and until their functionality is replaced, these
must be retained.

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

The custom executable programs used when installing CDR XMetaL for a
new user are in the [XMetaL/Tools](XMetal/Tools) directory.

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
drive at: L:\\OCPL\_Cross\CDR\WordMacros\CDRMacros.bas.
