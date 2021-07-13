function checkPWord(checkbox, pword) {
    if (checkbox.checked == true){
        pword.type = "text";
    }
    else {
        pword.type = "password";
    }
}

function changePage(firstPage, secondPage, firstForm, firstPassword) {
    firstForm.reset();
    firstPassword.type = "password";
    firstPage.style.display = "none";
    secondPage.style.display = "block";
}