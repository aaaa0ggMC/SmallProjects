# C! (Windows Only)\
2020年的小项目，历经多年风霜，最新版的源码我已经找不到了，所以这里的源码比main.zip中的exe文件要老一点

components中的MWB.exe程序似乎对电脑有坏处，具体为出现一堆弹窗，然后NtRaiseHardError

## 文件编码
ANSI (GBK maybe)

## 关于main.zip与doc
我自己曾为这个语言写了个doc:https://aaaa0ggmc.github.io/Old/CE/ !(访问)[https://aaaa0ggmc.github.io/Old/CE/]<br/>
关键字界面还没有完善，函数界面倒还可以看看

## 运行
```bash
cei [文件] # 预处理文件,生成后缀名为rb的与处理文件，这类文件的代码能直接使用code函数处理，更加方便运行
ce -help # 帮助
ce [文件.ce] #  运行ce文件
ce [文件.rb] # 运行rb文件
ce -version # 版本

# 以下内容只有latest-bin或者main.zip中的exe中才有
ce -line xxx # 执行一行代码
ce -e # 运行类似python的即时解释器
```
可以运行\_SF()函数来获取支持的所有内容
<br/>
有源代码的版本输出
```txt
#对不起，牢版本没有这个东西😅😅😅
```

最新版本输出
```txt
SupportFunctions:               |arguments
SupportFunctions(_SF)           |none |return function counts
print                           |a string | return count of output
println                         |a string | return count of output
String,var,float,Number,BaseObj |a var name & tag
input                           |a var name or empty | return input value
math                            |a math string       | result
runProgram                      |a string            | return string length
CE$input                        |a var name or empty | return input value
local                           |a var name          | return the attributes of the var
#pragma                         |not fixed
rand                            |tow numbers
declare_var                     |a string var name
SetConsolePosition(CE$setPos)   |tow coordinates
print$delay(print%d)            |a string & a number
print$color(print%c)            |a string & a number
break                           |none
continue                        |none
isRunAsAdmin(isAdmin)           |none|return 1(is admin) or 0(not admin)
seek                            |none|return NULL
LoadInstDLL(LoadDLL)            |dll's name and dll's path|return dll's name
UnloadInstDLL(UnloadDLL)        |dll's name|return NULL now
CalInstDLL(CalDLL)              |dll's name and the function's name u will call|return 0 now
const,extern,CESTDAPI,IGNORECASE|key word
OUTABLE                         |key word
clear                           |none|clear the console
ceEdit(cpowershell)             |none
system                          |cmd command
free                            |var name | free variable
myFriend                        |string   |Easter Eggs
time                            |none     |return now time
getKeyInt                       |var name     |return NULL
getKeyChar                      |varname      |return NULL
getMousePosX                    |varname      |return NULL
getMousePosY                    |varname      |return NULL
getThisMousePosX                |varname      |return NULL | Need WinXP or Higher
getThisMousePosY                |varname      |return NULL | Need WinXP or Higher
while,loop,if,elseif            |condition
rloop,else                      |none
Sleep                           |sleepTime    |return NULL
CEAPI                           |This is no longer used,it is used for creating useless statements | return NULL
Special:"else" token needs a bracket,or the compiler will alert error!
```

## 关于示例程序
fulafu.ce 伏拉夫
fulafu2.ce 伏拉夫2，ce牢版本运行不了

## 最后
最后，
```bash
print("Hello World!");
```

