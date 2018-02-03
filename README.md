# Building

For best results (and least irritation), create a directory or folder with a
name of your choosing, and clone this repository in that directory.  The
following command made in your new directory will build, among other things,
the two binaries of interest, <tt>printAllIsoPoz3</tt> and
<tt>printAllIsoPozDyck3</tt>.  (Note, '$' is the shell prompt.) 

<tt>$ make</tt>

To clean up the object files involved in building these binaries, do this.

<tt>$ make clean</tt>

(NOTE:  I have made no effort to make this code "multi-platform".  I wrote C code which compiles and runs
on my GNU/Linux system, and that's it.)

# What This Software Computes

Consider the set of cube-shaped directed graphs, with nodes at the vertices and
arrows at the edges.  We say that a graph is <i>acyclic</i> if there is no path
of non-zero length along the edges which respects the direction of the arrows
and returns to the starting point of the path.  We say that two graphs are
isomorphic if one can be transformed to the other via a cube isometry
[1].  To output a complete list of acyclic directed graphs, with
only one member from each isomorphism class, enter the following command in a
shell. 

<tt>$ ./printAllIsoPoz3</tt>

To restrict the list to those graphs which satisfy the condition described in
[2], enter the following

<tt>$ ./printAllIsoPozDyck3</tt>

Please read the comments in <tt>main.c</tt> for an explanation of the encoding of these graphs.

A similar analysis is partially carried out for the four dimensional cube in [3].

[1] Coxeter, Harold Scott MacDonald (1973). <i>Regular Polytopes</i>. Courier Corporation.

[2] Kristina Crona, Alex Gavryushkin, Devin Greene, Niko Beerenwinkel (2018) Inferring genetic interactions from comparative fitness data.  eLife 2017;6:e28629 doi: 10.7554/eLife.28629 

[3] https://github.com/devingreene/4-cube-partial-order-count.git
