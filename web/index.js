require('dotenv').config();

const express = require('express');
const bodyParser = require('body-parser');
const http = require('http');
const socketIo = require('socket.io');
const path = require('path');
const moistureRoute = require('./routes/moistureRoute');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.use(bodyParser.json());
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));
app.use(express.static(path.join(__dirname, 'public')));

app.use((req, res, next) => {
  req.io = io;
  next();
});

app.use('/', moistureRoute);

app.get('/', (req, res) => {
  res.render('index');
});

io.on('connection', (socket) => {
  console.log('A client connected');
});

server.listen(3000, () => {
  console.log('Server is running on port 3000');
});
