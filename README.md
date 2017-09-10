# Building

For best results (and least irritation), create a directory or folder with a
name of your choosing, and clone this repository in that directory.  The
following command made in your new directory will build, among other things,
the two binaries of interest, <tt>printAllIsoPoz3</tt> and
<tt>printAllIsoPozDyck3</tt>.  (Note, '$' is the shell prompt.) 

<tt>$ make</tt>

To clean up the object files involved in building these binaries, do this.

<tt>$ make clean</tt>

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

[1] Coxeter, Harold Scott MacDonald (1973). <i>Regular Polytopes</i>. Courier Corporation.

[2] Crona, Gavrushkin, Greene, Beerenwinkel. title. <i>Elife</i>. to appear
