#include <stdio.h>
#include <unistd.h>
  // create a pipe for associating "ls" with "sort"
  
  	// Redirect stdout to the input of the pipe and
  	// close unneeded file descriptors
  	dup2(fd[1],fileno(stdout));	// redirect stdout
    
    // Become "ls"
    // Redirect stdout to the exit of the pipe and
    // close unneeded file descriptors
    dup2(fd[0],fileno(stdin));		// redirect stdin
    
    // Become "sort"