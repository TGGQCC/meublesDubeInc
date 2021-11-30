const env = process.env;

const config = {
  db: { /* don't expose password or any sensitive info, done only for demo */
    host: env.DB_HOST || 'localhost',
    user: env.DB_USER || 'meublesdubeinc',
    password: env.DB_PASSWORD || 'Patate123.',
    database: env.DB_NAME || 'meublesdubeinc',
  }
};


module.exports = config;