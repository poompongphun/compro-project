const navbarDiv = document.getElementById("navbar");
window.onscroll = () => {
  if (document.documentElement.scrollTop == 0) {
    navbarDiv.classList.remove("active");
  } else navbarDiv.classList.add("active");
};
