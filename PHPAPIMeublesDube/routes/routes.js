const express = require('express');
const router = express.Router();
const meublesDubeInc = require('../services/meublesDubeInc');

/* GET liste des bois. */
router.get('/', async function(req, res, next) {
  try {
    res.json(await meublesDubeInc.getMultiple(req.query.page));
  } catch (err) {
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

module.exports = router;