# Wallpaper (原名: DesktopBack) (Windows Only)
一个简单的壁纸程序，本是MSVC项目，我做了点修改迁移到了msys2。

## 运行
```bash
wallpaper # 启动wallpaper程序，自动读取配置&运行ffplay,但是配置出错会弹出配置窗口
wallpaper ...(anything) # 弹出配置窗口
```

## 注意
检测ffplay窗口的逻辑很笨，为Sleep 2s然后检测窗口，有时可能会失败！
