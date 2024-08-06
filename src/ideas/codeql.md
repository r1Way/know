# codeql 使用 (C++)

## 架构

### 文件组成

```shell
.
├── cpp-database
├── incl
│   └── *.h (头文件)
├── src
│   └── *.cpp (源文件)
├── main.cpp
├── Makefile
├── query.ql
└── qlpack.yml
```

1. `Makefile`用来构建make配置
2. `query.ql`为查询包查询代码(名字可自定义)
3. `qlpack.yml`为查询包配置文件，描述了`query.ql`的依赖库，以方便后续安装依赖库。

### 使用

* 创建数据库(c++项目中)

  ```shell
  codeql database create <database> --language=cpp
  ```

  > [为 CodeQL 分析准备代码 - GitHub 文档](https://docs.github.com/zh/code-security/codeql-cli/getting-started-with-the-codeql-cli/preparing-your-code-for-codeql-analysis)

  或

  ```shell
  codeql database create <database> --language=cpp --command=make
  ```

  > [为 CodeQL 分析准备代码 - GitHub 文档](https://docs.github.com/zh/code-security/codeql-cli/getting-started-with-the-codeql-cli/preparing-your-code-for-codeql-analysis#specifying-build-commands)

* 创建配置文件`qlpack.yml`

  ```yaml
  name: my-cpp-queries
  version: 0.0.0
  libraryPathDependencies:
    - codeql-cpp
  ```
  
* 下载依赖包

  ```shell
  codeql resolve qlpacks
  ```
  
* 进行查询

  ```shell
  codeql database analyze <database name> <query> --format=csv --output=out.csv
  ```

> [使用 CodeQL 查询分析代码 - GitHub 文档](https://docs.github.com/zh/code-security/codeql-cli/getting-started-with-the-codeql-cli/analyzing-your-code-with-codeql-queries)

## 数据库

### 介绍

​	CodeQL databases contain queryable data extracted from a codebase, for a single language at a particular point in time. The database contains a full, hierarchical representation of the code, including a representation of the abstract syntax tree, the data flow graph, and the control flow graph.

> [About CodeQL — CodeQL (github.com)](https://codeql.github.com/docs/codeql-overview/about-codeql/#about-codeql-databases)

## Codeql 语法

### 结构示例

```sql
import cpp
from IfStmt ifstmt, BlockStmt block
where ifstmt.getThen() = block and
  block.getNumStmt() = 0
select ifstmt, "This 'if' statement is redundant."
```

> [CodeQL for C and C++ — CodeQL (github.com)](https://codeql.github.com/docs/codeql-language-guides/codeql-for-cpp/)
### Metadata 元数据

* 格式

  ```sql
  /**
   * @name Useless assignment to local variable
   * @description An assignment to a local variable that is not used later on, or whose value is always
   *              overwritten, has no effect.
   * @kind problem
   * @problem.severity warning
   * @id cs/useless-assignment-to-local
   * @tags maintainability
   *       external/cwe/cwe-563
   * @precision very-high
   * @security-severity 6.1
   */
  ```


> [Metadata for CodeQL queries — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/metadata-for-codeql-queries/#metadata-for-codeql-queries-1)
>
> [codeql/docs/query-metadata-style-guide.md at main · github/codeql](https://github.com/github/codeql/blob/main/docs/query-metadata-style-guide.md)
>
> [Error was: Expected result pattern(s) are not present for query kind "Problem"(INVALID_RESULT_PATTERNS) · Issue #2905 · github/codeql](https://github.com/github/codeql/issues/2905)

https://codeql.github.com/docs/writing-codeql-queries/defining-the-results-of-a-query/#adding-a-link-to-the-similar-file)



### Select 

* 在报错中插入链接

  Adding a link to the superclass

  > [Defining the results of a query — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/defining-the-results-of-a-query/#adding-a-link-to-the-superclass)

[Defining the results of a query — CodeQL (github.com)](

## Codeql参考

### Variables

* Free and bound variables

```sql
"hello".indexOf("l") = 1

min(float f | f in [-3 .. 3]) = -3

(i + 7) * 3 instanceof int

exists(float y | x.sqrt() = y)
```



> [Variables — CodeQL (github.com)](https://codeql.github.com/docs/ql-language-reference/variables/#free-and-bound-variables)

## Codeql 重要库

> [CodeQL library for C and C++ — CodeQL (github.com)](https://codeql.github.com/docs/codeql-language-guides/codeql-library-for-cpp/)
>
> [QL language reference — CodeQL (github.com)](https://codeql.github.com/docs/ql-language-reference/)

### 重要接口

### Function

* [getEnclosingElement (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/Element.qll/predicate.Element$Element$getEnclosingElement.0.html)

* [getBlock (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/Function.qll/predicate.Function$Function$getBlock.0.html)
* [calls (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/Function.qll/predicate.Function$Function$calls.1.html)
* [getACallToThisFunction (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/Function.qll/predicate.Function$Function$getACallToThisFunction.0.html)

### [BlockStmt](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/stmts/Block.qll/type.Block$BlockStmt.html)

* [getEnclosingFunction (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/stmts/Stmt.qll/predicate.Stmt$Stmt$getEnclosingFunction.0.html)

### Expr

* [getEnclosingVariable (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/exprs/Expr.qll/predicate.Expr$Expr$getEnclosingVariable.0.html)
* [getValue (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/exprs/Expr.qll/predicate.Expr$Expr$getValue.0.html)
* [getEnclosingVariable (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/exprs/Expr.qll/predicate.Expr$Expr$getEnclosingVariable.0.html)
* [hasLValueToRValueConversion (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/exprs/Expr.qll/predicate.Expr$Expr$hasLValueToRValueConversion.0.html)

### Node

* [Node (github.com)](https://codeql.github.com/codeql-standard-libraries/cpp/semmle/code/cpp/ir/dataflow/internal/DataFlowUtil.qll/type.DataFlowUtil$Node.html)

## 查询

* `conversion.ql`文件与项目在同一个文件夹时

  ```shell
  codeql database analyze cpp-database conversion.ql --format=csv --output=results.csv
  ```


> [使用 CodeQL 包自定义分析 - GitHub 文档](https://docs.github.com/zh/code-security/codeql-cli/getting-started-with-the-codeql-cli/customizing-analysis-with-codeql-packs#example-query-specifiers)

## 待看

* [Analyzing data flow in C and C++ — CodeQL (github.com)](https://codeql.github.com/docs/codeql-language-guides/analyzing-data-flow-in-cpp/#analyzing-data-flow-in-cpp)
* [Metadata for CodeQL queries — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/metadata-for-codeql-queries/)
* [About CodeQL queries — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/about-codeql-queries/)
  * **Alert queries**: queries that highlight issues in specific locations in your code.
  * **Path queries**: queries that describe the flow of information between a source and a sink in your code.
* [About data flow analysis — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/about-data-flow-analysis/#about-data-flow-analysis-1)
  *  These queries help you understand if data is used in an insecure way, whether dangerous arguments are passed to functions, or whether sensitive data can leak.


## Trouble Shooting 报错 

### Expected result pattern(s) 

* 问题描述  
  ```shell
  A fatal error occurred: Could not process query metadata for /home/riway/Documents/test2/conversion.ql.
  Error was: Expected result pattern(s) are not present for problem query: Expected alternating entity/string and string columns. [INVALID_RESULT_PATTERNS]
  ```

* 解决 

  最后加上--rerun
  
  ```shell
  codeql database analyze cpp-database conversion.ql --format=csv --output=results.csv --rerun
  ```
  

> [Expected alternating entity/string and string columns. [INVALID_RESULT_PATTERNS\] · Issue #6482 · github/codeql](https://github.com/github/codeql/issues/6482)
>
> [Error was: Expected result pattern(s) are not present for query kind "Problem"(INVALID_RESULT_PATTERNS) · Issue #2905 · github/codeql](https://github.com/github/codeql/issues/2905)

###  To be finalized before running queries

* 问题描述

  ```shell
  A fatal error occurred: Database at G:\research\data_race\CodeQL_test\rely\cpp-database needs to be finalized before running queries; please run codeql database finalize
  ```

* 解决

  ```shell
  codeql database create <database> --language=cpp --command=make
  ```

### A fatal error occurred: Exit status 1 from command

* 问题描述

  ```shell
  [2024-07-12 15:58:40] [build-stdout] CodeQL C++ autobuilder
  [2024-07-12 15:58:40] [build-stdout] Working directory: G:\research\data_race\CodeQL_test
  [2024-07-12 15:58:40] [build-stdout] Attempting to locate build script
  [2024-07-12 15:58:40] [build-stderr] Error: Could not auto-detect a suitable build method
  [2024-07-12 15:58:40] [ERROR] Spawned process exited abnormally (code 1; tried to run: [G:\research\data_race\codeql_app\codeql\tools\win64\tracer.exe, G:\research\data_race\codeql_app\codeql\tools\win64\runner.exe, cmd.exe, /C, type, NUL, &&, G:\research\data_race\codeql_app\codeql\cpp\tools\autobuild.cmd])
  A fatal error occurred: Exit status 1 from command: [G:\research\data_race\codeql_app\codeql\tools\win64\runner.exe, cmd.exe, /C, type, NUL, &&, G:\research\data_race\codeql_app\codeql\cpp\tools\autobuild.cmd]
  ```

* 解决

  切换到Makefile所在文件夹

  ```shell
  codeql database create cpp-database --language=cpp --command=make
  ```

  

## 示例

### 报告模板

查询名称|查询描述 |问题等级 |说明 |文件位置 |起始行号 |起始列号 |结束行号 |结束列号 
--|--|--|--|--|--|--|--|--
"Find enclosing function"|"A ql to find enclosing function." |"recommendation" |"(global namespace)main call ::test1" |"/main.cpp" |“31” |“5” |“31” |“8” 

### enFunc1

* 代码

```sql
/**
 * @name Find enclosing function
 * @description A ql to find enclosing function.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/enFunc
 */

import cpp

from Function f1,Function f2
where f1.calls(f2)
select f1,f1.toString()+" call "+f2.toString() 
```

* 报告

```shell
"Find enclosing function","A ql to find enclosing function.","recommendation","main call test1","/main.cpp","31","5","31","8"
```

### enFunc2

* 代码

```sql
/**
 * @name Find enclosing function
 * @description A ql to find enclosing function.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/enFunc
 */

 import cpp

 from Function f1,Function f2
 where f1.calls(f2)
 select f1,f1.getNamespace().toString()+f1.toString()+" call "+f2.getNamespace().getName()+"::"+f2.toString() 
```

* 报告

```shell
"Find enclosing function","A ql to find enclosing function.","recommendation","(global namespace)main call ::test1","/main.cpp","31","5","31","8"
```

### enFunc3

* 代码

```sql
/**
 * @name Find enclosing function
 * @description A ql to find enclosing function.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/enFunc
 */

 import cpp

 from Function f1,Function f2
 where f1.calls(f2) and f1.getName()="test1"
 select f1,f1.getNamespace().getName()+f1.getName()+" call "+f2.getNamespace().getName()+"::"+f2.toString() 
```

* 结果

```shell
"Find enclosing function","A ql to find enclosing function.","recommendation","test1 call std::operator<<
test1 call ::test2","/main.cpp","8","5","8","9"
```

### enVar1

* 代码

```sql
/**
 * @name Find enclosing variate 
 * @description A ql to find enclosing variate.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/enVar
 */

 import cpp

 from Function f, Variable v
 where f.accesses(v)
 select f,f.getNamespace().getName()+"::"+f.toString()+" calls "+v.getNamespace().getName()+"::"+v.toString() 
 
```

### enVar2

* 代码

```sql
/**
 * @name Find enclosing variate 
 * @description A ql to find enclosing variate.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/enVar
 */

 import cpp

 from Function f, LocalVariable v
 where  v.getFunction()=f
 select f,f.getNamespace().getName()+"::"+f.toString()+" calls "+v.getNamespace().getName()+"::"+v.toString() 
```

* 报告

```shell
"Find enclosing variate","A ql to find enclosing variate.","recommendation","::test1 calls ::num1","/main.cpp","8","5","8","9"
```

### flow1

* 代码

```sql
/**
 * @name Data flow
 * @description A ql to trace dataflow
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/flow
 */

 import cpp
 import semmle.code.cpp.dataflow.new.DataFlow

 from DataFlow::Node nodeFrom, DataFlow::Node nodeTo,Parameter source,Parameter sink
 where nodeFrom.asParameter() = source and
 nodeTo.asParameter() = sink and
 DataFlow::localFlow(nodeFrom, nodeTo)
 select nodeFrom,"from "+nodeFrom.toString()+" to "+nodeTo.toString()+" source: "+source.toString()+
 " sink : "+sink.toString()
```

#### 源文件1

```c++
#include<iostream>
using namespace std;

int test1(int a);
int test2(int b);

int test1(int a)
{
    cout<<"this is test 1\n";
    cout<<"a: "<<a<<endl;
    int num1=1;
    test2(a);
    return 0;
}

int test2(int b)
{
    cout<<"this is test 2\n";
    cout<<"b: "<<b<<endl;   
    return b;
}


int main()
{
    int num=1;
    test1(num);
    return 0;
}
```

* 结果1

```shell
"Data flow","A ql to trace dataflow","recommendation","from b to b source: b sink : b","/main.cpp","16","15","16","15"
```

#### 源文件2

```c++
#include<iostream>
using namespace std;

int test1(int &a);
int test2(int &b);

int test1(int &a)
{
    cout<<"this is test 1\n";
    cout<<"a: "<<a<<endl;
    int num1=1;
    test2(a);
    return 0;
}

int test2(int &b)
{
    cout<<"this is test 2\n";
    cout<<"b: "<<b<<endl;   
    return b;
}


int main()
{
    int num=1;
    test1(num);
    return 0;
}
```

* 结果

```shell
"Data flow","A ql to trace dataflow","recommendation","from *b to *b source: b sink : b","/main.cpp","16","16","16","16"
```

* 结论

`DataFlow::Node`能识别出地址传递还是值传递



### rely

* 代码

```sql
/**
 * @name Find expr
 * @description A ql to find expr.
 * @kind problem 
 * @problem.severity recommendation
 * @id cpp/rely
 */

import cpp

from Expr e
select e,e.toString() 
```

* 报告

```shell
"Find expr","A ql to find expr.","recommendation","call to test1","/main.cpp","27","5","27","9"
```



### Expr

```shell
"Data flow","A ql to trace dataflow","recommendation","Expr: num","/main.cpp","27","11","27","13"
"Data flow","A ql to trace dataflow","recommendation","Expr: cout","/main.cpp","18","5","18","8"
"Data flow","A ql to trace dataflow","recommendation","Expr: this is test 2
","/main.cpp","18","11","18","28"
"Data flow","A ql to trace dataflow","recommendation","Expr: endl","/main.cpp","19","21","19","24"
"Data flow","A ql to trace dataflow","recommendation","Expr: call to operator<<","/main.cpp","19","16","19","20"
"Data flow","A ql to trace dataflow","recommendation","Expr: b","/main.cpp","19","18","19","18"
"Data flow","A ql to trace dataflow","recommendation","Expr: call to operator<<","/main.cpp","19","9","19","17"
"Data flow","A ql to trace dataflow","recommendation","Expr: cout","/main.cpp","19","5","19","8"
"Data flow","A ql to trace dataflow","recommendation","Expr: b: ","/main.cpp","19","11","19","15"
"Data flow","A ql to trace dataflow","recommendation","Expr: cout","/main.cpp","9","5","9","8"
"Data flow","A ql to trace dataflow","recommendation","Expr: this is test 1
","/main.cpp","9","11","9","28"
"Data flow","A ql to trace dataflow","recommendation","Expr: endl","/main.cpp","10","21","10","24"
"Data flow","A ql to trace dataflow","recommendation","Expr: call to operator<<","/main.cpp","10","16","10","20"
"Data flow","A ql to trace dataflow","recommendation","Expr: a","/main.cpp","10","18","10","18"
"Data flow","A ql to trace dataflow","recommendation","Expr: call to operator<<","/main.cpp","10","9","10","17"
"Data flow","A ql to trace dataflow","recommendation","Expr: cout","/main.cpp","10","5","10","8"
"Data flow","A ql to trace dataflow","recommendation","Expr: a: ","/main.cpp","10","11","10","15"
"Data flow","A ql to trace dataflow","recommendation","Expr: a","/main.cpp","12","11","12","11"
"Data flow","A ql to trace dataflow","recommendation","Expr: b","/main.cpp","20","12","20","12"
"Data flow","A ql to trace dataflow","recommendation","Expr: 1","/main.cpp","26","13","26","13"
"Data flow","A ql to trace dataflow","recommendation","Expr: 0","/main.cpp","28","12","28","12"
"Data flow","A ql to trace dataflow","recommendation","Expr: 1","/main.cpp","11","14","11","14"
"Data flow","A ql to trace dataflow","recommendation","Expr: 0","/main.cpp","13","12","13","12"
```

