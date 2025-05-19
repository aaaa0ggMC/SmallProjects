//已安装油猴脚本
const sleep = (delay) => new Promise((resolve) => setTimeout(resolve, delay));

function toggler(){
    var idx = document.getElementsByClassName('el-radio');
        for(var i = 0;i < idx.length;++i){      if(idx[i].innerHTML.search("优秀") != -1){
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

pj()
