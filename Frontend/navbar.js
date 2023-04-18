const toggleButton = document.getElementsByClassName('toggle-button')[0]
const navbarLinks = document.getElementsByClassName('navbar-links')[0]
const bannerImage = document.getElementsByClassName('bannerimage')[0]

toggleButton.addEventListener('click', () => {
  navbarLinks.classList.toggle('active')
  bannerImage.classList.toggle('active')
})
