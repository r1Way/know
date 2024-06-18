[toc]

## Git

### 创建仓库

`git init repo_nmae`

### 切换目录

* `cd directory`

* `cd ..`返回上一级

* `cd .本级`

### 删除目录

`\rm -rf directory`

### 创建文件夹

`mkdir temp`

### 复制文件夹

`cp -rf  原文件名 复制后的文件名`

复制时会把版本号等都复制过去

### 文件

#### 写入

`echo 111 > file1.txt`

`echo 111 >temp/file2.txt` (temp是一个文件夹)

#### 显示

`cat file1.txt`

#### 修改

`vi file1.txt`

>  退出编辑模式`:wq`

#### 删除

`\rm -rf file1.txt`

#### 重命名

`mv old_folder_name new_folder_name`

### 查看所有文件

* `ls`

* `ls -a`包含隐藏

* `ls -ltr` 按照时间显示

* `git ls-files`查看暂存区文件

### 工作区->暂存区

`git add file1.txt`

`git add *.txt`

`git add .` 提交所有

### 缓存区->仓库区

`git commit file1.txt -m "first commit "`

`git commit -am "    "` 同时完成add 和commit（前提是该文件不是新建的）

### 查看提交记录

* `git log`
* `git log --oneline`

> 可按wq退出

### 回退版本

`git reset --soft/hard/mixed 版本号` 

> soft 保留工作区、暂存区
>
> hard 均不保留
>
> mixed 保留工作区，不保留暂存区
>

返回上一版本用 HEAD^

返回错了，可用`git reflog`查看

### 查看版本区别

* 基本

`git diff`工作区与暂存区

`git diff HEAD`工作区（及暂存区）与仓库区

`git diff --cached`暂存区与仓库区

* 扩展

`git diff version1  version2 ` 比较两个版本（版本2=版本1  --  ++)

`git diff version1 HEAD`（HEAD代表最新提交结点）

 `git diff version1 HEAD^`与 `git diff version1 HEAD~`为与上一个版本进行比较

`git diff HEAD~2  HEAD` HEAD与HEAD前2个版本进行比较

`git diff HEAD~3 HEAD file3.txt` 仅比较 file3.txt

### 删除文件

* 方法一

  `rm file1.txt`加`git add .`

* 方法二

  `git rm <file>` 将文件从工作区和暂存区删除

  `git rm --cached <file>` 将文件仅从暂存区删除

方法一与方法二用完后，都要记得`git commit -m ""`

* 方法三 删除文件夹

  `git rm -r --cached <directory_name>`

  然后commit，然后再push，这样远程仓库的文件夹就会被删除，但是本地的保留

### 忽略文件

* 忽略某个文件

`echo  <file> >> .gitignore`或者`vi .gitignore`

* 忽略某个后缀的文件

`echo *.txt >> .gitignore`

* 忽略某个文件夹

`echo  "temp/" >> .gitignore`

> 无法忽略已经提交过的文件

### 克隆

`git clone <SSH>` 

### 拉取更新（远程到本地）

`git pull <SSH>`

`git pull <远程库别名> <远程branch>:<本地branch>`

### 推送更新（本地到远程）

`git push <remote库><本地branch>:<远程branch>`

### 关联本地仓库和远程仓库

* 添加远程仓库

`git remote add <远程仓库别名> <远程仓库地址>` （别名多为origin）

把本地main与远程main 关联

`git push -u origin <本地分支名>:<远程分支名>`（-u指upstream， 若本地与远程名称相同，可省略冒号以后内容）

* 查看别名及地址

`git remote -v`

* 拉取远程仓库内容

`git pull <远程仓库r名> <远程分支名> :<本地分支名>` 

`git pull`默认将origin 的main与本地main合并

> 如果出问题了，就用`git branch -m main`将本地分支改个名

> 检查本地仓库是否是空的，或者有冲突的，然后就可以`git push -m origin main`

* 有冲突时（远程有本地没有的文件）报错

  ```shell
   ! [rejected]        main -> main (fetch first)
  error: failed to push some refs to 'github.com:r1Way/remote-repo.git'
  hint: Updates were rejected because the remote contains work that you do not
  hint: have locally. This is usually caused by another repository pushing to
  hint: the same ref. If you want to integrate the remote changes, use
  hint: 'git pull' before pushing again.
  hint: See the 'Note about fast-forwards' in 'git push --help' for details.
  ```

