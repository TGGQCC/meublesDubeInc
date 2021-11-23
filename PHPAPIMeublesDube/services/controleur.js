const db = require('./db');
const config = require('../config');
require('dotenv').config();
let jwt = require("jsonwebtoken");
//Loading the crypto module in node.js
var crypto = require('crypto');

async function getAllWoods(){
  return await db.query(
    `SELECT id, nom FROM bois`
  );
}

async function getCaracterisiticsOf(id){
  return await db.query(
    `SELECT * FROM bois where id = ?`, 
    [id]
  );
}

async function getCaracterisitics(nom){
  return await db.query(
    `SELECT * FROM bois where nom = ?`, 
    [nom]
  );
}

//Authentification
async function login (req,res) {
  var hash = crypto.createHash('sha512');
  data = hash.update(req.body.password + process.env.SALT, 'utf-8');
  gen_hash= data.digest('hex');
  let user = await db.query(`SELECT usager FROM usager where usager = ? AND motDePasse = ?`, [req.body.user, gen_hash]);
    if(user && user.length == 1){
        let token = jwt.sign({}, process.env.TOKEN_KEY);
        res.status(200).json({ token });
    }else{
        res.status(401).json({message: "Login ou mot de passe incorrect"});
    }
}

function test (req,res) {
    res.status(200).json({message: "Vous êtes bien authentifiés."});
}



module.exports = {
  getAllWoods,
  getCaracterisiticsOf,
  getCaracterisitics,
  login,
  test
}