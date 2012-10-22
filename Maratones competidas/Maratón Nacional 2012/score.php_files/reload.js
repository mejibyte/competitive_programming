/*/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//BOCA Online Contest Administrator
//    Copyright (C) 2003-2012 by BOCA Development Team (bocasystem@gmail.com)
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////
// Last modified 05/aug/2012 by cassio@ime.usp.br
*/
var msg = 0;
var rld  = 0;
var selecionando = 0;
var seg = 120;
function recarregar() {
	if (rld) {
		clearTimeout(rld);
        	rld  = 0;
        }
        if ((document.form1 && document.form1.message && document.form1.message.value) ||
            (document.form1 && document.form1.sourcefile && document.form1.sourcefile.value) ||
            (document.form1 && document.form1.answer && document.form1.answer.value) ||
            (document.form2 && document.form2.answer && document.form2.answer.value) ||
            (document.form2 && document.form2.message && document.form2.message.value) ||
            (document.form2 && document.form2.sourcefile && document.form2.sourcefile.value) ||
            selecionando == 1) {
            if (msg<5) {
				msg++;
			}
			else {
				alert("This page tried to reload, but it seems that you are filling\nthe form. To update, click on Reload button in your\nbrowser. This message will not be displayed again.");
            }
        } else
            document.location.reload();
    rld = setTimeout("recarregar()", seg * 1000);
}
function Comecar() {
	rld = setTimeout("recarregar()", seg * 1000);
}
function Parar() {
	if (rld) {
		clearTimeout(rld);
		rld  = 0;
	}
}
function Arquivo() {
	selecionando = 1;
}
