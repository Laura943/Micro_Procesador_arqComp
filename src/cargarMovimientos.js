const casa = document.getElementById("0");
const parque = document.getElementById("1");
const rest1 = document.getElementById("2");
const rest2 = document.getElementById("3");
const escuela = document.getElementById("4");
const plaza = document.getElementById("5");
const cine = document.getElementById("6");
const futbol = document.getElementById("7");

var entidades = new Array();
entidades.push(casa);
entidades.push(parque);
entidades.push(rest1);
entidades.push(rest2);
entidades.push(escuela);
entidades.push(plaza);
entidades.push(cine);
entidades.push(futbol);

const termoB = document.getElementById("termo_b");
const termoC = document.getElementById("termo_c");
const termoE = document.getElementById("termo_e");

var termos = new Array();
termos.push(termoB);
termos.push(termoC);
termos.push(termoE);


function removerColor(termo) {
	if( termo.classList.contains('bueno') )
		termo.classList.remove('bueno');
	if( termo.classList.contains('neutro') )
		termo.classList.remove('neutro');
	if( termo.classList.contains('malo') )
		termo.classList.remove('malo');
}



var datos = new Array();
var archivo = new XMLHttpRequest();
var ruta = './historial.txt';

archivo.open("GET", ruta, false);
archivo.send(null);
var txt = archivo.responseText;
for(var i = 0; i < txt.length; i++ ) {
	if(!isNaN( parseInt(txt[i]) )  )
		datos.push( parseInt(txt[i]));

}



var cont = 4;
function mover(data, entidades, termometros) {

	var nombreTermo = new Array;
	nombreTermo.push(' ');
	nombreTermo.push('bueno');
	nombreTermo.push('neutro');
	nombreTermo.push('malo');


	if(cont >= data.length) {
		clearInterval(repeticion);
	}

 	entidades[ data[cont-4] ].classList.toggle('selec');
	entidades[ data[cont] ].classList.toggle('selec');

	removerColor(termometros[0])
	removerColor(termometros[1])
	removerColor(termometros[2])

	termometros[0].classList.toggle( nombreTermo[data[cont+1]] );
	termometros[1].classList.toggle( nombreTermo[data[cont+2]] );
	termometros[2].classList.toggle( nombreTermo[data[cont+3]] );


	cont += 4;
}
var repeticion =  setInterval('mover(datos, entidades, termos)', 3000);
