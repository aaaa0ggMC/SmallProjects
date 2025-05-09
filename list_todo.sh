#!/bin/bash

# 初始化一个数组来存储没有README.md的文件夹
todo_folders=()

# 遍历当前目录下的直接子文件夹（不包括隐藏文件夹）
for folder in */; do
    # 去掉末尾的斜杠，获取纯目录名
    folder_name="${folder%/}"
    
    # 检查该文件夹是否包含README.md文件
    if [ ! -f "$folder_name/README.md" ]; then
        todo_folders+=("$folder_name")
    fi
done

# 输出结果
if [ ${#todo_folders[@]} -eq 0 ]; then
    echo "所有子文件夹都包含README.md文件"
else
    echo "以下文件夹缺少README.md文件 (TODO):"
    printf " - %s\n" "${todo_folders[@]}"
fi
