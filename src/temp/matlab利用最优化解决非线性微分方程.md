## matlab利用最优化解决非线性微分方程

```matlab
x = optimvar('x');
y = optimvar('y');

prob = optimproblem("Objective",peaks(x,y));

prob.Constraints.cons1 =x+y==2;
prob.Constraints.cons4 =x-y==0;
x0.x = 1;
x0.y = -1;
sol = solve(prob,x0)

```

