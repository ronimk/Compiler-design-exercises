The GCodeParser ios a part of a Metropolia fall 2020 project, to build a framework for a plotter machine:
<br>
![Plotter project diagram](ProjectDiagram.png)
<br>
The framework itself consists of the parser, a "Gcode pipe" through which the Gcodes are given and an interface to manipulate the framework:
<br>
![Framework diagram](FrameworkDiagram.png)
<br>
<br>
I was mostly responsible for creating the parser. I also co created the GcodePipe class hierarcy with my teammates.
<br>
The parser itself was designed in the spirit of the "Compilers"-book by Aho et al. Following the first two chapters of the book, a context free grammar was created for helping in the design process of the parser to parse the required subset of Gcodes (can be found at "CFG for Gcode.pdf"). The parser logic followed the designed CFG and the "Predictive Parsing" section (2.4.2) of the book.