* 最佳实践

  关联仓库时，本地先别提交，先拉取README.md，再push

* 删除远程库

`git remote rm <remote_name>`

### 分支

* 创建分支

`git branch <branch name>`

> 别忘记提交

* 查看分支

`git branch`

* 切换分支

`git switch <branch name>`

>  `git checkout <branch name>` (不好有歧义)
>
> 不同分支的文件内容在同一文件下，但用`ls`只能看到当前分支的内容（新分支会包含旧分支的文件）

* 合并分支

`git merge <branch name>`将该branch合并到本branch下，默认让我们进行一次提交

* 查看分支图

`git log --graph --oneline --decorate --all`

> 当main也有新的commit后，才容易看到合并的图像
>
> 分支被合并后不会消失

* 删除本地分支

若已经合并

`git branch -d <branch name>`

若未合并

`git branch -D <branch name>`

* 删除远程分支

  `git push origin --delete [branch_name]`

![image-20240605171148497](C:\Users\刘星池\AppData\Roaming\Typora\typora-user-images\image-20240605171148497.png)

```shell
刘星池@river-away MINGW64 ~/learn-git/branch-demo (main)
$ git log --graph --oneline --decorate --all
*   b334c02 (HEAD -> main) gerge branch 'other' merge the branch other
|\
| * f0db2b0 (other) commit other1.txt
* | fc0e809 commit main4.txt
|/
* 3618250 commit from branch dev
* 6dae08c first commit

刘星池@river-away MINGW64 ~/learn-git/branch-demo (main)
$ git log --oneline
b334c02 (HEAD -> main) gerge branch 'other' merge the branch other
fc0e809 commit main4.txt
f0db2b0 (other) commit other1.txt
3618250 commit from branch dev
6dae08c first commit

```

### 解决合并冲突

* 查看冲突文件

`git status`

* 查看冲突内容

`git diff`

此时冲突文件中会将两冲突同时显示在文件内

![image-20240606192123054](C:\Users\刘星池\AppData\Roaming\Typora\typora-user-images\image-20240606192123054.png)

等号上方为当前branch（主干），下方为被合并的branch（侧枝）。

把左箭头，右箭头等号都去掉。然后保存后提交

* 终止合并

`git merge --abort`

### 回退和rebase

`git rebase main`将本分支到公共结点的提交记录变基到另一条分支上

`git checkout -b dev <版本号>` 恢复被删除的分支

> `alias graph="git log --oneline --graph --decorate --all"` 来简化我们的命令

### 规范

* 版本号规则

`git tab` 标记版本号

![image-20240607124122985](C:\Users\刘星池\AppData\Roaming\Typora\typora-user-images\image-20240607124122985.png)

### 更改Git起始目录

http://t.csdnimg.cn/BhONz

原为:

目标F:\Git\Git\git-bash.exe --cd-to-home

起始位置%HOMEDRIVE%%HOMEPATH%

改为F:\Git\Git\git-bash.exe 

起始位置G:\inspire\simulator

> 注意是右斜线（反斜杠\)

## Vim

* 按到ctrl+c退出时

>  shell输入fg

* set number! 显示行号
* split水平线分割，vsplit竖直线分割

## Trouble Shooting

* 打开`git log --oneline`后，无法退出

  * 按q

* git pull后因为conflict跟本地分支merge了

  * vi 修改冲突后，add commit，后main|MERGING就消失了

  * ```shell
    刘星池@river-away MINGW64 /g/know/src (main)
    $ git pull
    Auto-merging src/SUMMARY.md
    CONFLICT (content): Merge conflict in src/SUMMARY.md
    Automatic merge failed; fix conflicts and then commit the result.
    
    刘星池@river-away MINGW64 /g/know/src (main|MERGING)
    $ vi SUMMARY.md
    
    刘星池@river-away MINGW64 /g/know/src (main|MERGING)
    $ git add .
    
    刘星池@river-away MINGW64 /g/know/src (main|MERGING)
    $ git commit -m"deal merge"
    [main 66f29ba] deal merge
    
    刘星池@river-away MINGW64 /g/know/src (main)
    $ git push
    
    ```
