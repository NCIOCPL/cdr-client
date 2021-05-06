# Creating/Modifying the Rules Files used by XMetaL
## Rules Files - Overview

The rules files (*.ctm files) are mini-templates for XMetaL to add blocks of elements to the document.

You can control the behavior of XMetaL based on the element that the user is working within by creating and modifying the CTM file that accompanies your customization. This file is an XML document that contains settings for each element in your customization's DTD or Schema.

## Creating a new CTM File

To greatly simplify the creation of a CTM file, start XMetaL Author and open a document based on your DTD or Schema. XMetaL Author creates the CTM file for you! At this point you can modify the values in the CTM file to suit your customization by copying the file from the

```
  C:\Users\<username>\AppData\Roaming\SoftQuad\XMetaL\9.0\Rules
```

folder to your git repository working folder

```
  /h/git/cdr-client/XMetaL/Rules
```

Open the new `<doctype>.ctm` file and ensure that the following option is included. If it's not part of the rules you need to add it. **Every `<doctype>.ctm` file must include this option**:

```
  <GlobalPrettyPrintOptions>
   <NoPrettyPrinting/>
  </GlobalPrettyPrintOptions>
```
Without the above option a serialized document may not preserve whitespace within elements which can result in validation failures.

### Previewing the Rules changes
After making all of the necessary changes to the CTM Rules file, copy the new `<doctype>.ctm` file from your working directory back to the XMetaL Rules directory:

```
  H:> copy <doctype>.ctm /y ...\SoftQuad\XMetaL 9.0\Rules
```

Once the CTM file has been copied, start XMetaL for the rules and template files to be reloaded. These files only get loaded once per session when the program is started.

### Moving Changes to the Server
When everything has been updated and looks good you'll have to copy the changes to the development server for CIAT to review. Once you have copied the files you must run the manifestmaker or nobody will be able to start XMetaL until it did run. Log on to the DEV server to submit the appropriate commands.

### Modifying an Existing CTM File

Open up your CTM file and observe its structure. Also open the ctm.dtd file to observe the elements and their attributes. Each element in this CTM file corresponds to a property you can set for each element in your DTD or Schema. The CTM and DTD files are generally located in the same directory - the Rules directory.

When defining a CTM file for your customization, you must add elements for each customization property you want to take advantage of as well-formed and valid XML.

For additional information see the CDR documentation on [Creating/Modifying the Rules Files used by XMetaL](https://cdr.cancer.gov/cgi-bin/cdr/Filter.py?DocId=CDR0000454921&Filter=name:Documentation+Help+Screens+Filter)