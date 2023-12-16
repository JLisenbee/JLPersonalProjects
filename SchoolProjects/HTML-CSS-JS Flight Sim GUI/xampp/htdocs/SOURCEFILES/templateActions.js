function goHome(location) {
    if (typeof(location) == 'undefined') {
        window.location.href = "../home/home.html";
    } else {
        window.location.href = location;

    }
}

function goGames() {
    window.location.href = "../games.html";
}

function goFood() {
    window.location.href = "../food.html";
}

function goCheckout() {
    window.location.href = "../checkout/checkout.html";
}

function goMovies() {
    window.location.href = "../movies.html";
}

function goFTracker() {
    window.location.href = "../flighttracker/flighttracker.html";
}

