// create a new XMLHttpRequest object
const xhr = new XMLHttpRequest();

// set the URL of the shared navbar HTML file
const url = "navbar.html";

// configure the XHR request
xhr.open("GET", url);

// define the callback function that will be called when the response is received
xhr.onload = function() {
  // check if the response was successful
  if (xhr.status === 200) {
    // get the response HTML content
    const navbarHtml = xhr.responseText;

    // insert the navbar HTML into the navbar div of the current page
    const navbarDiv = document.getElementById("navbar");
    navbarDiv.innerHTML = navbarHtml;
    window.scrollTo(0,0);
  }
};

// send the XHR request
xhr.send();
