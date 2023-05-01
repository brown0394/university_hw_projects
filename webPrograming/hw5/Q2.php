<?php
    ini_set('display_errors', 1);   // error message On

    // Initialize variables
    $mode = "select";
    $totalCount = 0;
    $err = "";
    $result = null;

    // Check and assignment POST parameters
    $name = "";
    $tel = "";
    $email = "";
    $memo = "";
    $mode = "";
    $tname = "";
    $ttel = "";
    $temail = "";
    $tmemo = "";

    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $name = $_POST['txt_name'];
        $tel = $_POST['txt_tel'];
        $email = $_POST['txt_email'];
        $memo = $_POST['txt_memo'];
        $mode = $_POST['mode'];
    }
    // Connect to MySQL
    $database = null;
    if(!($database = mysqli_connect("127.0.0.1", "root", "15411541"))) {
        die(mysqli_error($database));
    }
    if(!mysqli_select_db($database, "phonebook")) {
        die(mysqli_error($database));
    }
    $query = "";
    // Sql query processing according to mode
    if ($mode == "insert")
    {
        $query = "select name from contacts where name = \"$name\"";
        if(!($result = mysqli_query($database, $query))) {
            $err = "query failed";
        }
        if (mysqli_num_rows($result) > 0) {
            $err = "'$name'의 연락처는 이미 존재합니다.";
        }
        else if (!mb_ereg("[0-9]{3}-[0-9]{4}-[0-9]{3}", $tel)) {
            $err = "전화번호 형식은 xxx-xxxx-xxxx를 지켜주세요.";
            $mode = "select";
        }
        else if ($email != "" && !mb_ereg("[[:alnum:]]+@[[:alnum:]]+\.[[:alpha:]]+", $email)) {
            $err = "이메일 형식은 xxx@xxxx.xxx를 지켜주세요.";
            $mode = "select";
        }
        else {
            $result->close();
            $query = "insert into contacts";
            $cols = "(name, phone";
            $vals = "values('$name', '" . mysqli_real_escape_string($database, $tel) . "'";
            if ($email != "") {
                $cols = $cols . ", email";
                $vals = $vals . ", '$email'";
            }
            if ($memo != "") {
                $cols = $cols . ", memo";
                $vals = $vals . ", '$memo'";
            }
            $cols = $cols . ")";
            $vals = $vals . ")";
    
            $query = $query . $cols . $vals;
            if(!($result = mysqli_query($database, $query))) {
                $err = "query failed";
            }
        }
    }
    else if ($mode == "delete")
    {
        $query = "select name from contacts where name = \"$name\"";
        if(!($result = mysqli_query($database, $query))) {
            $err = "query failed";
        }
        if (mysqli_num_rows($result) == 0) {
            $err = "'$name'의 연락처는 존재하지않습니다.";
        }
        else {
            $result->close();
            $query = "delete from contacts where name = \"$name\"";
            if(!($result = mysqli_query($database, $query))) {
                $err = "query failed";
            }
        }
    }
    else if ($mode == "delete_all")
    {
        $query = "delete from contacts";
        if(!($result = mysqli_query($database, $query))) {
            $err = "query failed";
        }
    }
    // Execute select query
    $select_sql = "select * from contacts order by name";
    $data_arr = array();
    if(!($result = mysqli_query($database, $select_sql))) {
        $err = "query failed";
    }
    else {
        while($row = mysqli_fetch_row($result)) {
            $obj = array();
            foreach($row as $key => $val) {
                $a = "";
                if ($val != null) {
                    $a = $val;
                }
                switch ($key) {
                    case 0: {$obj['name'] = $a; break;}
                    case 1: {$obj['tel'] = $a; break;}
                    case 2: {$obj['email'] = $a; break;}
                    case 3: {$obj['memo'] = $a; break;}
                }
            }
            $data_arr[] = $obj;
        }
        $result->close();
    }
    mysqli_close($database);
    if ($err != "") {
        $tname = $name;
        $ttel = $tel;
        $temail = $email;
        $tmemo = $memo;
    }
