[toc]



## 制作自己的github page

### 功能开发

* 中文

[中文搜索](https://lijunlin2022.github.io/docs/tool/mdbook/#中文搜索)

mdBook 生成的文档和书记，默认只支持英文搜索，其实我们只需要几个简单的配置，就可以让 mdBook 生成的 HTML 支持中文搜索。

1. 新建一个和 src 同级的文件夹 assets。
2. 将 [fzf.umd.js](https://gist.github.com/lijunlin2022/1a9d90b078422192b51392c92e3a9dba) 和 [elasticlunr.js](https://gist.github.com/lijunlin2022/1a9d90b078422192b51392c92e3a9dba) 文件放到 assets 目录下。
3. 在 book.toml 的配置中添加配置

```text
[output.html]
additional-js = ["assets/fzf.umd.js", "assets/elasticlunr.js"]
```

> [mdbook | 小霖家的混江龙 (lijunlin2022.github.io)](https://lijunlin2022.github.io/docs/tool/mdbook/)

* 自动生成目录（！！mdbook无法显示）

在markdown文件第一行，输入`[toc]`并敲击回车

### 解决异常 Trouble Shooting  

#### The link items for nested chapters must only contain a hyperlink

> 经过测试，该方法在Typora可以进行，但在mdbook中无法生成。

* 报错

```shell
2024-06-17 07:06:54 [WARN] (mdbook::book::summary): Expected a start of a link, actually got Some(Text(Borrowed("常用 always")))
Error: -17 07:06:54 [ERROR] (mdbook::utils): Error: Summary parsing failed for file="/home/runner/work/know/know/src/SUMMARY.md"
Error: -17 07:06:54 [ERROR] (mdbook::utils): Caused By: There was an error parsing the numbered chapters
Error: -17 07:06:54 [ERROR] (mdbook::utils): Caused By: There was an error parsing the numbered chapters
Error: -17 07:06:54 [ERROR] (mdbook::utils): Caused By: failed to parse SUMMARY.md line 3, column 3: The link items for nested chapters must only contain a hyperlink
Error: Process completed with exit code 101
```

* 解决

你的 `SUMMARY.md` 文件中的问题出在 "常用 always" 和 "临时 temp" 这两行。在 mdBook 中，每一行都必须包含一个链接，包括章节的标题。如果一个章节的标题没有对应的链接，你可以创建一个空的 Markdown 文件并链接到那里，或者你可以将标题和其下的第一个子章节合并。

这是一个修改后的 `SUMMARY.md` 的例子：

```markdown
# Summary

- [常用 always](./always.md)
  - [Git](always/Git.md)
- [想法 ideas](./ideas.md)
  - [EASYX](ideas/EASYX.md)
  - [To_Do_List](ideas/To_Do_List.md)
  - [cs1.6_ai图像识别自动瞄准](ideas/cs1.6_ai图像识别自动瞄准.md)
- [系统知识 learn](./learn.md)
  - [51单片机学习](learn/51单片机学习.md)
  - [MarkDown教程](learn/MarkDown教程.md)
- [临时 temp](./temp.md)
```

在这个例子中，我添加了 `always.md`、`ideas.md`、`learn.md` 和 `temp.md` 这四个链接。你需要在相应的位置创建这些文件，或者将链接改为已经存在的文件。

###  

* UTF-8

```shell
Error: -17 09:53:19 [ERROR] (mdbook::utils): Error: Unable to read "处理文件名" (/home/runner/work/know/know/src/temp/处理文件名/temp.md)
Error: -17 09:53:19 [ERROR] (mdbook::utils): 	Caused By: stream did not contain valid UTF-8
Error: Process completed with exit code 101.
```

```shell
Error: -17 09:58:45 [ERROR] (mdbook::utils): Error: Unable to read "处理文件名" (/home/runner/work/know/know/src/temp/deal-file-name/temp.md)
Error: -17 09:58:45 [ERROR] (mdbook::utils): 	Caused By: stream did not contain valid UTF-8
Error: Process completed with exit code 101.
```

```shell
Run mdbook build
Error: -17 10:03:44 [ERROR] (mdbook::utils): Error: Unable to read "deal filename" (/home/runner/work/know/know/src/temp/deal-file-name/temp.md)
Error: -17 10:03:44 [ERROR] (mdbook::utils): 	Caused By: stream did not contain valid UTF-8
Error: Process completed with exit code 101.
```

```shell
Run mdbook build
Error: -17 10:11:00 [ERROR] (mdbook::utils): Error: Unable to read "deal filename" (/home/runner/work/know/know/src/temp/deal_file_name/temp.md)
Error: -17 10:11:00 [ERROR] (mdbook::utils): 	Caused By: stream did not contain valid UTF-8
Error: Process completed with exit code 101.
```



* 解决

似乎是因为之前temp.md是我由temp.txt更改拓展名得到的，因此出现了问题。

#### Redefinition & Duplicate

```shell
Run mdbook build
Error: -19 07:11:54 [ERROR] (mdbook::utils): Error: Invalid configuration file
Error: -19 07:11:54 [ERROR] (mdbook::utils): 	Caused By: redefinition of table `output.html` for key `output.html` at line 9 column 1
Error: Process completed with exit code 101.
```

```shell
Error: -19 07:17:00 [ERROR] (mdbook::utils): Error: Invalid configuration file
Error: -19 07:17:00 [ERROR] (mdbook::utils): 	Caused By: duplicate key: `additional-js` for key `output.html` at line 7 column 1
Error: Process completed with exit code 101.
```

* 解决

因为我之前还配置了中文搜索，之后又加上了右边栏目录，所以我的book.toml出现了

```toml
[output.html]
additional-js = ["assets/fzf.umd.js", "assets/elasticlunr.js"]
[output.html]
additional-css = ["theme/pagetoc.css"]
additional-js = ["theme/pagetoc.js"]
```

仅需将上文改为下文即可

```toml
additional-js = ["assets/fzf.umd.js", "assets/elasticlunr.js","theme/pagetoc.js"]
additional-css = ["theme/pagetoc.css"]
```

> [Adding a page table of contents to mdBook | Jorel's Blog](https://blog.jorel.dev/posts/mdbook-pagetoc/)
>
> [JorelAli/mdBook-pagetoc: A page table of contents for mdBook (github.com)](https://github.com/JorelAli/mdBook-pagetoc)

### 参考
- [部署 mdbook 到 github pages (blackcloud37.github.io)](https://blackcloud37.github.io/mdbook-blog/misc/deploy-mdbook.html)
- [GitHub Pages documentation - GitHub Docs](https://docs.github.com/en/pages)
- [通过mdBook制作图书 - mdBook 中文指南 （非官方） (xihaduanzi.github.io)](https://xihaduanzi.github.io/mdBook_guide_cn/guide/creating.html)
- [jekyll - "There isn't a GitHub Pages site here." - Stack Overflow](https://stackoverflow.com/questions/46759097/there-isnt-a-github-pages-site-here)
- [mdBook/guide/src/SUMMARY.md at master · rust-lang/mdBook (github.com)](https://github.com/rust-lang/mdBook/blob/master/guide/src/SUMMARY.md?plain=1)
- [mdbook | 小霖家的混江龙 (lijunlin2022.github.io)](https://lijunlin2022.github.io/docs/tool/mdbook/)
- [Adding a page table of contents to mdBook | Jorel's Blog](https://blog.jorel.dev/posts/mdbook-pagetoc/)
- [JorelAli/mdBook-pagetoc: A page table of contents for mdBook (github.com)](https://github.com/JorelAli/mdBook-pagetoc)

