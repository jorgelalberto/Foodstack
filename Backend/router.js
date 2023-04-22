/*
const express = require('express')
const router = express.Router()

// middleware that is specific to this router
router.use((req, res, next) => {
  console.log('Time: ', Date.now())
  next()
})
// define the home page route
router.get('/', (req, res) => {
    res.sendFile(__dirname + '../Frontend/index.html')
})
// define the about route
router.get('/homePage', (req, res) => {
    res.sendFile(__dirname + '../Frontend/homePage.html')
})

module.exports = router
*/