## matlab利用最优化解决非线性微分方程

### 使用一次

```matlab
x = optimvar('x');
y = optimvar('y');
x0=struct();
prob = optimproblem("Objective",peaks(x,y));

prob.Constraints.cons1 = x^2 + y^2 == 4;
prob.Constraints.cons2 = x^2 - y^2 == 0;
prob.Constraints.cons3 = x>=0;
prob.Constraints.cons4 = y>=0;
x0.x = 1;
x0.y = -1;
sol = solve(prob,x0)
```

> 约束不支持

### 当需要进行迭代时

```matlab
x = optimvar('x');
y = optimvar('y');
x0=struct();
prob = optimproblem("Objective",peaks(x,y));

prob.Constraints.cons1 = x^2 + y^2 == 4;
prob.Constraints.cons2 = x^2 - y^2 == 0;
prob.Constraints.cons3 = x>=0;
prob.Constraints.cons4 = y>=0;
x0.x = 1;
x0.y = 0;
sol = solve(prob,x0)

%允许的
prob = optimproblem("Objective",peaks(x,y));
prob.Constraints.cons1 = x^2 + y^2 == 2;
prob.Constraints.cons2 = x^2 - y^2 == 0;
prob.Constraints.cons3 = x>=0;
prob.Constraints.cons4 = y>=0;
x0.x = 1;
x0.y = 0;
sol = solve(prob,x0)
```



### 参考

* [基于问题的有约束的非线性方程组 - MATLAB & Simulink - MathWorks 中国](https://ww2.mathworks.cn/help/optim/ug/systems-of-equations-with-constraints-problem-based.html#NonlinearSystemsOfEquationsWithConstraintsProblemBasedExample-1)
* [求解优化问题或方程问题 - MATLAB solve - MathWorks 中国](https://ww2.mathworks.cn/help/optim/ug/optim.problemdef.optimizationproblem.solve.html?s_tid=doc_ta#mw_0da39407-9136-4f31-8f99-3ecb2857cddb)
* [求解优化问题或方程问题 - MATLAB solve - MathWorks 中国](https://ww2.mathworks.cn/help/optim/ug/optim.problemdef.optimizationproblem.solve.html?s_tid=doc_ta)