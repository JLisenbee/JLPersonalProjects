var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = 
function() { 
if (this.readyState == 4 && this.status == 200) { 
    var homeList = JSON.parse(this.responseText)
    var linkText = "";
    for (var i = 0; i < homeList.length; i++) {

        if(i == 0) var newItem = $("<div onclick='goMovies()'></div>").addClass("item");
        else if (i == 1) var newItem = $("<div onclick='goGames()'></div>").addClass("item");
        else if (i == 2) var newItem = $("<div onclick='goFTracker()'></div>").addClass("item");
        else if (i == 3) var newItem = $("<div onclick='goFood()'></div>").addClass("item");
        //else var newItem = $("<div></div>").addClass("item");
        $(newItem).append($('<b></b>').text(homeList[i].name).addClass("title"))
        $(newItem).append($('<p></p>').text(homeList[i].description).addClass("desc"))
        $(newItem).click(function() {
            $(".item").css("border", "3px dotted black");
            $(this).css("border", "3px solid red");
        });
        $(".demo").append(newItem)
    }
} 
}; 
xhttp.open("GET", "home.json", true); 
xhttp.send(); 