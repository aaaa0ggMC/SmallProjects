// ==UserScript==
// @name        附中评教自动脚本
// @decription 自动打“优秀”并提交。脚本也许会出问题，但是我没做手脚，出问题了后果自负。
// @namespace   aifz
// @match       http://pj.aifz.net/student/evaluation*
// @grant       GM_registerMenuCommand
// @version     1.0
// @author      aaaa0ggMC https://yslwd.eu.org
// @description 2025/5/19 12:54:24
// ==/UserScript==
const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));

function toggler(){
    var idx = document.getElementsByClassName('el-radio');
    for(var i = 0;i < idx.length;++i){
        if(idx[i].innerHTML.search("优秀") != -1){
            idx[i].getElementsByTagName('input')[0].click();
        }
    }
    var buttons = document.getElementsByClassName('el-button el-button--primary el-button--small');
    for(var i = 0;i < buttons.length;++i){
	  if(buttons[i].innerHTML.search('提交') != -1){
		  buttons[i].click();
    }
	}
}

async function pj(){
    var tiyu = prompt("你的体育老师是谁？？留空表示不知道");
    var teachers = document.getElementsByClassName('es-teacher')[0].getElementsByTagName('li');
    for(var i = 0;i < teachers.length;++i){
        teachers[i].getElementsByTagName('a')[0].click();
	if(teachers[i].innerHTML.search("体育") != -1 && tiyu != "" && teachers[i].innerHTML.search(tiyu) == -1){
		continue;
	}
        await sleep(1000);
        toggler();
    }
}

window.pj = pj;

GM_registerMenuCommand(
  "点我自动评教",
  ()=>{
    var x = confirm("脚本也许会出问题，但是我没做手脚，出问题了后果自负。");
    if(x){
      pj();
    }
  }
);
// 为什么改了网页就运作不了了？
//setTimeout(function(){document..innerHTML = "<button onclick='pj();'>点我开启懒人模式</button>" + document.head.innerHTML;},1500);
