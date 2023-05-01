var name1;
var phoneNumber;
var email;
var memo;
var addP;
var delA;
var delP;
var fbox;
var infoBox;
var pArr = new Array(4);
var count = 1;
var index = 0;
var storedArr = new Array();

function start() {
    name1 = document.getElementById("name1");
    phoneNumber = document.getElementById("phoneNumber");
    email = document.getElementById("email");
    memo = document.getElementById("memo");
    addP = document.getElementById("addP");
    delA = document.getElementById("delA");
    delP = document.getElementById("delP");
    fbox = document.getElementById("fbox");
    infoBox = document.getElementById("ibox")
    iSel = document.getElementById("is");

    for(var i = 0; i < 4; ++i) {
        pArr[i] = document.getElementById("p"+(i+1));
    }

    clear();

    addP.addEventListener("click", smit, false);
    delA.addEventListener("click", delAll, false);
    delP.addEventListener("click", delBox, false);
    storedArr = loadObj();
    drawBox(0);
}

function delAll() {
    localStorage.clear();
    count=1;
    index = 0;
    ibox.style.display = "none";
    storedArr = Array();
    drawBox(0);
    clear();
}

function checkEmailFormat() {
    if (email.value == "") return false;
    var atFlag = false;
    var dotFlag = false;
    var emailFlag = false;
    for (var i = 0; i < email.value.length; ++i) {
        if (email.value[i] == '@') {
            atFlag = true;
        }
        else if(email.value[i] == ' ') {
            emailFlag = false;
            break;
        }
        else if (atFlag && email.value[i] == '.'){
            dotFlag = true;
        }
        else if(atFlag && dotFlag) {
            emailFlag = true;
        }
    }
    return !emailFlag;
}

function checkPhoneForamt() {
    if (phoneNumber.value.length < 13 || phoneNumber.value.length > 13) {
        return true;
    }
    for (var i = 0; i < 13; ++i) {
        switch(i) {
            case 3: {}
            case 8: {
                if (phoneNumber.value[i] != '-') {
                    return true;
                }
                break;
            }
            default: {
                if (phoneNumber.value[i] < '0' || phoneNumber.value[i] > '9') {
                    return true;
                }
            }
        }
    }
    return false;
}

function smit() {
    if (name1.value == "") {
        window.alert("이름을 입력하시오");
        return;
    }
    else if (phoneNumber.value == "") {
        window.alert("전화번호를 입력하시오");
        return;
    }
    if (checkPhoneForamt()) {
        window.alert("전화번호 형식을 지켜주세요 : xxx-xxxx-xxxx");
        return;
    }
    if (checkEmailFormat()) {
        window.alert("이메일 형식을 지켜주세요 : xxx@xxx.xxx");
        return;
    }
    addBox();
}

function storeObj() {
    for (var i = 0; i < storedArr.length; ++i){
        localStorage.setItem(i, JSON.stringify(storedArr[i]));
    }
    localStorage.setItem("count", count);
    localStorage.setItem("index", index);
}

function loadObj() {
    var array = Array();
    for (var i = 0; i < (localStorage.length - 2); ++i){
        array[i] = JSON.parse(localStorage.getItem(i));
    }
    return array;
}

function loadCount() {
    var val = localStorage.getItem("count");
    if (val == null) {
        count = 1;
        localStorage.setItem("count", count);
    }
    else {
        count = parseInt(val);
    }
    val = localStorage.getItem("index");
    if (val == null) {
        index = 0;
        localStorage.setItem("index", index);
    }
    else {
        index = parseInt(val);
    }
}

function addBox() {
    loadCount();
    if (checkExist(name1.value)) {
        window.alert("같은 이름을 두개 등록할 수 없습니다.");
        return;
    }
    let item = {n : name1.value, p : phoneNumber.value, e : email.value, m : memo.value, i : count};
    localStorage.setItem(index++, JSON.stringify(item));
    storedArr = loadObj();
    storedArr.sort(objStrComp);
    localStorage.clear();
    ++count;
    storeObj();
    drawBox(0);
    clear();
}

function objStrComp(a, b) {
    if (a.n < b.n) return -1;
    else if (a.n == b.n) return 0;
    return 1;
}

function drawBox(base) {
    fbox.innerHTML = "";
    for (var i = base; i < storedArr.length && i < (base+10); ++i){
        fbox.innerHTML += "<button id = \"b"+i+ "\" onclick=\"showInfo(" + i + ")\"> " + storedArr[i].i + "</button>\n";
    }
    iSel.innerHTML = "";
    if (storedArr.length > 10) {
        var numbers = Math.ceil(storedArr.length / 10);    
        for (var j = 0; j < numbers; ++j) {
            iSel.innerHTML += "<input id = \"s"+j+ "\" type=\"button\" onclick=\"selectIndex(" + j + ")\" value=\"" + (j+1) + "\"/>\n";
        }
        var indexButton;
        if (base > 0) {
            indexButton = document.getElementById("s"+(base / 10));
        }
        else {
            indexButton = document.getElementById("s0");
        }
        indexButton.disabled = true;
    }
}

function selectIndex(Inum) {
    var base = Inum * 10;
    drawBox(base);
}

function delBox() {
    var length = localStorage.length - 2;
    var flag = false;
    storedArr = Array();
    var idx = 0;
    for (var i = 0; i < length; ++i){
        let got = JSON.parse(localStorage.getItem(i));
        if(got.n == name1.value) {
            flag = true;
        }
        else {
            storedArr[idx++] = got;
        }
    }
    if (flag) {
        localStorage.clear();
        --index;
        storeObj();
        ibox.style.display = "none";
    }

    drawBox(0);
    clear();
}

function checkExist(p_name) {
    var length = localStorage.length - 2;
    for (var i = 0; i < length; ++i){
        let got = JSON.parse(localStorage.getItem(i));
        if(got == null) {
            return false;
        }
        if (got.n == p_name) {
            return true;
        }
    }
    return false;
}

function showInfo(n) {
    if (n >= 0) {
        let got = storedArr[n];
        pArr[0].innerHTML = got.n;
        pArr[1].innerHTML = got.p;
        if (got.e == "") {
            pArr[2].innerHTML = "-";
        }
        else {
            pArr[2].innerHTML = got.e;
        }
        if (got.m == "") {
            pArr[3].innerHTML = "-";
        }
        else {
            pArr[3].innerHTML = got.m;
        }
        ibox.style.display = "block";
    }
}

function clear() {
    name1.value = "";
    phoneNumber.value = "";
    memo.value = "";
    email.value = "";
}

window.addEventListener("load", start, false);