?>
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>Example</title>
    <style type="text/css">
        #maindiv {
            width: 300px;
            float: left;
        }
        label {
            display: inline-block;
            width: 85px;
        }
        #div_btn {
            margin: 5px 0px;
        }
        #contactContainer {
            display: flex;
            flex-direction: column;
            flex-wrap: wrap;
            width: 200px;
            height: 250px;
        }    
        #contactContainer .contactBox {
            text-align: center;
            font-size: 1.5em;
            border: 1px solid;
            width: 80px;
            margin: 1px;
            padding: 5px;
            cursor: pointer;
        }
        #div_fullInfo {
            visibility: hidden;
            float: left;
            width: 200px;
            border: 2px solid black;
            border-radius: 10px;
            text-align: center;
        }
        #div_fullInfo span {
            display: block;
            font-size: 1.2em;
        }
        .pagination {
            visibility: hidden;
            display: inline-block;
        }
        .pagination div {
            float: left;
            padding: 8px 16px;
        }
        .pagination div.active {
            background-color: #4CAF50;
            color: white;
        }
        .pagination div:hover:not(.active) {background-color: #ddd;}
    </style>
    <script type="text/javascript">
        var contactArr = <?php echo json_encode($data_arr);?>;    // php 배열을 javascript 배열에 바로 대입하고 싶을 때는 json을 활용
        var curPage = 0;

        function makeAlert()    // php에서 생성한 에러 메시지를 경고창으로 띄워주는 함수
        {
            var err = "<?php echo $err;?>";
            if (err.length > 0)
            {
                window.alert(err);
                return;
            }
        }        
        function addContact()
        {
            var name = document.getElementById("txt_name").value;
            var tel = document.getElementById("txt_tel").value;
            var email = document.getElementById("txt_email").value;
            var memo = document.getElementById("txt_memo").value;

            if (name == "" || tel == "")
            {
                window.alert("이름과 연락처는 꼭 입력해야 합니다.");
                return;
            }

            // 이름 중복 체크는 php에서 수행
            //if (findContact(document.getElementById("txt_name").value) >= 0)
            //{
            //    window.alert("이미 등록된 연락처입니다.");
            //    return;
            //}

            //var contact = {name: name, tel: tel, email: email, memo: memo};
            //contactArr.push(contact);
            //contactArr.sort(compareName);

            //document.forms[0].reset();
            //makePages();
            //showContacts();
            //updateData();

            document.getElementById("mode").value = "insert";
            document.forms[0].submit();
        }
        function findContact(name)
        {
            for (var contactIdx in contactArr)
            {
                if (contactArr[contactIdx].name == name)
                    return contactIdx;
            }
            return -1;
        }
        /*function compareName(contect1, contect2)
        {
            if (contect1.name > contect2.name)
                return 1;
            else if (contect1.name < contect2.name)
                return -1;
            else
                return 0;
        }*/
        function delContact()
        {
            //var idx = findContact(document.getElementById("txt_name").value);
            // 이름 체크는 php에서 수행
            //if (idx < 0)
            //{
            //    window.alert("일치하는 이름을 가진 연락처가 없습니다.");
            //    return;
            //}
            //contactArr.splice(idx, 1);
            //makePages();
            //showContacts();
            //updateData();
            if (document.getElementById("txt_name").value == "")
            {
                window.alert("제거할 연락처의 이름을 입력해주세요.");
                return;
            }
            document.getElementById("mode").value = "delete";
            document.forms[0].submit();
        }
        function clearAll()
        {
            //contactArr = Array();
            //document.getElementById("contactContainer").innerHTML = "";
            //document.getElementById("div_fullInfo").style.visibility = "hidden";
            //makePages();
            //updateData();
            document.getElementById("mode").value = "delete_all";
            document.forms[0].submit();
        }
        function showContacts()
        {
            var contactContainer = document.getElementById("contactContainer");
            //contactContainer.innerHTML = "";
            contactContainer.replaceChildren();
            var startIdx = curPage * 10;
            var endIdx = startIdx + 9;
            for(var idx = startIdx; idx <= endIdx && idx < contactArr.length; idx++)
            {
                var contact = makeContact(contactArr[idx].name);
                //contactContainer.innerHTML += contact;
                contactContainer.appendChild(contact);
            }
            document.getElementById("div_fullInfo").style.visibility = "hidden";
        }
        function showContactInfo(name)
        {
            var contact = contactArr[findContact(name)];
            document.getElementById("info_name").innerHTML = contact.name;
            document.getElementById("info_tel").innerHTML = contact.tel;
            if (contact.email.length > 0)
                document.getElementById("info_email").innerHTML = contact.email;
            else
                document.getElementById("info_email").innerHTML = "-";
            if (contact.memo.length > 0)
                document.getElementById("info_memo").innerHTML = contact.memo;
            else
                document.getElementById("info_memo").innerHTML = "-";
            document.getElementById("div_fullInfo").style.visibility = "visible";

            //document.getElementById("txt_name").value = contact.name;
        }
        function makeContact(name)
        {
            //return "<div id='" + name + "' class='contactBox' onclick='showContactInfo(id)'>" + name + "</div>";
            var newnode = document.createElement("div");
            newnode.setAttribute("id", name);
            newnode.setAttribute("class", "contactBox");
            newnode.setAttribute("onclick", "showContactInfo(id)");
            newnode.appendChild(document.createTextNode(name));
            return newnode;
        }

        function getNav(i) {
            var newnode = document.createElement("div");
            newnode.setAttribute("onclick", "changePage(" + i + ")");
            newnode.appendChild(document.createTextNode(i+1));
            if (i == curPage) {
                newnode.setAttribute("class", "active");
            }
            return newnode;
        }

        function makePages()
        {
            if (contactArr.length > 10)
            {
                var pageNav = document.getElementById("pageNav");
                pageNav.style.visibility = "visible";
                //pageNav.innerHTML = "";
                pageNav.replaceChildren();
                var nPage = Math.ceil(contactArr.length / 10);
                for(var i =0; i < nPage; i++)
                {
                    /*
                    if (i == curPage)
                        pageNav.innerHTML += "<div class=\"active\" onclick=\"changePage(" + i +")\">" + (i + 1) + "</div>";
                    else
                        pageNav.innerHTML += "<div onclick=\"changePage(" + i +")\">" + (i + 1) + "</div>";
                    */
                   pageNav.appendChild(getNav(i));
                   }
            }
            else
            {
                var pageNav = document.getElementById("pageNav");
                pageNav.style.visibility = "hidden";
                pageNav.replaceChildren();
                //pageNav.innerHTML = "";
            }
        }
        function changePage(pageNum)
        {
            curPage = pageNum;
            makePages();
            showContacts();
        }
        //function updateData()
        //{
        //    localStorage.removeItem("contacts");
        //    localStorage.setItem("contacts", JSON.stringify(contactArr));
        //}
        function start()
        {
            makeAlert();
            //var contacts = localStorage.getItem("contacts");
            //if (contacts != null)
            //{
                //contactArr = JSON.parse(contacts);
                makePages();
                showContacts();
            //}
        }
    </script>
    </head>
<body onload="start()">
    <div id="maindiv">
        <form name="form1" method="POST" action="Q2.php">
            <label for="txt_name">이름:</label><input type="text" name="txt_name" id="txt_name" value=<?php print("$tname")?>><br>
            <label for="txt_tel">전화번호:</label><input type="text" name="txt_tel" id="txt_tel" value=<?php print("$ttel")?>></label><br>
            <label for="txt_email">이메일:</label><input type="text" name="txt_email" id="txt_email" value=<?php print("$temail")?>></label><br>
            <label for="txt_memo">메모:</label><input type="text" name="txt_memo" id="txt_memo" value=<?php print("$tmemo")?>></label><br>
            <div id="div_btn">
                <input type="button" name="addBtn" id="addBtn" value="연락처 추가" onclick="addContact()">
                <input type="button" name="delBtn" id="delBtn" value="연락처 삭제" onclick="delContact()">
                <input type="reset" name="ClearBtn" id="clearBtn" value="모두 삭제" onclick="clearAll()">
            </div>
            <!--submit 구분을 위한 hidden input 추가-->
            <input type="hidden" name="mode" id="mode" value="insert"/>
        </form>
        <br>
        <div id="contactContainer">
        </div>
        <nav class="pagination" id="pageNav">
        </nav>
    </div>
    <div id="div_fullInfo">
        <span id="info_name"></span>
        <span id="info_tel"></span>
        <span id="info_email"></span>
        <span id="info_memo"></span>
    </div>
</body>
</html>