# ft_readline
How to use it:
```
int   main(void)
{
    t_rl_reader    *r;
    char            *line;
    
    r = ftrl_init();
    ftrl_init_history(r, "my_hist_file");
    line = ft_readline(r, "$> ");
    //use line
    free(line);
    ftrl_exit(r);
    return (0);
}
```
