const db = require('./db');
const config = require('../config');

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

module.exports = {
  getAllWoods,
  getCaracterisiticsOf,
  getCaracterisitics
}