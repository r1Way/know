## 制作自己的github page

### Trouble Shooting 

#### The link items for nested chapters must only contain a hyperlink

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

### 参考
- [部署 mdbook 到 github pages (blackcloud37.github.io)](https://blackcloud37.github.io/mdbook-blog/misc/deploy-mdbook.html)
- [GitHub Pages documentation - GitHub Docs](https://docs.github.com/en/pages)
- [通过mdBook制作图书 - mdBook 中文指南 （非官方） (xihaduanzi.github.io)](https://xihaduanzi.github.io/mdBook_guide_cn/guide/creating.html)
- [jekyll - "There isn't a GitHub Pages site here." - Stack Overflow](https://stackoverflow.com/questions/46759097/there-isnt-a-github-pages-site-here)
- [mdBook/guide/src/SUMMARY.md at master · rust-lang/mdBook (github.com)](https://github.com/rust-lang/mdBook/blob/master/guide/src/SUMMARY.md?plain=1)

