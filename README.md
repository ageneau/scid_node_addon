# Overview
SCID is an open application to view, edit, and manage collections of chess games.

SCID's low level functions are written in C++ and its graphical interface is in Tcl/Tk.
This node addon is a binding to the C++ layer of SCID.

Installation
------------
``` bash
$ npm install scid
```

# CAVEAT

The API is currently the same as the Tcl API and is quite low level.

# API Reference

You can look in test/test.js for some basic usage. The API is identical to the Tcl one so the best reference is probably the various Tcl files in the SCID source code.

# See Also
- [http://scid.sourceforge.net/](http://scid.sourceforge.net/)
