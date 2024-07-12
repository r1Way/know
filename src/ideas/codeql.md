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

## Metadata 元数据

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

### select 语法

* 在报错中插入链接

  Adding a link to the superclass
  
  > [Defining the results of a query — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/defining-the-results-of-a-query/#adding-a-link-to-the-superclass)

[Defining the results of a query — CodeQL (github.com)](https://codeql.github.com/docs/writing-codeql-queries/defining-the-results-of-a-query/#adding-a-link-to-the-similar-file)

## Codeql 语法

### 结构

```sql
import cpp
from IfStmt ifstmt, BlockStmt block
where ifstmt.getThen() = block and
  block.getNumStmt() = 0
select ifstmt, "This 'if' statement is redundant."
```

> [CodeQL for C and C++ — CodeQL (github.com)](https://codeql.github.com/docs/codeql-language-guides/codeql-for-cpp/)

## Codeql 重要库

> [CodeQL library for C and C++ — CodeQL (github.com)](https://codeql.github.com/docs/codeql-language-guides/codeql-library-for-cpp/)

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

### Expected result pattern(s) are not present for problem query

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
