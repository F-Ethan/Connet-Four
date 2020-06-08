var origBoard;
const huPlayer= 'O';
const aiPlayer= 'x';
var wPlayer = [aiPlayer, huPlayer];
var twoP = true;
var color = false;
const cells = document.querySelectorAll('.cell');
//console.log(cells);
startGame();
var key = 0;
var winSquare = [];
var CanPlay;
var played;

function twoPlayer(){
	if (twoP){
		twoP = false;
		wPlayer[0] = huPlayer;
	}else{
		twoP = true;
		wPlayer[0] = aiPlayer;
		}
	startGame();
}

function changeColor() {
	if (color){
		color = false;
		document.querySelector(".color").style.borderColor = "inherit";

	}else{
		color = true;
		document.querySelector(".color").style.borderColor = "red";
		}
	//startGame();
}


function startGame(){
	origBoard = Array.from(Array(47).keys());
	document.querySelector(".gameWon").style.display = "none";
	CanPlay = [40,41,42,43,44,45,46];
	winSquare = [];
	key = 0;
	document.querySelector(".game").innerText =
	twoP == true ? "Two Player" : "One Player";	
	document.querySelector(".twoPlayer").innerText =
	twoP == true ? "One Player" : "Two Player";

	for(i=0; i<cells.length; i++){
		cells[i].innerText = '';
		cells[i].style.removeProperty('background-color');
		if(i>39 && i<47){
			cells[i].addEventListener('click', turnClick, false);
		}
	}

	function turnClick(square){
		key ++;
		if(typeof origBoard[square.target.id] == 'number'){
			turn(square.target.id, wPlayer[key%2]);
			if (twoP == false){
				if (!checkwin(origBoard, huPlayer) && !checkTie()) turn(bestSpot(), aiPlayer);
			}
		}
	}

	function turn(squareId, player) {
		cells[squareId].removeEventListener('click',turnClick, false);
		origBoard[squareId] = player;
		if(squareId>8) CanPlay.push(squareId-8);
		var old = availS(squareId);
		CanPlay = old;
		document.getElementById(squareId).innerText = player;
		if(color){
			document.getElementById(squareId).style.backgroundColor = 
			player == huPlayer ? "blue" : "hotPink";
		}
		let gameWon = checkwin(origBoard, player);
		if (gameWon) gameOver(gameWon);
		if(squareId>7) cells[squareId-8].addEventListener('click',turnClick, false);
	}

	function availS(squareId){
		return CanPlay.filter(function(id){
			return id != squareId;
		});
	}

	function checkwin(board, player){
		let plays = board.reduce((a,e,i)=>
			(e === player) ? a.concat(i) : a, []);
		let gameWon = null;
			for(i=0; i<plays.length;i++){
			var a = plays[i];
				var winCombos = [
					[a-0,a-1,a-2,a-3],
					[a,a-8,a-16,a-24],
					[a,a-7,a-14,a-21],
					[a,a-9,a-18,a-27]
				];
			for (let [index, win] of winCombos.entries()) {
				if (win.every(elem => plays.indexOf(elem) > -1)) {
				gameWon = {index: index, player: player};
					for (let index of winCombos[gameWon.index]) {
						winSquare.push(index);
					}
				break;
				}
			}
		}
		return gameWon;
	}

	function gameOver(gameWon){
		var who =  "congratulations "+ (gameWon.player == huPlayer ? "Player 1" : "Player 2") +" has one. ";
		document.querySelector(".gameWon").style.display = "block";
		declareWinner(who);
		//document.querySelector(".gameWon p").innerText = "you win! would you like to play again?";
		for(var i=0; i<winSquare.length;i++){
			document.getElementById(winSquare[i]).style.backgroundColor =
			 gameWon.player == huPlayer ? "orange" : "yellow";
		}
		for (var i=0; i<cells.length;i++){
			cells[i].removeEventListener('click', turnClick, false);
		}
	}

	function declareWinner(who){
		document.querySelector(".gameWon p").innerText = who;
	}

	function emptySquares (){
		return CanPlay;
	}

	function bestSpot (){
		/*return minimax(origBoard, aiPlayer).index;
		console.log("bestSpot");*/
		var num = Math.round(Math.random()* CanPlay.length);
		console.log(num);
		if(num>CanPlay.length-1){
			console.log(CanPlay);
			console.log(num);
			return CanPlay[0];
		}
		return CanPlay[num];
	}

	function checkTie (){
		console.log(CanPlay);
		if (emptySquares().length == 0){
			for (var i = 0; i < cells.length; i++) {
				cells[i].style.backgroundColor = 'green';
				cells[i].removeEventListener('click', turnClick, false);
			}
			declareWinner("Tie Game!");
			return true;
		}
		return false;
	}


	function minimax(newBoard, player) {
	var availSpots = emptySquares();
	
	if (checkwin(newBoard, huPlayer)) {
		return {score: -10};
	} else if (checkwin(newBoard, aiPlayer)) {
		return {score: 10};
	} else if (availSpots.length === 0) {
		return {score: 0};
	}
	var moves = [];
	console.log(moves);

	for (var i = 0; i < availSpots.length; i++) {
		var move = {};
		move.index = newBoard[availSpots[i]];
		newBoard[availSpots[i]] = player;

		if (player == aiPlayer) {
			var result = minimax(newBoard, huPlayer);
			move.score = result.score;
		} else {
			var result = minimax(newBoard, aiPlayer);
			move.score = result.score;
		}

		newBoard[availSpots[i]] = move.index;

		moves.push(move);
	}

	var bestMove;
	if(player === aiPlayer) {
		var bestScore = -10000;
		for(var i = 0; i < moves.length; i++) {
			if (moves[i].score > bestScore) {
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	} else {
		var bestScore = 10000;
		for(var i = 0; i < moves.length; i++) {
			if (moves[i].score < bestScore) {
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	}

		return moves[bestMove];
	}

} //end of startGame();













