const express = require('express');
const router = express.Router();
const controleur = require('../services/controleur');
const auth = require('../middleware/auth');

//Authentification
router.post("/login", function(req,res){controleur.login(req,res)});
router.get("/test", auth, function(req,res){controleur.test(req,res)});

/* GET liste des bois. */
router.get('/getAllWoods', auth, async function(req, res, next) {
  try {
    res.json(await controleur.getAllWoods());
  } catch (err) {
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

/*GET caractéritiques d'un bois*/
router.get('/getCaracterisiticsOf/:id', auth, async function(req, res, next){
  try{
    res.json(await controleur.getCaracterisiticsOf(req.params.id));
  } catch(err){
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

/*GET caractéritiques d'un bois à partir de son nom*/
router.get('/getCaracterisitics/:nom', auth, async function(req, res, next){
  try{
    res.json(await controleur.getCaracterisitics(req.params.nom));
  } catch(err){
    console.error(`Error while getting programming languages `, err.message);
    next(err);
  }
});

module.exports = router;