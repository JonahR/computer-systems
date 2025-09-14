// Code segment for problem

if (Fork() == 0) { /* Child */
  /* What code is the shell executing right here? */
  Dup2(0, 3);
  Execve("fstatcheck", argv, envp);
}
