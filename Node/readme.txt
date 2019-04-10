在nodejs文件夹里面新建以下两个目录：node_global和node_cache

启动CMD依次执行以下两条命令
npm config set prefix "C:\Program Files\nodejs\node_global"
npm config set cache "C:\Program Files\nodejs\node_cache"

设置环境变量NODE_PATH为"C:\Program Files\nodejs\node_global"


安装node软件包：npm install express -g