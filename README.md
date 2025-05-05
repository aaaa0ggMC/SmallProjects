# SmallPrograms
 业余写点小玩意儿

>Github2FA学长太阴险了，这个项目暂时放到Gitlab Hongkong

## 环境
### Shell
- msys64
- fish
### C++(ucrt64)
- sfml 2.6.1+
- gcc c++20/23(ucrt)
### Editor
- vim9.1

## 目标
- 尽一切可能使用现代C++特性
- Work,then work faster. 保证代码能工作，尽量保证效率

## nbodies
受euuen启发而写的一个小小的模拟星球运动的程序,行数约190行，用时2.5h-3h编写
### 编译
```bash
g++ severalbodies.cpp -o nbody.exe -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system
```
### 运行
#### 随机生成
```bash
nbody [星球数量,可以没有，默认为3]
```
#### 文件
```bash
nbody -file xxx
```
文件示例：
```
# 这是注释
# p x y v_x v_y mass r g b
p 400 300 1 1 100 255 255 255
```

## boids (flocks) [WIP TODO ]
受到StephenLague的启发，however没什么时间，于是有些代码以及逻辑是Deepseek生成的，比较凌乱......
### 编译
```bash
g++ flocks.cpp -o flocks.exe -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system
```
### 运行
```bash
flocks [鸟数量，可以没有，默认为10]
```

