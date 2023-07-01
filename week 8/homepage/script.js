document.addEventListener('DOMContentLoaded', function(){
    var elements = document.getElementsByClassName("generalParagraph");
    for (var i = 0; i < elements.length; i++) {
        elements[i].style.display = "none";
    }
    buttons = document.querySelectorAll('.dropdownButton');
    buttons.forEach(function(button) {
        button.addEventListener('click', function(event) {
            let buttonID = event.target.id;
            let paragraph = document.getElementById(buttonID.replace("Button", ""));
            if (paragraph.style.display === 'none') {
                paragraph.style.display = 'block';
            }
            else {
                paragraph.style.display = 'none';
            }
        });
    });
});