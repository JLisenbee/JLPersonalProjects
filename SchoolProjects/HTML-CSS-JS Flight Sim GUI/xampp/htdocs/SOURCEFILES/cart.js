var totalPrice = 0.0;
var totalMiles = 0;
var paidWith;


function cartHighlight() {
    if ($(this).hasClass("selected") ) {
        $(this).css("border", "").removeClass("selected");
        totalPrice -= parseFloat($(this).attr("price"))
        totalMiles -= parseInt($(this).attr("miles"))
    } else {
        $(this).css("border", "3px solid red").addClass("selected");
        totalPrice += parseFloat($(this).attr("price"))
        totalMiles += parseInt($(this).attr("miles"))

    }
}

function payWithCredit() {
    $(".opts").hide()
    $(".phone").hide()
    $(".entry").hide()

    var newData = $(DIV).addClass("entry").css("order", "1");
    var textFields = $(DIV).addClass("textFields")
    $(textFields).append($(DIV).text("Thank you for paying with credit!"))
    $(textFields).append($(DIV).text(`Your total was $${totalPrice}`))
    $(newData).append(textFields)
    $(".menu").append(newData)
    $(".reciept").css("order", "10").show()
    paidWith = 'miles'

}




function payWithMiles() {
    $(".opts").hide()
    $(".phone").hide()
    $(".entry").hide()
    
    var newData = $(DIV).addClass("entry").css("order", "1");
    var textFields = $(DIV).addClass("textFields")
    $(textFields).append($(DIV).text("Thank you for paying with miles!"))
    $(textFields).append($(DIV).text(`Your total was ${totalMiles} miles`))
    $(newData).append(textFields)
    $(".menu").append(newData)
    $(".reciept").css("order", "10").show()
    paidWith = 'miles'
}


function finalize() {
    $(".menu").hide()
    $(".header").after($(DIV).text("Thank you for ordering! An attendant will be by shortly.").css("font-size", "1.5vw"))
}

function getReciept() {
    $(".entry").hide()
    $(".entry").each(function() {
        if ($(this).attr("price") != "undefined" && $(this).hasClass("selected")) {
            $(".menu").append($(this).children(".textFields"))
        }
        
    });
    $(".menu").append($(DIV).text(`Total Price: $${totalPrice} or ${totalMiles} miles`).addClass("price").addClass("entry").css("font-size", "1.5vw").css("order", "9"))
    $(".reciept").off("click", getReciept);
    $(".reciept").on("click", finalize);
}

var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = 
function() { 
if (this.readyState == 4 && this.status == 200) { 
    $(".phone").hide()
    $(".reciept").hide()
    var dataList = JSON.parse(this.responseText)
    for (var i = 0; i < dataList.length; i++) {
        
        $('.menu').children(".entry").children(".textFields").eq(i).append($(DIV).text(`Price: $${dataList[i].price} or ${dataList[i].miles} miles`).css("margin-top", "auto").css("margin-bottom", "3vh"))
        $('.menu').children(".entry").eq(i).attr('price', dataList[i].price).attr('miles', dataList[i].miles).attr("index", i);
        
    }
    
    $(".entry").off("click", (highlight));
    $(".entry").on("click", cartHighlight);
} 
}; 
xhttp.open("GET", $('script[src*=loadData]').attr('dataFile'), true); 
xhttp.send(); 

function checkout() {
    $(".entry:not(.selected)").hide()
    $(".selected").css("border", "");
    $("#checkout").hide()
    $(".entry").off("click", cartHighlight);
    $(".menu").append($(DIV).text(`Total Price: $${totalPrice} or ${totalMiles} miles`).addClass("price").addClass("entry").css("font-size", "1.5vw").css("order", "9"))
    $(".opts").append($('<button type="button" style="width: 128px; height: 128px;">Miles</button>').addClass("useMiles"))
    $(".opts").append($('<button type="button" style="width: 128px; height: 128px;">Credit</button>').addClass("useCredit"))
    $(".useCredit").on("click", payWithCredit);
    $(".useMiles").on("click", payWithMiles);
    $(".phone").show()
}

function addNumber() {
    var newData = $(DIV).addClass("entry").css("order", "8");
    var textFields = $(DIV).addClass("textFields")
    $(textFields).append($(DIV).text("Call To " + $(".number").val()))
    $(textFields).append($(DIV).text("Price: $3 or 30 miles").css("margin-top", "1vh").css("margin-bottom", "3vh"))
    $(newData).append(textFields).attr('price', "3").attr('miles', "30").addClass("selected")
    $(".menu").append(newData)
    totalMiles += 30
    totalPrice += 3.0
    $(".price").text(`Total Price: $${totalPrice} or ${totalMiles} miles`)
    $(".phone").hide()

}


$("#checkout").on("click", checkout);
$(".addNumber").on("click", addNumber);
$(".reciept").on("click", getReciept);

//<input type="text" name="str" required="required" placeholder="Enter a String" />