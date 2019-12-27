# fsm2dot

Usage: fsm2dot <state_variable> <sourcefile.c>

The purpose of this program is to represent a finite state machine (FSM) in a C language program graphically using the GraphViz program.

https://www.graphviz.org/

It is a command line program which searches for the FSM in "switch()" statement in the provided C language file.  Each case in the switch is assumed to be a state.  Each state transition is expected to be in the form of "state_variable = newstate" inside each case.

The GraphViz 'dot', 'fdp', and 'sfdp' layout engines seem to work best for finite state machines.  It may be necessary to adjust the order of the statements inside the GraphViz file, or alternatively inside the switch() statement, to create a clean graph.

This software was written with CodeBlocks but any command line C compiler should be fine.  

http://www.codeblocks.org/

# Planned Enhancements

* Add command line options to suppress specific states.
* Add code to support state transition labels extracted from the C file comments.


# MIT License

Copyright 2020

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

