var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = 
function() { 
if (this.readyState == 4 && this.status == 200) { 
    for (var i = 0; i < gamesList.length; i++) {
        var newGame = $('<div></div>').addClass("game");
        $(newGame).append($("<img src='" + gamesList[i].logo + ".png'/>").addClass("logo"))
        $(newGame).append($("<img src='" + gamesList[i].logo + "_gameplay.png'/>").addClass("gameplay"))
        $(newGame).append($('<div></div>').text(gamesList[i].description))
        $(newGame).click(function() {
            $(".game").css("border", "3px dotted black");
            $(this).css("border", "3px solid red");
        });
        $(".demo").append(newGame)
    }
} 
}; 
xhttp.open("GET", "games.json", true); 
xhttp.send(); 