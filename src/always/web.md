## Web 开发

> [MDN Web Docs](https://developer.mozilla.org/zh-CN/)

## 上线网站

> [【合集完结】想上线网站？通俗易懂的网站上线部署发布教程 | 个人网站如何托管建站 | 服务器 IP DNS CDN 备案 工作原理 | 腾讯云开发静态网站托管](https://www.bilibili.com/video/BV18a4y1Y7e9?p=6&vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### 域名

>  [域名注册购买_域名注册选购 - 腾讯云](https://buy.cloud.tencent.com/domain)
>
>  [域名注册 单个域名注册-注册新域名-文档中心-腾讯云](https://cloud.tencent.com/document/product/242/9595)
>
>  [ICP 备案 如何快速备案您的网站或 APP-快速入门-文档中心-腾讯云](https://cloud.tencent.com/document/product/243/39038)
>
>  [我的备案 - ICP备案 - 控制台](https://console.cloud.tencent.com/beian/manage/material)
>
>  [轻量应用服务器 安装和配置宝塔 Linux 面板腾讯云专享版-实践教程-文档中心-腾讯云](https://cloud.tencent.com/document/product/1207/54078)

### 服务器



## 其它

> [学生云服务器_学生云主机_学生云数据库_云+校园特惠套餐 - 腾讯云](https://cloud.tencent.com/act/campus?fromSource=gwzcw.8476543.8476543.8476543&utm_medium=cpc&utm_id=gwzcw.8476543.8476543.8476543&msclkid=ef5d14ca39621e0f4f4373ab0078c3a7)

* 在线环境

  > [HTML/CSS/JS 在线工具 | 菜鸟工具](https://www.jyshare.com/front-end/61/)

* 手册

> [MDN Web Docs](https://developer.mozilla.org/zh-CN/)

* 课程
> [全网首发AI+JavaWeb开发入门，Tlias教学管理系统项目实战全套视频教程，从需求分析、设计、前后端开发、测试、程序优化到项目部署一套搞定](https://www.bilibili.com/video/BV1yGydYEE3H?p=3&vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## CMS内容管理系统

>  https://blog.csdn.net/weixin_36338224/article/details/109105047?fromshare=blogdetail&sharetype=blogdetail&sharerId=109105047&sharerefer=PC&sharesource=r1Way&sharefrom=from_link

## Django

### 命令行

* ./mysite下 创建应用

```shell
py magage.py startapp blog
```

* 启动项目

```shell
py manage.py runserver
```

### 静态文件

> [如何管理静态文件（如图片、JavaScript、CSS） | Django 文档 | Django](https://docs.djangoproject.com/zh-hans/5.1/howto/static-files/)

### 改变模型

1. 编辑models.py
2. ` py manage.py makemigrations users`  生成迁移文件
3. `py manage.py migrate`应用数据库迁移

### 创建超级用户管理员

`py manage.py createsuperuser`

admin 123456

### URL调度器

[URL调度器 | Django 文档 | Django](https://docs.djangoproject.com/zh-hans/5.1/topics/http/urls/)

## Django实例

> [编写你的第一个 Django 应用，第 1 部分 | Django 文档 | Django](https://docs.djangoproject.com/zh-hans/5.1/intro/tutorial01/)

## 图片浮出

### html

```html
<!DOCTYPE html>
<html lang="zh-cn">
<head>
    <meta charset="UTF-8">
    <title>图片浮现效果</title>
    <link rel="stylesheet" href="script.css">
</head>
<body>
    <div class="content" style="height:200px;">
        <!-- 这里是页面内容，用于产生滚动条 -->
    </div>
    <img src="1.png" alt="浮现的图片" class="fade-in-image">
    <script src="script.js"></script>
</body>
</html>
```



### css

```css
/* 移除了固定定位 */
.fade-in-image {
    opacity: 0; /* 初始透明度为0 */
    /* position: fixed; 移除这一行 */
    /* bottom: 20px; 移除这一行 */
    /* right: 20px; 移除这一行 */
    transition: opacity 1s ease-in-out; /* 透明度变化过渡效果 */
}

/* 当图片进入视口时的样式 */
.fade-in-image.visible {
    opacity: 1; /* 透明度变为1 */
}
```



### js

```javascript
document.addEventListener('DOMContentLoaded', function() {
    // 获取图片元素
    var img = document.querySelector('.fade-in-image');

    // 创建一个IntersectionObserver实例
    var observer = new IntersectionObserver(function(entries, observer) {
        entries.forEach(function(entry) {
            if (entry.isIntersecting) {
                // 当图片进入视口时，添加'visible'类
                img.classList.add('visible');
            } else {
                // 当图片离开视口时，移除'visible'类
                img.classList.remove('visible');
            }
        });
    }, {
        rootMargin: '0px', // 可以设置一个边距，提前触发
        threshold: 0.4 // 当图片的40%进入视口时触发
    });

    // 开始观察图片元素
    observer.observe(img);
});
```

