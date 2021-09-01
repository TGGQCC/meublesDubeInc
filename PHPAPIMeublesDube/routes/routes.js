const express = require('express');
const router = express.Router();
const meublesDubeInc = require('../services/meublesDubeInc');

/* GET liste des bois. */
router.get('/getAllWoods', async function(req, res, next) {
  try {
    res.json(await meublesDubeInc.getAllWoods(req.query.page));
  } catch (err) {
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

/*GET caractéritiques d'un bois*/
router.get('/getCaracterisiticsOf/:id', async function(req, res, next){
  try{
    res.json(await meublesDubeInc.getCaracterisiticsOf(req.params.id, req.query.page));
  } catch(err){
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

module.exports = router;